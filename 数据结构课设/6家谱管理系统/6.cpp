#include <iostream>
#include<string>
#include<cassert>

template<class T>
class Stack {
private:
	T* elements;
	int top;
	int maxSize;
	void overflowProcess() {
		maxSize += 50;
		assert((elements = (T*)realloc(elements, maxSize)) != NULL);
	}
public:
	Stack() {
		maxSize = 50;
		elements = (T*)calloc(maxSize, sizeof(T));
		assert(elements != NULL);
		top = -1;
	}
	~Stack() {
		free(elements);
	}
	bool push(T& value) {
		if (isFull()) {
			overflowProcess();
		}
		elements[++top] = value;
		return true;
	}
	bool pop(T& value) {
		if (isEmpty()) {
			return false;
		}
		value = elements[top--];
		return true;
	}
	bool getTop(T& topNum) {
		if (isEmpty()) {
			return false;
		}
		else {
			topNum = elements[top];
			return true;
		}
	}
	bool isEmpty() {
		if (top == -1) {
			return true;
		}
		else {
			return false;
		}
	}
	bool isFull() {
		if (top == maxSize - 1) {
			return true;
		}
		else {
			return false;
		}
	}
	int getSize() {
		return top + 1;
	}
	void makeEmpty() {
		top = -1;
	}
};

class TreeNode {
private:
	char data[10];
	TreeNode* firstChild, * nextSibling;
public:
	TreeNode() {
		memset(data, 0, 10);
		firstChild = NULL;
		nextSibling = NULL;
	}
	TreeNode(char* value, TreeNode* fc, TreeNode* ns) {
		strcpy_s(data, 10, value);
		firstChild = fc;
		nextSibling = ns;
	}
	char* getData() {
		return data;
	}
	TreeNode* getFirstChild() {
		return this->firstChild;
	}
	TreeNode* getNextSibling() {
		return this->nextSibling;
	}
	void changeData(char* value) {
		strcpy_s(data, 10, value);
	}
	void changeFirstChild(TreeNode* fc) {
		this->firstChild = fc;
	}
	void changeNextSibling(TreeNode* ns) {
		this->nextSibling = ns;
	}
	bool insertSibling(TreeNode* newNode) {
		if (this->nextSibling == NULL) {
			this->nextSibling = newNode;
			return true;
		}
		else {
			return false;
		}
	}
	bool insertChild(TreeNode* newNode) {
		if (this->firstChild == NULL) {
			this->firstChild = newNode;
			return true;
		}
		else {
			return false;
		}
	}
};

class Tree {
private:
	TreeNode* root;
public:
	Tree() { root = NULL; }
	Tree(TreeNode* root) {
		this->root = root;
	}
	TreeNode* getRoot();
	bool firstChild(TreeNode* p);
	bool nextSibling(TreeNode* p);
	char* getData(TreeNode* p);
	bool insertChild(TreeNode* p, char* value);
	void deleteChild(TreeNode* pPre, TreeNode* p);
	void dfs(TreeNode* p, Stack<TreeNode*>& stack);
	bool isEmpty() {
		return root == NULL;
	}
	bool find(TreeNode* p, char* value, TreeNode*& resultNode);
	bool find(TreeNode* p, char* value, TreeNode*& resultNode, TreeNode*& resultNodePre);
};

void initPrint();

bool caseA(char* tempName, Tree tree, TreeNode*& tempAdd);

bool caseB(char* tempName, Tree tree, TreeNode*& tempAdd);

bool caseC(char* tempName, Tree tree, TreeNode*& tempAdd);

bool caseD(char* tempName, TreeNode*& tempAdd);

TreeNode* Tree::getRoot() {
	return root;
}

bool Tree::firstChild(TreeNode* p) {
	if (p != NULL && p->getFirstChild() != NULL) {
		return true;
	}
	else {
		return false;
	}
}

bool Tree::nextSibling(TreeNode* p) {
	if (p != NULL && p->getNextSibling() != NULL) {
		return true;
	}
	else {
		return false;
	}
}

char* Tree::getData(TreeNode* p) {
	if (p != NULL) {
		return p->getData();
	}
	else {
		return NULL;
	}
}

