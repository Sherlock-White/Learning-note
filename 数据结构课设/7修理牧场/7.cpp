#include<iostream>
//class Node {
//private:
//	int data;
//	Node* left;
//	Node* right;
//public:
//	Node() {
//		data = NULL;
//		left = NULL;
//		right = NULL;
//	}
//	Node(int value, Node* left, Node* right) {
//		data = value;
//		this->left = left;
//		this->right = right;
//	}
//	int getData() {
//		return data;
//	}
//	Node* getLeft() {
//		return left;
//	}
//	Node* getRight() {
//		return right;
//	}
//	void changeData(int value){
//		data = value;
//	}
//	void changeLeft(Node* p) {
//		left = p;
//	}
//	void changeRight(Node* p) {
//		right = p;
//	}
//};

class MinHeap{
private:
	int* heap;
	int MaxHeapSize;
	int CurrentSize;
	void FilterDown(int start, int endOfHeap);
	void FilterUp(int i);
public:
	MinHeap() {
		heap = NULL;
		MaxHeapSize = 0;
		CurrentSize = 0;
	}
	MinHeap(int arr[],int size) {
		heap = (int*)malloc(size * sizeof(int));
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
	~MinHeap(){
		if (heap != NULL) {
			free(heap);
		}
	}
	bool Insert(const int& x);
	bool RemoveMin(int& x);
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

void MinHeap::FilterDown(int start, int endOfHeap) {
	int i = start, j = 2 * i + 1;
	int temp = heap[i];
	while (j <= endOfHeap) {
		//两子女中选小的
		if (j<endOfHeap && heap[j]>heap[j + 1]) {
			j++;
		}
		if (temp <= heap[j]) {
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

void MinHeap::FilterUp(int start) {
	int j = start, i = (j - 1) / 2;
	int temp = heap[j];
	while (j > 0) {
		if (heap[i] <= temp) {
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

bool MinHeap::Insert(const int& x) {
	if (CurrentSize == MaxHeapSize) {
		std::cout << "堆已满" << std::endl;
		return false;
	}
	heap[CurrentSize] = x;
	FilterUp(CurrentSize);
	CurrentSize++;
	return true;
}

bool MinHeap::RemoveMin(int& x) {
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

//------------------------------------------------

int main() {
	int num;
	while (1) {
		std::cout << "----------------------------\n";
		std::cout << "请输入要将木头锯成几块：";
		std::cin >> num;
		if (std::cin.fail()|| num <= 0 ) {
			std::cout << "输入不合法，请输入正整数\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}
		break;
	}
	//---------------------------------------------
	int* arr = (int*)malloc(num * sizeof(int));
	int temp;
	bool flag = true;
	while (1) {
		std::cout << "请输入每一段木块的长度：\n";
		for (int i = 0; i < num; i++) {
			std::cin >> temp;
			if (std::cin.fail() || temp <= 0) {
				std::cout << "输入不合法，请重新输入正整数序列\n";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				flag = false;
				break;
			}
			if (arr != NULL) {
				arr[i] = temp;
			}
		}
		if (flag) {
			break;
		}
		else {
			flag = true;
		}
	}
	//--------------------------------------------
	MinHeap minHeap(arr, num);
	int sum = 0;
	int tempNum;
	int min1, min2;
	if(num != 1) {
		while (!minHeap.isEmpty()) {
			minHeap.RemoveMin(min1);
			if (!minHeap.isEmpty()) {
				minHeap.RemoveMin(min2);
				tempNum = min1 + min2;
				sum += tempNum;
				minHeap.Insert(tempNum);
			}
		}
	}
	std::cout << "最小开销为:" << sum << std::endl;
	free(arr);
	system("pause");
	return 0;
}