#include "gobang.h"

//步数
int num=0;
//游戏结束标示
int gameover=0;
//先后手标示 1:先 2：后
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
            while(1){
                Player();
                if(JudgeDisplay()){
                    break;
                }
            }break;
        case 2://pve玩家先手
            display();
            while (1){
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
            while (1){
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

//玩家回合
void Player(void)
{
    char c;
    int x;
    Point p;
    printf("player%d输入坐标:",id);
    scanf("%c %d",&c,&x);
    scanf("%c %d",&c,&x);//一个迷惑的bug
    p.x=15-x;
    p.y=c-'a';

    while(innerBoard[p.x][p.y]!=0 || !inBoard(p) ){
            printf("请重新输入坐标:");
            scanf("%c %d",&c,&x);
            scanf("%c %d",&c,&x);//一个迷惑的bug
            p.x=15-x;
            p.y=c-'a';
    }

    set(p,id);
    gameover=JudgeFive(p.x,p.y)* id;

    if(id==1){//禁手判断
        Info info=getInfo(p,id);
        if(forbiddenHand(info))
            gameover = 3;
    }
    innerLayout();
    display();


}

//电脑回合
void Computer(void)
{
    if(num==0){
        srand(time(NULL));
        int a=rand()%2;
        int b=rand()%2;
        ai_x=7-a;
        ai_y=7-b;
    }//随机开局
    else
        alphaBeta(DEPTH,NINF,PINF,id);

    Point p={ai_x,ai_y};
    set(p,id);
    gameover=JudgeFive(ai_x,ai_y)* id;
    innerLayout();
    display();
    printf("电脑选择下在:%c%d\n",ai_y+'A',15-ai_x);

}

//落子函数
void set(struct Point p,int player)
{
    innerBoard[p.x][p.y]=player;
    num++;
}

//取消落子
void unSet(Point p)
{
    innerBoard[p.x][p.y]=0;
    num--;
}

//在棋盘内没有越界
int inBoard(struct Point p){
    if(p.x>=0 && p.x<SIZE && p.y>=0 && p.y<SIZE)
        return 1;
    else return 0;
}


//对手
int opp(int player){
    if(player==1)
        return 2;
    else
        return 1;
}

//判断五连
int JudgeFive(int x, int y)
{
    int i, j, k;
    const int direction[4][2]={{1,0},{0,1},{1,1},{1,-1}};//表示横竖加斜四个方向
    for(i=0;i<4;++i)
    {
        const int d[2]={-1,1};
        int count=1;
        for(j=0;j<2;++j){
            for(k=1;k<=4;++k){
                int row=x+k*d[j]*direction[i][0];
                int col=y+k*d[j]*direction[i][1];
                if( row>=0 && row<SIZE &&
                    col>=0 && col<SIZE &&
                    innerBoard[x][y] == innerBoard[row][col])
                    count++;
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
    id=opp(id);//交换玩家
    if(num == SIZE*SIZE)
    {
        display();
        printf("    ----平局！---\n");
        return 1;//对局结束
    }
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
    if(gameover == 3)
    {
        display();
        printf("    ----禁手！---\n");
        getchar();
        return 0;//不结束避免判断错
    }
    return 0;
}
