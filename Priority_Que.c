#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
#include<math.h>

#define MAX_SIZE_QUE_MODEL 5

// 배열을 이용한 우선순위 큐
//배열을 이용한 기존 큐에 우선순위를 적용하는 두가지 방법
//1. 우선순위에 맞게 인큐시 배열 재배치
//2. 우선순위에 맞게 인큐시 배열 재배치 없이 디큐시 트리구조로 가장 높은 구조를 탐색해서 추출

//두가지는 각 장단점이 있는데 1번은 인큐시 정렬해야해서 느림 디큐 빠름 2번 인큐빠름 디큐1번보단 느리지만 트리구조라 빠르긴함

typedef struct Array_Priority_Que {
	struct Array_Priority_Que_Data* Data[MAX_SIZE_QUE_MODEL];	
	int size;
}Array_Priority_Que;

typedef struct Array_Priority_Que_Data {
	int Data;
	int priority;
}Array_Priority_Que_Data;

int Priority_isEmptyFull(Array_Priority_Que* Model) {
	if (Model->size >= MAX_SIZE_QUE_MODEL) {
		return -1;
	}
	return 1;
}

Array_Priority_Que* Priority_Que_Model_Init() {	//큐 모델 초기화
	Array_Priority_Que* que_model = (Array_Priority_Que_Data*)malloc(sizeof(Array_Priority_Que));
	que_model->size = 0;
	return que_model;
}

Array_Priority_Que_Data* Priority_Que_Data_Init() {	//큐노드 데이터 초기화
	Array_Priority_Que_Data* newNode = (Array_Priority_Que_Data*)malloc(sizeof(Array_Priority_Que_Data));
	newNode->Data = 0;
	newNode->priority = 0;
	return newNode;
}

boolean Priority_isFull(Array_Priority_Que* model) {
	if (model->size >= MAX_SIZE_QUE_MODEL) {
		return 1;
	}
	return 0;
}

boolean Priority_isEmpty(Array_Priority_Que* model) {
	if (model->size == 0) {
		return 1;
	}
	return 0;
}

void Priority_Enque(Array_Priority_Que* model ,int Data, int priority) {		//인큐
	if (Priority_isFull(model)) {
		printf("큐가 가득 찼습니다.");
		return;
	}
	/*	단순 인큐
	Array_Priority_Que_Data* newNode = Priority_Que_Data_Init();
	newNode->Data = Data;
	newNode->priority = priority;
	model->Data[model->size] = newNode;
	model->size++;
	*/
	Array_Priority_Que_Data* newNode = Priority_Que_Data_Init();
	int i = model->size-1;

	while (i >= 0 && model->Data[i]->priority > priority) {
		model->Data[i + 1] = model->Data[i];
		i--;
	}

	newNode->Data = Data;
	newNode->priority = priority;
	model->Data[i + 1] = newNode;
	model->size++;
}

Array_Priority_Que_Data* Priority_Deque(Array_Priority_Que* model) {		//디큐
	if (Priority_isEmpty(model)) {
		printf("큐가 비어있습니다.");
		return NULL;
	}
	Array_Priority_Que_Data* node = model->Data[0];
	int i;
	for (i = 0; i < model->size-1; i++) {
		model->Data[i] = model->Data[i + 1];
		model->Data[i + 1] = NULL;
	}
	model->size--;
	return node;
}

void Priority_Deque_Free(Array_Priority_Que_Data* node){
	free(node);
}

void Priority_Que_print(Array_Priority_Que* model) {
	printf("큐 내부 목록 : ");
	for (int i = 0; i < model->size; i++) {
		printf("%d[val : %d,  pri : %d] ", i, model->Data[i]->Data, model->Data[i]->priority);
	}
	printf("\n");
}

void Priority_Arr_Que_main() {
	Array_Priority_Que* que_model;
	Array_Priority_Que_Data* node;

	que_model = Priority_Que_Model_Init();

	Priority_Enque(que_model, 10, 5);
	Priority_Enque(que_model, 20, 2);
	Priority_Enque(que_model, 30, 4);
	Priority_Enque(que_model, 40, 1);
	Priority_Enque(que_model, 50, 3);

	Priority_Que_print(que_model);	

	printf("데이터 추출 디큐 진행\n");

	for (int i = 0; i < 6; i++) {
		node = Priority_Deque(que_model);
		if(node!=NULL)	Priority_Deque_Free(node);
		Priority_Que_print(que_model);
	}
}


//원형 큐에 우선순위를 적용할경우
typedef struct Priority_Linked_Que_Model {
	struct Priority_Linked_Que* Data[MAX_SIZE_QUE_MODEL];
	int size;
	int front;
	int rear;
}Priority_Linked_Que_Model;