bool Tree::insertChild(TreeNode* p, char* value) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->changeData(value);
	newNode->changeFirstChild(NULL);
	newNode->changeNextSibling(NULL);
	if (firstChild(p)) { //p���������Ů���
		TreeNode* temp = p->getFirstChild();
		while (1) {
			if (temp->getNextSibling() == NULL) {
				return temp->insertSibling(newNode);
			}
			temp = temp->getNextSibling();
		}
	}
	else {
		return p->insertChild(newNode);
	}
}

void Tree::deleteChild(TreeNode*pPre,TreeNode* p) {
	if (p != getRoot()) {
		if (pPre->getNextSibling() == p) {
			pPre->changeNextSibling(p->getNextSibling());
		}
		else {
			pPre->changeFirstChild(NULL);
		}
	}
	TreeNode* deletePoint;
	Stack<TreeNode*> freeStack;
	dfs(p, freeStack);
	while (!freeStack.isEmpty()) {
		freeStack.pop(deletePoint);
		if (deletePoint != getRoot()) {
			free(deletePoint);
		}
	}
}

void Tree::dfs(TreeNode* p,Stack<TreeNode*>& stack) {
	if (p != NULL) {
		stack.push(p);
		for (p = p->getFirstChild(); p != NULL; p = p->getNextSibling()) {
			dfs(p, stack);
		}
	}
}

bool Tree::find(TreeNode* p, char* value,TreeNode*& resultNode) {
	bool result = false;
	if (!strcmp(p->getData(), value)) {
		result = true;
		resultNode = p;
	}
	else {
		TreeNode* q = p->getFirstChild();
		while (q != NULL && !(result = find(q, value, resultNode))) {
			q = q->getNextSibling();
		}
	}
	return result;
}

bool Tree::find(TreeNode* p, char* value, TreeNode*& resultNode,TreeNode*& resultNodePre) {
	bool result = false;
	if (!strcmp(p->getData(), value)) {
		result = true;
	}
	else {
		TreeNode* q = p->getFirstChild();
		resultNodePre = p;
		while (q != NULL && !(result = find(q,value,resultNode,resultNodePre))) {
			resultNodePre = q;
			q = q->getNextSibling();
		}
	}
	return result;
}

void initPrint() {
	std::cout << "**          ���׹���ϵͳ          **\n";
	std::cout << "====================================\n";
	std::cout << "**      ��ѡ��Ҫִ�еĲ�����      **\n";
	std::cout << "**        A --- ���Ƽ���          **\n";
	std::cout << "**        B --- ��ӳ�Ա          **\n";
	std::cout << "**        C --- ��ɢ�ֲ�          **\n";
	std::cout << "**        D --- ��������          **\n";
	std::cout << "**        E --- �˳�����          **\n";
	std::cout << "====================================\n";
}

bool caseA(char* tempName, Tree tree, TreeNode*& tempAdd) {
	if (tempAdd == NULL) {
		std::cout << "��Ϊ" << tempName << "�ĳ�Ա�����ڣ�����������\n";
		return false;
	}
	//-------------------------------------------------
	std::cout << "������" << tempName << "�Ķ�Ů����:";
	int num;
	while (1) {
		std::cin >> num;
		if (std::cin.fail() || num<=0 ) {
			std::cout << "���벻�Ϸ���������һ��������\n";
			return false;
		}
		else {
			break;
		}
	}
	//--------------------------------------------------
	std::cout << "����������" << tempName << "�Ķ�Ů������:";
	char tempChildName[10];
	for (int i = 0; i < num; i++) {
		std::cin >> tempChildName;
		tree.insertChild(tempAdd, tempChildName);
	}
	//---------------------------------------------------
	std::cout << tempName << "�ĵ�һ�������ǣ�";
	tempAdd = tempAdd->getFirstChild();
	while (tempAdd != NULL) {
		std::cout << tempAdd->getData() << " ";
		tempAdd = tempAdd->getNextSibling();
	}
	std::cout << std::endl;
	return true;
}

