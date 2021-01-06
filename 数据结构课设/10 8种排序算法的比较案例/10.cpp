#include<iostream>
#include<ctime>

void initPrint() {
	std::cout << "**          排序算法比较          **\n";
	std::cout << "====================================\n";
	std::cout << "**      请选择要执行的操作：      **\n";
	std::cout << "**        1 --- 冒泡排序          **\n";
	std::cout << "**        2 --- 选择排序          **\n";
	std::cout << "**        3 --- 直接插入          **\n";
	std::cout << "**        4 --- 希尔排序          **\n";
	std::cout << "**        5 --- 快速排序          **\n";
	std::cout << "**        6 --- 堆排序            **\n";
	std::cout << "**        7 --- 归并排序          **\n";
	std::cout << "**        8 --- 基数排序          **\n";
	std::cout << "**        9 --- 退出程序          **\n";
	std::cout << "====================================\n";
}

void bubbleSort(int arr[], int len){
	long long int exchangeNum = 0;
	int* tempArr = new int[len];
	for (int i = 0; i < len; i++) {
		tempArr[i] = arr[i];
	}
	//--------------------------------------------
	clock_t timeStart = clock();
	for (int j = 0; j < len - 1; j++){
		for (int i = 0; i < len - 1 - j; i++) {
			if (tempArr[i] > tempArr[i + 1]){
				std::swap(tempArr[i], tempArr[i + 1]);
				exchangeNum++;
			}
		}
	}
	//---------------------------------------------------------------------------------------------
	clock_t timeEnd = clock();
	std::cout << "冒泡排序所用时间：" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "冒泡排序交换次数：" << exchangeNum << std::endl;
	std::cout << std::endl;
	//for (int i = 0; i < len; i++) {
	//	std::cout << tempArr[i] << ' ';
	//}
	//std::cout << std::endl;
	delete[]tempArr;
}

void slectionSort(int arr[],int len) {
	long long int exchangeNum = 0;
	int* tempArr = new int[len];
	for (int i = 0; i < len; i++) {
		tempArr[i] = arr[i];
	}
	//--------------------------------------------
	clock_t timeStart = clock();
	for (int i = 0; i < len - 1; i++) {
		int min = i;
		for (int j = i + 1; j < len; j++) {
			if (tempArr[j] < tempArr[min]) {
				min = j;
			}
		}
		std::swap(tempArr[i], tempArr[min]);
		exchangeNum++;
	}
	clock_t timeEnd = clock();
	std::cout << "选择排序所用时间：" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "选择排序交换次数：" << exchangeNum << std::endl;
	std::cout << std::endl;
	//for (int i = 0; i < len; i++) {
	//	std::cout << tempArr[i] << ' ';
	//}
	//std::cout << std::endl;
	delete[]tempArr;
}

void insertionSort(int arr[],int len) {
	long long int exchangeNum = 0;
	int* tempArr = new int[len];
	for (int i = 0; i < len; i++) {
		tempArr[i] = arr[i];
	}
	//--------------------------------------------
	clock_t timeStart = clock();
	int preIndex, current;
	for (int i = 1; i < len; i++) {
		preIndex = i - 1;
		current = tempArr[i];
		while (preIndex >= 0 && tempArr[preIndex] > current) {
			tempArr[preIndex + 1] = tempArr[preIndex];
			preIndex--;
		}
		tempArr[preIndex + 1] = current;
		exchangeNum++;
	}
	//----------------------------------------------
	clock_t timeEnd = clock();
	std::cout << "插入排序所用时间：" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "插入排序交换次数：" << exchangeNum << std::endl;
	std::cout << std::endl;
	//for (int i = 0; i < len; i++) {
	//	std::cout << tempArr[i] << ' ';
	//}
	//std::cout << std::endl;
	delete[]tempArr;
}

