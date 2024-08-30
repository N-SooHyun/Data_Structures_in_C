#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
#include<math.h>

#define MAX_SIZE_QUE_MODEL 5

// �迭�� �̿��� �켱���� ť
//�迭�� �̿��� ���� ť�� �켱������ �����ϴ� �ΰ��� ���
//1. �켱������ �°� ��ť�� �迭 ���ġ
//2. �켱������ �°� ��ť�� �迭 ���ġ ���� ��ť�� Ʈ�������� ���� ���� ������ Ž���ؼ� ����

//�ΰ����� �� ������� �ִµ� 1���� ��ť�� �����ؾ��ؼ� ���� ��ť ���� 2�� ��ť���� ��ť1������ �������� Ʈ�������� ��������

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

Array_Priority_Que* Priority_Que_Model_Init() {	//ť �� �ʱ�ȭ
	Array_Priority_Que* que_model = (Array_Priority_Que_Data*)malloc(sizeof(Array_Priority_Que));
	que_model->size = 0;
	return que_model;
}

Array_Priority_Que_Data* Priority_Que_Data_Init() {	//ť��� ������ �ʱ�ȭ
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

void Priority_Enque(Array_Priority_Que* model ,int Data, int priority) {		//��ť
	if (Priority_isFull(model)) {
		printf("ť�� ���� á���ϴ�.");
		return;
	}
	/*	�ܼ� ��ť
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

Array_Priority_Que_Data* Priority_Deque(Array_Priority_Que* model) {		//��ť
	if (Priority_isEmpty(model)) {
		printf("ť�� ����ֽ��ϴ�.");
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
	printf("ť ���� ��� : ");
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

	printf("������ ���� ��ť ����\n");

	for (int i = 0; i < 6; i++) {
		node = Priority_Deque(que_model);
		if(node!=NULL)	Priority_Deque_Free(node);
		Priority_Que_print(que_model);
	}
}


//���� ť�� �켱������ �����Ұ��
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
		return 1;//���� ������
	}
	return 0;//��������
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
		printf("���� á���ϴ�.");
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
		printf("��� �ֽ��ϴ�.");
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
		printf("������ : %d,  %d\n", node->data, node->priority);
		free(node);
	}

	Priority_Linked_Que_Enque(que_model, 10, 5);
	Priority_Linked_Que_Enque(que_model, 20, 4);
	Priority_Linked_Que_Enque(que_model, 30, 3);
	Priority_Linked_Que_Enque(que_model, 40, 2);

	printf("\n");
	for (int i = 0; i < 4; i++) {
		node = Priority_Linked_Que_Deque(que_model);
		printf("������ : %d,  %d\n", node->data, node->priority);
		free(node);
	}
}


//�������� �迭		���� : O(1)		���� : O(n)
//�������� ���� ����Ʈ	O(1)		O(n)
//���ĵ� �迭			O(n)		O(1)
//���ĵ� ���Ḯ��Ʈ		O(n)		O(1)
//���� �̿�				O(logn)		O(logn)

/*
���� ť�� ����ť�� ���������� �Ǿ� �ֱ⿡ �켱������ ���� ���ġ�� �ʿ��ϴ�
������ ��(heap)���� �� Ʈ�������� �̿��Ѵٸ� ��ť�� ���ġ���� �ʰ� Ʈ�������� �°Բ� �����ϰ� Ʈ�������� �°Բ� �����Ͽ� ���� �� ȿ�����̰� ���� �� �ִ�.
���� �� �ΰ��� ������ �ִµ�
�ִ��� : �θ� ���� �ڽ� ��庸�� ũ�ų� ����
�ּ��� : �θ� ���� �ڽ� ��庸�� �۰ų� ����
*/
/*
���� ���ʿ� ��������Ʈ���� �����̱⿡ ���԰����� ������ �������ִ�.
1. �θ�, �����ڽ�, �������ڽ� ������ ���� ���� ������ �����Ѵ�.
2. ���Ե� ���� �ڽĵ���� ������ �ƴ� �θ�� �񱳸� �����Ͽ� �θ𺸴� �۰ų�(�ּ�) ũ��(�ִ�)�θ���� �ڸ��� �ٲ۴�.
3. �θ��� ����(��ť)�� �������� ��������� ��������带 �θ��忡 ��ġ�ϰ� 2���� ����
4. 2������ �� �״�� �θ���� �ڽĳ�尣 �ּ� �ִ� ���� �°� �����Ͽ� �θ���� �ڸ��� �ٲٰ� ������ �׷������� �ٲ���
�̷� �����̱⿡ ���Խÿ��� ������ �ϰ� �����ÿ��� ������ �����ϱ⿡ ȿ����
*/ 

//���� �迭�� �̿��� �켱���� Ʈ�� ����
//Ư¡-����ũ��, ��������  ����-���� ���� �� ����,  ������ ����   ����-������ũ��, �޸𸮳��񰡴ɼ�(�������� �˳��� �Ҵ��� ��)
//�������� ��ǥ��� 1. ��������Ʈ���� ����, 2. �켱���� ���� ����, 3. �켱���� ��ť, 4. ��ť �� ��������� root���°�

typedef struct Priority_Heap_Arr_Que_Model {
	struct Priority_Heap_Arr_Que* nodes;
	int size;
	int capacity;
}Priority_Heap_Arr_Que_Model;

typedef struct Priority_Heap_Arr_Que {
	int Value;
	int Priority;
}Priority_Heap_Arr_Que;

Priority_Heap_Arr_Que_Model* Priority_Heap_Arr_Que_init(int capacity) {//�ʱ�ȭ ��
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
	
	while (i != 0 && model->nodes[Priority_Heap_Arr_Que_getParent(i)].Priority > model->nodes[i].Priority) {//�ּ���-�θ��尡 �ڽĺ��� �۰ų� ������
		//�θ� �ڽĺ��� ũ�� �ּ��տ� ���յ��� ������ �����������
		Priority_Heap_Arr_Que_swap(&model->nodes[Priority_Heap_Arr_Que_getParent(i)], &model->nodes[i]);
		i = Priority_Heap_Arr_Que_getParent(i);//�����θ�鵵 �������� ã������
	}
}

Priority_Heap_Arr_Que* Priority_Heap_Arr_deque(Priority_Heap_Arr_Que_Model* model) {
	if (model->size <= 0) {
		printf("ť�� ��� �ֽ��ϴ�.");
		exit(EXIT_FAILURE);
	}
	if (model->size == 1) {
		model->size--;
		return &model->nodes[0];
	}
	Priority_Heap_Arr_Que root = model->nodes[0];
	model->nodes[0] = model->nodes[--model->size];//���� ��������带 �θ��忡 ����
	

	int i = 0;
	while (1) {
		int left = Priority_Heap_Arr_Que_getLeftChild(i);
		int right = Priority_Heap_Arr_Que_getRightChild(i);
		int smallest = i;		//�񱳴������ �θ���

		//��������Ʈ���� �����ڽİ� smallest�� ���� ���Ұ��� ���� �������ڽİ� smallest���� ���Ұ���
		if (left < model->size && model->nodes[left].Priority < model->nodes[smallest].Priority)
			smallest = left;
		if (right < model->size && model->nodes[right].Priority < model->nodes[smallest].Priority)
			smallest = right;
		if (smallest != i) {
			Priority_Heap_Arr_Que_swap(&model->nodes[i], &model->nodes[smallest]);		//�θ���i�� �ٲٰ����ϴ� �ڽĳ�� smallest�� ����
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
		printf("��ť : %d  (�켱���� : %d) \n", que_node->Value, que_node->Priority);
	}
}





//���Ḯ��Ʈ�� �̿��� �켱���� Ʈ�� ����
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
		//ť�� ����ְų� ���ο� ��尡 �켱������ ���� �������
		newNode->next = model->front;
		model->front = newNode;
	}
	else {
		//�켱 ������ ���� ��带 ����
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

	printf("�켱���� ť \n");
	Priority_Heap_Linked_Que_print(&que_model);

	Priority_Heap_Linked_Que* node;
	while ((node = Priority_Heap_Linked_Que_deque(&que_model)) != NULL) {
		printf("deque Value : %d,  Priority : %d\n", node->Value, node->Priority);
		//free(node);
	}

	Priority_Heap_Linked_Que_free(&que_model);

}