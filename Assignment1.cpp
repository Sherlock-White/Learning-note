#include <iostream>
#include <string>

//To check whether the input is an none-negative integer
//检查输入是否为一个非负整型
bool inputCheck(std::string str) {
	int length = str.length();
	for (int i = 0; i < length; i++) {
		if (!(str[i] >= '0' && str[i] <= '9')) {
			return false;
		}
	}
	return true;
}

//change string to integer
//将字符串转换为整型
int changeStrToInt(std::string str) {
	int length = str.length();
	int sum = 0;
	for (int i = 0; i < length; i++) {
		sum *= 10;
		sum += (str[i] - '0');
	}
	return sum;
}

//init n and k
//初始化n和k
bool init(int& intN,int& intK) {
	std::string strN, strK;
	std::cout << "Please input the variable n." << std::endl;
	std::cout << "请输入变量n。" << std::endl;
	while (1) {
		std::cin >> strN;
		if (inputCheck(strN)) {
			intN = changeStrToInt(strN);
			if (intN > 0) {
				break;
			}
		}
		std::cout << "Please input an none-negative integer." << std::endl;
		std::cout << "请输入一个非负整型。" << std::endl;
	}
	//------------------------------------------------------
	std::cout << "Please input the variable k." << std::endl;
	std::cout << "请输入变量k。" << std::endl;
	while (1) {
		std::cin >> strK;
		if (inputCheck(strK)) {
			intK = changeStrToInt(strK);
			if (intK >= 0 && intK <= 9) {
				break;
			}
		}
		std::cout << "Please input an none-negative integer between 0 and 9." << std::endl;
		std::cout << "请输入一个介于0到9之间的非负整型。" << std::endl;
	}
	return true;
}

class Node {
private:
	int _num;
	Node* _left;
	Node* _right;
public:
	Node(int num,Node* left,Node* right):_num(num),_left(left),_right(right){}
	int getValue() {
		return _num;
	}
	void setValue(int num) {
		_num = num;
	}
	Node* getLeftChild() {
		return _left;
	}
	void setLeftChild(Node* left) {
		_left = left;
	}
	Node* getRightChild() {
		return _right;
	}
	void setRightChild(Node* right) {
		_right = right;
	}
};

class Number {
private:
	int n;
	int k;
	Node* root;
	long result;
	int resultNum;
public:
	Number(int intN, int intK):n(intN),k(intK){
		root = nullptr;
		result = 0;
		resultNum = 0;
	}
	bool rangeCheck(int num) {
		return (num >= 0 && num <= 9) ? true : false;
	}
	int changeCharToInt(char c) {
		return c - '0';
	}

	void creatTree(Node* p,int depth) {
		if (depth >= n || p == nullptr) {
			return;
		}else{
			Node* left = (Node*)malloc(sizeof(Node));
			Node* right = (Node*)malloc(sizeof(Node));
			left->setValue(p->getValue() - k);
			right->setValue(p->getValue() + k);
			left->setLeftChild(nullptr);
			left->setRightChild(nullptr);
			right->setLeftChild(nullptr);
			right->setRightChild(nullptr);
			//-----------------------------------
			if (rangeCheck(left->getValue())) {
				p->setLeftChild(left);
				creatTree(left, depth + 1);
			}else{
				free(left);
				left = nullptr;
			}
			//------------------------------------
			if (rangeCheck(right->getValue())) {
				p->setRightChild(right);
				creatTree(right, depth + 1);
			}else{
				free(right);
				right = nullptr;
			}
		}
		return;
	}

	void travelsal(Node* p,int depth) {
		if (p == nullptr) {
			return;
		}else{
			result *= 10;
			result += p->getValue();
			if (depth == n) {
				resultNum++;
				if (resultNum != 1) {
					std::cout << ',';
				}
				std::cout << result;
				return;
			}
			Node* pLeft = p->getLeftChild();
			Node* pRight = p->getRightChild();
			if (pLeft != nullptr) {
				travelsal(pLeft, depth + 1);
				result /= 10;
			}
			if (pRight != nullptr) {
				travelsal(pRight, depth + 1);
				result /= 10;
			}
			return;
		}
	}
	void travelsal(Node* p) {
		if (p == nullptr) {
			return ;
		}else{
			Node* pLeft = p->getLeftChild();
			Node* pRight = p->getRightChild();
			if (pLeft != nullptr) {
				travelsal(pLeft);
			}
			if (pRight != nullptr) {
				travelsal(pRight);
			}
			free(p);
		}
	}
	
	void reset(Node* p) {
		result = 0;
		travelsal(p);
	}

	bool run() {
		/*(n == 1) means no matter what value k is,it can never meet the demand
			* (n == 1)意味着不论k的值为多少，都无法满足要求			*/
		if (n == 1) {
			std::cout << "[]" << std::endl;
		}
		else {
			std::cout << '[';
			for (int rootNum = 1; rootNum <= 9; rootNum++) {
				root = (Node*)malloc(sizeof(Node));
				root->setLeftChild(nullptr);
				root->setRightChild(nullptr);
				root->setValue(rootNum);
				/*cause the number cannot start with zero
				* 因为数字不能以0开头 */
				if (k == 0) {
					/*if (k == 0) then it would not be a binary tree
					*如果（k == 0）则就不会是一棵二叉树，可以直接输出*/
					for (int i = 0; i < n; i++) {
						std::cout << rootNum;
					}
					if (rootNum != 9) {
						std::cout << ',';
					}
				}
				else {
					creatTree(root , 1);
					travelsal(root,1);
				}
				reset(root);
			}
			std::cout << ']' << std::endl;
		}
		return true;
	}
};

int main() {
	int intN = 0, intK = 0;
	if (init(intN, intK)) {
		Number number(intN, intK);
		std::cout << "The result is:";
		number.run();
	}
	return 0;
}