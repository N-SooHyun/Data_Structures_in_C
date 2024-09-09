#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <string.h>

/*
	���� ����
	1. �������� 2.�������� 3.�������� 4.������ 5.�պ����� 6.������ 7.�������� 8.�������
*/

//�������� - ��������
// �Ѱ��� ����Ʈ�� ���� ���������� ����� ������ ���ĵ��� �������� �����ĵ� ������ ����� ����
//���� �������� �迭 ����
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

	//1. �ּڰ� Ž�� 2.���õ� �ε��� ����
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

//�������� - ��������
//������ ����Ʈ�� �� �ε����� �������� ���Խ��� ���Ľ�Ű�� �˰���
//�������İ� ���������� ���ĵ� ���ʸ���Ʈ, ���ĵ������� ������ ����Ʈ�� �������� �Ѱ��� ����Ʈ�� ������
//���ĵ� ���� ����Ʈ ù��°�� �������� ������ �ε��� ���� �Ѱ��� �������� �޾ƿͼ� ���� ����Ʈ�� ���� �����ġ�� ���Խ�Ű���� �Ǵ��ϴ� ����

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

//�������� - ��������
//�����Ű�°�ó�� 01 12 23 �̷������� �ε��� �ΰ��� ���ؼ� ���ʺ��� ���ʴ�� ���Ľ�Ű�°�
//�̰� �ѹ� ����Ŭ�� ���� ��ĵ1 �̶�� �ϸ� �� ��ĵ1�� ������ ���� �ִ밪�� �������� �׾Ƽ� ������ �ϴ� ����

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

//�� ���� - ��������
//�������Ŀ��� ������ 1/2�� �ٿ��� ���ݳ��� ������ ������
//���÷� arr[10]�̶�� N/2 5�� �������� 0 5,1 6, 2 7, 3 8, 4 9 �̷� ������ ����Ʈ�� �������� �����
//������� ����Ʈ���� ������ �����ϰ� ��ü�迭�� ������� 5�� N/2 2�� ���ݾ� 0 2 4 6 8, 1 3 5 7 9 �ΰ��� �����z �������� �����
//������� ����Ʈ�鳢�� ������ ���� �� ��ü�迭 ����� ���� ���� 1�� ��������

void Shell_Sort_insertion(int* n_sortArr, int first, int last, int gap){//�������� ����
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
			//���� ���ݳ��� ����� �ε������� ���������� �̷����
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


//�պ� ���� - ��������
//�ϳ��� ����Ʈ�� �� ���� �յ��� ũ��� �����Ͽ� ���ҵ� �κ� ����Ʈ�� �����ϰ� �ٽ� ���Ͽ� ��ü ����Ʈ ���ı��
//�������� ����� ������ �д�.
//1. �迭�� 2���� ������ 2.���Ŀ��� ��� 2���� ������ ����ȭ���� �պ��� ����

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

void Merge_Sort_Arr_divide(int* n_sortArr, int left, int right) {//ex arr[6]�ϰ�� left 012, right 345 ��� left=0, right=5
	int temp;
	int mid;
	if (left < right) {
		mid = left + (right - left) / 2;
		//���� ������
		Merge_Sort_Arr_divide(n_sortArr, left, mid);
		//������ ������
		Merge_Sort_Arr_divide(n_sortArr, mid + 1, right);
		
		//				(0 2 5) ����(left mid right)
		//		 (0 1 2)				(3 4 5)
		//����(0 1 0)	(2 2 2)		(3 4 3)	  (5 5 5)
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


//�� ���� - ��������
