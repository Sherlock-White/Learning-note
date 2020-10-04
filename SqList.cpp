#include<iostream>
#include<cassert>
#define INSERT 1
#define DELETE 2
#define REWRITE 3
#define SHOW 4

#define MaxSize 10   //������󳤶�
typedef struct {
	int data[MaxSize];//ElemType data[MaxSize];
	int length;       //˳���ĵ�ǰ����
}SqList;              //˳�������Ͷ��壨��̬���䷽ʽ��

//#define InitSize 10  //��ʼ����
//typedef struct {
//	int* data;       //ָʾ��̬���������ָ��
//	int maxSize;     //�������
//	int length;      //��ǰ����
//}SeqList;

bool InitList(SqList& L){
	std::cout << "������10�����ڵ����֣����ÿո����,�Իس�������\n";
	int count = 0;
	int num;
	while (std::cin >> num) {
		while(std::cin.peek() == ' ') {//�����м������ո�
			std::cin.get();
		}
		count++;
		assert(!(count > MaxSize));      //��ֹ���
		L.data[count-1] = num;

		if (std::cin.peek() == '\n') {//���س�����
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
	if (i<1 || i>L.length + 1) {  //�ж�i�ķ�Χ�Ƿ���Ч
		std::cout << "�����i�ķ�Χ���Ϸ�\n";
		return false;
	}
	if (L.length >= MaxSize) {    //�洢�ռ�����
		std::cout << "�洢�ռ�����\n";
		return false;
	}
	for (int j = L.length; j >= i; j--) {
		L.data[j] = L.data[j - 1]; //����i��Ԫ�ؼ�֮���Ԫ�غ���
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}

bool ListDelete(SqList& L, int i, int& e) {
	if (i<1 || i>L.length) {
		std::cout << "�����i�ķ�Χ���Ϸ�\n";
		return false;
	}
	e = L.data[i - 1];  //����ɾ����Ԫ�ظ���e
	for (int j = i; j < L.length; j++) {
		L.data[j - 1] = L.data[j];//����i��λ�ú��Ԫ��ǰ��
	}
	L.length--;
	return true;
}

bool ListRewrite(SqList& L, int i, int e) {
	if (i<1 || i>L.length) {
		std::cout << "�����i�ķ�Χ���Ϸ�\n";
		return false;
	}
	L.data[i - 1] = e;
	return true;
}

int main() {
	SqList list;
	std::cout << "����б���г�ʼ��\n";
	InitList(list);
	int location;
	int elem;
	while (1) {
		std::cout << "��ѡ��ָ�1���룬2ɾ����3�޸ģ�4��ӡ�������������˳�\n";
		int command = 0;
		std::cin >> command;
		switch (command){
		case INSERT:
			std::cout << "����������λ��\n";
			std::cin >> location;
			std::cout << "����������ֵ\n";
			std::cin >> elem;
			ListInsert(list, location, elem);
			break;
		case DELETE:
			std::cout << "������ɾ�����ݵ�λ��\n";
			std::cin >> location;
			ListDelete(list, location, elem);
			std::cout << "ɾ�����ǵ�" << location << "λ��" << elem;
			break;
		case REWRITE:
			std::cout << "�������޸ĵ�λ��\n";
			std::cin >> location;
			std::cout << "�������µ�ֵ\n";
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