typedef struct Priority_Linked_Que {
	int data;
	int priority;
}Priority_Linked_Que;

Priority_Linked_Que_Model* Priority_Linked_Que_Model_init() {
	Priority_Linked_Que_Model* newModel = (Priority_Linked_Que_Model*)malloc(sizeof(Priority_Linked_Que_Model));
	newModel->front = 0;
	newModel->rear = 0;
	return newModel;
}

Priority_Linked_Que* Priority_Linked_Que_init(int data, int priority) {
	Priority_Linked_Que* newNode = (Priority_Linked_Que*)malloc(sizeof(Priority_Linked_Que));
	newNode->data = data;
	newNode->priority = priority;
	return newNode;
}

boolean Priority_Linked_Que_isFull(Priority_Linked_Que_Model* model) {
	return ((model->front + 1) % MAX_SIZE_QUE_MODEL == model->rear);

	int i = model->front;
	int j = model->rear;
	int max = MAX_SIZE_QUE_MODEL;
	i++;
	if (max % i == j) {
		return 1;//가득 찬거임
	}
	return 0;//안찬거임
}

boolean Priority_Linked_Que_isEmpty(Priority_Linked_Que_Model* model) {
	return (model->front == model->rear);

	int i = model->front;
	int j = model->rear;
	int max = MAX_SIZE_QUE_MODEL;
	if (i == j)return 1;
	return 0;
}

void Priority_Linked_Que_Enque(Priority_Linked_Que_Model* model, int data, int priority) {
	if (Priority_Linked_Que_isFull(model)) {
		printf("가득 찼습니다.");
		return;
	}

	Priority_Linked_Que* newNode = Priority_Linked_Que_init(data, priority);
	/*
	int i = model->front - 1;

	model->Data[i + 1] = newNode;
	model->front++;
	if (model->front % MAX_SIZE_QUE_MODEL == 0) 
		model->front = 0;
	*/

	int rear = model->rear;
	int front = model->front;
	int max = MAX_SIZE_QUE_MODEL;

	while (front != rear) {
		if (model->Data[rear]->priority > priority) {
			model->Data[front] = model->Data[(front - 1 == -1 ? max - 1 : front - 1)];
			front = front - 1 == -1 ? max - 1 : front - 1;
		}
		else {
			rear = rear + 1 == max ? 0 : rear + 1;
		}
	}

	model->Data[front] = newNode;
	model->front = model->front + 1 >= max ? 0 : model->front+1;
}

Priority_Linked_Que* Priority_Linked_Que_Deque(Priority_Linked_Que_Model* model) {
	if (Priority_Linked_Que_isEmpty(model)) {
		printf("비어 있습니다.");
		return;
	}
	int i = model->rear;
	Priority_Linked_Que* node = model->Data[i];
	model->Data[i] = NULL;
	model->rear++;
	if (model->rear % MAX_SIZE_QUE_MODEL == 0)
		model->rear = 0;

	return node;
}

void Priority_Linked_Que_main() {
	Priority_Linked_Que_Model* que_model;
	Priority_Linked_Que* node;

	que_model = Priority_Linked_Que_Model_init();
	
	Priority_Linked_Que_Enque(que_model, 10, 1);
	Priority_Linked_Que_Enque(que_model, 20, 2);
	Priority_Linked_Que_Enque(que_model, 30, 3);
	Priority_Linked_Que_Enque(que_model, 40, 4);

	for (int i = 0; i < 4; i++) {
		node = Priority_Linked_Que_Deque(que_model);
		printf("빠진값 : %d,  %d\n", node->data, node->priority);
		free(node);
	}

	Priority_Linked_Que_Enque(que_model, 10, 5);
	Priority_Linked_Que_Enque(que_model, 20, 4);
	Priority_Linked_Que_Enque(que_model, 30, 3);
	Priority_Linked_Que_Enque(que_model, 40, 2);

	printf("\n");
	for (int i = 0; i < 4; i++) {
		node = Priority_Linked_Que_Deque(que_model);
		printf("빠진값 : %d,  %d\n", node->data, node->priority);
		free(node);
	}
}


//순서없는 배열		삽입 : O(1)		삭제 : O(n)
//순서없는 연결 리스트	O(1)		O(n)
//정렬된 배열			O(n)		O(1)
//정렬된 연결리스트		O(n)		O(1)
//힙을 이용				O(logn)		O(logn)

