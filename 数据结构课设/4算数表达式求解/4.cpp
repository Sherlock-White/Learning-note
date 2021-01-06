#include<iostream>
#include<cassert>
#include<string>

#define CONTINUE 1
#define STOP 0

#define STACK_INCREASE_SIZE 20 

template<class T>
class Stack {
private:
	T* elements;
	int top;
	int maxSize;
	void overflowProcess();
public:
	Stack();
	~Stack();
	bool push(T& value);
	bool pop(T& value);
	bool getTop(T& topNum);
	bool isEmpty();
	bool isFull();
	int getSize();
	void makeEmpty();
};

class Calculator {
private:
	Stack<double> numStack;
	Stack<char> operationStack;
	void addOperand(double value);
	bool get2Operand(double& left, double& right);
	bool doOperator(char op);
public:
	Calculator();
	//bool run(std::string str);
	void clear();

	bool checkChar(const std::string& str);
	void changeStr(std::string& str, int& position, int& length);
	bool checkGramma(std::string& str);

	double adjustNum(const std::string& str, int& position);
	bool calculate(const std::string& str);
	//std::string postfix(const std::string& str);
};

int continueOrNot();

int isp(char ch);

int icp(char ch);


template<class T>
void Stack<T>::overflowProcess() {
	maxSize += 50;
	assert((elements = (T*)realloc(elements, maxSize))!= NULL);
}

template<class T>
Stack<T>::Stack() {
	maxSize = 50;
	elements = (T*)calloc(maxSize, sizeof(T));
	assert(elements != NULL);
	top = -1;
}

template<class T>
Stack<T>::~Stack() {
	free(elements);
}

template<class T>
bool Stack<T>::push(T& value) {
	if (isFull()) {
		overflowProcess();
	}
	elements[++top] = value;
	return true;
}

template<class T>
bool Stack<T>::pop(T& value) {
	if (isEmpty()) {
		return false;
	}
	value = elements[top--];
	return true;
}

template<class T>
bool Stack<T>::getTop(T& topNum) {
	if (isEmpty()) {
		return false;
	}
	else {
		topNum = elements[top];
		return true;
	}
}

template<class T>
bool Stack<T>::isEmpty() {
	if (top == -1) {
		return true;
	}
	else {
		return false;
	}
}

template<class T>
bool Stack<T>::isFull() {
	if (top == maxSize - 1) {
		return true;
	}
	else {
		return false;
	}
}

template<class T>
int Stack<T>::getSize() {
	return top + 1;
}

template<class T>
void Stack<T>::makeEmpty() {
	top = -1;
}
//----------------------------------------------
void Calculator::addOperand(double value) {
	numStack.push(value);
}

bool Calculator::get2Operand(double& left, double& right) {
	if (numStack.isEmpty()) {
		std::cerr << "ȱ���Ҳ�������\n" << std::endl;
		return false;
	}
	numStack.pop(right);
	if (numStack.isEmpty()) {
		std::cerr << "ȱ�����������\n" << std::endl;
		return false;
	}
	numStack.pop(left);
	return true;
}

bool Calculator::doOperator(char op) {
	double left, right, value;
	if (get2Operand(left, right)) {
		switch (op) {
		case '+':
			value = left + right;
			numStack.push(value);
			break;
		case '-':
			value = left - right;
			numStack.push(value);
			break;
		case'*':
			value = left * right;
			numStack.push(value);
			break;
		case'/':
			if (right == 0.0) {
				std::cout << "�﷨���󣡳�������Ϊ0��\n";
				return false;
			}
			value = left / right;
			numStack.push(value);
			break;
		case '%':
			if ((int)(left * 100000) % 100000 != 0 || 
				(int)(right * 100000) % 100000 != 0) {
				std::cout << "�﷨����С���޷�����ȡ�࣡\n";
				return false;
			}
			value = (int)left % (int)right;
			numStack.push(value);
			break;
		case'^':
			value = 1;
			for (int i = 0; i < right; i++) {
				value *= left;
			}
			numStack.push(value);
			break;
		}
	}
	return true;
}

Calculator::Calculator() {
}

void Calculator::clear() {
	numStack.makeEmpty();
	operationStack.makeEmpty();
}

bool Calculator::checkChar(const std::string& str) {
	int len = str.length();
	for (int i = 0; i < len; i++) {
		if (!((str[i] >= '0' && str[i] <= '9') ||
			str[i] == '+' || str[i] == '-' ||
			str[i] == '*' || str[i] == '/' ||
			str[i] == '%' || str[i] == '^' ||
			str[i] == '(' || str[i] == ')' || str[i] == '=')) {
			std::cout << "���벻�Ϸ�������������\n";
			return false;
		}
	}
	return true;
}

void Calculator::changeStr(std::string& str, int& position, int& length) {
	//����0
	str = str.insert(position, 1, '0');
	length++; position++;
	//������в�����
	str = str.insert(position - 1, 1, '(');
	length++; position++;
	//��Ϊposition+1��λ�ÿ϶������֣����Բ�����i = position + 1���
	for (int i = position + 1; i <= length - 1; i++) {
		if (!(str[i] >= '0' && str[i] <= '9')) {
			str = str.insert(i, 1, ')');
			length++;
			position = i;
			break;
		}
	}
}

