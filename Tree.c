#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
#include <math.h>
#include<time.h>

/*
	트리 비선형 계층적 구조
	물리적으로는 선형적인 구조이지만
	논리적으로는 비선형 계층구조이다.
	<트리 종류>
	일반트리-자식 노드의 크기가 고정되지 않는 트리
	이진(Binary)트리-자식 노드의 크기가 최대 2개인 트리
	삼진(Ternary)트리-자신 노드의 크기가 최대 3개인 트리
	등등 4 5 6으로도 구현 가능
	<트리 용어>
	레벨(높이), 부모-자식(root,자식,손자 등), 단말노드(자식노드가없는노드), 비단말(반대)
	<이진 트리 특징 or 트리의 전반적 특징>
	root는 한개로정의되며 부모노드는 반드시 한개이기에
	노드개수 - 1 = 간선
	높이 == 최소 노드 개수, 이진트리인경우 최대노드계수 2^높이-1을 따름
	예제 : 높이3짜리 이진트리 최대계수 = (2^1-1)+(2^2-1)+(2^3-1)=(1)+(2)+(4)=7

	<코드구현>
	배열표현법 - 선형구조에 논리를 적용한 방법
	arr[7]이 있다고 가정할시 arr[0]-root, arr[1,2]-root자식, arr[3,4]-1의자식,arr[5,6]-2의자식
	3개의 공식이 적용되어 논리적으로 구성된
	자신(5)의 부모님을 찾는 공식 - i=5  i-1/2 = (5-1/2=2)  or i=6  i-1/2 = (6-1/2=2)
	자신(3)의 왼쪽 자식을 찾는공식 - i=3	2i + 1
	자신의(3) 오른쪽 자식을 찾는공식 - i=3  2i +2
	링크표현법 - 링크리스트와 비슷하게 구조체로 왼쪽자식노드 오른쪽자식노드의 구조체포인터를 활용
*/

/*-------------------------배열표현법으로 구성된 search 탐색 트리-----------------------------*/
// 0~100까지의 난수 7개를 가지고 표현
#define MAX_SIZE 15
int tree[MAX_SIZE];

void Array_Tree_init() {//트리 초기화
	for (int i = 0; i < MAX_SIZE; i++)
		tree[i] = -1;
}

int  Array_Tree_insert(int data, int index) {
	if (index >= MAX_SIZE){
		printf("트리가 가득 찼습니다. %d값은 삽입이 불가능합니다.\n",data);
		return;
	}

	//삽입시 왼쪽은 작음값 오른쪽은 큰값이라는 규칙을 정해두고 삽입시 재귀를 통해서 진행
	if (tree[index] == -1) {
		tree[index] = data;
	}
	else if (data < tree[index]) {
		Array_Tree_insert(data, 2 * index + 1);
		//기존 노드의 값보다 작으니 왼쪽으로 들어감 공식 적용 2(이진노드)*(현재노드위치)+1 = 2i+1
	}
	else if (data > tree[index]) {
		Array_Tree_insert(data, 2 * index + 2);
		//기존 노드의 값보다 크니 오른쪽으로 들어감 공식 적용 2(이진노드)*(현재노드위치)+2 = 2i+2
	}
	return;
}

int Array_Tree_level(int index) {
	//노드의 개수를 알면 레벨(층)도 알 수 있음
	//높이를 알면 노드의 개수를 알 수 있음 2^높이-1
	//레벨=h      h=log2(n+1)-1  = 2 고로 0 1 2 -> 3층이됨(n=7일시)
	//n=8일시에는 4층이되어야하나 h=log2(8+1)-1 = 2가 됨 이유는 완전이진트리로 다 채워지지 않아서임n=15가되면h=3이됨
	//또한 레벨을 안다면 특정 레벨마다 최대 노드의 개수를 알 수 있음(거듭제곱을통해)
	//h=2인경우 2^0 = 1(root한개), 2^1=2(1층 자식2명), 2^2(2층 자식 4명)
	//log공식적용시 2^n = index;이니까 
	// 2^n/2 = index/2;하면 n을 찾을 수 있다. 이게 log2(n) = index; 임
	double level = log2(index + 1) - 1;
	int floor = (int)ceil(level);//올림적용
	return floor;//레벨 반환
}

void Array_Tree_print(int index) {
	printf("이진 탐색 트리 배열표현법\n");
	int level = Array_Tree_level(index);
	int idx = 0;
	printf("%d\n", level);
	for (int i = 0; i <= level; i++) {
		int start_index = (int)pow(2,i) - 1; //level별 시작노드 pow제곱함수 2^i
		int end_index = start_index + (int)pow(2, i);
		printf("%d층 노드 [ ", i);
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
	int randNum;	//트리 노드 개수
	int* arrRandom;
	printf("만들고 싶은 난수 개수(%d 이하) : ", MAX_SIZE);
	scanf_s("%d", &randNum);

	if (randNum > MAX_SIZE) {
		printf("개수가 너무 많아요.");
		return;
	}

	arrRandom = (int*)malloc(randNum * sizeof(int));
	Array_Tree_init();
	for (int i = 0; i < randNum; i++) {
		arrRandom[i] = rand() % 100;
		printf("난수 %d\n", arrRandom[i]);
		Array_Tree_insert(arrRandom[i], 0);
	}
	free(arrRandom);

	Array_Tree_print(randNum);
}