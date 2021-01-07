#ifndef __GOBANG_H__
#define __GOBANG_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 15
#define CHARSIZE 2//棋盘使用的是GBK编码，每一个中文字符占用2个字节。
#define NINF -2147483648
#define PINF 2147483647
#define DEPTH 4 //深度(必须为偶数)

struct Point{
    int x;
    int y;
};

struct Type{
    int win5;//20000000
    int alive4;//活4
    int dalive4;//冲4 10000
    int dead4;//死4 5000
    int alive3;//活3 10000
    int dalive3;//眠3 1000
    int dead3;//死3 500
    int alive2; //活2 1000
    int dalive2; //眠2 200
    int dead2; //死2 50
    int alive1; //活1 100
    int dalive1; //眠1 10
    int dead1; //死1 5
};

extern int innerBoard[SIZE][SIZE];
extern char displayBoard[SIZE][SIZE*CHARSIZE+1];
extern int id;
extern int num;


void initRecordBoard(void);//初始化一个空棋盘格局
void innerLayout(void);//将innerBoard中记录的棋子位置，转化到displayBoard中
void display(void);//显示棋盘格局
void menu(void);

void Set(int x,int y,int player);
void Player(void);
void Computer(void);
int JudgeFive(int x,int y);
int JudgeDisplay(void);


struct Point nextPoint(struct Point p,int d,int di);
int inBoard(struct Point p);
void getBoundary(struct Point p,int d,int *s,int way,int player);
int getLength(struct Point p,int d,int *left,int *right,int player);
int singleScore(struct Point p,int player);
int wholeScore(int player);
struct Type typeAnalysis(int length,int *left, int *right,int player);

int alphaBeta(int depth,int alpha,int beta);
struct POINTS inspireFind(int player);
#endif