/*
기존 큐와 원형큐는 선형구조로 되어 있기에 우선순위에 따른 재배치가 필요하다
하지만 힙(heap)구조 즉 트리구조를 이용한다면 인큐시 재배치하지 않고 트리구조에 맞게끔 삽입하고 트리구조에 맞게끔 추출하여 조금 더 효율적이게 만들 수 있다.
힙은 총 두개의 구조가 있는데
최대힙 : 부모 노드는 자식 노드보다 크거나 같다
최소힙 : 부모 노드는 자식 노드보다 작거나 같다
*/
/*
힙은 애초에 완전이진트리의 구조이기에 삽입과정과 순서가 정해져있다.
1. 부모, 왼쪽자식, 오른쪽자식 순으로 노드는 먼저 삽입을 진행한다.
2. 삽입된 노드는 자식들과의 경쟁이 아닌 부모와 비교를 진행하여 부모보다 작거나(최소) 크면(최대)부모노드와 자리를 바꾼다.
3. 부모노드 삭제(디큐)시 힙구조에 마지막노드 최하위노드를 부모노드에 위치하고 2번을 진행
4. 2번진행 말 그대로 부모노드와 자식노드간 최소 최대 값에 맞게 경쟁하여 부모노드와 자리를 바꾸고 층별로 그런식으로 바꿔줌
이런 순서이기에 삽입시에도 정렬을 하고 삭제시에도 정렬을 진행하기에 효율적
*/ 

//동적 배열을 이용한 우선순위 트리 구조
//특징-고정크기, 빠른접근  장점-빠른 삽입 및 삭제,  간단한 구현   단점-고정된크기, 메모리낭비가능성(동적으로 넉넉히 할당할 시)
//만들어야할 대표기능 1. 완전이진트리식 삽입, 2. 우선순위 비교후 스왑, 3. 우선순위 디큐, 4. 디큐 후 최하위노드 root노드승격

typedef struct Priority_Heap_Arr_Que_Model {
	struct Priority_Heap_Arr_Que* nodes;
	int size;
	int capacity;
}Priority_Heap_Arr_Que_Model;

typedef struct Priority_Heap_Arr_Que {
	int Value;
	int Priority;
}Priority_Heap_Arr_Que;

Priority_Heap_Arr_Que_Model* Priority_Heap_Arr_Que_init(int capacity) {//초기화 모델
	Priority_Heap_Arr_Que_Model* newModel = (Priority_Heap_Arr_Que_Model*)malloc(sizeof(Priority_Heap_Arr_Que_Model));
	newModel->size = 0;
	newModel->capacity = capacity;
	newModel->nodes = (Priority_Heap_Arr_Que*)malloc(sizeof(Priority_Heap_Arr_Que) * capacity);
	return newModel;
}

void Priority_Heap_Arr_Que_swap(Priority_Heap_Arr_Que* a, Priority_Heap_Arr_Que* b) {
	Priority_Heap_Arr_Que temp = *a;
	*a = *b;
	*b = temp;
}

int Priority_Heap_Arr_Que_getParent(int i) { return (i - 1) / 2; }
int Priority_Heap_Arr_Que_getLeftChild(int i) { return 2 * i + 1; }
int Priority_Heap_Arr_Que_getRightChild(int i) { return 2 * i + 2; }

void Priority_Heap_Arr_Que_enque(Priority_Heap_Arr_Que_Model* model, int value, int priority) {
	if (model->size == model->capacity) {
		model->capacity *= 2;
		model->nodes = (Priority_Heap_Arr_Que*)realloc(model->nodes, sizeof(Priority_Heap_Arr_Que) * model->capacity);
	}

	int i = model->size++;
	model->nodes[i].Value = value;
	model->nodes[i].Priority = priority;
	
	while (i != 0 && model->nodes[Priority_Heap_Arr_Que_getParent(i)].Priority > model->nodes[i].Priority) {//최소합-부모노드가 자식보다 작거나 같을때
		//부모가 자식보다 크면 최소합에 부합되지 않으니 스왑해줘야함
		Priority_Heap_Arr_Que_swap(&model->nodes[Priority_Heap_Arr_Que_getParent(i)], &model->nodes[i]);
		i = Priority_Heap_Arr_Que_getParent(i);//상위부모들도 스왑할지 찾기위해
	}
}

