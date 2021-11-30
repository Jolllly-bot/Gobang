#include "gobang.h"

//����
int num=0;
//��Ϸ������ʾ
int gameover=0;
//�Ⱥ��ֱ�ʾ 1:�� 2����
int id=1;
//�����һ������
Point lp;


//��һغ�
void Player(void)
{
    char c=0;
    int x=0;
    Point p={-1,-1};

    printf("player%d����������:",id);
    while(1){
        scanf("%c %d",&c,&x);
        cleanInput();//�����´ζ�ȡ������Ҫ������
        p.x=15-x;
        p.y=c-'a';
        //����
        if(c=='r'){
            Point aip={ai_x,ai_y};
            unSet(lp);//����������һ������
            unSet(aip);//���ص�������
            innerLayout();
            display();
            printf("��������������:");
            continue;
        //���ӵ�ǿջ�Խ��
        }else if(innerBoard[p.x][p.y]!=0 || !inBoard(p) ) {
            printf("��������������:");
            continue;
        //�Ϸ�����
        }else{
            set(p,id);
            lp=p;//��¼����
            gameover=JudgeFive(p.x,p.y)* id;//�ж���Ϸ�Ƿ����
            if(forbiddenHand(p,id))//����
                gameover = 3;

            innerLayout();
            changeCurrent(p,id);
            display();
            break;
        }
    }
}

//���Իغ�
void Computer(void)
{
    int kill=0;//��ɱ��ʾ
    if(num==0){
        ai_x=7;
        ai_y=7;
    }//����
    else {
#ifndef NKILL
        kill = killSearch();//��ɱ
        if (!kill) {//��ɱʧ�� ��ȡ����С����
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
    printf("����ѡ������:%c%d\n",ai_y+'A',15-ai_x);

}

//��ձ�׼���뻺����
void cleanInput(void){
    int c;
    while((c=getchar())!=EOF && c!='\n')
        ;
}

//���Ӻ���
void set(struct Point p,int player){
    innerBoard[p.x][p.y]=player;
    num++;
}

//ȡ������
void unSet(Point p){
    innerBoard[p.x][p.y]=0;
    num--;
}

//p��������û��Խ��
int inBoard(struct Point p){
    if(p.x>=0 && p.x<SIZE && p.y>=0 && p.y<SIZE)
        return 1;
    else
        return 0;
}


//��ȡ����id
int opp(int player){
    return (player==1)?2:1;
}

//�ж�����xy��Χ�Ƿ�������
int JudgeFive(int x, int y)
{
    int i, j, k;
    const int direction[4][2]={{1,0},{0,1},{1,1},{1,-1}};//��ʾ������б�ĸ�����
    for(i=0;i<4;++i)
    {
        const int d[2]={-1,1};//��ʾ������������
        int count=1;
        for(j=0;j<2;++j){
            for(k=1;k<=4;++k){
                int row=x+k*d[j]*direction[i][0];//�к�
                int col=y+k*d[j]*direction[i][1];//�к�
                if( row>=0 && row<SIZE && col>=0 && col<SIZE &&
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
    id=opp(id);//�ı��Ⱥ��ֱ�ʾ �������
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
    if(gameover == 3)
    {
        display();
        printf("    ----���֣�---\n");
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
    printf("1 -pvp ���˶�ս\n");
    printf("2 -pve ������֣�ִ�ڣ�\n");
    printf("3 -pve ��Һ��֣�ִ�ף�\n\n");
    printf(">>���������ʽ��Сд��ĸ ����\n");
    scanf("%d", &m);
    cleanInput();//������뻺����
    switch (m)
    {
        case 1://pvp ���˶�ս
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
                    //break;
                    //��break��Ϊ��һ����Ի���
                }
            }break;
        case 3://pve��Һ���
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
