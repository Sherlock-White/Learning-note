//#include"project1.h"
#include<iostream>
#include<cstdlib>
#include<cassert>

//һЩָ��
#define COMMAND_INSERT 1
#define COMMAND_DELETE 2
#define COMMAND_FIND 3
#define COMMAND_REWRITE 4
#define COMMAND_SUM_UP 5
#define COMMAND_CANCEL 0

//��󳤶�
#define MAXSIZE_NAME 10
#define MAXSIZE_TYPE 20
#define MAXSIZE_GENDER 5
#define MAXSIZE_NUMBER 20
#define MAXSIZE_AGE 4
#define MAXSIZE_NUM 50


//����
typedef struct listPoint {
	struct listPoint* next;
	unsigned int number;         //ѧ��
	char name[MAXSIZE_NAME];     //����
	char gender[MAXSIZE_GENDER]; //�Ա�
	unsigned int age;            //����
	char type[MAXSIZE_TYPE];     //��������
}listPoint, * linkList;

unsigned int length;//����ĳ���

bool changeCharToInt(char* string, unsigned int& num);
//��ʼ��,����Ĳ�������������������ͷ���
bool init(linkList& L);
//��ʼ������������
bool initInsert(linkList& L, unsigned int num);
//��λ�β�����Ϣ��i����λ��
bool insertInfo(linkList& L, unsigned int i, unsigned int number, char* name,
	char* gender, unsigned int age, char* type);
//������ɾ����Ϣ
bool deleteInfo(linkList& L, unsigned int number);
//�����Ų�����Ϣ
bool findInfo(linkList L, unsigned int number);
//�޸���Ϣ
bool rewriteInfo(linkList& L, unsigned int number);
//��ӡ���
void sumInfo(linkList& L);
//�ͷ��ڴ�
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
	L = (listPoint*)malloc(sizeof(listPoint)); //����һ��ͷ�ڵ�

	L->number = -1;
	L->age = 0;
	memset(L->name, 0, sizeof(L->name));
	memset(L->type, 0, sizeof(L->type));
	memset(L->gender, 0, sizeof(L->gender));

	if (L == NULL) {
		return false;                          //�ڴ治�㣬����ʧ��
	}
	L->next = NULL;
	return true;
}

bool initInsert(linkList& L, unsigned int num) {
//---------------------------��ʼ׼��--------------------------------------
	char name[MAXSIZE_NAME], type[MAXSIZE_TYPE], gender[MAXSIZE_GENDER], 
		ageChar[MAXSIZE_AGE], numberChar[MAXSIZE_TYPE];
	unsigned int number = 0, age = 0;
	memset(name, 0, sizeof(name));
	memset(type, 0, sizeof(type));
	memset(gender, 0, sizeof(gender));
	memset(ageChar, 0, sizeof(ageChar));
	memset(numberChar, 0, sizeof(numberChar));
//---------------------------��������-------------------------------------
	for (unsigned int i = 1; i <= num; i++) {
		std::cin >> numberChar >> name >> gender >> ageChar >> type;
		if (!changeCharToInt(numberChar, number)) {
			std::cout << "�����ѧ�Ų��Ϸ�\n";
			return false;
		}
		if (!changeCharToInt(ageChar, age)) {
			std::cout << "��������䲻�Ϸ�\n";
			return false;
		}
		insertInfo(L,i,number,name,gender,age,type);
	}
	return true;
}

