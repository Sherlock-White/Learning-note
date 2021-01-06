//#include"project1.h"
#include<iostream>
#include<cstdlib>
#include<cassert>

//一些指令
#define COMMAND_INSERT 1
#define COMMAND_DELETE 2
#define COMMAND_FIND 3
#define COMMAND_REWRITE 4
#define COMMAND_SUM_UP 5
#define COMMAND_CANCEL 0

//最大长度
#define MAXSIZE_NAME 10
#define MAXSIZE_TYPE 20
#define MAXSIZE_GENDER 5
#define MAXSIZE_NUMBER 20
#define MAXSIZE_AGE 4
#define MAXSIZE_NUM 50


//链表
typedef struct listPoint {
	struct listPoint* next;
	unsigned int number;         //学号
	char name[MAXSIZE_NAME];     //姓名
	char gender[MAXSIZE_GENDER]; //性别
	unsigned int age;            //年龄
	char type[MAXSIZE_TYPE];     //报考类型
}listPoint, * linkList;

unsigned int length;//链表的长度

bool changeCharToInt(char* string, unsigned int& num);
//初始化,传入的参数是链表，对链表生成头结点
bool init(linkList& L);
//初始化，插入数据
bool initInsert(linkList& L, unsigned int num);
//按位次插入信息，i代表位次
bool insertInfo(linkList& L, unsigned int i, unsigned int number, char* name,
	char* gender, unsigned int age, char* type);
//按考号删除信息
bool deleteInfo(linkList& L, unsigned int number);
//按考号查找信息
bool findInfo(linkList L, unsigned int number);
//修改信息
bool rewriteInfo(linkList& L, unsigned int number);
//打印表格
void sumInfo(linkList& L);
//释放内存
bool destoryInfo(linkList& L);
//---------------------------------------------------------------
bool changeCharToInt(char* string, unsigned int& num) {
	char* p = string;
	int s = 0;
	while (*p != '\0') {
		if (*p >= '0' && *p <= '9') {
			s = s * 10 + *p - '0';
			p++;
		}
		else {
			return false;
		}
	}
	num = s;
	return true;
}

bool init(linkList& L) {
	L = (listPoint*)malloc(sizeof(listPoint)); //分配一个头节点

	L->number = -1;
	L->age = 0;
	memset(L->name, 0, sizeof(L->name));
	memset(L->type, 0, sizeof(L->type));
	memset(L->gender, 0, sizeof(L->gender));

	if (L == NULL) {
		return false;                          //内存不足，分配失败
	}
	L->next = NULL;
	return true;
}

bool initInsert(linkList& L, unsigned int num) {
//---------------------------初始准备--------------------------------------
	char name[MAXSIZE_NAME], type[MAXSIZE_TYPE], gender[MAXSIZE_GENDER], 
		ageChar[MAXSIZE_AGE], numberChar[MAXSIZE_TYPE];
	unsigned int number = 0, age = 0;
	memset(name, 0, sizeof(name));
	memset(type, 0, sizeof(type));
	memset(gender, 0, sizeof(gender));
	memset(ageChar, 0, sizeof(ageChar));
	memset(numberChar, 0, sizeof(numberChar));
//---------------------------插入数据-------------------------------------
	for (unsigned int i = 1; i <= num; i++) {
		std::cin >> numberChar >> name >> gender >> ageChar >> type;
		if (!changeCharToInt(numberChar, number)) {
			std::cout << "输入的学号不合法\n";
			return false;
		}
		if (!changeCharToInt(ageChar, age)) {
			std::cout << "输入的年龄不合法\n";
			return false;
		}
		insertInfo(L,i,number,name,gender,age,type);
	}
	return true;
}

bool insertInfo(linkList& L, unsigned int i, unsigned int number, char* name,
	           char* gender, unsigned int age, char* type) {
//---------------------------内存分配----------------------------
	listPoint* p;    //p指向当前扫描到的结点
	unsigned int locate = 0;  //p指向的是第几个结点
	p = L;           //p指向头节点

	while (p != NULL && locate < i - 1) {//让p指向i-1个结点
		p = p->next;
		locate++;
	}
	listPoint* temp = (listPoint*)malloc(sizeof(listPoint));
	if (temp == NULL) {
		std::cout << "内存分配失败！\n";
		return false;
	}
	temp->number = number;
	temp->age = age;
	strcpy_s(temp->name, name);
	strcpy_s(temp->gender, gender);
	strcpy_s(temp->type, type);
	temp->next = p->next;
	p->next = temp;
	length++;
	return true;
}

bool deleteInfo(linkList& L,unsigned int number) {
	listPoint* p = L;
	listPoint* deleteInfo = NULL;
	while (1) {
		deleteInfo = p->next;
		if (deleteInfo == NULL) {                //因为p要指向我们要寻找的结点的前一个结点
			std::cout << "没有查找到此人";
			return false;
		}
		else {
			if (deleteInfo->number == number) {  //如果找到了
				p->next = deleteInfo->next;
				std::cout << "删除了考号为" << number << "的学生信息\n";
				free(deleteInfo);
				deleteInfo = NULL;
				length--;
				return true;
			}
			else {
				p = p->next;
			}
		}
	}
}

bool findInfo(linkList L, unsigned int number) {
	listPoint* p = L;
	while (1) {
		if (p == NULL) {
			std::cout << "查无此人\n";
			return false;
		}
		else {
			if (p->number == number) {
				std::cout << p->number << "    " << p->name << "  " << p->gender << "   " << p->age << "  " << p->type << "\n";
				return true;
			}
			else {
				p = p->next;
			}
		}
	}
}