bool caseB(char* tempName, Tree tree, TreeNode*& tempAdd) {
	if (tempAdd == NULL) {
		std::cout << "��Ϊ" << tempName << "�ĳ�Ա�����ڣ�����������\n";
		return false;
	}
	//-------------------------------------------------
	std::cout << "������" << tempName << "����ӵĶ��ӣ���Ů����������:";
	char tempChildName[10];
	std::cin >> tempChildName;
	tree.insertChild(tempAdd, tempChildName);
	//---------------------------------------------------
	std::cout << tempName << "�ĵ�һ�������ǣ�";
	tempAdd = tempAdd->getFirstChild();
	while (tempAdd != NULL) {
		std::cout << tempAdd->getData() << " ";
		tempAdd = tempAdd->getNextSibling();
	}
	std::cout << std::endl;
	return true;
}

bool caseC(char* tempName, Tree tree, TreeNode*& tempAdd) {
	if (tempAdd == NULL) {
		std::cout << "��Ϊ" << tempName << "�ĳ�Ա�����ڣ�����������\n";
		return false;
	}
	//-------------------------------------------------
	TreeNode* p = tempAdd->getFirstChild();
	if (p == NULL) {
		std::cout << tempName << "û�е�һ������\n";
	}
	else {
		std::cout << tempName << "�ĵ�һ�������ǣ�";
		while (p != NULL) {
			std::cout << p->getData() << ' ';
			p = p->getNextSibling();
		}
		std::cout << std::endl;
	}
	//---------------------------------------------------
	TreeNode* resultNodePre = tree.getRoot();
	TreeNode* resultNode = NULL;
	tree.find(tree.getRoot(), tempName, resultNode, resultNodePre);
	tree.deleteChild(resultNodePre, tempAdd);
	return true;
}

bool caseD(char* tempName, TreeNode*& tempAdd) {
	if (tempAdd == NULL) {
		std::cout << "��Ϊ" << tempName << "�ĳ�Ա�����ڣ�����������\n";
		return false;
	}
	//-------------------------------------------------
	std::cout << "��������ĺ�ĵ�����:";
	char newName[10];
	std::cin >> newName;
	tempAdd->changeData(newName);
	//---------------------------------------------------
	std::cout << tempName << "�Ѹ���Ϊ" << newName << std::endl;
	return true;
}

int main() {
	initPrint();
	char rootName[10];
	std::cout << "���Ƚ���һ�����ף�\n";
	std::cout << "���������ȵ�������";
	std::cin >> rootName;
	TreeNode root(rootName, NULL, NULL);
	Tree tree(&root);
	std::cout << "�˼��׵������ǣ�" << root.getData() << std::endl;
	std::cout << std::endl;
	//-------------------------------------------------------
	while (1) {
		std::cout << "--------------------------\n";
		std::cout << "��ѡ��Ҫ����Ĳ���\n";
		char cmd;
		std::cin >> cmd;
		char tempName[10];
		TreeNode* tempAdd = NULL;
		switch (cmd) {
		case 'A':
		case 'a':
			std::cout << "������Ҫ������ͥ���˵�������";
			std::cin >> tempName;
			tree.find(&root, tempName,tempAdd);
			if (!caseA(tempName, tree, tempAdd)) {
				continue;
			}
			break;
		case 'B':
		case 'b':
			std::cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
			std::cin >> tempName;
			tree.find(&root, tempName,tempAdd);
			if (!caseB(tempName, tree, tempAdd)) {
				continue;
			}
			break;
		case 'C':
		case 'c':
			std::cout << "������Ҫ��ɢ��ͥ���˵�������";
			std::cin >> tempName;
			tree.find(&root, tempName,tempAdd);
			if (!caseC(tempName,tree, tempAdd)) {
				continue;
			}
			break;
		case 'D':
		case 'd':
			std::cout << "������Ҫ�����������˵�Ŀǰ������";
			std::cin >> tempName;
			tree.find(&root, tempName,tempAdd);
			if (!caseD(tempName,tempAdd)) {
				continue;
			}
			break;
		case'E':
		case'e':
			tree.deleteChild(tree.getRoot(),tree.getRoot());
			exit(0);
			break;
		default:
			std::cout << "�Ҳ�����������������룡\n";
			break;
		}
	}
	system("pause");
	return 0;
}