#include "gobang.h"


int ai_x,ai_y;

int isWin(){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(innerBoard[i][j]!=0 && JudgeFive(i,j))
                return 1;
        }
    }
    return 0;
}

//2���������е�
int hasNeighbor(Point p){
    if(num==1 || num==2){//���ֵڶ���������ֻ�Һ��ӾŹ���
        for(int i=0;i<4;i++){
            for(int j=-1;j<=1;j++){
                if(j!=0){
                    Point np=nextPoint(p,i,j);
                    if(inBoard(np) && innerBoard[np.x][np.y]==1)
                        return 1;
                }
            }
        }
    }else{
        for(int i=0;i<4;i++){
            for(int j=-2;j<=2;j++){
                if(j!=0){
                    Point np=nextPoint(p,i,j);
                    if(inBoard(np) && innerBoard[np.x][np.y]!=0)
                        return 1;
                }
            }
        }
    }
    return 0;
}

//������Сֵ����
LL alphaBeta(int depth,LL alpha,LL beta,int player) {
    if (isWin())//�ֳ�ʤ��
        return wholeScore(player);
    if (depth == 0 || num==SIZE*SIZE) {
        return wholeScore(player);
    }

    Move moves[224];
    int length=inspireFind(moves,player);
    if(length>WIDTH)
        length=WIDTH-rand()%3;//������֦ �������

    for (int i = 0; i < length; i++) {
        set(moves[i].p, player);//ģ������
        LL temp = -alphaBeta(depth - 1, -beta, -alpha, opp(player));
        unSet(moves[i].p);//��ԭ����
        if (temp >= beta) {
            return beta;//��֦
        }
        if (temp > alpha) {
            alpha = temp;
            if (depth == DEPTH) {//��߲��������������
                ai_x = moves[i].p.x;
                ai_y = moves[i].p.y;
            }
        }
    }
    return alpha;
}

int inspireFind(Move *scoreBoard,int player){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {
                Point p = {i, j};

                if (hasNeighbor(p) && !forbiddenHand(p, player)) {
                    scoreBoard[length].score = singleScore(p,player);//������
                    if(!forbiddenHand(p,opp(player))){
                        scoreBoard[length].score += singleScore(p,opp(player));//���ص�
                    }
                    scoreBoard[length++].p = p;
                }
            }
        }
    }
    shellSort(scoreBoard,length);
    return length;
}

void shellSort(Move *s,int len)
{
    int i,j,gap;
    Move temp;
    for (gap=len/2;gap>0;gap/=2)
    {
        for(i=gap;i<len;i+=1)
        {
            for(j=i-gap;j>=0 && s[j].score<s[j+gap].score;j-=gap)
            {
                temp = s[j+gap];
                s[j+gap]=s[j];
                s[j]=temp;
            }
        }
    }
}

//��ɱ���
int killSearch(void){
    int depth=12;//��ɱ���
    Move kill[100];
    int length=findComKill(kill);
    if(length==0)
        return 0;
    if (length>10)
        length=10;
    for (int i=0;i<length; i++){
        set(kill[i].p,id);
        int killed=minKill(depth-1,kill[i].p);
        unSet(kill[i].p);
        if(killed){
            ai_x=kill[i].p.x;
            ai_y=kill[i].p.y;
            return 1;
        }
    }
    return 0;
}

//������ɱ�����Բ�
int maxKill(int depth,Point p){
    if(JudgeFive(p.x,p.y)){
        return 0;
    }
    if(depth==0)
        return 0;

    Move kill[100];
    int length=findComKill(kill);
    if(length==0)
        return 0;
    for (int i=0;i<length; i++){
        set(kill[i].p,id);
        int killed=minKill(depth-1,kill[i].p);
        unSet(kill[i].p);
        if(killed){
            return 1;
        }
    }
    return 0;
}

//��С��ɱ����Ҳ�
int minKill(int depth,Point p){
    if(JudgeFive(p.x,p.y)){
        return 1;//������Ӯ��
    }
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
    return 1;//û��ס
}

int findComKill(Move *move){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {
                Point p = {i, j};
                if (hasNeighbor(p) && !forbiddenHand(p,id)) {
                    set(p, id);
                    int score = singleScore(p,id);
                    unSet(p);
                    if(score>5000){
                        move[length].score=score;
                        move[length++].p = p;
                    }
                }
            }
        }
    }
    shellSort(move,length);
    return length;
}

int findHumKill(Move *move){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {
                Point p = {i, j};
                if (hasNeighbor(p) && !forbiddenHand(p,opp(id))) {
                    int score = singleScore(p,opp(id));//��ҷ�ɱ��
                    if(!forbiddenHand(p,id)){
                        score += singleScore(p,id);//���Է�ɱ��
                    }
                    if(score>5000){
                        move[length].score=score;
                        move[length++].p = p;
                    }
                }
            }
        }
    }
    shellSort(move,length);
    return length;
}
