#include "gobang.h"

struct POINTS{//�������λ��,[0]�������,[9]�������
    Point pos[LIST];
    LL score[LIST];
};

int ai_x,ai_y;

int isWin(){
    int i,j,k;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(innerBoard[i][j]!=0 && ((k=JudgeFive(i,j))!=0))
                break;
        }
    }
    return k;
}


LL alphaBeta(int depth,LL alpha,LL beta,int player) {
    if (depth == 0 || num==SIZE*SIZE)  {//������Сֵ�㷨
        return wholeScore(id);
    }
    if (isWin())//�ֳ�ʤ��
        return PINF;

    struct POINTS P = inspireFind(player);

    for (int i = 0; i < LIST; i++) {
        set(P.pos[i], player);//ģ������
        LL temp = -alphaBeta(depth - 1, -beta, -alpha, opp(player));
        unSet(P.pos[i]);//��ԭ����
        if (temp >= beta) {
            return beta;//��֦
        }
        if (temp > alpha) {
            alpha = temp;
            if (depth == DEPTH) {//��߲��������������
                ai_x = P.pos[i].x;
                ai_y = P.pos[i].y;
            }
        }
    }
    return alpha;
}



struct POINTS inspireFind(int player){
    static LL score[SIZE][SIZE];
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
                    for(int di=-3;di<=3;di++){//��������3�������ڿ����ӵ�
                        struct Point np=nextPoint(p,k,di);
                        if(inBoard(np) && score[np.x][np.y]==NINF && innerBoard[np.x][np.y]==0){
                                innerBoard[np.x][np.y] = player;
                                score[np.x][np.y] = wholeScore(player);
                                innerBoard[np.x][np.y] = 0;
                            }
                        }

                    }
                }
            }
        }


    for(int k=0;k<LIST;k++){
        LL temp=NINF;
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
        score[bestPoints.pos[k].x][bestPoints.pos[k].y]=NINF;//������ҵ���һ����߷ֵ��λ�úͷ���
    }
    return bestPoints;
}