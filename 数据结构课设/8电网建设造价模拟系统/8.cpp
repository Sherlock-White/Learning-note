#include<iostream>
#include<string>

void initPrint() {
	std::cout << "**          电网造价模拟系统            **\n";
	std::cout << "==========================================\n";
	std::cout << "**        请选择要执行的操作：          **\n";
	std::cout << "**        A --- 创建电网顶点            **\n";
	std::cout << "**        B --- 添加电网的边            **\n";
	std::cout << "**        C --- 构造最小生成树          **\n";
	std::cout << "**        D --- 显示最小生成树          **\n";
	std::cout << "**        E --- 退出程序                **\n";
	std::cout << "==========================================\n";
}

const int DefaultVertices = 30;

class Edge{
private:
	int dest;
	int cost;
	Edge* link;
public:
	friend class Graph;
	Edge() {
		dest = 0;
		cost = 0;
		link = NULL;
	}
	Edge(int dest, int cost, Edge* edge) {
		this->dest = dest;
		this->cost = cost;
		link = edge;
	}
};

class Node{
private:
	char data[20];
	Edge* adj;
public:
	friend class Graph;
	Node() {
		memset(data, '0', 20);
		adj = NULL;
	}
	Node(char* data, Edge* adj) {
		strcpy_s(this->data, data);
		this->adj = adj;
	}
	char* getData(){
		return data;
	}
};

class MSTEdgeNode {
	friend class Graph;
	friend class MinHeap;
private:
	int tail, head;
	int key;
public:
	friend class MinSpanTree;
	MSTEdgeNode() {
		tail = -1;
		head = -1;
		key = 0;
	}
	MSTEdgeNode(int tail, int head, int key) {
		this->tail = tail;
		this->head = head;
		this->key = key;
	}
	int getId() {
		return head;
	}
	int getKey() {
		return key;
	}
	int getTail() {
		return tail;
	}
};

class MinSpanTree {
	friend class Graph;
private:
	MSTEdgeNode* edgeValue;
	int maxSize;
	int curSize;
public:
	MinSpanTree() {
		edgeValue = NULL;
		maxSize = 0;
		curSize = 0;
	}
	~MinSpanTree() {
		free(edgeValue);
	}
	void setMST(int nodeNum) {
		int edgeNum = nodeNum * (nodeNum - 1) / 2;
		edgeValue = (MSTEdgeNode*)malloc(edgeNum * sizeof(MSTEdgeNode));
		maxSize = edgeNum;
		curSize = 0;
	}
	bool insert(MSTEdgeNode& item) {
		if (curSize < maxSize) {
			edgeValue[curSize] = item;
			curSize++;
			return true;
		}
		else {
			std::cout << "插入失败！" << std::endl;
			return false;
		}
	}
	MSTEdgeNode* getNode() {
		return edgeValue;
	}
};

class MinHeap {
private:
	MSTEdgeNode* heap;
	int MaxHeapSize;
	int CurrentSize;
	void FilterDown(int start, int endOfHeap) {
		int i = start, j = 2 * i + 1;
		MSTEdgeNode temp = heap[i];
		while (j <= endOfHeap) {
			//两子女中选小的
			if (j < endOfHeap && heap[j].key > heap[j + 1].key) {
				j++;
			}
			if (temp.key <= heap[j].key) {
				break;
			}
			else {
				heap[i] = heap[j];
				i = j;
				j = 2 * j + 1;
			}
			heap[i] = temp;
		}
	}
	void FilterUp(int start) {
		int j = start, i = (j - 1) / 2;
		MSTEdgeNode temp = heap[j];
		while (j > 0) {
			if (heap[i].key <= temp.key) {
				break;
			}
			else {
				heap[j] = heap[i];
				j = i;
				i = (i - 1) / 2;
			}
			heap[j] = temp;
		}
	}
public:
	MinHeap() {
		heap = NULL;
		MaxHeapSize = 0;
		CurrentSize = 0;
	}
	MinHeap(int size) {
		heap = (MSTEdgeNode*)malloc(size * sizeof(MSTEdgeNode));
		MaxHeapSize = size;
		CurrentSize = 0;
	}
	MinHeap(MSTEdgeNode arr[], int size) {
		heap = (MSTEdgeNode*)malloc(size * sizeof(MSTEdgeNode));
		for (int i = 0; i < size; i++) {
			if (heap != NULL) {
				heap[i] = arr[i];
			}
		}
		MaxHeapSize = size;
		CurrentSize = size;
		//------------------------------
		int currentPos = (CurrentSize - 2) / 2;
		while (currentPos >= 0) {
			FilterDown(currentPos, CurrentSize - 1);
			currentPos--;
		}
	}
	~MinHeap() {
		if (heap != NULL) {
			free(heap);
		}
	}
	bool Insert(const MSTEdgeNode& x) {
		if (CurrentSize == MaxHeapSize) {
			std::cout << "堆已满" << std::endl;
			return false;
		}
		heap[CurrentSize] = x;
		FilterUp(CurrentSize);
		CurrentSize++;
		return true;
	}
	bool RemoveMin(MSTEdgeNode& x) {
		if (!CurrentSize) {
			std::cout << "堆已空" << std::endl;
			return false;
		}
		x = heap[0];
		heap[0] = heap[CurrentSize - 1];
		CurrentSize--;
		FilterDown(0, CurrentSize - 1);
		return true;
	}
	int isEmpty()const {
		return CurrentSize == 0;
	}
	int isFull()const {
		return CurrentSize == MaxHeapSize;
	}
	void MakeEmpty() {
		CurrentSize = 0;
	}
};

