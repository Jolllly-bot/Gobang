#include "gobang.h"

//步数
int num=0;
//游戏结束标示
int gameover=0;
//先后手标示 1:先 2：后
int id=1;
//玩家上一次落子
Point lp;


//玩家回合
void Player(void)
{
    char c=0;
    int x=0;
    Point p={-1,-1};

    printf("player%d请输入坐标:",id);
    while(1){
        scanf("%c %d",&c,&x);
        cleanInput();//避免下次读取到不需要的内容
        p.x=15-x;
        p.y=c-'a';
        //悔棋
        if(c=='r'){
            Point aip={ai_x,ai_y};
            unSet(lp);//撤回人类上一步落子
            unSet(aip);//撤回电脑落子
            innerLayout();
            display();
            printf("请重新输入坐标:");
            continue;
        //落子点非空或越界
        }else if(innerBoard[p.x][p.y]!=0 || !inBoard(p) ) {
            printf("请重新输入坐标:");
            continue;
        //合法落子
        }else{
            set(p,id);
            lp=p;//记录落子
            gameover=JudgeFive(p.x,p.y)* id;//判断游戏是否结束
            if(forbiddenHand(p,id))//禁手
                gameover = 3;

            innerLayout();
            changeCurrent(p,id);
            display();
            break;
        }
    }
}

//电脑回合
void Computer(void)
{
    int kill=0;//算杀标示
    if(num==0){
        ai_x=7;
        ai_y=7;
    }//开局
    else {
#ifndef NKILL
        kill = killSearch();//算杀
        if (!kill) {//算杀失败 采取极大极小搜索
            printf(":(\n");
            minmax(DEPTH, NINF, PINF, id);
        }
    }
#endif
#ifdef NKILL
        minmax(DEPTH, NINF, PINF, id);
    }
#endif

    Point p={ai_x,ai_y};
    set(p,id);
    gameover=JudgeFive(ai_x,ai_y)* id;
    innerLayout();
    changeCurrent(p,id);
    display();
    if(kill)
        printf(";-)\n");
    printf("电脑选择下在:%c%d\n",ai_y+'A',15-ai_x);

}

//清空标准输入缓冲区
void cleanInput(void){
    int c;
    while((c=getchar())!=EOF && c!='\n')
        ;
}

//落子函数
void set(struct Point p,int player){
    innerBoard[p.x][p.y]=player;
    num++;
}

//取消落子
void unSet(Point p){
    innerBoard[p.x][p.y]=0;
    num--;
}

//p在棋盘内没有越界
int inBoard(struct Point p){
    if(p.x>=0 && p.x<SIZE && p.y>=0 && p.y<SIZE)
        return 1;
    else
        return 0;
}


//获取对手id
int opp(int player){
    return (player==1)?2:1;
}

//判断坐标xy周围是否有五连
int JudgeFive(int x, int y)
{
    int i, j, k;
    const int direction[4][2]={{1,0},{0,1},{1,1},{1,-1}};//表示横竖加斜四个方向
    for(i=0;i<4;++i)
    {
        const int d[2]={-1,1};//表示左右两个方向
        int count=1;
        for(j=0;j<2;++j){
            for(k=1;k<=4;++k){
                int row=x+k*d[j]*direction[i][0];//行号
                int col=y+k*d[j]*direction[i][1];//列号
                if( row>=0 && row<SIZE && col>=0 && col<SIZE &&
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
    id=opp(id);//改变先后手标示 交换玩家
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
        return 0;
    }
    return 0;
}

void menu()
{
    int m;
    printf("    ---GOBANG by Jolllly---\n");
    printf("Select mode:\n");
    printf("1 -pvp 人人对战\n");
    printf("2 -pve 玩家先手（执黑）\n");
    printf("3 -pve 玩家后手（执白）\n\n");
    printf(">>坐标输入格式：小写字母 数字\n");
    scanf("%d", &m);
    cleanInput();//清空输入缓冲区
    switch (m)
    {
        case 1://pvp 人人对战
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
                    //break;
                    //不break因为玩家还可以悔棋
                }
            }break;
        case 3://pve玩家后手
            while (1){
                Computer();
                if (JudgeDisplay()){
                    //break;
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
