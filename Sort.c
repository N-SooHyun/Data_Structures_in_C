#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <string.h>

/*
	정렬 구현
	1. 선택정렬 2.삽입정렬 3.버블정렬 4.쉘정렬 5.합병정렬 6.퀵정렬 7.히프정렬 8.기수정렬
*/

//선택정렬 - 선형구조
// 한개의 리스트를 왼쪽 오른쪽으로 나누어서 왼쪽은 정렬된쪽 오른쪽은 비정렬된 쪽으로 나누어서 진행
//랜덤 선형구조 배열 생성
int* RandNum_Sort_Arr(int n) {
	int randNum = n;
	srand((unsigned)time(NULL));
	int* arrRandom = (int*)malloc(sizeof(int) * randNum);
	for (int i = 0; i < randNum; i++) {
		arrRandom[i] = (rand() % 100)+1;
	}
	return arrRandom;
}

int* Select_Sort_Arr(int* n_sortArr) {
	int max;
	int min;
	int temp;
	int arr_num;
	for (int i = 0;; i++) {
		if (n_sortArr[i] <= -1) {
			arr_num = i;
			break;
		}
	}

	//1. 최솟값 탐색 2.선택된 인덱스 정렬
	for (int i = 0; i < arr_num-1; i++) {
		min = 1000;
		int mNum = 0;
		int j;
		for (j = i + 1; j < arr_num; j++) {
			if (min > n_sortArr[j]) {
				min = n_sortArr[j];
				mNum = j;
			}
		}
		if (n_sortArr[mNum] < n_sortArr[i]) {
			temp = n_sortArr[mNum];
			n_sortArr[mNum] = n_sortArr[i];
			n_sortArr[i] = temp;
		}
	}
	return n_sortArr;
}

void Select_Sort_main() {
	int randNum = 500;
	int* arrRandom = RandNum_Sort_Arr(randNum);
	int i;
	
	arrRandom = Select_Sort_Arr(arrRandom);

	for (int i = 0; i < randNum; i++) {
		printf("arr[%d] = %d\n", i, arrRandom[i]);
	}
}

//삽입정렬 - 선형구조
//기존에 리스트에 한 인덱스씩 왼쪽으로 삽입시켜 정렬시키는 알고리즘
//선택정렬과 마찬가지로 정렬된 왼쪽리스트, 정렬되지않은 오른쪽 리스트로 논리적으로 한개의 리스트를 나눈후
//정렬된 왼쪽 리스트 첫번째를 기준으로 오른쪽 인덱스 값을 한개씩 차근차근 받아와서 왼쪽 리스트와 비교해 어느위치에 삽입시키는지 판단하는 정렬

int* Insert_Sort_Arr(int* n_sortArr) {
	int arr_num;
	for (int i = 0;; i++) {
		if (n_sortArr[i] <= -1) {
			arr_num = i;
			break;
		}
	}
	int key;
	int i, j;
	for (i = 1; i < arr_num; i++) {
		key = n_sortArr[i];
		for (j = i - 1; j >= 0 && key < n_sortArr[j]; j--) {
			n_sortArr[j + 1] = n_sortArr[j];
		}
		n_sortArr[j+1] = key;
	}
	return n_sortArr;
}

void Insert_Sort_main() {
	int randNum = 5;
	int* arrRandom = RandNum_Sort_Arr(randNum);
	int i;

	arrRandom = Insert_Sort_Arr(arrRandom);
	
	for (int i = 0; i < randNum; i++) {
		printf("arr[%d] = %d\n", i, arrRandom[i]);
	}
}

//버블정렬 - 선형구조
//버블시키는것처럼 01 12 23 이런식으로 인덱스 두개씩 비교해서 왼쪽부터 차례대로 정렬시키는것
//이걸 한번 싸이클을 돌면 스캔1 이라고 하며 이 스캔1로 오른쪽 끝에 최대값을 차곡차곡 쌓아서 정렬을 하는 느낌

void Bubble_Sort_Arr(int* n_sortArr) {
	int arr_num;
	int temp;
	for (int i = 0;; i++) {
		if (n_sortArr[i] <= -1) {
			arr_num = i;
			break;
		}
	}

	for (int i = arr_num - 1; i > 0; i--) {
		for (int j = 0; j < arr_num - 1; j++) {
			if (n_sortArr[j] > n_sortArr[j+1]) {
				temp = n_sortArr[j];
				n_sortArr[j] = n_sortArr[j + 1];
				n_sortArr[j + 1] = temp;
			}
		}
	}
}

void Bubble_Sort_main() {
	int randNum = 50;
	int* arrRandom = RandNum_Sort_Arr(randNum);
	int i;

	Bubble_Sort_Arr(arrRandom);

	for (int i = 0; i < randNum; i++) {
		printf("arr[%d] = %d\n", i, arrRandom[i]);
	}
}