class Graph{
	friend class MinSpanTree;
private:
	Node* NodeTable;
	bool* Vmst;
	int nodeNum;
	int edgeNum;
public:
	Graph() {
		NodeTable = NULL;
		nodeNum = 0;
		edgeNum = 0;
		Vmst = NULL;
	}
	~Graph() {
		Edge* p;
		Edge* freeEdge;
		for (int i = 0; i < nodeNum; i++) {
			p = NodeTable[i].adj;
			while (p != NULL) {
				freeEdge = p;
				p = p->link;
				free(freeEdge);
			}
		}
		free(NodeTable);
		delete[]Vmst;
	}
	void setGraph() {
		NodeTable = (Node*)malloc(nodeNum * sizeof(Node));
		if (NodeTable == NULL) {
			std::cerr << "存储分配错误！" << std::endl;
			exit(1);
		}
		this->nodeNum = 0;
		edgeNum = 0;
	}
	char* getName(int i) {
		return NodeTable[i].data;
	}
	Node* getNodeTable() {
		return NodeTable;
	}
	int getWeight(int v1, int v2) {
		if (isValid(v1) && isValid(v2)) {
			Edge* p = NodeTable[v1].adj;
			while (p != NULL && p->dest != v2) {
				p = p->link;
			}
			if (p != NULL) {
				return p->cost;
			}
			return -1;
		}
		else {
			std::cout << "越界!" << std::endl;
			return 0;
		}
	}
	bool insertNode(const Node& newNode) {
		NodeTable[nodeNum] = newNode;
		nodeNum++;
		return true;
	}
	bool insertEdge(int v1,int v2, int cost) {
		if (isValid(v1) && isValid(v2)) {
			Edge* p = NodeTable[v1].adj;
			Edge* newV1 = (Edge*)malloc(sizeof(Edge));
			if (newV1 != NULL) {
				newV1->cost = cost;
				newV1->dest = v2;
				newV1->link = NULL;
			}
			//------------------------------------------
			if (p == NULL) {
				NodeTable[v1].adj = newV1;
			}
			else {
				while (p->link != NULL) {
					if (p->dest == v2) {
						std::cout << v1 << "到" << v2 << "之间的边已经存在！" << std::endl;
						free(newV1);
						return false;
					}
					p = p->link;
				}
				p->link = newV1;
			}
			return true;
		}
		else {
			std::cout << "越界！不存在这样的点！" << std::endl;
			return false;
		}
	}
	int getFirstNeighbor(int v) {
		if (isValid(v)) {
			Edge* p = NodeTable[v].adj;
			if (p != NULL) {
				return p->dest;
			}
			return -1;
		}
		else {
			std::cout << "越界!不存在" << v << "点" << std::endl;
			return -1;
		}
	}
	int getNextNeighbor(int v, int w) {
		if (isValid(v)) {
			Edge* p = NodeTable[v].adj;
			while (p != NULL && p->dest != w) {
				p = p->link;
			}
			if (p != NULL && p->link != NULL) {
				return p->link->dest;
			}
			return -1;
		}
		else {
			std::cout << "越界!不存在" << v << "点" << std::endl;
			return -1;
		}
	}
	bool isValid(int v) {
		return (v >= 0 && v < nodeNum) ? true : false;
	}
	int findID(char* name) {
		for (int i = 0; i < nodeNum; i++) {
			if (!strcmp(NodeTable[i].data, name)) {
				return i;
			}
		}
		return -1;
	}
	void edgeNumPlus() {
		edgeNum++;
	}
	void prim(Graph& graph, char* u0, MinSpanTree& MST) {
		MSTEdgeNode ed;
		int v, count;
		int n = nodeNum;
		int m = edgeNum;
		int u = findID(u0);
		MinHeap minHeap(edgeNum);
		Vmst = new bool[n];
		for (int i = 0; i < n; i++) {
			Vmst[i] = false;
		}
		Vmst[u] = true;
		count = 1;
		do {
			v = graph.getFirstNeighbor(u);
			while (v != -1) {
				if (Vmst[v] == false) {
					ed.tail = u;
					ed.head = v;
					ed.key = graph.getWeight(u, v);
					minHeap.Insert(ed);
				}
				v = graph.getNextNeighbor(u, v);
			}
			while (!minHeap.isEmpty() && count < n) {
				minHeap.RemoveMin(ed);
				if (!Vmst[ed.head]) {
					MST.insert(ed);
					u = ed.head;
					Vmst[u] = true;
					count++;
					break;
				}
			}
		} while (count < n);
	}
};

