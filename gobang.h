#ifndef __GOBANG_H__
#define __GOBANG_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 15 //���̹�ģ
#define CHARSIZE 2//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�
#define NINF -9223372036854775807
#define PINF 9223372036854775807

#define KILLDEPTH 12 //��ɱ���
//����С������� ���������ģʽ
#ifndef SIX
    #define DEPTH 4 //���
    #define WIDTH 45 //��ѡ�Ӹ���
#endif
#ifdef SIX
    #define DEPTH 6 
    #define WIDTH 22 
#endif

typedef long long LL;
typedef struct Point{
    int x;
    int y;
}Point;
typedef struct Info{
    int more;//����
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
}Info;
typedef struct Move{
    Point p;
    int score;
}Move;

extern int innerBoard[SIZE][SIZE];//�洢���ݵ�����
extern int id;//�Ⱥ���
extern int num;//��������
extern int ai_x,ai_y;//�����������

//main.c
void initRecordBoard(void);
void innerLayout(void);
void display(void);
void changeCurrent(Point p,int player);
void menu(void);

//intereact.c
void cleanInput(void);
void set(Point p,int player);
void unSet(Point p);
int opp(int player);
void Player(void);
void Computer(void);
int JudgeFive(int x,int y);
int JudgeDisplay(void);

//score.c
Point nextPoint(Point p,int d,int di);
int inBoard(Point p);
void getBoundary(Point p,int d,int *s,int way,int player);
int getLength(Point p,int d,int *left,int *right,int player);
int singleScore(Point p,int player);
LL wholeScore(int player);
Info typeAnalysis(int length,int *left, int *right,int player);
Info getInfo(Point p,int player);
int forbiddenHand(Point p,int player);

//minmax.c
LL minmax(int depth,LL alpha,LL beta,int player);
LL alphaBeta(int depth,LL alpha,LL beta,int player,Point p);
int inspireFind(Move *s,int player);
void shellSort(Move *s,int len);
int killSearch(void);
int maxKill(int depth,Point p);
int minKill(int depth,Point p);
int findComKill(Move *move);
int findHumKill(Move *move);
#endif