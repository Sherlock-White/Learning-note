#include<iostream>
#include<cassert>
#define INSERT 1
#define DELETE 2
#define REWRITE 3
#define SHOW 4

#define MaxSize 10   //定义最大长度
typedef struct {
	int data[MaxSize];//ElemType data[MaxSize];
	int length;       //顺序表的当前长度
}SqList;              //顺序表的类型定义（静态分配方式）

//#define InitSize 10  //初始长度
//typedef struct {
//	int* data;       //指示动态分配数组的指针
//	int maxSize;     //最大容量
//	int length;      //当前长度
//}SeqList;

bool InitList(SqList& L){
	std::cout << "请输入10个以内的数字，并用空格隔开,以回车键结束\n";
	int count = 0;
	int num;
	while (std::cin >> num) {
		while(std::cin.peek() == ' ') {//跳过中间的任意空格
			std::cin.get();
		}
		count++;
		assert(!(count > MaxSize));      //防止溢出
		L.data[count-1] = num;

		if (std::cin.peek() == '\n') {//到回车结束
			break;
		}
	}
	L.length = count;
	return true;
}

void ShowList(SqList L) {
	for (int i = 0; i < L.length; i++) {
		std::cout << L.data[i];
		std::cout << " ";
	}
}

bool ListInsert(SqList& L, int i, int e) {
	if (i<1 || i>L.length + 1) {  //判断i的范围是否有效
		std::cout << "输入的i的范围不合法\n";
		return false;
	}
	if (L.length >= MaxSize) {    //存储空间已满
		std::cout << "存储空间已满\n";
		return false;
	}
	for (int j = L.length; j >= i; j--) {
		L.data[j] = L.data[j - 1]; //将第i个元素及之后的元素后移
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}

bool ListDelete(SqList& L, int i, int& e) {
	if (i<1 || i>L.length) {
		std::cout << "输入的i的范围不合法\n";
		return false;
	}
	e = L.data[i - 1];  //将被删除的元素赋给e
	for (int j = i; j < L.length; j++) {
		L.data[j - 1] = L.data[j];//将第i个位置后的元素前移
	}
	L.length--;
	return true;
}

bool ListRewrite(SqList& L, int i, int e) {
	if (i<1 || i>L.length) {
		std::cout << "输入的i的范围不合法\n";
		return false;
	}
	L.data[i - 1] = e;
	return true;
}

int main() {
	SqList list;
	std::cout << "请对列表进行初始化\n";
	InitList(list);
	int location;
	int elem;
	while (1) {
		std::cout << "请选择指令，1插入，2删除，3修改，4打印，按下其他键退出\n";
		int command = 0;
		std::cin >> command;
		switch (command){
		case INSERT:
			std::cout << "请输入插入的位置\n";
			std::cin >> location;
			std::cout << "请输入插入的值\n";
			std::cin >> elem;
			ListInsert(list, location, elem);
			break;
		case DELETE:
			std::cout << "请输入删除数据的位置\n";
			std::cin >> location;
			ListDelete(list, location, elem);
			std::cout << "删除的是第" << location << "位的" << elem;
			break;
		case REWRITE:
			std::cout << "请输入修改的位置\n";
			std::cin >> location;
			std::cout << "请输入新的值\n";
			std::cin >> elem;
			ListRewrite(list, location, elem);
			break;
		case SHOW:
			ShowList(list);
			break;
		default:
			return -1;
		}
	}
	return 0;
}