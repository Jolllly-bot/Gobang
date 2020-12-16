#include "gobang.h"

void Move(int x,int y);
void Player(void);
void Computer(void);
int JudgeFive(int x,int y);
int JudgeDisplay(void);

//��Ϸ������ʾ
int gameover=0;
//�Ⱥ��ֱ�ʾ
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
        while(1)
        {
            Player();
            if(JudgeDisplay()){
                break;
            }
            
        }break;
    case 2://pve�������
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
    case 3://pve��Һ���
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

//���Ӻ���
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
    
    id=(id==1)?2:1;//�л��Ⱥ��ֹ�ϵ
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

        if(InnerBoard[x][y]!=0 || x<0 || x>=SIZE || y<0 || y>=SIZE){
            printf("��������������:");
            continue;
            
        //if(����) todo

        }else{
            Move(x,y);
            break;
        }
    }
    
}

//���Իغ�
void Computer(void)
{
    int x,y;
    
    srand(time(NULL));//��������Ϊ
    x=rand()%SIZE;
    y=rand()%SIZE;
    
    Move(x,y);
    printf("����ѡ������:%c%d\n",y+'A',15-x);
}

//�ж�����
int JudgeFive(int x, int y)
{
    int i, j, k;
    const int step[4][2]={{1,0},{0,1},{1,1},{1,-1}};//��ʾ������б�ĸ�����
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
            return 1;//����������
    }
    return 0;
}

//�����Ϸ���
int JudgeDisplay(void)
{
    /*if(num == SIZE*SIZE)
    {
        display();
        printf("    ----ƽ�֣�---\n");
        return 1;//�Ծֽ���
    }*/
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
