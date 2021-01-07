#include "gobang.h"

//����
int num=0;
//��Ϸ������ʾ
int gameover=0;
//�Ⱥ��ֱ�ʾ 1:�� 2����
int id=1;
//������һ������
int x_1=-1,y_1=-1;
//������һ������
int x_2=-1,y_2=-1;

void menu()
{
    int m;
    printf("    ---GOBANG by Jolllly---\n");
    printf("Select mode:\n");
    printf("1 -pvp\n");
    printf("2 -pve �������\n");
    printf("3 -pve ��Һ���\n");
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
        case 2://pve�������
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
        case 3://pve��Һ���
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

//���Ӻ���
void Set(int x,int y,int player)
{
    innerBoard[x][y]=player;
    num++;
}



//��һغ�
void Player(void)
{
    char c;
    int x=0,y=0;

    printf("player%d��������:",id);
    while(1){
        scanf("%c %d",&c,&x);
        scanf("%c %d",&c,&x);//һ���Ի��bug
        x=15-x;
        y=c-'a';
        struct Point p={x,y};
        if(innerBoard[x][y]!=0 || !inBoard(p) ){
            printf("��������������:");
            continue;

            //if(����) todo

        }else{
            Set(x,y,id);
            gameover=JudgeFive(x,y)* id;
            innerLayout();
            display();
            break;
        }
    }

}

//���Իغ�
void Computer(void)
{
    extern int ai_x,ai_y;
    if(num==0){
        srand(time(NULL));
        int a=rand()%2;
        int b=rand()%2;
        ai_x=7-a;
        ai_y=7-a;
    }
    else
        alphaBeta(DEPTH,NINF,PINF);

    Set(ai_x,ai_y,id);
    gameover=JudgeFive(ai_x,ai_y)* id;
    innerLayout();
    display();
    printf("����ѡ������:%c%d\n",ai_y+'A',15-ai_x);

}

//�ж�����
int JudgeFive(int x, int y)
{
    int i, j, k;
    const int direction[4][2]={{1,0},{0,1},{1,1},{1,-1}};//��ʾ������б�ĸ�����
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
            return 1;//����������
    }
    return 0;
}

//�����Ϸ���
int JudgeDisplay(void)
{
    id=(id==1)?2:1;
    if(num == SIZE*SIZE)
    {
        display();
        printf("    ----ƽ�֣�---\n");
        return 1;//�Ծֽ���
    }
    if(gameover == 1)
    {
        display();
        printf("    ----�����ʤ��---\n");
        return 1;//�Ծֽ���
    }
    if(gameover == 2)
    {
        display();
        printf("    ----�����ʤ��---\n");
        return 1;//�Ծֽ���
    }
    return 0;
}
