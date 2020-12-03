#include"stackg.h"
// 构造一个空栈S。
int InitStack(SqStack *S)
{
	// 为栈底分配一个指定大小的存储空间
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if( !(*S).base )
		exit(0); // 存储分配失败
	(*S).top = (*S).base; // 栈底与栈顶相同表示一个空栈
	(*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

int GetTop(SqStack S,SElemType *e)
{
	if(S.top > S.base)
	{
		*e = *(S.top-1); // 栈顶指针的下一个位置为栈顶元素
		return 1;
	}
	else
		return 0;
}

int Push(SqStack *S, SElemType e)
{
	if((*S).top - (*S).base >= (*S).stacksize) // 栈满，追加存储空间
	{
		(*S).base = (SElemType *)realloc((*S).base,
		((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if( !(*S).base )
			exit(0); // 存储分配失败
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++=e;
// 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

int Pop(SqStack *S,SElemType *e)
{
	if((*S).top == (*S).base)
		return 0;
	*e = *--(*S).top;
// 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

SElemType Precede(SElemType t1,SElemType t2)
{
	SElemType f;
	switch(t2)
	{
	
		case '+':
		case '-':
			if(t1=='('||t1=='#')
				f='<';
			else
				f='>';
		break;
		case '*':
		case '/':
			if(t1=='*'||t1=='/'||t1==')')
				f='>';
			else
				f='<';
		break;
		case '(':
			if(t1==')')
			{
				printf("ERROR1\n");
				exit(0);
			}
			else
				f='<';
			break;
		case ')':
			switch(t1)
			{
				case '(':
					f='=';
				break;
				case '#':
					printf("ERROR2\n");
					exit(0);
				default:
					f='>';
			}
		break;
		case '#':
			switch(t1)
			{
				case '#':
					f='=';
				break;
				case '(':
					printf("ERROR3\n");
					exit(0);
				default:
					f='>';
			}
	}
	return f;
}


int In(SElemType c)
{
	switch(c)
	{
		case'-':
		case'*':
		case'/':
		case'(':
		case')':
		case'#':return 1;
		default:return 0;
	}
}


SElemType Operate(SElemType a,SElemType theta,SElemType b)
{
	SElemType c;
	a=a-48; //ASCII值转化为对应的十进制值
	b=b-48; //ASCII值转化为对应的十进制值

	switch(theta)
	{
		case'+':
			c=a+b+48;
		break;
		case'-':
			c=a-b+48;
		break;
		case'*':
			c=a*b+48;
		break;
		case'/':c=a/b+48;
	}
	return c;
}

// 算术表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈
SElemType EvaluateExpression()
{
	SqStack OPTR,OPND;
	SElemType a,b,c,x,theta;

	InitStack(&OPTR);
	Push(&OPTR,'#');
	InitStack(&OPND);
	c=getchar();
	GetTop(OPTR,&x);
	while(c!='#'||x!='#')
	{
		if(In(c)) // 是7种运算符之一
		{
			switch(Precede(x,c))
			{
				case'<':
					Push(&OPTR,c); // 栈顶元素优先权低
					c=getchar();
				break;
				case'=':
					Pop(&OPTR,&x); // 脱括号并接收下一字符
					c=getchar();
				break;
				case'>':
					Pop(&OPTR,&theta); // 退栈并将运算结果入栈
					Pop(&OPND,&b);
					Pop(&OPND,&a);
					Push(&OPND,Operate(a,theta,b));
				break;
			}
		}
		else if(c>='0'&&c<='9') // c是操作数
		{
			Push(&OPND,c);
			c=getchar();
		}
		else // c是非法字符
		{
			printf("非法字符\n");
			exit(0);
		}

		GetTop(OPTR,&x);
	}
	GetTop(OPND,&x);
	return x;
}


