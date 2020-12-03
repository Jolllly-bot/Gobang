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
char DisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; 

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";

//���������ڼ�¼��ǰ�����̵ĸ�� 
int InnerBoard[SIZE][SIZE];

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
	//ͨ��˫��ѭ������InnerBoard��0
    int i,j;
    for(i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            InnerBoard[i][j]=0;
        
}

//��InnerBoard�м�¼������λ�ã�ת����DisplayBoard��
void innerLayout(void){
	//��һ������EmptyBoard�м�¼�Ŀ����̣����Ƶ�DisplayBoard��
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<=SIZE*CHARSIZE-1;j++){
            DisplayBoard[i][j]=EmptyBoard[i][j];
        }
    }



	//�ڶ�����ɨ��InnerBoard����������0��Ԫ�أ�������ߡ��Ƶ�DisplayBoard����Ӧλ����
	//ע�⣺DisplayBoard����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(InnerBoard[i][j]==1){
                DisplayBoard[i][CHARSIZE*j]=play1Pic[0];
                DisplayBoard[i][CHARSIZE*j+1]=play1Pic[1];
            }else if(InnerBoard[i][j]==2){
                DisplayBoard[i][CHARSIZE*j]=play2Pic[0];
                DisplayBoard[i][CHARSIZE*j+1]=play2Pic[1];
            }else if(InnerBoard[i][j]==3){
                DisplayBoard[i][CHARSIZE*j]=play1CurrentPic[0];
                DisplayBoard[i][CHARSIZE*j+1]=play1CurrentPic[1];
            }else if(InnerBoard[i][j]==4){
                DisplayBoard[i][CHARSIZE*j]=play2CurrentPic[0];
                DisplayBoard[i][CHARSIZE*j+1]=play2CurrentPic[1];
            }
        }
    }
 
}


//��ʾ���̸�� 
void display(void){
	int i;
	//��һ��������
	system("clear");   //����  
	//�ڶ�������DisplayBoard�������Ļ��
    for(i=0;i<SIZE;i++){
        printf("%3d %s\n",SIZE-i,DisplayBoard[i]);
    }

	//������������������һ����ĸA B .... 
    printf("   ");
    for(i=0;i<SIZE;i++)
        printf("%2c",'A'+i);
    printf("\n");
} 
