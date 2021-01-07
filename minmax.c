#include "gobang.h"

struct POINTS{//�������λ��,[0]�������,[9]�������
    struct Point pos[10];
    int score[10];
};

int ai_x,ai_y;

int alphaBeta(int depth,int alpha,int beta){
    if(depth==0){
        struct POINTS P = inspireFind(id);//������ѵĿ�������λ��
        return P.score[0];//�������λ�ö�Ӧ����߷�
    }
    //else if()//�ֳ�ʤ��
    //return wholeScore(id);

    else if(depth%2==0){//max��,�ҷ�����
        struct POINTS P=inspireFind(id);

        for(int i=0;i<10;i++){
            innerBoard[P.pos[i].x][P.pos[i].y]=id;//ģ�⼺������
            int temp=alphaBeta(depth-1,alpha,beta);
            innerBoard[P.pos[i].x][P.pos[i].y]=0;//��ԭ����
            if(temp>alpha){
                alpha=temp;
                if(depth==DEPTH){//�������������
                    ai_x=P.pos[i].x;
                    ai_y=P.pos[i].y;
                }
            }
            if(beta<=alpha)
                break;//��֦
        }
        return alpha;

    }else{//min��,�з�����
        int opp=(id==1)?2:1;
        struct POINTS P=inspireFind(opp);

        for(int i=0;i<10;i++){
            innerBoard[P.pos[i].x][P.pos[i].y]=opp;//ģ��з�����
            int temp=alphaBeta(depth-1,alpha,beta);
            innerBoard[P.pos[i].x][P.pos[i].y]=0;//��ԭ����
            if(temp<beta)
                beta=temp;
            if(beta<=alpha)
                break;//��֦
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
                    for(int di=-3;di<=3;di++){//��������3�������ڿ����ӵ�
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
        score[bestPoints.pos[k].x][bestPoints.pos[k].y]=NINF;//������ҵ���һ����߷ֵ��λ�úͷ���
    }
    return bestPoints;
}