#include "gobang.h"

//返回d方向上相邻di距离的点
struct Point nextPoint(struct Point p,int d,int di){
    const int direction[4][2]={{1,0},{0,1},{1,1},{1,-1}};
    struct Point np;
    np.x = p.x + di*direction[d][0];
    np.y = p.y + di*direction[d][1];
    return np;
}

int inBoard(struct Point p){
    if(p.x>=0 && p.y<SIZE && p.x>=0 && p.y<SIZE)
        return 1;
    else return 0;
}

void getBoundary(struct Point p,int d,int *s,int way,int player){
    for (int i = 0; i < 4; i++)
    {
        struct Point np = nextPoint(p, d, way*i);
        if (inBoard(np))
            s[i] = innerBoard[np.x][np.y];
        else
            s[i] = (player==1)?2:1;
    }
}

int getLength(struct Point p,int d,int *left,int *right,int player)
{
    int i;
    int count=1;
    for(i=1; ;i++){
        struct Point np = nextPoint(p,d,-i);
        if( inBoard(np) && player == innerBoard[np.x][np.y])
            count++;
        else{
            getBoundary(np,d,left,-1,player);
            break;
        }
    }
    for(i=1; ;i++){
        struct Point np = nextPoint(p,d,i);
        if( inBoard(np) && player == innerBoard[np.x][np.y])
            count++;
        else{
            getBoundary(np,d,right,1,player);
            break;
        }
    }
    return count;
}


int singleScore(struct Point p,int player){
    int score=0;
    int i;
    struct Type info[4]={0};
    int win5=0,alive4=0,dalive4=0,alive3=0;
    for(i=0;i<4;i++){
        int length;
        int left[4],right[4];
        length=getLength(p,i,left,right,player);
        info[i]= typeAnalysis(length, left, right, player);
    }
    for(i=0;i<4;i++){
        win5+=info[i].win5;
        alive4+=info[i].alive4;
        dalive4+=info[i].dalive4;
        alive3+=info[i].alive3;
        score+= (info[i].alive4*100000 + info[i].dalive4*10000 + info[i].dead4*5000
                + info[i].alive3*10000 + info[i].dalive3*1000 + info[i].dead3*500
                + info[i].alive2*1000 + info[i].dalive2*200 + info[i].dead2*50
                + info[i].alive1*100 + info[i].dalive1*10 + info[i].dead1*5);
    }
    if(win5>=1)
        score+=20000000;
    if(alive4 >= 1|| dalive4 >= 2 || (dalive4 >= 1 && alive3 >= 1) || alive3 >= 2)//必胜
        score+=1000000;
    return score;
}

int wholeScore(int player){
    int opp=(player==1)?2:1;
    int comScore=0,humScore=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++) {
            struct Point p={i,j};
            if(innerBoard[i][j]==player)
                comScore += singleScore(p,player);
            else if(innerBoard[i][j]==opp)
                humScore += singleScore(p,opp);
        }
    }
    return comScore-humScore;
}

/*struct Point findPoint(){
    struct Point p;
    int i,j;
    int max=-2147483648,temp;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0){
                innerBoard[i][j]=id;
                if( (temp=wholeScore()) >= max){
                    max = temp;
                    p.x=i;
                    p.y=j;
                }
                innerBoard[i][j]=0;
            }
        }
    }
    return p;
}*/

