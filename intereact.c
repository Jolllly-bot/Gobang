#include "gobang.h"

void Player(void);
void Computer(void);
int Judge(int x,int y);
int JudgeDisplay(void);

extern int arrayForInnerBoardLayout[SIZE][SIZE];
int gameover=0;//��Ϸ������ʾ
int id=1;//�Ⱥ���
int x1=-1,y1=-1;
int x2=-1,y2=-1;//��һ������

void Move(int x,int y,int id){
    if(id==1){
        if(x1>=0 && y1>=0){
            arrayForInnerBoardLayout[x1][y1]=id;
        }
        arrayForInnerBoardLayout[x][y]=id+2;
        x1=x,y1=y;
    }else if(id==2){
        if(x2>=0 && y2>=0){
            arrayForInnerBoardLayout[x2][y2]=id;
        }
        arrayForInnerBoardLayout[x][y]=id+2;
        x2=x,y2=y;
    }
    innerLayoutToDisplayArray();
    gameover=Judge(x,y)*id;
}

void Player(){
    char c;
    int x=0,y=0;
    displayBoard();
    printf("player%d��������:",id);
    
    while(1){
        scanf("%c %d",&c,&x);
        scanf("%c %d",&c,&x);//һ���Ի��bug
        x=15-x;
        y=c-'a';

        if(arrayForInnerBoardLayout[x][y]!=0 || x<0 || x>=SIZE || y<0 || y>=SIZE){
            printf("�������������꣺");
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
    
    srand(time(NULL));//��������Ϊ
    x=rand()%SIZE;
    y=rand()%SIZE;

    Move(x,y,cid);

}


int Judge(int x, int y)//�ж�����
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
            return 1;
    }
    return 0;
}

int  JudgeDisplay(void)
{
    /*if(num == SIZE*SIZE)
    {
        displayBoard();
        printf("    ----ƽ�֣�---\n");
        return 1;//�Ծֽ���
    }*/
    if(gameover == 1)
    {
        displayBoard();
        printf("    ----�����ʤ��---\n");
        return 1;//�Ծֽ���
    }
    if(gameover == 2)
    {
        displayBoard();
        printf("    ----�����ʤ��---\n");
        return 1;//�Ծֽ���
    }
    return 0;
}

void menu(){
    int m;
    printf("1 -pvp\n");
    printf("2 -pve �������\n");
    printf("3 -pve ��Һ���\n");
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