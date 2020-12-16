#include "gobang.h"

void Move(int x,int y);
void Player(void);
void Computer(void);
int JudgeFive(int x,int y);
int JudgeDisplay(void);

//游戏结束标示
int gameover=0;
//先后手标示
int id=1;
//先手上一次落子
int x_1=-1,y_1=-1;
//后手上一次落子
int x_2=-1,y_2=-1;

void menu()
{
    int m;
    printf("    ---GOBANG by Jolllly---\n");
    printf("Select mode:\n");
    printf("1 -pvp\n");
    printf("2 -pve 玩家先手\n");
    printf("3 -pve 玩家后手\n");
    scanf("%d", &m);
    switch (m)
    {
    case 1://pvp
        display();
        while(1)
        {
            Player();
            if(JudgeDisplay()){
                break;
            }
            
        }break;
    case 2://pve玩家先手
        display();
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
        }break;
    case 3://pve玩家后手
        while (1)
        {
            Computer();
            if (JudgeDisplay()){
                break;
            }
            Player();
            if(JudgeDisplay()){
                break;
            }
        }break;
    default:
        break;
    }
}

//落子函数
void Move(int x,int y)
{
    if(x_1>=0)
        InnerBoard[x_1][y_1]=1;
    if(x_2>=0)
        InnerBoard[x_2][y_2]=2;
    if(id==1){
        x_1=x,y_1=y;
    }else{
        x_2=x,y_2=y;
    }
    InnerBoard[x][y]=id+2;
    gameover=JudgeFive(x,y)* id;
    innerLayout();
    display();
    
    id=(id==1)?2:1;//切换先后手关系
}

//玩家回合
void Player(void)
{
    char c;
    int x=0,y=0;

    printf("player%d输入坐标:",id);
    while(1){
        scanf("%c %d",&c,&x);
        scanf("%c %d",&c,&x);//一个迷惑的bug
        x=15-x;
        y=c-'a';

        if(InnerBoard[x][y]!=0 || x<0 || x>=SIZE || y<0 || y>=SIZE){
            printf("请重新输入坐标:");
            continue;
            
        //if(禁手) todo

        }else{
            Move(x,y);
            break;
        }
    }
    
}

//电脑回合
void Computer(void)
{
    int x,y;
    
    srand(time(NULL));//大猩猩行为
    x=rand()%SIZE;
    y=rand()%SIZE;
    
    Move(x,y);
    printf("电脑选择下在:%c%d\n",y+'A',15-x);
}

//判断五连
int JudgeFive(int x, int y)
{
    int i, j, k;
    const int step[4][2]={{1,0},{0,1},{1,1},{1,-1}};//表示横竖加斜四个方向
    for(i=0;i<4;++i)
    {
        const int d[2]={-1,1};
        int count=1;
        for(j=0;j<2;++j){
            for(k=1;k<=4;++k){
                int row=x+k*d[j]*step[i][0];
                int col=y+k*d[j]*step[i][1];
                if( row>=0 && row<SIZE &&
                    col>=0 && col<SIZE &&
                    InnerBoard[x][y]-2 == InnerBoard[row][col])
                    count+=1;
                else
                    break;
            }
        }
        if(count>=5)
            return 1;//存在五连子
    }
    return 0;
}

//输出游戏结果
int JudgeDisplay(void)
{
    /*if(num == SIZE*SIZE)
    {
        display();
        printf("    ----平局！---\n");
        return 1;//对局结束
    }*/
    if(gameover == 1)
    {
        display();
        printf("    ----黑棋获胜！---\n");
        return 1;//对局结束
    }
    if(gameover == 2)
    {
        display();
        printf("    ----白棋获胜！---\n");
        return 1;//对局结束
    }
    return 0;
}