int main() {
	initPrint();
	int num, id;
	Graph graph;
	MinSpanTree MST;
	int cmdNum[4] = { 0 };
	int count = 0;
	while (1) {
		std::cout << "--------------------------\n";
		std::cout << "请选择操作:";
		char cmd;
		std::cin >> cmd;
		switch (cmd) {
		case 'A':
		case 'a':
			cmdNum[0]++;
			std::cout << "请输入顶点的个数：";
			std::cin >> num;
			if (std::cin.fail()||num <= 0) {
				std::cout << "输入不合法，请输入正整数！" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				continue;
			}
			//-----------------------------------------
			graph.setGraph();
			char tempName[20];
			std::cout << "请依次输入各顶点的名称：";
			for (int i = 0; i < num; i++) {
				std::cin >> tempName;
				Node newNode(tempName, NULL);
				graph.insertNode(newNode);
			}
			break;
		case 'B':
		case 'b':
			cmdNum[1]++;
			if (cmdNum[0] == 0) {
				std::cout << "请先进行A创建电网操作！\n";
				continue;
			}
			while (1) {
				std::cout << "请输入两个顶点及边：";
				char nodeName1[20], nodeName2[20];
				int weight;
				std::cin >> nodeName1;
				if (!strcmp(nodeName1, "exit")||count > num*(num-1)/2) {
					break;
				}
				std::cin >> nodeName2;
				int id1 = graph.findID(nodeName1);
				int id2 = graph.findID(nodeName2);
				if (!(graph.isValid(id1) && graph.isValid(id2))) {
					std::cout << "查找不到该顶点，请重新输入" << std::endl;
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					continue;
				}
				std::cin >> weight;
				if ( weight < 0||std::cin.fail()) {
					std::cout << "边长请输入正整数" << std::endl;
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					continue;
				}
				//------------------------------------------------------
				graph.insertEdge(id1, id2, weight);
				graph.insertEdge(id2, id1, weight);
				graph.edgeNumPlus();
				count++;
			}
			break;
		case 'C':
		case 'c':
			cmdNum[2]++;
			if (cmdNum[0] == 0 || cmdNum[1] == 0) {
				std::cout << "请先完成A和B的操作！\n";
				continue;
			}
			std::cout << "请输入起始顶点：";
			char nodeName[20];
			std::cin >> nodeName;
			id = graph.findID(nodeName);
			if (!graph.isValid(id)) {
				std::cout << "查找不到该顶点，请重新输入" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				continue;
			}
			//-------------------------------------------------------
			MST.setMST(num);
			graph.prim(graph, nodeName, MST);
			std::cout << "生成prim最小生成树！" << std::endl;
			break;
		case 'D':
		case 'd':
			cmdNum[3]++;
			if (cmdNum[0] == 0 || cmdNum[1] == 0 || cmdNum[2] == 0) {
				std::cout << "请先完成A、B、C的操作！\n";
				continue;
			}
			std::cout << "最小生成树的顶点及边为：" << std::endl;
			for (int i = 0; i < num - 1; i++) {
				MSTEdgeNode node = MST.getNode()[i];
				int id = node.getId();
				int id2 = node.getTail();
				char* name = graph.getNodeTable()[id % num].getData();
				char* name2 = graph.getNodeTable()[id2 % num].getData();
				std::cout << name << "-<" << node.getKey() << ">->" << name2 << std::endl;
			}
			break;
		case'E':
		case'e':
			exit(0);
			break;
		default:
			std::cout << "找不到该命令，请重新输入！\n";
			break;
		}
	}
	system("pause");
	return 0;
}