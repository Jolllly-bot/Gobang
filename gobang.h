#ifndef __GOBANG_H__
#define __GOBANG_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 15
#define CHARSIZE 2//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�
#define NINF -2147483648
#define PINF 2147483647
#define DEPTH 4 //���(����Ϊż��)

struct Point{
    int x;
    int y;
};

struct Type{
    int win5;//20000000
    int alive4;//��4
    int dalive4;//��4 10000
    int dead4;//��4 5000
    int alive3;//��3 10000
    int dalive3;//��3 1000
    int dead3;//��3 500
    int alive2; //��2 1000
    int dalive2; //��2 200
    int dead2; //��2 50
    int alive1; //��1 100
    int dalive1; //��1 10
    int dead1; //��1 5
};

extern int innerBoard[SIZE][SIZE];
extern char displayBoard[SIZE][SIZE*CHARSIZE+1];
extern int id;
extern int num;


void initRecordBoard(void);//��ʼ��һ�������̸��
void innerLayout(void);//��innerBoard�м�¼������λ�ã�ת����displayBoard��
void display(void);//��ʾ���̸��
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