bool rewriteInfo(linkList& L, unsigned int number) {
	listPoint* p = L;
	char name[MAXSIZE_NAME], type[MAXSIZE_TYPE], gender[MAXSIZE_GENDER],
		numChar[MAXSIZE_NUMBER],ageChar[MAXSIZE_AGE];
	unsigned int num = 0, age = 0;
	while (1) {
		if (p == NULL) {
			std::cout << "查无此人\n";
			return false;
		}
		else {
			if (p->number == number) {
				std::cout << "请输入该同学新的考号、姓名、性别、年龄及报考类别\n";
				std::cin >> numChar >> name >> gender >> ageChar >> type;
				if (!changeCharToInt(numChar, num)) {
					std::cout << "输入的学号不合法\n";
					return false;
				}
				if (!changeCharToInt(ageChar, age)) {
					std::cout << "输入的年龄不合法\n";
					return false;
				}
				p->number = num;
				p->age = age;
				strcpy_s(p->name, name);
				strcpy_s(p->gender, gender);
				strcpy_s(p->type, type);
				return true;
			}
			else {
				p = p->next;
			}
		}
	}
}

void sumInfo(linkList& L) {
	listPoint* p = L;
	std::cout << "\n\n考号 姓名 性别 年龄 报考类别\n";
	while (1) {
		p = p->next;
		if (p == NULL) {
			break;
		}
		std::cout << p->number << "    " << p->name << "  " << p->gender << "   " << p->age << "  " << p->type << "\n";
	}
}

bool destoryInfo(linkList& L) {
	listPoint* p = L;
	listPoint* freePointer = L;
	while (1) {
		if (p == NULL) {
			return true;
		}
		else {
			freePointer = p;
			p = p->next;
			free(freePointer);
		}
	}
}

int main() {
//--------------------------初始化链表-----------------------------------------
	length = 0;
	std::cout << "首先请建立考生信息系统！\n" << "请输入考生人数：";
	unsigned int num = 0;        //学生人数
	char numChar[MAXSIZE_NUM];
	memset(numChar, 0, sizeof(numChar));
	std::cin >> numChar;
	if (!changeCharToInt(numChar, num)) {
		std::cout << "输入的学生人数不合法\n";
		return -1;
	}
	if (num > 0) {
		std::cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别！(用空格隔开)\n";
	}
	linkList L;              //一个指向单链表的指针
	init(L);
	initInsert(L, num);
//--------------------------变量声明-------------------------------------------
	char name[MAXSIZE_NAME], type[MAXSIZE_TYPE], gender[MAXSIZE_GENDER],
		ageChar[MAXSIZE_AGE], numberChar[MAXSIZE_TYPE], locationChar[MAXSIZE_NUM];
	unsigned int number = 0, age = 0,location = 0;
	int command;
	while (1) {
		memset(name, 0, sizeof(name));
		memset(type, 0, sizeof(type));
		memset(gender, 0, sizeof(gender));
		memset(ageChar, 0, sizeof(ageChar));
		memset(numberChar, 0, sizeof(numberChar));
		memset(locationChar, 0, sizeof(locationChar));
//-------------------------------------------------------------------------------------------------------
		std::cout << "---------------------------------------------------------------------------\n";
		std::cout << "\n请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）\n";
		std::cin >> command;
		switch (command){
		//-----------------------------插入信息------------------------------------------------
		case COMMAND_INSERT:
			std::cout << "请输入您要插入的考生的位置:";
			std::cin >> locationChar;
			if (!changeCharToInt(locationChar, location)) {
				std::cout << "输入的位置不合法！\n";
				continue;
			}
			if (location < 1 || location > length + 1) {
				std::cout << "输入的位置不合法！\n";
				continue;
			}
			else {
				std::cout << "请依次输入要插入的考生的考号、姓名、性别、年龄及报考类别！\n";
				std::cin >> numberChar >> name >> gender >> ageChar >> type;
				if (!changeCharToInt(numberChar, number) || !changeCharToInt(ageChar, age)) {
					std::cout << "输入的信息不合法\n";
				}
				else {
					insertInfo(L, location, number, name, gender, age, type);
				}
				sumInfo(L);
			}
			break;
		//---------------------------删除信息-----------------------------------
		case COMMAND_DELETE:
			std::cout << "请输入您要删除的考生的考号：";
			std::cin >> numberChar;
			if (!changeCharToInt(numberChar, number) || number == 0) {
				std::cout << "输入的考号不合法！\n";
				continue;
			}
			deleteInfo(L,number);
			sumInfo(L);
			break;
		//---------------------------查找信息---------------------
		case COMMAND_FIND:
			std::cout << "请输入要查找的考生的考号：";
			std::cin >> numberChar;
			if (!changeCharToInt(numberChar, number)) {
				std::cout << "输入的考号不合法！\n";
				continue;
			}
			findInfo(L,number);
			break;
		//------------修改信息-----------------------------
		case COMMAND_REWRITE:
			std::cout << "请输入你要修改的考生的考号：";
			std::cin >> numberChar;
			if (!changeCharToInt(numberChar, number)) {
				std::cout << "输入的考号不合法！\n";
				continue;
			}
			rewriteInfo(L,number);
			sumInfo(L);
			break;
		//---------统计信息-----------------
		case COMMAND_SUM_UP:
			sumInfo(L);
		//--------退出操作-------------
		case COMMAND_CANCEL:
			destoryInfo(L);
			break;
		default:
			std::cout << "请输入正确的指令";
			break;
		}

		if (command == COMMAND_CANCEL) {
			break;
		}
	}
	return 0;
}