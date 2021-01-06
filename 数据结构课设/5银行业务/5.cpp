#include<iostream>
#include<assert.h>
#include<string>

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
	friend class Queue;
public:
	List();
	bool makeEmpty();
	bool reset();
	int getLength();
	ListPoint* find(int location);
	bool insert(int value, int location);
	bool remove(int location);
	bool check(int value);
};

class Queue {
private:
	List list;
public:
	Queue();
	~Queue();
	bool isEmpty();
	bool push(int value);
	bool pop(int& value);
	void reset();
	bool check(int value);
};

bool checkNum(const std::string& str, int& length);

bool checkAndInit(const std::string& str, Queue& queueA, Queue& queueB);

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

bool List::check(int value) {
	ListPoint* p = head->right;
	while (1) {
		if (p == NULL) {
			return true;
		}
		if (p->data == value) {
			std::cout << "不能出现重复的号码\n";
			return false;
		}
		p = p->right;
	}
}

Queue::Queue() {
}

Queue::~Queue() {
	list.makeEmpty();
}

bool Queue::isEmpty() {
	if (list.getLength() == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Queue::push(int value) {
	if (list.insert(value, list.getLength())) {
		return true;
	}
	else {
		return false;
	}
}

bool Queue::pop(int& value) {
	if (!isEmpty()) {
		value=list.find(1)->getNum();
		list.remove(1);
		return true;
	}
	else {
		return false;
	}
}

void Queue::reset() {
	list.reset();
}

bool Queue::check(int value) {
	if (list.check(value)) {
		return true;
	}
	else {
		return false;
	}
}

bool checkNum(const std::string& str, int& length) {
	for (int position = 0; str[position] != '\0'; position++) {
		if (str[position] >= '0' && str[position] <= '9') {
			length = length * 10 + str[position] - '0';
		}
		else {
			std::cout << "输入不合法，请输入人数 0 < N <= 1000.\n";
			return false;
		}
	}
	if (length > 1000 || length == 0) {
		return false;
	}
	return true;
}

bool checkAndInit(const std::string& str, Queue& queueA, Queue& queueB) {
	int temp = 0;
	for (int pos = 0; str[pos] != '\0'; pos++) {
		if (str[pos] >= '0' && str[pos] <= '9') {
			temp = temp * 10 + str[pos] - '0';
		}
		else {
			std::cout << "输入不合法，正整数号码.\n";
			return false;
		}
	}
	if (temp % 2 == 0) {
		if (queueB.check(temp)) {
			queueB.push(temp);
		}
		else {
			return false;
		}
	}
	else {
		if (queueA.check(temp)) {
			queueA.push(temp);
		}
		else {
			return false;
		}
	}
	return true;
}

int main() {
	Queue queueA;
	Queue queueB;
	int length = 0;
	int count = 0;
	//----------------输入---------------------------
	while (1) {
		std::cout << "-------------------------------------\n";
		std::cout << "请输入一行若干个正整数构成的序列\n";
		std::string str;
		std::cin >> str;
		if (!checkNum(str, length)) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;
		}
		//--------------------------------------------
		for (int i = 0; i < length; i++) {
			std::string tempStr;
			std::cin >> tempStr;
			if (!checkAndInit(tempStr, queueA, queueB)) {
				break;
			}
			count++;
		}
		if (count != length) {
			queueA.reset();
			queueB.reset();
		}
		else {
			break;
		}
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
	//--------------------------------------
	int temp = 0;
	count = 0;
	while (count != length) {
		if (queueA.pop(temp)) {
			count++;
			std::cout << temp;
			if (count != length) {
				std::cout << ' ';
			}
		}
		if (queueA.pop(temp)) {
			count++;
			std::cout << temp;
			if (count != length) {
				std::cout << ' ';
			}
		}
		if (queueB.pop(temp)) {
			count++;
			std::cout << temp;
			if (count != length) {
				std::cout << ' ';
			}
		}
	}
	std::cout << "\n";
	system("pause");
	return 0;
}