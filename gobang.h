#ifndef __GOBANG_H__
#define __GOBANG_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 15
#define CHARSIZE 2//棋盘使用的是GBK编码，每一个中文字符占用2个字节。
#define NINF -9223372036854775807
#define PINF 9223372036854775807
#define DEPTH 4 //深度
#define WIDTH 50

typedef long long LL;
typedef struct Point{
    int x;
    int y;
}Point;

typedef struct Info{
    int more;//长连
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
}Info;

typedef struct Move{
    Point p;
    LL score;
}Move;

extern int innerBoard[SIZE][SIZE];
extern int id;
extern int num;
extern int ai_x,ai_y;


void initRecordBoard(void);//初始化一个空棋盘格局
void innerLayout(void);//将innerBoard中记录的棋子位置，转化到displayBoard中
void display(void);//显示棋盘格局
void changeCurrent(Point p,int player);
void menu(void);

void cleanInput(void);
void set(Point p,int player);
void unSet(Point p);
int opp(int player);
void Player(void);
void Computer(void);
int JudgeFive(int x,int y);
int JudgeDisplay(void);


Point nextPoint(Point p,int d,int di);
int inBoard(Point p);
void getBoundary(Point p,int d,int *s,int way,int player);
int getLength(Point p,int d,int *left,int *right,int player);
LL singleScore(Point p,int player);
LL wholeScore(int player);
Info typeAnalysis(int length,int *left, int *right,int player);
Info getInfo(Point p,int player);
int forbiddenHand(Point p,int player);

LL alphaBeta(int depth,LL alpha,LL beta,int player);
int inspireFind(Move *s,int player);
void shellSort(Move *s,int len);
#endif