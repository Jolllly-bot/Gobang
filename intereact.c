#include "gobang.h"

void Player(void);
void Computer(void);
int Judge(int x,int y);
int JudgeDisplay(void);

extern int arrayForInnerBoardLayout[SIZE][SIZE];
int gameover=0;//游戏结束标示
int id=1;//先后手判断
int x_1=-1,y_1=-1;//先手上一次落子
int x_2=-1,y_2=-1;//后手上一次落子

void Move(int x,int y,int id){
    if(x_1>=0)
        arrayForInnerBoardLayout[x_1][y_1]=1;
    if(x_2>=0)
        arrayForInnerBoardLayout[x_2][y_2]=2;
    if(id==1){
        x_1=x;
        y_1=y;
    }else{
        x_2=x;
        y_2=y;
    }
    arrayForInnerBoardLayout[x][y]=id+2;
    innerLayoutToDisplayArray();
    gameover=Judge(x,y)*id;
}

void Player(){
    char c;
    int x=0,y=0;
    displayBoard();
    printf("player%d输入坐标:",id);
    
    while(1){
        scanf("%c %d",&c,&x);
        scanf("%c %d",&c,&x);//一个迷惑的bug
        x=15-x;
        y=c-'a';

        if(arrayForInnerBoardLayout[x][y]!=0 || x<0 || x>=SIZE || y<0 || y>=SIZE){
            printf("请重新输入坐标：");
            continue;
            
        }else{
            Move(x,y,id);
            break;
        }
    }
    
}

void Computer(){
    int x,y,cid;
    cid=(id==1)?2:1;
    displayBoard();
    
    srand(time(NULL));//大猩猩行为
    x=rand()%SIZE;
    y=rand()%SIZE;

    Move(x,y,cid);

}


int Judge(int x, int y)//判断五连
{
    int i, j, k;
    const int step[4][2]={{1,0},{0,1},{1,1},{1,-1}};
    for(i=0;i<4;++i)
    {
        const int d[2]={-1,1};
        int count=1;
        for(j=0;j<2;++j){
            for(k=1;k<=4;++k){
                int row=x+k*d[j]*step[i][0];
                int col=y+k*d[j]*step[i][1];
                if( row>=0 && row<SIZE &&
                    col>=1 && col<SIZE &&
                    arrayForInnerBoardLayout[x][y]-2 == arrayForInnerBoardLayout[row][col])
                    count+=1;
                else
                    break;
            }
        }
        if(count>=5)
            return 1;//五连
    }
    return 0;
}

int  JudgeDisplay(void)
{
    /*if(num == SIZE*SIZE)
    {
        displayBoard();
        printf("    ----平局！---\n");
        return 1;//对局结束
    }*/
    if(gameover == 1)
    {
        displayBoard();
        printf("    ----黑棋获胜！---\n");
        return 1;//对局结束
    }
    if(gameover == 2)
    {
        displayBoard();
        printf("    ----白棋获胜！---\n");
        return 1;//对局结束
    }
    return 0;
}

void menu(){
    int m;
    printf("1 -pvp\n");
    printf("2 -pve 玩家先手\n");
    printf("3 -pve 玩家后手\n");
    scanf("%d", &m);
    switch (m)
    {
    case 1:
        while(1)
        {
            Player();
            if(JudgeDisplay()){
                break;
            }
            id=(id==1)?2:1;
        }
        break;
    case 2:
        while (1)
        {
            Player();
            if(JudgeDisplay()){
                break;
            }
            Computer();
            if(JudgeDisplay()){
                break;
            }
        }
        break;
    case 3:
        while (1)
        {
            id=2;
            Computer();
            if (JudgeDisplay())
            {
                break;
            }
            Player();
            if(JudgeDisplay()){
                break;
            }
            
        }
        break;
    default:
        break;
    }
}