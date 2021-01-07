#include "gobang.h"

struct POINTS{//最佳落子位置,[0]分数最高,[9]分数最低
    struct Point pos[10];
    int score[10];
};

int ai_x,ai_y;

int alphaBeta(int depth,int alpha,int beta){
    if(depth==0){
        struct POINTS P = inspireFind(id);//生成最佳的可能落子位置
        return P.score[0];//返回最佳位置对应的最高分
    }
    //else if()//分出胜负
    //return wholeScore(id);

    else if(depth%2==0){//max层,我方决策
        struct POINTS P=inspireFind(id);

        for(int i=0;i<10;i++){
            innerBoard[P.pos[i].x][P.pos[i].y]=id;//模拟己方落子
            int temp=alphaBeta(depth-1,alpha,beta);
            innerBoard[P.pos[i].x][P.pos[i].y]=0;//还原落子
            if(temp>alpha){
                alpha=temp;
                if(depth==DEPTH){//用来找最佳落子
                    ai_x=P.pos[i].x;
                    ai_y=P.pos[i].y;
                }
            }
            if(beta<=alpha)
                break;//剪枝
        }
        return alpha;

    }else{//min层,敌方决策
        int opp=(id==1)?2:1;
        struct POINTS P=inspireFind(opp);

        for(int i=0;i<10;i++){
            innerBoard[P.pos[i].x][P.pos[i].y]=opp;//模拟敌方落子
            int temp=alphaBeta(depth-1,alpha,beta);
            innerBoard[P.pos[i].x][P.pos[i].y]=0;//还原落子
            if(temp<beta)
                beta=temp;
            if(beta<=alpha)
                break;//剪枝
        }
        return beta;
    }
}

struct POINTS inspireFind(int player){
    static int score[SIZE][SIZE];
    struct POINTS bestPoints;
    int i,j;
    for(i=0;i<SIZE;i++) {
        for (j = 0; j < SIZE; j++) {
            score[i][j] = NINF;
        }
    }
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){

            if(innerBoard[i][j]!=0){
                struct Point p={i,j};
                for(int k=0;k<4;k++){
                    for(int di=-3;di<=3;di++){//搜索相邻3个距离内可落子点
                        struct Point np=nextPoint(p,k,di);
                        if(inBoard(np) && score[np.x][np.y]==NINF && innerBoard[np.x][np.y]==0){
                            innerBoard[np.x][np.y]=player;
                            score[np.x][np.y]=wholeScore(player);
                            innerBoard[np.x][np.y]=0;
                        }
                    }
                }
            }
        }
    }

    for(int k=0;k<10;k++){
        int temp=NINF;
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(score[i][j]>temp){
                    temp=score[i][j];
                    struct Point p={i,j};
                    bestPoints.pos[k]=p;
                }
            }
        }
        bestPoints.score[k]=temp;
        score[bestPoints.pos[k].x][bestPoints.pos[k].y]=NINF;//清除以找到下一个最高分点的位置和分数
    }
    return bestPoints;
}