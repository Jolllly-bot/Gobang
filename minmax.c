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

//3���������е�
int hasNeighbor(Point p){
    for(int i=0;i<4;i++){
        for(int j=-2;j<=2;j++){
            if(j!=0){
                Point np=nextPoint(p,i,j);
                if(inBoard(np) && innerBoard[np.x][np.y]!=0)
                    return 1;
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

    LL before=wholeScore(player);
    Move moves[200];//���ع���
    int length=inspireFind(moves,player,before);
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

int inspireFind(Move *scoreBoard,int player,LL before){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {
                Point p = {i, j};

                if (hasNeighbor(p) && !forbiddenHand(p, player)) {
                    set(p, player);
                    scoreBoard[length].score = wholeScore(player)-before;
                    unSet(p);
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