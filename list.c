#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE_DATA 100
#define MAX_LIST_SIZE 100

/*
	����Ʈ ���� 1.��������Ʈ, 2.���Ḯ��Ʈ
	����Ʈ != �迭
	�迭 - �����Ҵ�, ����ũ��, ���� �޸�
	����Ʈ - �����Ҵ�, ������ũ��, �񿬼� �޸�
	<�迭>
	���� - �������ټӵ�, �޸� ȿ����(�������̾ �޸𸮻�� ����), ������ ���̼�
	���� - ������ ũ��, ���� �� ������ ��ȿ����, �޸𸮳���
	<����Ʈ>
	���� - ����ũ��, ���� ���� ����, �޸� ȿ����(�Ҵ�ȸ�ŭ������Ͽ� ���� ����)
	���� - ���� ���� �ӵ�(�ε������� ��������), �߰� �޸� ���(������), ������ ���⼺

	Array -> linked list -> ArrayList
	���Ḯ��Ʈ(���Ͽ���, ���߿���, ��������, �������߿���)

	<����Ʈ ������ �ٽ�>
	���, ���, ������, ����
	����, ����, Ž��
*/

/*------------------------ - ���� ���Ḯ��Ʈ ����---------------------------- */
typedef struct Single_Node {
	int data;
	struct Single_Node* next;
}Single_Node;

Single_Node* Single_head = NULL;

void Single_insert(int data) { //�߰�
	Single_Node* newNode = (Single_Node*)malloc(sizeof(Single_Node));
	newNode->data = data;
	newNode->next = Single_head;
	Single_head = newNode;
}

void Single_delete(int data) {	//���� Ž���� ���Ҿ ����
	Single_Node* temp = Single_head;
	Single_Node* prev = NULL;

	while (temp != NULL && temp->data != data) {	//Ž��
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) return; //��带 ã�� ���� ���

	if (prev == NULL) {	//ù ����� ���
		Single_head = temp->next;	//ù ��尡 ����Ű�� next==null�� head�� ��ȯ
	}
	else {	//ù ��尡 �ƴ� ���
		prev->next = temp->next;
	}
	free(temp);
}

void Single_printList() {		//���
	Single_Node* temp = Single_head;
	while (temp != NULL) {
		printf("%d\n", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}

void Single_main() {
	Single_insert(10);
	Single_insert(20);
	Single_insert(30);

	Single_printList();

}
// �迭�� ���Ͽ� �����
/*
	���� - ����ũ������, ���Ի�������, �޸��Ҵ�(�ʿ��Ѹ�ŭ�� ����� �������)
	���� - �ε������� ���� ���� �Ұ���, �߰��޸𸮻��(������带����Ű��������), �����Ͱ���
*/

/*-----------------------���� ���Ḯ��Ʈ ����-------------------------------*/

typedef struct Double_Node {
	int Data;
	struct Double_Node* prev;
	struct Double_Node* next;
}Double_Node;

Double_Node* Double_Head = NULL;
Double_Node* Double_Tail = NULL;

Double_Node* Double_List_Create(int data) {//����Ʈ �ʱ�ȭ ó�� ����
	Double_Node* newNode = (Double_Node*)malloc(sizeof(Double_Node));
	newNode->Data = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void Double_append(int data) {//����Ʈ �߰�
	Double_Node* newNode = Double_List_Create(data);

	if (Double_Head == NULL) {
		Double_Head = newNode;
	}
	else {
		Double_Head->next = newNode;
		newNode->prev = Double_Head;
		Double_Head = newNode;
	}
}

void Double_select(int data) {//����Ʈ �˻�
	Double_Node* temp = Double_Head;
	while (temp != NULL) {
		if (temp->Data == data) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void Double_print() {
	Double_Node* node = Double_Head;
	while (node->prev != NULL && node != NULL) {
		printf("%d\n", node->Data);
		node = node->prev;
	}
	printf("%d\n", node->Data);
	printf("NULL\n");
}

void Double_main() {
	Double_append(10);
	Double_append(20);
	Double_append(30);
	Double_append(40);

	Double_print();
}
//���� ���Ͽ��Ḯ��Ʈ���� �����
/*
	���� - �������� ����Ǿ Ž���� �������� �� ȿ���ִ� 1/2
	���� - Ž���� ȿ���� �����ϳ� �� Ž���� ���� �˰����� �ý����� �ʿ�
*/

/*---------------------------���� ���� ����Ʈ-------------------------------*/
typedef struct Single_Circle_List {
	int Data;
	struct Single_Circle_List* next;
}Single_Circle_List;

Single_Circle_List* Single_Circle_Head = NULL;

Single_Circle_List* Create_Single_List(int data) {
	Single_Circle_List* list = (Single_Circle_List*)malloc(sizeof(Single_Circle_List));
	list->Data = data;
	list->next = NULL;
	return list;
}

void Single_Circle_Append(int data) {
	Single_Circle_List* newNode = Create_Single_List(data);
	if (Single_Circle_Head == NULL) {
		Single_Circle_Head = newNode;
		Single_Circle_Head->next = Single_Circle_Head;
	}
	else {
		newNode->next = Single_Circle_Head->next;
		Single_Circle_Head = newNode;
	}
}

void Single_Circle_Delete(int data) {
	Single_Circle_List* list = Single_Circle_Head;
	while (list->next != Single_Circle_Head && list != NULL) {
		list = list->next;
	}
	
	if (list->Data != data) return;
	else {
		
	}
}
