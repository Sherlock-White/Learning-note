#include<stdio.h>
#include<stdlib.h>

int main() {
	printf("�������м京����ո�����������������֣�");
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
	printf("����ǣ�%d", sum);
	printf("\n");
	system("pause");
	return 0;
}