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
#define MAX_SIZE 31
int tree[MAX_SIZE];

void Array_Tree_init() {//트리 초기화
	for (int i = 0; i < MAX_SIZE; i++)
		tree[i] = -1;
}

void Array_Tree_insert(int data, int index) {
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

int Array_Tree_level() {
	//노드의 개수를 알면 레벨(층)도 알 수 있음
	//높이를 알면 노드의 개수를 알 수 있음 2^높이-1
	//레벨=h      h=log2(n+1)-1  = 2 고로 0 1 2 -> 3층이됨(n=7일시)
	//n=8일시에는 4층이되어야하나 h=log2(8+1)-1 = 2가 됨 이유는 완전이진트리로 다 채워지지 않아서임n=15가되면h=3이됨
	//또한 레벨을 안다면 특정 레벨마다 최대 노드의 개수를 알 수 있음(거듭제곱을통해)
	//h=2인경우 2^0 = 1(root한개), 2^1=2(1층 자식2명), 2^2(2층 자식 4명)
	//log공식적용시 2^n = index;이니까 
	// 2^n/2 = index/2;하면 n을 찾을 수 있다. 이게 log2(n) = index; 임

	double level = log2(MAX_SIZE + 1) - 1;
	int floor = (int)ceil(level);//올림적용
	return floor;//레벨 반환
}

//순회를 통해 트리에 있는 모든 노드를 방문해서 값을 찾는걸 의미

void Array_Tree_preorder_traverse(int index) {//전위 순회
	//root부터 왼쪽순으로 탐색 0 1 3 7 8 4 9 10 순으로
	if (index >= MAX_SIZE || tree[index] == -1) return;
	printf("%d ", tree[index]); //현재 노드 방문
	Array_Tree_preorder_traverse(2 * index + 1);//왼쪽 자식 노드 방문
	Array_Tree_preorder_traverse(2 * index + 2);//오른쪽 자식 노드 방문
}

void Array_Tree_inorder_traverse(int index) {//중위 순회
	//왼쪽하위부터 root 오른쪽순서 7 3 8 1 9 4 10 0
	if (index >= MAX_SIZE || tree[index] == -1) return;
	Array_Tree_inorder_traverse(2 * index + 1);//왼쪽 자식 노드 먼저 방문
	printf("%d ", tree[index]);	//현재 노드 출력
	Array_Tree_inorder_traverse(2 * index + 2);//오른쪽 자식 노드 이후 방문
}

void Array_Tree_postorder_traverse(int index) {//후위 순회
	//하위 트리를 전부 방문 후 root 7 8 3 9 10 4 1 11 12 5
	if (index >= MAX_SIZE || tree[index] == -1) return;
	Array_Tree_postorder_traverse(2 * index + 1);//왼쪽 먼저 방문
	Array_Tree_postorder_traverse(2 * index + 2);//오른쪽 이후 방문
	printf("%d ", tree[index]);//현재 노드 출력
}

void Array_Tree_levelorder_traverse(int index) {//층별 순회
	for (int i = index; i < MAX_SIZE; i++) {
		if (tree[i] != -1) 
			printf("%d ", tree[i]);
	}
}

void Array_Tree_reverse_levelorder_traverse(int index) {
	for (int i = MAX_SIZE-1; i <= index; i--) {
		if(tree[i] != -1)
			printf("%d ", tree[i]);
	}
}

int Array_Tree_Select(int data, int idx) {//찾고자 하는 값을 찾는 함수
	if (idx >= MAX_SIZE || idx < 0) {
		printf("찾고자 하는 값이 노드에 없습니다.");
		return -1;
	}
	if (tree[idx] == data) {
		printf("%d 노드에 존재합니다.\n", idx);
		return idx;
	}
	else if (tree[idx] > data) {
		Array_Tree_Select(data, 2 * idx + 1);
	}
	else if (tree[idx] < data) {
		Array_Tree_Select(data, 2 * idx + 2);
	}
}

void Array_Tree_Delete(int data) {//찾고자 하는 노드를 삭제
	//1. 자식이없는노드 2. 자식이 한개인 노드 3. 자식이 두개인 노드
	int idx = Array_Tree_Select(data, 0);
	if (idx == -1)return;
	
	//자식이 없는 경우
	if (tree[2 * idx + 1] == -1 && tree[2 * idx + 2] == -1)
		tree[idx] = -1; //단순 노드 삭제
	//자식이 하나인 경우
	else if (tree[2 * idx + 1] == -1 || tree[2 * idx + 2] == -1) {
		int child_idx = (tree[2 * idx + 1] != -1 ? 2 * idx + 1 : 2 * idx + 2);
		tree[idx] = tree[child_idx];
		tree[child_idx] = -1;
	}
	//자식이 두개인 경우
	else if (tree[2 * idx + 1] != -1 && tree[2 * idx + 2] != -1) {
		int left_child_idx = 2 * idx + 1;
		int right_child_idx = 2 * idx + 2;
		int min_idx = right_child_idx;		//오른쪽 자식을 기준으로 가장 작은 값
		int max_idx = left_child_idx;		//왼쪽 자식을 기준으로 가장 큰 값
		
		//이 두가지 기준을 지켜야 트리의 크기를 오버하지 않는 기존 값을 통해서 균형잡힌 트리를 만들 수 있음
		//임의로 아무나 부모로 올리게 되면 더 복잡해지고 자식들의 관계가 왼쪽 혹은 오른쪽으로 치우쳐져서 기존 트리크기를 벗어날 수 있음
		
		//오른쪽 자식을 기준으로 가장 작은값
		while (tree[2 * min_idx + 1] != -1)//고로 오른쪽자식을 기준 왼쪽 자식을 탐색
			min_idx = 2 * min_idx + 1;

		tree[idx] = tree[min_idx];	//찾은 노드의 값을 현재 노드에 대입

		//min_idx는 이미 오른쪽 노드의 가장 끝왼쪽 자식이기때문에 
		//오른쪽 자식이 있는지없는지만 여부를 판단하면 된다.
		if (tree[2 * min_idx + 2] != -1) {	//오른쪽 자식이 있다면
			tree[min_idx] = tree[2 * min_idx + 2];
			tree[2 * min_idx + 2] = -1;
		}
		else {
			tree[min_idx] = -1;
		}
	}
}

void Array_Tree_print() {
	printf("이진 탐색 트리 배열표현법\n");
	int level = Array_Tree_level();
	int idx = 0;
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

	printf("전위 순회 : ");
	Array_Tree_preorder_traverse(0);
	printf("\n");

	printf("중위 순회 : ");
	Array_Tree_inorder_traverse(0);
	printf("\n");

	printf("후위 순회 : ");
	Array_Tree_postorder_traverse(0);
	printf("\n");

	printf("층별 순회 : ");
	Array_Tree_levelorder_traverse(0);
	printf("\n");

	printf("역층별 순회 : ");
	Array_Tree_reverse_levelorder_traverse(0);
	printf("\n");

	free(arrRandom);

	Array_Tree_print();

	int selectNum;
	printf("찾고자 하는 값 : ");
	scanf_s("%d", &selectNum);
	Array_Tree_Select(selectNum, 0);
	Array_Tree_print();

	printf("삭제하고자 하는 값 : ");
	scanf_s("%d", &selectNum);
	Array_Tree_Delete(selectNum);
	Array_Tree_print();
}

/*----------------------------------구조체 연결을 이용한 트리--------------------------------*/
//1.모델생성 2.노드생성 3.노드삽입 4.노드순회,탐색 5.메모리해제 6.노드삭제
typedef struct {
	int Data;
	struct Linked_Tree_Node* Left;
	struct Linked_Tree_Node* Right;
}Linked_Tree_Node;


Linked_Tree_Node* Create_Linked_Tree_Node(int data) {	//노드 생성
	Linked_Tree_Node* newNode = (Linked_Tree_Node*)malloc(sizeof(Linked_Tree_Node));
	newNode->Data = data;
	newNode->Left = NULL;
	newNode->Right = NULL;
	return newNode;
}

Linked_Tree_Node* Linked_Tree_Insert_Node(Linked_Tree_Node* node, int data) {//노드 삽입 재귀 적용
	if (node == NULL) {
		return Create_Linked_Tree_Node(data);
	}
	if (data < node->Data) {
		node->Left = Linked_Tree_Insert_Node(node->Left, data);//왼쪽 재귀
	}
	else if (data > node->Data) {
		node->Right = Linked_Tree_Insert_Node(node->Right, data);//오른쪽 재귀
	}
	return node;
}

int Linked_Tree_height(Linked_Tree_Node* root) {		//왼쪽 오른쪽 탐색해서 최대높이 구하는 재귀함수
	if (root == NULL) return 0;
	int leftHeight = Linked_Tree_height(root->Left);
	int rightHeight = Linked_Tree_height(root->Right);
	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void Linked_Tree_current_level(Linked_Tree_Node* root, int level) {//현재 층에 대한 노드 출력 재귀
	//층별로 노드의 개수는 정해짐 1:1, 2:2, 3:4, 4:8   즉 2^n승씩 늘어남 2^0 2^1 2^2 2^3
	if (root == NULL) {
		printf("NL ");
		return;
	}
	if (level == 1)//층이 한개 노드가 한개 2^0승을 의미
		printf("%d ", root->Data);
	else if (level > 1) {//노드가 최소 2이상이됨
		Linked_Tree_current_level(root->Left, level - 1);
		Linked_Tree_current_level(root->Right, level - 1);
	}	
}

void Linked_Tree_levelorder_Traversal(Linked_Tree_Node* root) {
	int Height = Linked_Tree_height(root);
	for (int i = 1; i <= Height; i++) {
		printf("%d층 노드 [ ", i - 1);
		Linked_Tree_current_level(root, i);
		printf("]\n");
	}
}

Linked_Tree_Node* Linked_Tree_select(Linked_Tree_Node* root, int data) {
	//재귀를 이용한 트리에 탐색
	if (root == NULL) {
		printf("찾고자 하는 값이 없습니다.\n");
		return NULL;
	}
	if (root->Data == data) {
		return root;
	}
	else if (root->Data > data) {
		Linked_Tree_select(root->Left, data);
	}
	else if (root->Data < data) {
		Linked_Tree_select(root->Right, data);
	}
}

Linked_Tree_Node* Linked_Tree_Delete(Linked_Tree_Node* root, int data) {
	if (root == NULL) return root;

	if (root->Data > data) {
		root->Left = Linked_Tree_Delete(root->Left, data);
	}
	else if (root->Data < data) {
		root->Right = Linked_Tree_Delete(root->Right, data);
	}
	else {
		//자식노드가 없는 경우
		if (root->Left == NULL && root->Right == NULL) {
			free(root);
			return NULL;
		}
		//자식노드가 한개인경우
		else if (root->Left == NULL) {
			Linked_Tree_Node* temp = root->Right;
			free(root);
			return temp;
		}
		else if (root->Right == NULL) {
			Linked_Tree_Node* temp = root->Left;
			free(root);
			return temp;
		}
		//자식노드가 두개인 경우
		//부모가 되는 기준 1. 오른쪽 자식노드 기준 최소값 2. 왼쪽 자식노드 기준 최대값
		else {
			Linked_Tree_Node* temp;
			temp = root->Right;
			while (temp->Left != NULL) {
				temp = temp->Left;
			}//최종적으로 부모값을 찾을 수 있음
			root->Data = temp->Data;
			root->Right = Linked_Tree_Delete(root->Right, temp->Data);
		}
	}
	return root;
}



void Linked_Tree_preorder_traversal(Linked_Tree_Node* root) {//전위 순회
	if (root == NULL)return;
	printf("%d ", root->Data);
	Linked_Tree_preorder_traversal(root->Left);
	Linked_Tree_preorder_traversal(root->Right);
}

void Linked_Tree_inorder_traversal(Linked_Tree_Node* root) {//중위 순회
	if (root == NULL)return;
	Linked_Tree_inorder_traversal(root->Left);
	printf("%d ", root->Data);
	Linked_Tree_inorder_traversal(root->Right);
}

void Linked_Tree_postorder_traversal(Linked_Tree_Node* root) {//후위 순회
	if (root == NULL)return;
	Linked_Tree_postorder_traversal(root->Left);
	Linked_Tree_postorder_traversal(root->Right);
	printf("%d ", root->Data);
}


void Linked_Tree_main() {
	Linked_Tree_Node* root = NULL;

	srand((unsigned)time(NULL));
	int randNum;	//트리 노드 개수
	int* arrRandom;
	printf("만들고 싶은 난수 개수 : ");
	scanf_s("%d", &randNum);

	arrRandom = (int*)malloc(randNum * sizeof(int));
	for (int i = 0; i < randNum; i++) {
		arrRandom[i] = rand() % 100;
		printf("난수 %d\n", arrRandom[i]);
		root = Linked_Tree_Insert_Node(root, arrRandom[i]);
	}

	printf("층별 순회\n");
	Linked_Tree_levelorder_Traversal(root);
	printf("\n");

	printf("전위 순회 : ");
	Linked_Tree_preorder_traversal(root);
	printf("\n");

	printf("중위 순회 : ");
	Linked_Tree_inorder_traversal(root);
	printf("\n");

	printf("후위 순회 : ");
	Linked_Tree_postorder_traversal(root);
	printf("\n");

	int selectNum;
	Linked_Tree_Node* selectNode;
	/*printf("찾고자 하는 값 : ");
	scanf_s("%d", &selectNum);
	selectNode = Linked_Tree_select(root, selectNum);
	printf("%d\n", selectNode->Data);*/
	
	printf("삭제하고자 하는 값 : ");
	scanf_s("%d", &selectNum);
	root = Linked_Tree_Delete(root, selectNum);
	Linked_Tree_levelorder_Traversal(root);
}



