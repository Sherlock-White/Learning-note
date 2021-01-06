#include<iostream>
#include<ctime>

void initPrint() {
	std::cout << "**          �����㷨�Ƚ�          **\n";
	std::cout << "====================================\n";
	std::cout << "**      ��ѡ��Ҫִ�еĲ�����      **\n";
	std::cout << "**        1 --- ð������          **\n";
	std::cout << "**        2 --- ѡ������          **\n";
	std::cout << "**        3 --- ֱ�Ӳ���          **\n";
	std::cout << "**        4 --- ϣ������          **\n";
	std::cout << "**        5 --- ��������          **\n";
	std::cout << "**        6 --- ������            **\n";
	std::cout << "**        7 --- �鲢����          **\n";
	std::cout << "**        8 --- ��������          **\n";
	std::cout << "**        9 --- �˳�����          **\n";
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
	std::cout << "ð����������ʱ�䣺" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "ð�����򽻻�������" << exchangeNum << std::endl;
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
	std::cout << "ѡ����������ʱ�䣺" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "ѡ�����򽻻�������" << exchangeNum << std::endl;
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
	std::cout << "������������ʱ�䣺" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "�������򽻻�������" << exchangeNum << std::endl;
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
	std::cout << "ϣ����������ʱ�䣺" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "ϣ�����򽻻�������" << exchangeNum << std::endl;
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
	std::cout << "������������ʱ�䣺" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "�������򽻻�������" << exchangeNum << std::endl;
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
	std::cout << "����������ʱ�䣺" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "�����򽻻�������" << exchangeNum << std::endl;
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
	std::cout << "�鲢��������ʱ�䣺" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "�鲢���򽻻�������" << exchangeNum << std::endl;
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
	std::cout << "������������ʱ�䣺" << 1000 * (timeEnd - timeStart) / (long)CLOCKS_PER_SEC << "ms\n";
	std::cout << "�������򽻻�������" << exchangeNum << std::endl;
	std::cout << std::endl;
	//for (int i = 0; i < len; i++) {
	//	std::cout << tempArr[i] << ' ';
	//}
	//std::cout << std::endl;
	delete[]tempArr;
}

int main() {
	initPrint();
	std::cout << "������Ҫ������������ĸ�����";
	int num;
	while (1) {
		std::cin >> num;
		if (std::cin.fail()||num <= 0) {
			std::cout << "������������\n";
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
		std::cout << "��ѡ�������㷨��";
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
			std::cout << "��������Ϸ������������룡\n";
			break;
		}
	}
	delete[]numArr;
	system("pause");
	return 0;
}