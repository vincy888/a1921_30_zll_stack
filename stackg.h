#ifndef stackg_h
#define stackg_h

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define STACK_INIT_SIZE 10 // 存储空间初始分配量
#define STACKINCREMENT 2 // 存储空间分配增量



typedef int SElemType; 
typedef struct SqStack
{
	SElemType *base; // 在栈构造之前和销毁之后，base的值为NULL
	SElemType *top; // 栈顶指针
	int stacksize; // 当前已分配的存储空间，以元素为单位
}SqStack; // 顺序栈

int InitStack(SqStack *S);
int GetTop(SqStack S,SElemType *e);
int Push(SqStack *S, SElemType e);
int Pop(SqStack *S,SElemType *e);
SElemType Precede(SElemType t1,SElemType t2);
int In(SElemType c);
SElemType Operate(SElemType a,SElemType theta,SElemType b);
SElemType EvaluateExpression();

#endif










