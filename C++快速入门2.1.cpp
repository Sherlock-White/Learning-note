#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]) {
	FILE* in, * out;
	int ch;

	//确保输入参数个数
	if (argc != 3) {
		fprintf(stderr, "输入形式：copyFile 源文件名 目标文件名 \n");
		exit(EXIT_FAILURE);
	}
	//以二进制的形式按可读打开，成功就返回指针
	if ((in = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "打不开文件：%s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	//以二进制的形式按可写打开，成功就返回指针
	if ((out = fopen(argv[2], "wb")) == NULL) {
		fprintf(stderr, "打不开文件：%s\n", argv[2]);
		fclose(in);//记得fopen要和fclose搭配使用
		exit(EXIT_FAILURE);
	}
	while ((ch = getc(in) != EOF)) {//EOF == end of file
		if (putc(ch, out) == EOF) {
			break;
		}
	}
	if (ferror(in)) {
		printf("读取文件 %s失败！\n", argv[1]);
	}
	if (ferror(out)) {
		printf("写入文件 %s 失败！\n", argv[2]);
	}
	printf("成功复制1个文件！\n");

	fclose(in);
	fclose(out);
	return 0;
}