bool Calculator::checkGramma(std::string& str) {
	int len = str.length();
	int numCount = 0, charCount = 0;
	Stack<char>charStack;
	//-------------------------------------------
	if (str[len - 1] != '=') {
		std::cout << "���벻�Ϸ�������=��β��\n";
		return false;
	}
	//-------------------------------------------
	for (int i = 0; i < len; i++) {
		char ch = str[i];
		if (ch >= '0' && ch <= '9') {
			for (; i < len; i++) {
				if (!(str[i+1] >= '0' && str[i+1] <= '9')) {
					numCount++;
					break;
				}
			}
		}
		else {
			if (!(ch == '(' || ch == ')' || ch == '=')) {
				charCount++;
			}
			//---------------------------------------
			else if (ch == '(') {
				if (!charStack.isFull()) {
					charStack.push(ch);
				}
			}
			else if (ch == ')') {
				if (!charStack.isEmpty()) {
					charStack.pop(ch);
				}
				else {
					std::cout << "���Ų�ƥ�䣡\n";
					return false;
				}
			}
			else {
				if (!charStack.isEmpty()) {
					std::cout << "���Ų�ƥ�䣡\n";
					return false;
				}
			}
		}
		//-------------------------------------------
		//˵��������Ŀ�����
		if (charCount > numCount) {
			if (ch == '+' || ch == '-') {//ֻ��+��-�ǵ�Ŀ�����
				if (i != 0 && (!(str[i - 1] >= '0' && str[i - 1] <= '9'))
					&& (str[i - 1] != '(')) {
					return false;
				}
				//��Ϊ���϶����ԵȺŽ�β�����Բ�����str[i+1]���
				if (str[i + 1] >= '0' && str[i + 1] <= '9') {
					changeStr(str, i, len);
					numCount += 2;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}
	return true;
}

double Calculator::adjustNum(const std::string& str, int& position) {
	int sum = str[position] - '0';
	position++;
	while (1) {
		if (str[position] >= '0' && str[position] <= '9') {
			sum *= 10;
			sum += str[position++] - '0';
		}
		else {
			break;
		}
	}
	position--;
	double sumD = (double)sum;
	return sumD;
}

bool Calculator::calculate(const std::string& str) {
	char ch = '='; char ch1; char op = NULL;
	bool breakFlag = false;
	double num = 0; int position = 0;
	//-----------------------------------
	operationStack.push(ch);
	ch = str[position];
	while (1) {
		if (ch >= '0' && ch <= '9') {
			num = adjustNum(str, position);
			numStack.push(num);
			ch = str[++position];
		}
		else {
			operationStack.getTop(ch1);
			if (isp(ch1) < icp(ch)) {
				operationStack.push(ch);
				ch = str[++position];
			}
			else if (isp(ch1) > icp(ch)) {
				operationStack.pop(op);
				if (!doOperator(op)) {
					return false;
				}
			}
			else {
				operationStack.pop(op);
				if (op == '(') {
					ch = str[++position];
				}
				if (op == '=') {
					breakFlag = true;
				}
			}
		}
		if (breakFlag) {
			break;
		}
	}
	numStack.pop(num);
	std::cout << num << '\n';
	return true;
}

int continueOrNot() {
	while (1) {
		std::cout << "--------------------------------\n";
		std::cout << "�Ƿ������y��n����";
		char command;
		std::cin >> command;
		if (command == 'y' || command == 'Y') {
			return CONTINUE;
		}
		else if (command == 'n' || command == 'N') {
			return STOP;
		}
		else {
			std::cout << "������Ϸ����룬y��n\n";
			continue;
		}
	}
}

int isp(char ch) {
	if (ch == '=') {
		return 0;
	}
	else if (ch == '(') {
		return 1;
	}
	else if (ch == '+' || ch == '-') {
		return 3;
	}
	else if (ch == '*' || ch == '/' || ch == '%') {
		return 5;
	}
	else if (ch == '^') {
		return 7;
	}
	else {
		return 8;
	}
}

int icp(char ch) {
	if (ch == '=') {
		return 0;
	}
	else if (ch == '(') {
		return 8;
	}
	else if (ch == '+' || ch == '-') {
		return 2;
	}
	else if (ch == '*' || ch == '/' || ch == '%') {
		return 4;
	}
	else if (ch == '^') {
		return 6;
	}
	else {
		return 1;
	}
}

int main() {
	while (1) {
		std::cout << "----------------------------------------\n";
		std::string str;
		std::cout << "��������ʽ\n";
		std::cin >> str;
		Calculator cal;
		if (!cal.checkChar(str)) {
			continue;
		}
		if (!cal.checkGramma(str)) {
			continue;
		}
		//---------------------------------
		if (!cal.calculate(str)) {
			std::cout << "����������\n";
			continue;
		}
		//---------------------------------
		if (continueOrNot() == CONTINUE) {
			continue;
		}
		else {
			break;
		}
	}
	system("pause");
	return 0;
}