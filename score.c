#include "gobang.h"


//返回d方向上相邻di距离的点
struct Point nextPoint(struct Point p,int d,int di){
    const int direction[4][2]={{1,0},{0,1},{1,1},{1,-1}};
    struct Point np;
    np.x = p.x + di*direction[d][0];
    np.y = p.y + di*direction[d][1];
    return np;
}


void getBoundary(struct Point p,int d,int *s,int way,int player){
    for (int i = 0; i < 4; i++)
    {
        struct Point np = nextPoint(p, d, way*i);
        if (inBoard(np))
            s[i] = innerBoard[np.x][np.y];
        else //边界
            s[i] = (player==1)?2:1;
    }
}

int getLength(struct Point p,int d,int *left,int *right,int player)
{
    int i;
    int count=1;
    for(i=1; ;i++){//左边判断
        struct Point np = nextPoint(p,d,-i);
        if( inBoard(np) && player == innerBoard[np.x][np.y])
            count++;
        else{
            getBoundary(np,d,left,-1,player);
            break;
        }
    }
    for(i=1; ;i++){//右边判断
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

int forbiddenHand(struct Type info){
    if(info.more>0){
        return 1;
    }
    if(info.win5==0 && (info.alive3>=2 || info.alive4+info.dalive4>=2)) {
        return 1;
    }
    return 0;
}

int singleScore(struct Point p,int player){
    int score=0;
    struct Type info;
    info = getInfo(p,player);

    if(player==1 && forbiddenHand(info)){//禁手
        score=NINF/2;//todo 禁手极小分避免选择，+10避免重复
    }else{
        score+= ( info.alive4*100000 + info.dalive4*10000 + info.dead4*3000
                 + info.alive3*10000 + info.dalive3*1000 + info.dead3*300
                 + info.alive2*1000 + info.dalive2*200 + info.dead2*30
                 + info.alive1*100 + info.dalive1*10 + info.dead1*3);

        if(info.win5>=1)
            score+=20000000;
        if(info.alive4 >= 2 || info.dalive4>=2 || (info.dalive4 >= 1 && info.alive3 >= 1) || info.alive3 >= 2)//必胜
            score+=1000000;
    }
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

struct Type getInfo(struct Point p,int player){

    struct Type temp = {0};
    for(int i=0;i<4;i++){
        struct Type info[4];
        int length;
        int left[4],right[4];
        length=getLength(p,i,left,right,player);
        info[i] = typeAnalysis(length, left, right, player);
        temp.more += info[i].more;
        temp.win5 += info[i].win5;
        temp.alive4 += info[i].alive4;
        temp.dalive4 += info[i].dalive4;
        temp.dead4 += info[i].dead4;
        temp.alive3 += info[i].alive3;
        temp.dalive3 += info[i].dalive3;
        temp.dead3 += info[i].dead3;
        temp.alive2 += info[i].alive2;
        temp.dalive2 += info[i].dalive2;
        temp.dead2 += info[i].dead2;
        temp.alive1 += info[i].alive1;
        temp.dalive1 += info[i].dalive1;
        temp.dead1 += info[i].dead1;
    }
    return temp;
}

struct Type typeAnalysis(int length,int *left, int *right,int player)
{
    struct Type temp={0};
    if(length >5)
        temp.more++;
    else if (length == 5)
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
        if ((left[0] == 0 && left[1] == player) && (right[0] == 0 && right[1] == player))
            temp.dalive4+=2;
        else if((left[0] == 0 && left[1] == player) || (right[0] == 0 && right[1] == player))
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
        if ((left[0] == 0 && left[1] == player && left[2] == player) &&
            (right[0] == 0 && right[1] == player && right[2] == player))
            temp.dalive4+=2;
        else if ((left[0] == 0 && left[1] == player && left[2] == player) ||
            (right[0] == 0 && right[1] == player && right[2] == player))
            temp.dalive4++;
        else if(left[0]==0 && right[0]==0 && ((right[1]==player) || left[1]==player))
            temp.alive3++;
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
        if ((left[0] == 0 && left[1] == player && left[2] == player && left[3] == player) &&
            (right[0] == 0 && right[1] == player && right[2] == player && right[3] == player))
            temp.dalive4+=2;
        else if ((left[0] == 0 && left[1] == player && left[2] == player && left[3] == player) ||
                 (right[0] == 0 && right[1] == player && right[2] == player && right[3] == player))
            temp.dalive4++;
        else if ((left[0] == 0 && right[0] == 0) && ((left[1] == player && left[2] == player && left[3] == 0) ||
                                                     (right[1] == player && right[2] == player && right[3] == 0)))
            temp.alive3++;
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