void shellSort(int arr[], int len) {
	long long int exchangeNum = 0;
	int* tempArr = new int[len];
	for (int i = 0; i < len; i++) {
		tempArr[i] = arr[i];
	}
	//--------------------------------------------
	clock_t timeStart = clock();
	for (int gap = len / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < len; i++) {
			int j;
			int inserted = tempArr[i];
			for (j = i - gap; j >= 0 && inserted < tempArr[j]; j -= gap) {
				tempArr[j + gap] = tempArr[j];
			}
			tempArr[j + gap] = inserted;
			exchangeNum++;
		}
	}
	clock_t timeEnd = clock(); 
	//----------------------------------------------------------------------------------------------
	std::cout << "希尔排序所用时间：" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "希尔排序交换次数：" << exchangeNum << std::endl;
	std::cout << std::endl;
	//for (int i = 0; i < len; i++) {
	//	std::cout << tempArr[i] << ' ';
	//}
	//std::cout << std::endl;
	delete[]tempArr;
}

void quickSort(int tempArr[], int len, int left, int right,long long int& exchangeNum){
	if (left < right) {
		int i = left, j = right, key = tempArr[left];
		while (i < j) {
			while (i < j && tempArr[j] >= key) {
				j--;
			}
			if (i < j) {
				tempArr[i++] = tempArr[j];
			}
			while (i < j && tempArr[i] < key) {
				i++;
			}
			if (i < j) {
				tempArr[j--] = tempArr[i];
			}
		}
		tempArr[i] = key;
		exchangeNum++;
		quickSort(tempArr, len, left, i - 1,exchangeNum);
		quickSort(tempArr, len, i + 1, right,exchangeNum);
	}
}

void quickSortInit(int arr[],int len, int left, int right){
	long long int exchangeNum = 0;
	int* tempArr = new int[len];
	for (int i = 0; i < len; i++) {
		tempArr[i] = arr[i];
	}
	//--------------------------------------------
	clock_t timeStart = clock();
	quickSort(tempArr, len, left, right, exchangeNum);
	clock_t timeEnd = clock();
	//----------------------------------------------------------------------------------------------
	std::cout << "快速排序所用时间：" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "快速排序交换次数：" << exchangeNum << std::endl;
	std::cout << std::endl;
	//for (int i = 0; i < len; i++) {
	//	std::cout << tempArr[i] << ' ';
	//}
	//std::cout << std::endl;
	delete[]tempArr;
}

void heapify(int tempArr[], int i, int len, long long int& exchangeNum) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int maxIndex = i;
	if (left<len && tempArr[left]>tempArr[maxIndex]) {
		maxIndex = left;
	}
	if (right<len && tempArr[right]>tempArr[maxIndex]) {
		maxIndex = right;
	}
	if (maxIndex != i) {
		std::swap(tempArr[i], tempArr[maxIndex]);
		exchangeNum++;
		heapify(tempArr, maxIndex, len,exchangeNum);
	}
}

void heapSortInit(int arr[], int len) {
	long long int exchangeNum = 0;
	int* tempArr = new int[len];
	for (int i = 0; i < len; i++) {
		tempArr[i] = arr[i];
	}
	//--------------------------------------------
	clock_t timeStart = clock();
	int tempLen = len;
	for (int i = tempLen / 2 - 1; i >= 0; i--) {
		heapify(tempArr, i, tempLen,exchangeNum);
	}
	for (int i = tempLen - 1; i > 0; i--) {
		std::swap(tempArr[i], tempArr[0]);
		exchangeNum++;
		tempLen--;
		heapify(tempArr, 0, tempLen,exchangeNum);
	}
	clock_t timeEnd = clock();
	//----------------------------------------------------------------------------------------------
	std::cout << "堆排序所用时间：" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "堆排序交换次数：" << exchangeNum << std::endl;
	std::cout << std::endl;
	//for (int i = 0; i < len; i++) {
	//	std::cout << tempArr[i] << ' ';
	//}
	//std::cout << std::endl;
	delete[]tempArr;
}

void mergeSort(int arr[], int left, int right,long long int& exchangeNum) {
	if (left == right) {
		return;
	}
	int mid = (left + right)/2;
	mergeSort(arr, left, mid,exchangeNum);
	mergeSort(arr, mid + 1, right,exchangeNum);
	//----------------------------------------------------------
	int* temp = new int[right - left + 1];
	int i = 0, p1 = left, p2 = mid + 1, length = right - left + 1;
	while (p1 <= mid && p2 <= right) {
		if (arr[p1] < arr[p2]) {
			temp[i++] = arr[p1++];
		}
		else {
			temp[i++] = arr[p2++];
			exchangeNum++;
		}
	}
	while (p1 <= mid) {
		temp[i++] = arr[p1++];
	}
	while (p2 <= right) {
		temp[i++] = arr[p2++];
	}
	for (i = 0; i < length; i++) {
		arr[left + i] = temp[i];
	}
}

