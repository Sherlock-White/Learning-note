//#include "project2.h"
#include<iostream>

class ListPoint {
private:
	int data;
	ListPoint* left;
	ListPoint* right;
	friend class List;
public:
	ListPoint(const int& item);
	bool insert(ListPoint*& curPosition, ListPoint*& newNode);
	int getNum();
};

class List {
private:
	ListPoint* head;
	ListPoint* tail;
	int length;
public:
	List();
	bool makeEmpty();
	bool reset();
	int getLength();
	ListPoint* find(int location);
	bool insert(int value, int location);
	bool remove(int location);
	bool check();
	void compare(List* list2, List*& resultList);
	void print();
};

void init(int& num, List& list);

ListPoint::ListPoint(const int& item) {
	data = item;
	left = NULL;
	right = NULL;
}

bool ListPoint::insert(ListPoint*& curPosition, ListPoint*& newNode) {
	if (curPosition == NULL) {          //后插操作，所以不存在curPosition==NULL的插入
		return false;
	}
	newNode->left = curPosition;
	newNode->right = curPosition->right;
	if (curPosition->right != NULL) {   //在末尾插入就不需要后面的NULL指针指向newNode了
		newNode->right->left = newNode;
	}
	curPosition->right = newNode;
	return true;
}

int ListPoint::getNum() {
	return data;
}

List::List() {
	head = (ListPoint*)malloc(sizeof(ListPoint));
	tail = (ListPoint*)malloc(sizeof(ListPoint));
	head->data = NULL;
	head->left = NULL;
	head->right = NULL;
	tail->data = NULL;
	tail->left = NULL;
	tail->right = NULL;
	length = 0;
}

bool List::makeEmpty() {
	ListPoint* p = head->right;
	ListPoint* freePoint = p;
	while (1) {
		if (p == NULL) {
			length = 0;
			return true;
		}
		freePoint = p;
		p = p->right;
		free(freePoint);
	}
}

bool List::reset() {
	if (!makeEmpty()) {
		return false;
	}
	head->right = NULL;
	tail = head;
	return true;
}

int List::getLength() {
	return length;
}

ListPoint* List::find(int location) {
	ListPoint* p = head;
	int count = 0;
	while (1) {
		if (p == NULL || count == location) {
			break;
		}
		p = p->right;
		count++;
	}
	return p;
}

bool List::insert(int value, int location) {
	if (location < 0) {
		return false;
	}
	else if (location > length) {
		location = length;
	}

	ListPoint* p = head;
	p = find(location);  //后插操作要找到location的前一个结点

	ListPoint* newNode = (ListPoint*)malloc(sizeof(ListPoint));
	newNode->data = value;
	if (!newNode->insert(p, newNode)) {
		return false;
	}
	if (newNode->right == NULL) {
		tail = newNode;
	}
	length++;
	return true;
}

bool List::remove(int location) {
	if (location<0 || location>length) {
		return false;
	}
	ListPoint* p = head;
	p = find(location);

	p->left->right = p->right;
	if (p->right != NULL) {
		p->right->left = p->left;
	}
	free(p);
	p = NULL;
	length--;
	return true;
}

bool List::check() {
	ListPoint* p = head->right;//指向头结点之后的下一个结点
	if (p == NULL) {
		return true;           //是空表的情况
	}
	ListPoint* pNext = p->right;
	if (pNext == NULL) {       //只有一个结点的情况
		return true;
	}
	//--------------------------------------------------------
	while (pNext != NULL) {
		if (!(p->getNum() <= pNext->getNum())) {
			std::cout << "输入不合法,请输入非降序序列\n";
			return false;
		}
		p = pNext;
		pNext = p->right;
	}
	return true;
}

void List::compare(List* list2, List*& resultList) {
	ListPoint* p1 = head->right;
	ListPoint* p2 = list2->head->right;
	int p1Num, p2Num;
	while (1) {
		if (p1 == NULL || p2 == NULL) {
			break;
		}
		p1Num = p1->getNum();
		p2Num = p2->getNum();
		if (p1Num == p2Num) {
			resultList->insert(p1Num, resultList->getLength());
			p1 = p1->right;
			p2 = p2->right;
		}
		if (p1Num < p2Num) {
			p1 = p1->right;
		}
		else if (p1Num > p2Num) {
			p2 = p2->right;
		}
	}
}

void List::print() {
	ListPoint* p = head->right;
	if (p == NULL) {
		std::cout << "NULL";
	}
	while (1) {
		if (p == NULL) {
			break;
		}
		std::cout << p->getNum();
		p = p->right;
		if (p != NULL) {
			std::cout << ' ';
		}
	}
	std::cout << "\n";
}

void init(int& num, List& list) {
	while (1) {
		while (1) {
			std::cin >> num;
			if (std::cin.fail()) {
				std::cout << "输入不合法,请输入正整数,并以-1结尾\n";
				list.reset();
				std::cin.clear();
				std::cin.ignore(sizeof(num), '\n');
				continue;
			}
			else {
				if (num == -1) {
					break;
				}
				else if (num < -1) {
					std::cout << "输入不合法,请输入正整数,并以-1结尾\n";
					list.reset();
					std::cin.clear();
					std::cin.ignore(sizeof(num), '\n');
				}
				else {
					list.insert(num, list.getLength());
				}
			}
		}
		if (list.check()) {  //如果读入的是降序则继续输入
			std::cout << "输入正确！\n";
			break;
		}
		else {
			list.reset();
		}
	}
}

int main() {
	std::cout << "请输入两串若干个正整数构成的非降序序列，以-1结束输入\n";
	int num;
	List list1;
	List list2;
	List resultList;
	init(num, list1);
	init(num, list2);
	List* resultPointer = &resultList;
	//--------------------------------------
	list1.compare(&list2,resultPointer);
	resultList.print();
	//--------------------------------------
	list1.makeEmpty();
	list2.makeEmpty();
	resultList.makeEmpty();
	system("pause");
	return 0;
}