struct Type typeAnalysis(int length,int *left, int *right,int player)
{
    struct Type temp={0};
    if (length >= 5)
        temp.win5++;
    else if (length == 4)
    {
        if (left[0] == 0 && right[0] == 0)
            temp.alive4++;
        else if (left[0] == 0 || right[0] == 0)
            temp.dalive4++;
        else
            temp.dead4++;
    }
    else if (length == 3)
    {
        if ((left[0] == 0 && left[1] == player) || (right[0] == 0 && right[1] == player))
            temp.dalive4++;
        else if (left[0] == 0 && right[0] == 0 && (left[1] == 0 || right[1] == 0))
            temp.alive3++;
        else if ((left[0] == 0 && left[1] == 0) || (right[0] == 0 && right[1] == 0))
            temp.dalive3++;
        else
            temp.dead3++;
    }
    else if (length == 2)
    {
        if ((left[0] == 0 && left[1] == player && left[2] == player) ||
            (right[0] == 0 && right[1] == player && right[2] == player))
            temp.dalive4++;
        else if (left[0] == 0 && right[0] == 0 &&
                 ((left[1] == player && left[2] == 0) || (right[1] == player && right[2] == 0)))
            temp.dalive3++;
        else if ((left[0] == 0 && left[2] == 0 && left[1] == player) ||
                 (right[0] == 0 && right[2] == 0 && right[1] == player))
            temp.dead3++;
        else if ((left[0] == 0 && right[0] == 0) &&
                 (left[1] == player || right[1] == player))
            temp.dead3++;
        else if ((left[0] == 0 && left[1] == 0 && left[2] == player) ||
                 (right[0] == 0 && right[1] == 0 && right[2] == player))
            temp.dead3++;
        else if ((left[0] == 0 && right[0] == 0 && right[1] == 0 && right[2] == 0) ||
                 (left[0] == 0 && left[1] == 0 && right[0] == 0 && right[1] == 0) ||
                 (left[0] == 0 && left[1] == 0 && left[2] == 0 && right[0] == 0))
            temp.alive2++;
        else if ((left[0] == 0 && left[1] == 0 && left[2] == 0) ||
                 (right[0] == 0 && right[1] == 0 && right[2] == 0))
            temp.dead2++;
    }
    else if (length == 1) {
        if ((left[0] == 0 && left[1] == player && left[2] == player && left[3] == player) ||
            (right[0] == 0 && right[1] == player && right[2] == player && right[3] == player))
            temp.dalive4++;
        else if ((left[0] == 0 && right[0] == 0) && ((left[1] == player && left[2] == player && left[3] == 0) ||
                                                     (right[1] == player && right[2] == player && right[3] == 0)))
            temp.dalive3++;
        else if ((left[0] == 0 && right[0] == 0) &&
                 ((left[1] == player && left[2] == player) || (right[1] == player && right[2] == player)))
            temp.dead3++;
        else if ((left[0] == 0 && left[3] == 0 && left[1] == player && left[2] == player) ||
                 (right[0] == 0 && right[3] == 0 && right[1] == player && right[2] == player))
            temp.dead3++;
        else if ((left[0] == 0 && left[1] == 0 && left[2] == player && left[3] == player) ||
                 (right[0] == 0 && right[1] == 0 && right[2] == player && right[3] == player))
            temp.dead3++;
        else if ((left[0] == 0 && left[2] == 0 && left[1] == player && left[3] == player) ||
                 (right[0] == 0 && right[2] == 0 && right[1] == player && right[3] == player))
            temp.dead3++;
        else if ((left[0] == 0 && right[0] == 0 && right[2] == 0 && right[1] == player) && (left[1] == 0 || right[3] == 0))
            temp.dalive2++;
        else if ((right[0] == 0 && left[0] == 0 && left[2] == 0 && left[1] == player) &&
                 (right[1] == 0 || left[3] == 0))
            temp.dalive2++;
        else if ((left[0] == 0 && right[0] == 0 && right[1] == 0 && right[3] == 0 && right[2] == player) ||
                 (right[0] == 0 && left[0] == 0 && left[1] == 0 && left[3] == 0 && left[2] == player))
            temp.dalive2++;
        else if ((left[0] == 0 && left[2] == 0 && left[3] == 0 && left[1] == player) ||
                 (right[0] == 0 && right[2] == 0 && right[3] == 0 && right[1] == player))
            temp.dead2++;
        else if ((left[0] == 0 && right[0] == 0 && right[1] == 0 && left[1] == player) ||
                 (right[0] == 0 && left[0] == 0 && left[1] == 0 && right[1] == player))
            temp.dead2++;
        else if ((left[0] == 0 && left[1] == 0 && left[3] == 0 && left[2] == player) ||
                 (right[0] == 0 && right[1] == 0 && right[3] == 0 && right[2] == player))
            temp.dead2++;
        else if ((left[0] == 0 && left[1] == 0 && right[0] == 0 && left[2] == player) ||
                 (right[0] == 0 && right[1] == 0 && left[0] == 0 && right[2] == player))
            temp.dead2++;
        else if ((left[0] == 0 && left[1] == 0 && left[2] == 0 && left[3] == player) ||
                 (right[0] == 0 && right[1] == 0 && right[2] == 0 && right[3] == player))
            temp.dead2++;
        else if (left[0] == 0 && right[0] == 0)
            temp.alive1++;
        else if (left[0] == 0 || right[0] == 0)
            temp.dalive1++;
        else
            temp.dead1++;
    }
    return temp;
}