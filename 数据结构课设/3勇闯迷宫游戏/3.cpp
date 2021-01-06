//#include"project3.h"
#include<iostream>

#define MARKED 1
#define UNMARKED 0
#define MAX_LENGTH 1000
#define COMMAND_1 1
#define COMMAND_2 2
#define COMMAND_3 3
#define COMMAND_4 4

int moveDir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

class Map {
private:
	char** map; //�洢��ͼ
	int** book; //����߹���·��
	int rLength;//��ͼ�ĳ�
	int cLength;//��ͼ�Ŀ�
	int startX; //��������
	int startY; //���������
	int destX;  //�յ������
	int destY;  //�յ�������
	int length; //���ߵĲ���
	int* resultX;
	int* resultY;
	bool flag;
public:
	Map(int command, int startX, int startY, int destX, int destY);
	~Map();
	void printMap();
	void dfs(int x, int y);
	bool getFlag();
};

Map::Map(int command,int startX, int startY, int destX, int destY) {
	rLength = 7;
	cLength = 7;
	map = new char* [rLength];
	book = new int* [rLength];
	resultX = (int*)malloc(MAX_LENGTH * sizeof(int));
	resultY = (int*)malloc(MAX_LENGTH * sizeof(int));
	for (int i = 0; i < MAX_LENGTH; i++) {
		resultX[i] = 0;
		resultY[i] = 0;
	}
	for (int i = 0; i < rLength; i++) {
		map[i] = new char[cLength];
		book[i] = new int[rLength];
	}
	for (int i = 0; i < rLength; i++) {
		for (int j = 0; j < cLength; j++) {
			book[i][j] = UNMARKED;
		}
	}
	//---------------------------------------
	for (int i = 0; i < cLength; i++) {
		map[0][i] = '#';
		map[6][i] = '#';
	}
	for (int i = 0; i < rLength; i++) {
		map[i][0] = '#';
		map[i][6] = '#';
	}
	switch (command) {
	case COMMAND_1:
		map[1][2] = map[2][2] = map[2][4] = map[2][5] = map[3][4] = map[4][2] = map[5][2] = map[5][4] = '#';
		map[1][1] = map[2][1] = map[3][1] = map[3][2] = map[3][3] = map[4][3] = map[4][4] = map[4][5] = map[5][5] = '.';
		map[1][3] = map[1][4] = map[1][5] = map[2][3] = map[3][5] = map[4][1] = map[5][1] = map[5][3] = '#';
		break;
	case COMMAND_2:
		map[1][2] = map[1][3] = map[1][4] = map[1][5] = map[2][5] = map[3][5] = map[5][4] = '.';
		map[1][1] = map[2][1] = map[3][1] = map[3][2] = map[3][3] = map[4][3] = map[4][4] = map[4][5] = map[5][5] = '.';
		map[2][2] = map[2][3] = map[2][4] = map[3][4] = map[4][2] = map[4][1] = map[5][1] = map[5][2] = map[5][3] = '#';
		break;
	case COMMAND_3:
		map[1][2] = map[1][3] = map[1][4] = map[1][5] = map[2][5] = map[3][5] = map[5][4] = '.';
		map[1][1] = map[3][1] = map[3][2] = map[3][3] = map[4][3] = map[4][4] = map[4][5] = map[5][5] = '.';
		map[2][2] = map[2][3] = map[2][4] = map[3][4] = map[4][2] = map[4][1] = map[5][1] = map[5][2] = map[5][3] = map[2][1] =  '#';
		break;
	case COMMAND_4:
		map[1][2] = map[1][3] = map[1][4] = map[1][5] = map[2][5] = map[3][5] = map[5][4] = '.';
		map[1][1] = map[3][1]  = map[3][3] = map[4][3] = map[4][4] = map[4][5] = map[5][5] = '.';
		map[2][2] = map[2][3] = map[2][4] = map[3][4] = map[4][2] = map[4][1] = map[5][1] = map[5][2] = map[5][3] = map[2][1] = map[3][2] = '#';
		break;
	}
	//-------------------------------------
	this->startX = startX;
	this->startY = startY;
	this->destX = destX;
	this->destY = destY;
	length = 0;
	resultX[0] = startX;
	resultY[0] = startY;
	book[startX][startY] = MARKED;
	flag = false;
}

