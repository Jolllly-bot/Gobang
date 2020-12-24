#ifndef __GOBANG_H__
#define __GOBANG_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 15
#define CHARSIZE 2//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

struct point{
    int x;
    int y;
};

void initRecordBoard(void);
void innerLayout(void);
void display(void);
void menu(void);

extern int innerBoard[SIZE][SIZE];

#endif