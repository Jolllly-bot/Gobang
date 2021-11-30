#include "gobang.h"

//������ģ�� 
char EmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
		"���өөөөөөөөөөөөө�",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
//������洢������ʾ������ 
char displayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; //�������������

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";//�������������

//���������ڼ�¼��ǰ�����̵ĸ�� 
int innerBoard[SIZE][SIZE];

int main()
{
    
    initRecordBoard();    //��ʼ��һ��������
    innerLayout();
    display();

    menu();
    
    return 0;
}

//��ʼ��һ�������̸��
void initRecordBoard(void){
    int i,j;
    for(i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            innerBoard[i][j]=0;
}

//��innerBoard�м�¼������λ�ã�ת����displayBoard��
void innerLayout(void){
	//��һ������EmptyBoard�м�¼�Ŀ����̣����Ƶ�displayBoard��
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<=SIZE*CHARSIZE-1;j++){
            displayBoard[i][j]=EmptyBoard[i][j];
        }
    }
	//�ڶ�����ɨ��innerBoard����������0��Ԫ�أ�������ߡ��Ƶ�displayBoard����Ӧλ����
	//ע�⣺displayBoard����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(innerBoard[i][j]==1){
                displayBoard[i][CHARSIZE*j]=play1Pic[0];
                displayBoard[i][CHARSIZE*j+1]=play1Pic[1];
            }else if(innerBoard[i][j]==2){
                displayBoard[i][CHARSIZE*j]=play2Pic[0];
                displayBoard[i][CHARSIZE*j+1]=play2Pic[1];
            }
        }
    }
}

//��ʾ���̸��
void display(void){
	int i;
	system("clear");   //����  
    for(i=0;i<SIZE;i++){
        printf("%3d %s\n",SIZE-i,displayBoard[i]);
    }
    printf("   ");
    for(i=0;i<SIZE;i++)
        printf("%2c",'A'+i);
    printf("\n");
} 

//�ı�������ӵ���״
void changeCurrent(Point p,int player){
    if (player==1){
        displayBoard[p.x][CHARSIZE*p.y]=play1CurrentPic[0];
        displayBoard[p.x][CHARSIZE*p.y+1]=play1CurrentPic[1];
    }else if(player==2){
        displayBoard[p.x][CHARSIZE*p.y]=play2CurrentPic[0];
        displayBoard[p.x][CHARSIZE*p.y+1]=play2CurrentPic[1];
    }
}