//쉘 정렬 - 선형구조
//삽입정렬에서 간격을 1/2로 줄여서 간격끼리 정렬을 진행함
//예시로 arr[10]이라면 N/2 5의 간격으로 0 5,1 6, 2 7, 3 8, 4 9 이런 간격의 리스트를 논리적으로 만들고
//만들어진 리스트끼리 정렬을 진행하고 전체배열로 만든다음 5의 N/2 2의 간격씩 0 2 4 6 8, 1 3 5 7 9 두개의 리스틑 논리적으로 만들고
//만들어진 리스트들끼리 정렬을 진행 후 전체배열 만들고 이후 간격 1씩 정렬진행

void Shell_Sort_insertion(int* n_sortArr, int first, int last, int gap){//삽입정렬 진행
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = n_sortArr[i];
		for (j = i - gap; j >= first && key < n_sortArr[j]; j = j - gap)
			n_sortArr[j + gap] = n_sortArr[j];
		n_sortArr[j + gap] = key;
	}
}

void Shell_Sort_Arr(int* n_sortArr) {
	int arr_num;
	int temp;
	for (int i = 0;; i++) {
		if (n_sortArr[i] <= -1) {
			arr_num = i;
			break;
		}
	}
	
	int first = 0, last = arr_num - 1, gap, i;
	
	/*
	for (gap = last / 2; gap > 0; gap = gap / 2) {
		for (i = 0; i < gap; i++) {
			Shell_Sort_insertion(n_sortArr, i, last, gap);
		}
	}
	*/

	for (gap = last / 2; gap > 0; gap = gap / 2) {
		for (int i = 0; i < gap; i++) {
			//실제 간격끼리 연결된 인덱스끼리 삽입정렬이 이루어짐
			int front,middle, key;
			for (middle = first + gap; middle <= last; middle += gap) {
				key = n_sortArr[middle];
				for (front = middle - gap; front >= first && n_sortArr[front] > key; front -= gap)
					n_sortArr[front + gap] = n_sortArr[front];
				n_sortArr[front + gap] = key;
			}
		}
	}
}

void Shell_Sort_main() {
	int randNum = 100;
	int* arrRandom = RandNum_Sort_Arr(randNum);
	int i;

	Shell_Sort_Arr(arrRandom);

	for (int i = 0; i < randNum; i++) {
		printf("arr[%d] = %d\n", i, arrRandom[i]);
	}
}


//합병 정렬 - 선형구조
//하나의 리스트를 두 개의 균등한 크기로 분할하여 분할된 부분 리스트를 정렬하고 다시 합하여 전체 리스트 정렬기법
//분할정복 기법에 바탕을 둔다.
//1. 배열을 2개로 나누고 2.이후에도 계속 2개씩 나누고 정렬화시켜 합병을 진행

void Merge_Sort_Arr_Add(int* n_sortArr, int left, int mid, int right) {
	printf("left - %d, mid - %d, right - %d\n", left, mid, right);
	int temp;
	int n1 = mid - left + 1;
	int n2 = right - mid;
	
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	for (int i = 0; i < n1; i++)
		L[i] = n_sortArr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = n_sortArr[mid + 1 + j]; 

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			n_sortArr[k] = L[i];
			i++;
		}
		else {
			n_sortArr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		n_sortArr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		n_sortArr[k] = R[j];
		j++;
		k++;
	}
	free(L);
	free(R);
}

void Merge_Sort_Arr_divide(int* n_sortArr, int left, int right) {//ex arr[6]일경우 left 012, right 345 고로 left=0, right=5
	int temp;
	int mid;
	if (left < right) {
		mid = left + (right - left) / 2;
		//왼쪽 나누기
		Merge_Sort_Arr_divide(n_sortArr, left, mid);
		//오른쪽 나누기
		Merge_Sort_Arr_divide(n_sortArr, mid + 1, right);
		
		//				(0 2 5) 시작(left mid right)
		//		 (0 1 2)				(3 4 5)
		//왼쪽(0 1 0)	(2 2 2)		(3 4 3)	  (5 5 5)
		Merge_Sort_Arr_Add(n_sortArr, left, mid, right);
	}
}

void Merge_Sort_Arr(int* n_sortArr) {
	int arr_num;
	for (int i = 0;; i++) {
		if (n_sortArr[i] <= -1) {
			arr_num = i;
			break;
		}
	}
	
	Merge_Sort_Arr_divide(n_sortArr, 0, arr_num - 1);
}

void Merge_Sort_main() {
	int randNum = 6;
	int* arrRandom = RandNum_Sort_Arr(randNum);
	int i;

	Merge_Sort_Arr(arrRandom);

	for (int i = 0; i < randNum; i++) {
		printf("arr[%d] = %d\n", i, arrRandom[i]);
	}
}


//퀵 정렬 - 선형구조
