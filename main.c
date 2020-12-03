#include "gobang.h"

//空棋盘模板 
char EmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
//此数组存储用于显示的棋盘 
char DisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲"; 

char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";

//此数组用于记录当前的棋盘的格局 
int InnerBoard[SIZE][SIZE];

int main()
{
    
    initRecordBoard();    //初始化一个空棋盘
    innerLayout();
    display();

    menu();
    
    return 0;
}


//初始化一个空棋盘格局 
void initRecordBoard(void){
	//通过双重循环，将InnerBoard清0
    int i,j;
    for(i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            InnerBoard[i][j]=0;
        
}

//将InnerBoard中记录的棋子位置，转化到DisplayBoard中
void innerLayout(void){
	//第一步：将EmptyBoard中记录的空棋盘，复制到DisplayBoard中
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<=SIZE*CHARSIZE-1;j++){
            DisplayBoard[i][j]=EmptyBoard[i][j];
        }
    }



	//第二步：扫描InnerBoard，当遇到非0的元素，将●或者◎复制到DisplayBoard的相应位置上
	//注意：DisplayBoard所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
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


//显示棋盘格局 
void display(void){
	int i;
	//第一步：清屏
	system("clear");   //清屏  
	//第二步：将DisplayBoard输出到屏幕上
    for(i=0;i<SIZE;i++){
        printf("%3d %s\n",SIZE-i,DisplayBoard[i]);
    }

	//第三步：输出最下面的一行字母A B .... 
    printf("   ");
    for(i=0;i<SIZE;i++)
        printf("%2c",'A'+i);
    printf("\n");
} 
