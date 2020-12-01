#include "gobang.h"

//������ģ�� 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
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
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; 

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";

//���������ڼ�¼��ǰ�����̵ĸ�� 
int arrayForInnerBoardLayout[SIZE][SIZE];

int main()
{
    
    initRecordBoard();    //��ʼ��һ��������
    innerLayoutToDisplayArray();
    displayBoard();

    menu();
    
    return 0;
}


//��ʼ��һ�������̸�� 
void initRecordBoard(void){
	//ͨ��˫��ѭ������arrayForInnerBoardLayout��0
    int i,j;
    for(i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            arrayForInnerBoardLayout[i][j]=0;
        
}

//��arrayForInnerBoardLayout�м�¼������λ�ã�ת����arrayForDisplayBoard��
void innerLayoutToDisplayArray(void){
	//��һ������arrayForEmptyBoard�м�¼�Ŀ����̣����Ƶ�arrayForDisplayBoard��
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<=SIZE*CHARSIZE-1;j++){
            arrayForDisplayBoard[i][j]=arrayForEmptyBoard[i][j];
        }
    }



	//�ڶ�����ɨ��arrayForInnerBoardLayout����������0��Ԫ�أ�������ߡ��Ƶ�arrayForDisplayBoard����Ӧλ����
	//ע�⣺arrayForDisplayBoard����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(arrayForInnerBoardLayout[i][j]==1){
                arrayForDisplayBoard[i][CHARSIZE*j]=play1Pic[0];
                arrayForDisplayBoard[i][CHARSIZE*j+1]=play1Pic[1];
            }else if(arrayForInnerBoardLayout[i][j]==2){
                arrayForDisplayBoard[i][CHARSIZE*j]=play2Pic[0];
                arrayForDisplayBoard[i][CHARSIZE*j+1]=play2Pic[1];
            }else if(arrayForInnerBoardLayout[i][j]==3){
                arrayForDisplayBoard[i][CHARSIZE*j]=play1CurrentPic[0];
                arrayForDisplayBoard[i][CHARSIZE*j+1]=play1CurrentPic[1];
            }else if(arrayForInnerBoardLayout[i][j]==4){
                arrayForDisplayBoard[i][CHARSIZE*j]=play2CurrentPic[0];
                arrayForDisplayBoard[i][CHARSIZE*j+1]=play2CurrentPic[1];
            }
        }
    }
 
}


//��ʾ���̸�� 
void displayBoard(void){
	int i;
	//��һ��������
	system("clear");   //����  
	//�ڶ�������arrayForDisplayBoard�������Ļ��
    for(i=0;i<SIZE;i++){
        printf("%3d %s\n",SIZE-i,arrayForDisplayBoard[i]);
    }

	//������������������һ����ĸA B .... 
    printf("   ");
    for(i=0;i<SIZE;i++)
        printf("%2c",'A'+i);
    printf("\n");
} 
