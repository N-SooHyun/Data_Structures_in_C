#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
#include <math.h>
#include<time.h>

/*
	Ʈ�� ���� ������ ����
	���������δ� �������� ����������
	�������δ� ���� ���������̴�.
	<Ʈ�� ����>
	�Ϲ�Ʈ��-�ڽ� ����� ũ�Ⱑ �������� �ʴ� Ʈ��
	����(Binary)Ʈ��-�ڽ� ����� ũ�Ⱑ �ִ� 2���� Ʈ��
	����(Ternary)Ʈ��-�ڽ� ����� ũ�Ⱑ �ִ� 3���� Ʈ��
	��� 4 5 6���ε� ���� ����
	<Ʈ�� ���>
	����(����), �θ�-�ڽ�(root,�ڽ�,���� ��), �ܸ����(�ڽĳ�尡���³��), ��ܸ�(�ݴ�)
	<���� Ʈ�� Ư¡ or Ʈ���� ������ Ư¡>
	root�� �Ѱ������ǵǸ� �θ���� �ݵ�� �Ѱ��̱⿡
	��尳�� - 1 = ����
	���� == �ּ� ��� ����, ����Ʈ���ΰ�� �ִ����� 2^����-1�� ����
	���� : ����3¥�� ����Ʈ�� �ִ��� = (2^1-1)+(2^2-1)+(2^3-1)=(1)+(2)+(4)=7

	<�ڵ屸��>
	�迭ǥ���� - ���������� ���� ������ ���
	arr[7]�� �ִٰ� �����ҽ� arr[0]-root, arr[1,2]-root�ڽ�, arr[3,4]-1���ڽ�,arr[5,6]-2���ڽ�
	3���� ������ ����Ǿ� �������� ������
	�ڽ�(5)�� �θ���� ã�� ���� - i=5  i-1/2 = (5-1/2=2)  or i=6  i-1/2 = (6-1/2=2)
	�ڽ�(3)�� ���� �ڽ��� ã�°��� - i=3	2i + 1
	�ڽ���(3) ������ �ڽ��� ã�°��� - i=3  2i +2
	��ũǥ���� - ��ũ����Ʈ�� ����ϰ� ����ü�� �����ڽĳ�� �������ڽĳ���� ����ü�����͸� Ȱ��
*/

/*-------------------------�迭ǥ�������� ������ search Ž�� Ʈ��-----------------------------*/
// 0~100������ ���� 7���� ������ ǥ��
#define MAX_SIZE 15
int tree[MAX_SIZE];

void Array_Tree_init() {//Ʈ�� �ʱ�ȭ
	for (int i = 0; i < MAX_SIZE; i++)
		tree[i] = -1;
}

int  Array_Tree_insert(int data, int index) {
	if (index >= MAX_SIZE){
		printf("Ʈ���� ���� á���ϴ�. %d���� ������ �Ұ����մϴ�.\n",data);
		return;
	}

	//���Խ� ������ ������ �������� ū���̶�� ��Ģ�� ���صΰ� ���Խ� ��͸� ���ؼ� ����
	if (tree[index] == -1) {
		tree[index] = data;
	}
	else if (data < tree[index]) {
		Array_Tree_insert(data, 2 * index + 1);
		//���� ����� ������ ������ �������� �� ���� ���� 2(�������)*(��������ġ)+1 = 2i+1
	}
	else if (data > tree[index]) {
		Array_Tree_insert(data, 2 * index + 2);
		//���� ����� ������ ũ�� ���������� �� ���� ���� 2(�������)*(��������ġ)+2 = 2i+2
	}
	return;
}

int Array_Tree_level(int index) {
	//����� ������ �˸� ����(��)�� �� �� ����
	//���̸� �˸� ����� ������ �� �� ���� 2^����-1
	//����=h      h=log2(n+1)-1  = 2 ��� 0 1 2 -> 3���̵�(n=7�Ͻ�)
	//n=8�Ͻÿ��� 4���̵Ǿ���ϳ� h=log2(8+1)-1 = 2�� �� ������ ��������Ʈ���� �� ä������ �ʾƼ���n=15���Ǹ�h=3�̵�
	//���� ������ �ȴٸ� Ư�� �������� �ִ� ����� ������ �� �� ����(�ŵ�����������)
	//h=2�ΰ�� 2^0 = 1(root�Ѱ�), 2^1=2(1�� �ڽ�2��), 2^2(2�� �ڽ� 4��)
	//log��������� 2^n = index;�̴ϱ� 
	// 2^n/2 = index/2;�ϸ� n�� ã�� �� �ִ�. �̰� log2(n) = index; ��
	double level = log2(index + 1) - 1;
	int floor = (int)ceil(level);//�ø�����
	return floor;//���� ��ȯ
}

void Array_Tree_print(int index) {
	printf("���� Ž�� Ʈ�� �迭ǥ����\n");
	int level = Array_Tree_level(index);
	int idx = 0;
	printf("%d\n", level);
	for (int i = 0; i <= level; i++) {
		int start_index = (int)pow(2,i) - 1; //level�� ���۳�� pow�����Լ� 2^i
		int end_index = start_index + (int)pow(2, i);
		printf("%d�� ��� [ ", i);
		for (int j = start_index; j < end_index && j < MAX_SIZE; j++) {
			if (tree[j] != -1)
				printf("%d ", tree[j]);
			else
				printf("NL ");
		}
		printf("]\n");
	}
}

void Array_Tree_main() {
	srand((unsigned)time(NULL));
	int randNum;	//Ʈ�� ��� ����
	int* arrRandom;
	printf("����� ���� ���� ����(%d ����) : ", MAX_SIZE);
	scanf_s("%d", &randNum);

	if (randNum > MAX_SIZE) {
		printf("������ �ʹ� ���ƿ�.");
		return;
	}

	arrRandom = (int*)malloc(randNum * sizeof(int));
	Array_Tree_init();
	for (int i = 0; i < randNum; i++) {
		arrRandom[i] = rand() % 100;
		printf("���� %d\n", arrRandom[i]);
		Array_Tree_insert(arrRandom[i], 0);
	}
	free(arrRandom);

	Array_Tree_print(randNum);
}