Map::~Map() {
	for (int i = 0; i < rLength; i++) {
		delete[]map[i];
	}
	for (int i = 0; i < rLength; i++) {
		delete[]book[i];
	}
	free(resultX);
	free(resultY);
}

void Map::printMap() {
	std::cout << "     ";
	for (int i = 0; i < cLength; i++) {
		std::cout << "     " << i << "��";
	}
	std::cout << '\n';
	for (int i = 0; i < rLength; i++) {
		std::cout << i << "��";
		for (int j = 0; j < cLength; j++) {
			std::cout << "       " << map[i][j];
		}
		std::cout << '\n';
	}
}

 void Map::dfs(int x, int y) {
	int curX, curY;
	if (x == destX && y == destY) {
		for (int i = 0; i < length; i++) {
			std::cout << "<" << resultX[i] << "," << resultY[i] << "> ---> ";
		}
		std::cout << "<" << destX << "," << destY << ">\n";
		flag = true;
		return;
	}
	for (int i = 0; i < 4; i++) {
		curX = x + moveDir[i][0];
		curY = y + moveDir[i][1];
		if (curX<0 || curX>=rLength || curY<0 || curY>=cLength) {
			continue;
		}
		if (book[curX][curY] == UNMARKED) {
			if (map[curX][curY] == '.') {

				book[curX][curY] = MARKED;
				length++;
				resultX[length] = curX;
				resultY[length] = curY;

				dfs(curX, curY);

				book[curX][curY] = UNMARKED;
				resultX[length] = 0;
				resultY[length] = 0;
				length--;
			}
		}
	}
	return;
}

 bool Map::getFlag() {
	 return flag;
 }

int main() {
	int startX = 1, startY = 1, destX = 5, destY = 5;
	std::cout << "������������������ͼ�������ǵ�һ����ͼ��\n";
	Map map1(COMMAND_1,startX,startY,destX,destY);
	std::cout << "�Թ�1��ͼ��\n";
	map1.printMap();
	std::cout << "\n\n";
	std::cout << "�Թ�1·����\n";
	map1.dfs(startX, startY);//�����������λ�ô�ϵ�
	if (!map1.getFlag()) {
		std::cout << "û��������·��\n";
	}
	std::cout << "\n---------------------------------------------------------\n";
	//----------------------------------------------------
	Map map2(COMMAND_2, startX, startY, destX, destY);
	std::cout << "�Թ�2��ͼ��\n";
	map2.printMap();
	std::cout << "\n\n";
	std::cout << "�Թ�2·����\n";
	map2.dfs(startX, startY);
	if (!map2.getFlag()) {
		std::cout << "û��������·��\n";
	}
	std::cout << "\n---------------------------------------------------------\n";
	//----------------------------------------------------
	destX = 3; destY = 1;
	Map map3(COMMAND_3, startX, startY, destX, destY);
	std::cout << "�Թ�3��ͼ��\n";
	map3.printMap();
	std::cout << "\n\n";
	std::cout << "�Թ�3·����\n";
	map3.dfs(startX, startY);
	if (!map3.getFlag()) {
		std::cout << "û��������·��\n";
	}
	std::cout << "\n---------------------------------------------------------\n";
	//----------------------------------------------------
	destX = 3; destY = 1;
	Map map4(COMMAND_4, startX, startY, destX, destY);
	std::cout << "�Թ�4��ͼ��\n";
	map4.printMap();
	std::cout << "\n\n";
	std::cout << "�Թ�4·����\n";
	map4.dfs(startX, startY);
	if (!map4.getFlag()) {
		std::cout << "û��������·��\n";
	}
	std::cout << "\n---------------------------------------------------------\n";
	//----------------------------------------------------
	system("pause");
	return 0;
}