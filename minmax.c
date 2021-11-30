#include "gobang.h"

//电脑最后决定的落子
int ai_x,ai_y;

//判断点是否有邻居 增加效率
int hasNeighbor(Point p){
    if(num==1 || num==2){//开局第二第三个子只找黑子九宫格
        for(int i=0;i<4;i++){//4个方向
            for(int j=-1;j<=1;j++){//左右距离1
                if(j!=0){
                    Point np=nextPoint(p,i,j);
                    if(inBoard(np) && innerBoard[np.x][np.y]==1)
                        return 1;
                }
            }
        }
    }else{//之后找棋盘上有落子点2个距离内
        for(int i=0;i<4;i++){
            for(int j=-2;j<=2;j++){//左右距离2
                if(j!=0){
                    Point np=nextPoint(p,i,j);
                    if(inBoard(np) && innerBoard[np.x][np.y]!=0)
                        return 1;
                }
            }
        }
    }
    return 0;//没有邻居
}

//极大极小搜索顶层入口
LL minmax(int depth,LL alpha,LL beta,int player) {
    Move moves[224];
    int length=inspireFind(moves,player);//搜索可落子点
    if(length>WIDTH)
        length=WIDTH-rand()%3;//初步剪枝 加随机性

    for (int i = 0; i < length; i++) {
        set(moves[i].p, player);//模拟落子
        LL temp = -alphaBeta(depth - 1, -beta, -alpha,opp(player),moves[i].p);//递归
        unSet(moves[i].p);//还原落子
        if (temp >= beta) {
            return beta;//剪枝
        }
        if (temp > alpha) {
            alpha = temp;
            ai_x = moves[i].p.x;//记录最佳落子
            ai_y = moves[i].p.y;
        }
    }
    return alpha;
}

//负极大极小值搜索 是一种综合了双方的简练写法
LL alphaBeta(int depth,LL alpha,LL beta,int player,Point p) {
    if (JudgeFive(p.x,p.y))//落子后成五
        return wholeScore(player);//返回当前局面分
    if (depth == 0 || num==SIZE*SIZE) {//深度为0或满盘
        return wholeScore(player);
    }

    Move moves[224];
    int length=inspireFind(moves,player);
    if(length>WIDTH)
        length=WIDTH-rand()%3;//初步剪枝 加随机性

    for (int i = 0; i < length; i++) {
        set(moves[i].p, player);//模拟落子
        LL temp = -alphaBeta(depth - 1, -beta, -alpha,opp(player),moves[i].p);//注意要取负值并交换alpha和beta
        unSet(moves[i].p);//还原落子
        if (temp >= beta) {
            return beta;//剪枝
        }
        if (temp > alpha) {
            alpha = temp;
        }
    }
    return alpha;
}

//启发式搜索
int inspireFind(Move *scoreBoard,int player){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {//只看棋盘上的空位
                Point p = {i, j};

                if (hasNeighbor(p) && !forbiddenHand(p, player)) {
                    scoreBoard[length].score = singleScore(p,player);//我方适合进攻的点
                    if(!forbiddenHand(p,opp(player))){
                        scoreBoard[length].score += singleScore(p,opp(player));//对方需要防守的点
                    }
                    scoreBoard[length++].p = p;
                }
            }
        }
    }
    shellSort(scoreBoard,length);//依据分数进行排序 可以增加剪枝效率
    return length;
}

//希尔排序
void shellSort(Move *s,int len){
    int i,j,gap;
    Move temp;
    for (gap=len/2;gap>0;gap/=2){
        for(i=gap;i<len;i+=1){
            for(j=i-gap;j>=0 && s[j].score<s[j+gap].score;j-=gap){
                temp = s[j+gap];
                s[j+gap]=s[j];
                s[j]=temp;
            }
        }
    }
}

//算杀采取双方分开的写法 因此每个函数都有一个对称函数
//统一用1表示电脑杀棋成功 0表示失败
//算杀最顶层
int killSearch(void){
    int depth=KILLDEPTH;
    Move kill[100];
    int length=findComKill(kill);//搜索杀点
    if(length==0)//没有找到杀点
        return 0;
    if (length>9)//在杀点较多时减少深度
        depth=8;
    for (int i=0; i<length; i++){
        set(kill[i].p,id);//模拟落子
        int killed=minKill(depth-1,kill[i].p);//进入玩家极小层
        unSet(kill[i].p);//还原落子
        if(killed){//算杀成功
            ai_x=kill[i].p.x;//记录最佳落子点
            ai_y=kill[i].p.y;
            return 1;
        }
    }
    return 0;
}

//极大算杀，电脑层
int maxKill(int depth,Point p){
    if(JudgeFive(p.x,p.y))//玩家落子成五
        return 0;
    if(depth==0)//到最深仍未杀棋成功
        return 0;

    Move kill[100];
    int length=findComKill(kill);
    if(length==0)
        return 0;
    for (int i=0;i<length; i++){
        set(kill[i].p,id);
        int killed=minKill(depth-1,kill[i].p);
        unSet(kill[i].p);
        if(killed){//在下一层杀棋成功
            return 1;
        }
    }
    return 0;
}

//极小算杀，玩家层
int minKill(int depth,Point p){
    if(JudgeFive(p.x,p.y))//电脑落子成五
        return 1;
    if(depth==0)
        return 0;

    Move kill[100];
    int length=findHumKill(kill);
    if(length==0)
        return 0;
    for (int i=0;i<length; i++){
        set(kill[i].p,opp(id));
        int killed=maxKill(depth-1,kill[i].p);
        unSet(kill[i].p);
        if(!killed){
            return 0;
        }
    }
    return 1;//都无法防住
}

//寻找电脑可落子点
int findComKill(Move *move){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {//只看空位
                Point p = {i, j};
                if (hasNeighbor(p) && !forbiddenHand(p,id)) {
                    int score = singleScore(p,id);
                    if(score>5000){//只找杀点
                        move[length].score=score;
                        move[length++].p = p;
                    }
                }
            }
        }
    }
    shellSort(move,length);//排序
    return length;
}

//寻找人类可落子点
int findHumKill(Move *move){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {//只看空位
                Point p = {i, j};
                if (hasNeighbor(p) && !forbiddenHand(p,opp(id))) {
                    int score = singleScore(p,opp(id));//玩家方杀点 进攻
                    if(!forbiddenHand(p,id)){
                        score += singleScore(p,id);//电脑方杀点 防守
                    }
                    if(score>5000){
                        move[length].score=score;
                        move[length++].p = p;
                    }
                }
            }
        }
    }
    shellSort(move,length);//排序
    return length;
}
