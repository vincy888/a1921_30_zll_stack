#include"stackg.h"
int main()
{
	printf("请输入算术表达式（中间值及最终结果要在0～9之间），""并以#结束\n");
	printf("例如：3*(7-5)#\n");
	printf("%c\n",EvaluateExpression());

	return 0;
}