Priority_Heap_Arr_Que* Priority_Heap_Arr_deque(Priority_Heap_Arr_Que_Model* model) {
	if (model->size <= 0) {
		printf("큐가 비어 있습니다.");
		exit(EXIT_FAILURE);
	}
	if (model->size == 1) {
		model->size--;
		return &model->nodes[0];
	}
	Priority_Heap_Arr_Que root = model->nodes[0];
	model->nodes[0] = model->nodes[--model->size];//가장 최하위노드를 부모노드에 세움
	

	int i = 0;
	while (1) {
		int left = Priority_Heap_Arr_Que_getLeftChild(i);
		int right = Priority_Heap_Arr_Que_getRightChild(i);
		int smallest = i;		//비교대상자인 부모노드

		//완전이진트리라서 왼쪽자식과 smallest와 비교후 스왑결정 이후 오른쪽자식과 smallest비교후 스왑결정
		if (left < model->size && model->nodes[left].Priority < model->nodes[smallest].Priority)
			smallest = left;
		if (right < model->size && model->nodes[right].Priority < model->nodes[smallest].Priority)
			smallest = right;
		if (smallest != i) {
			Priority_Heap_Arr_Que_swap(&model->nodes[i], &model->nodes[smallest]);		//부모노드i와 바꾸고자하는 자식노드 smallest와 스왑
			i = smallest;
		}
		else {
			break;
		}
	}
	return &root;
}


void Priority_Heap_Arr_main() {
	Priority_Heap_Arr_Que_Model* que_model = Priority_Heap_Arr_Que_init(5);
	Priority_Heap_Arr_Que* que_node;

	Priority_Heap_Arr_Que_enque(que_model, 10, 2);
	Priority_Heap_Arr_Que_enque(que_model, 20, 1);
	Priority_Heap_Arr_Que_enque(que_model, 30, 4);
	Priority_Heap_Arr_Que_enque(que_model, 40, 3);


	for (int i = 0; i < 4; i++) {
		que_node = Priority_Heap_Arr_deque(que_model);
		printf("디큐 : %d  (우선순위 : %d) \n", que_node->Value, que_node->Priority);
	}
}





//연결리스트를 이용한 우선순위 트리 구조
typedef struct Priority_Heap_Linked_Que {
	int Value;
	int Priority;
	struct Priority_Heap_Linked_Que* prev;
	struct Priority_Heap_Linked_Que* next;
}Priority_Heap_Linked_Que;

typedef struct Priority_Heap_Linked_Que_Root {
	Priority_Heap_Linked_Que* front;
}Priority_Heap_Linked_Que_Root;

void Priority_Heap_Linked_Que_init(Priority_Heap_Linked_Que_Root* model) {
	model->front = NULL;
}

void Priority_Heap_Linked_Que_enque(Priority_Heap_Linked_Que_Root* model, int value, int priority) {
	Priority_Heap_Linked_Que* newNode = (Priority_Heap_Linked_Que*)malloc(sizeof(Priority_Heap_Linked_Que));
	newNode->Value = value;
	newNode->Priority = priority;
	newNode->prev = NULL;
	newNode->next = NULL;

	if (model->front == NULL || model->front->Priority < priority) {
		//큐가 비어있거나 새로운 노드가 우선순위가 가장 높은경우
		newNode->next = model->front;
		model->front = newNode;
	}
	else {
		//우선 순위에 따라 노드를 삽입
		Priority_Heap_Linked_Que* current = model->front;
		while (current->next != NULL && current->next->Priority >= priority) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

Priority_Heap_Linked_Que* Priority_Heap_Linked_Que_deque(Priority_Heap_Linked_Que_Root* model) {
	if (model->front == NULL) {
		return NULL;
	}

	Priority_Heap_Linked_Que* temp = model->front;
	model->front = model->front->next;
	return temp;
}

void Priority_Heap_Linked_Que_print(Priority_Heap_Linked_Que_Root* model) {
	Priority_Heap_Linked_Que* current = model->front;
	while (current != NULL) {
		printf("Value : %d, Priority : %d\n", current->Value, current->Priority);
		current = current->next;
	}
}

void Priority_Heap_Linked_Que_free(Priority_Heap_Linked_Que_Root* model) {
	Priority_Heap_Linked_Que* current = model->front;
	Priority_Heap_Linked_Que* nextNode;
	while (current != NULL) {
		nextNode = current->next;
		free(current);
		current = nextNode;
	}
	model->front = NULL;
}

void Priority_Heap_Linked_Que_main() {
	Priority_Heap_Linked_Que_Root que_model;
	Priority_Heap_Linked_Que_init(&que_model);

	Priority_Heap_Linked_Que_enque(&que_model, 10, 2);
	Priority_Heap_Linked_Que_enque(&que_model, 20, 4);
	Priority_Heap_Linked_Que_enque(&que_model, 30, 1);
	Priority_Heap_Linked_Que_enque(&que_model, 40, 3);

	printf("우선순위 큐 \n");
	Priority_Heap_Linked_Que_print(&que_model);

	Priority_Heap_Linked_Que* node;
	while ((node = Priority_Heap_Linked_Que_deque(&que_model)) != NULL) {
		printf("deque Value : %d,  Priority : %d\n", node->Value, node->Priority);
		//free(node);
	}

	Priority_Heap_Linked_Que_free(&que_model);

}