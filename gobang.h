#ifndef __GOBANG_H__
#define __GOBANG_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 15
#define CHARSIZE 2//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�

void initRecordBoard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
void menu(void);

extern int arrayForInnerBoardLayout[SIZE][SIZE];

#endif