void mergeSortInit(int arr[], int len) {
	long long int exchangeNum = 0;
	int* tempArr = new int[len];
	for (int i = 0; i < len; i++) {
		tempArr[i] = arr[i];
	}
	//--------------------------------------------
	clock_t timeStart = clock();
	mergeSort(tempArr, 0, len - 1,exchangeNum);
	clock_t timeEnd = clock();
	//----------------------------------------------------------------------------------------------
	std::cout << "归并排序所用时间：" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "归并排序交换次数：" << exchangeNum << std::endl;
	std::cout << std::endl;
	//for (int i = 0; i < len; i++) {
	//	std::cout << tempArr[i] << ' ';
	//}
	//std::cout << std::endl;
	delete[]tempArr;
}

void radixSort(int arr[], int len) {
	long long int exchangeNum = 0;
	int* tempArr = new int[len];
	for (int i = 0; i < len; i++) {
		tempArr[i] = arr[i];
	}
	//--------------------------------------------
	clock_t timeStart = clock();
	int maxData = tempArr[0];
	for (int i = 1; i < len; ++i) {
		if (maxData < tempArr[i]) {
			maxData = tempArr[i];
		}
	}
	int d = 1, p = 10;
	while (maxData >= p) {
		maxData /= 10;
		++d;
	}
	//------------------------------
	int* tmp = new int[len];
	int* count = new int[10];
	int k;
	int radix = 1;
	for (int i = 1; i <= d; i++) {
		for (int j = 0; j < 10; j++) {
			count[j] = 0;
		}
		for (int j = 0; j < len; j++) {
			k = (tempArr[j] / radix) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; j++) {
			count[j] = count[j - 1] + count[j];
		}
		for (int j = len - 1; j >= 0; j--) {
			k = (tempArr[j] / radix) % 10;
			tmp[count[k] - 1] = tempArr[j];
			exchangeNum++;
			count[k]--;
		}
		for (int j = 0; j < len; j++) {
			tempArr[j] = tmp[j];
		}
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
	clock_t timeEnd = clock();
	//----------------------------------------------------------------------------------------------
	std::cout << "基数排序所用时间：" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "基数排序交换次数：" << exchangeNum << std::endl;
	std::cout << std::endl;
	//for (int i = 0; i < len; i++) {
	//	std::cout << tempArr[i] << ' ';
	//}
	//std::cout << std::endl;
	delete[]tempArr;
}

int main() {
	initPrint();
	std::cout << "请输入要产生的随机数的个数：";
	int num;
	while (1) {
		std::cin >> num;
		if (std::cin.fail()||num <= 0) {
			std::cout << "请输入正整数\n";
			std::cin.clear();
			std::cin.ignore(sizeof(num), '\n');
			continue;
		}
		break;
	}
	//-----------------------------------------
	int* numArr= new int[num];
	for (int i = 0; i < num; i++) {
		numArr[i] = rand() % num;
	}
	//------------------------------------------
	int command;
	while (1) {
		std::cout << "请选择排序算法：";
		std::cin >> command;
		switch (command){
		case 1:
			bubbleSort(numArr, num);
			break;
		case 2:
			slectionSort(numArr, num);
			break;
		case 3:
			insertionSort(numArr, num);
			break;
		case 4:
			shellSort(numArr, num);
			break;
		case 5:
			quickSortInit(numArr, num, 0, num - 1);
			break;
		case 6:
			heapSortInit(numArr, num);
			break;
		case 7:
			mergeSortInit(numArr, num);
			break;
		case 8:
			radixSort(numArr, num);
			break;
		case 9:
			exit(0);
			break;
		default:
			std::cout << "输入命令不合法，请重新输入！\n";
			break;
		}
	}
	delete[]numArr;
	system("pause");
	return 0;
}