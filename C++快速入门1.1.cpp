#include<stdio.h>
#include<stdlib.h>

int main() {
	printf("请输入中间含任意空格数的任意个数的数字：");
	int tempNum;
	int sum = 0;
	char ch;
	while (scanf_s("%d", &tempNum)) {
		sum += tempNum;
		while ((ch = getchar()) == ' ') {
			;
		}
		if (ch == '\n') {
			break;
		}
		ungetc(ch, stdin);
	}
	printf("结果是：%d", sum);
	printf("\n");
	system("pause");
	return 0;
}