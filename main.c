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
char displayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲"; //黑棋子最后落子

char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";//白棋子最后落子

//此数组用于记录当前的棋盘的格局 
int innerBoard[SIZE][SIZE];

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
    int i,j;
    for(i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            innerBoard[i][j]=0;
}

//将innerBoard中记录的棋子位置，转化到displayBoard中
void innerLayout(void){
	//第一步：将EmptyBoard中记录的空棋盘，复制到displayBoard中
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<=SIZE*CHARSIZE-1;j++){
            displayBoard[i][j]=EmptyBoard[i][j];
        }
    }
	//第二步：扫描innerBoard，当遇到非0的元素，将●或者◎复制到displayBoard的相应位置上
	//注意：displayBoard所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
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

//显示棋盘格局
void display(void){
	int i;
	system("clear");   //清屏  
    for(i=0;i<SIZE;i++){
        printf("%3d %s\n",SIZE-i,displayBoard[i]);
    }
    printf("   ");
    for(i=0;i<SIZE;i++)
        printf("%2c",'A'+i);
    printf("\n");
} 

//改变最后落子的形状
void changeCurrent(Point p,int player){
    if (player==1){
        displayBoard[p.x][CHARSIZE*p.y]=play1CurrentPic[0];
        displayBoard[p.x][CHARSIZE*p.y+1]=play1CurrentPic[1];
    }else if(player==2){
        displayBoard[p.x][CHARSIZE*p.y]=play2CurrentPic[0];
        displayBoard[p.x][CHARSIZE*p.y+1]=play2CurrentPic[1];
    }
}