bool insertInfo(linkList& L, unsigned int i, unsigned int number, char* name,
	           char* gender, unsigned int age, char* type) {
//---------------------------�ڴ����----------------------------
	listPoint* p;    //pָ��ǰɨ�赽�Ľ��
	unsigned int locate = 0;  //pָ����ǵڼ������
	p = L;           //pָ��ͷ�ڵ�

	while (p != NULL && locate < i - 1) {//��pָ��i-1�����
		p = p->next;
		locate++;
	}
	listPoint* temp = (listPoint*)malloc(sizeof(listPoint));
	if (temp == NULL) {
		std::cout << "�ڴ����ʧ�ܣ�\n";
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
		if (deleteInfo == NULL) {                //��ΪpҪָ������ҪѰ�ҵĽ���ǰһ�����
			std::cout << "û�в��ҵ�����";
			return false;
		}
		else {
			if (deleteInfo->number == number) {  //����ҵ���
				p->next = deleteInfo->next;
				std::cout << "ɾ���˿���Ϊ" << number << "��ѧ����Ϣ\n";
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
			std::cout << "���޴���\n";
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
			std::cout << "���޴���\n";
			return false;
		}
		else {
			if (p->number == number) {
				std::cout << "�������ͬѧ�µĿ��š��������Ա����估�������\n";
				std::cin >> numChar >> name >> gender >> ageChar >> type;
				if (!changeCharToInt(numChar, num)) {
					std::cout << "�����ѧ�Ų��Ϸ�\n";
					return false;
				}
				if (!changeCharToInt(ageChar, age)) {
					std::cout << "��������䲻�Ϸ�\n";
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
	std::cout << "\n\n���� ���� �Ա� ���� �������\n";
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
//--------------------------��ʼ������-----------------------------------------
	length = 0;
	std::cout << "�����뽨��������Ϣϵͳ��\n" << "�����뿼��������";
	unsigned int num = 0;        //ѧ������
	char numChar[MAXSIZE_NUM];
	memset(numChar, 0, sizeof(numChar));
	std::cin >> numChar;
	if (!changeCharToInt(numChar, num)) {
		std::cout << "�����ѧ���������Ϸ�\n";
		return -1;
	}
	if (num > 0) {
		std::cout << "���������뿼���Ŀ��š��������Ա����估�������(�ÿո����)\n";
	}
	linkList L;              //һ��ָ�������ָ��
	init(L);
	initInsert(L, num);
//--------------------------��������-------------------------------------------
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
		std::cout << "\n��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������\n";
		std::cin >> command;
		switch (command){
		//-----------------------------������Ϣ------------------------------------------------
		case COMMAND_INSERT:
			std::cout << "��������Ҫ����Ŀ�����λ��:";
			std::cin >> locationChar;
			if (!changeCharToInt(locationChar, location)) {
				std::cout << "�����λ�ò��Ϸ���\n";
				continue;
			}
			if (location < 1 || location > length + 1) {
				std::cout << "�����λ�ò��Ϸ���\n";
				continue;
			}
			else {
				std::cout << "����������Ҫ����Ŀ����Ŀ��š��������Ա����估�������\n";
				std::cin >> numberChar >> name >> gender >> ageChar >> type;
				if (!changeCharToInt(numberChar, number) || !changeCharToInt(ageChar, age)) {
					std::cout << "�������Ϣ���Ϸ�\n";
				}
				else {
					insertInfo(L, location, number, name, gender, age, type);
				}
				sumInfo(L);
			}
			break;
		//---------------------------ɾ����Ϣ-----------------------------------
		case COMMAND_DELETE:
			std::cout << "��������Ҫɾ���Ŀ����Ŀ��ţ�";
			std::cin >> numberChar;
			if (!changeCharToInt(numberChar, number) || number == 0) {
				std::cout << "����Ŀ��Ų��Ϸ���\n";
				continue;
			}
			deleteInfo(L,number);
			sumInfo(L);
			break;
		//---------------------------������Ϣ---------------------
		case COMMAND_FIND:
			std::cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
			std::cin >> numberChar;
			if (!changeCharToInt(numberChar, number)) {
				std::cout << "����Ŀ��Ų��Ϸ���\n";
				continue;
			}
			findInfo(L,number);
			break;
		//------------�޸���Ϣ-----------------------------
		case COMMAND_REWRITE:
			std::cout << "��������Ҫ�޸ĵĿ����Ŀ��ţ�";
			std::cin >> numberChar;
			if (!changeCharToInt(numberChar, number)) {
				std::cout << "����Ŀ��Ų��Ϸ���\n";
				continue;
			}
			rewriteInfo(L,number);
			sumInfo(L);
			break;
		//---------ͳ����Ϣ-----------------
		case COMMAND_SUM_UP:
			sumInfo(L);
		//--------�˳�����-------------
		case COMMAND_CANCEL:
			destoryInfo(L);
			break;
		default:
			std::cout << "��������ȷ��ָ��";
			break;
		}

		if (command == COMMAND_CANCEL) {
			break;
		}
	}
	return 0;
}