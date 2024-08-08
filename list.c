#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE_DATA 100
#define MAX_LIST_SIZE 100

/*
	리스트 종류 1.순차리스트, 2.연결리스트
	리스트 != 배열
	배열 - 정적할당, 고정크기, 연속 메모리
	리스트 - 동적할당, 유연한크기, 비연속 메모리
	<배열>
	장점 - 빠른접근속도, 메모리 효율성(연속적이어서 메모리사용 좋음), 구현의 용이성
	단점 - 고정된 크기, 삽입 맟 삭제의 비효율성, 메모리낭비
	<리스트>
	장점 - 동적크기, 삽입 삭제 용이, 메모리 효율성(할당된만큼만사용하여 낭비 적음)
	단점 - 느린 접근 속도(인덱스없어 순차접근), 추가 메모리 사용(포인터), 구현의 복잡성

	Array -> linked list -> ArrayList
	연결리스트(단일연결, 이중연결, 원형연결, 원형이중연결)

	<리스트 구현의 핵심>
	노드, 헤드, 포인터, 테일
	삽입, 삭제, 탐색
*/

/*------------------------ - 단일 연결리스트 구현---------------------------- */
typedef struct Single_Node {
	int data;
	struct Single_Node* next;
}Single_Node;

Single_Node* Single_head = NULL;

void Single_insert(int data) { //추가
	Single_Node* newNode = (Single_Node*)malloc(sizeof(Single_Node));
	newNode->data = data;
	newNode->next = Single_head;
	Single_head = newNode;
}

void Single_delete(int data) {	//삭제 탐색과 더불어서 진행
	Single_Node* temp = Single_head;
	Single_Node* prev = NULL;

	while (temp != NULL && temp->data != data) {	//탐색
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) return; //노드를 찾지 못한 경우

	if (prev == NULL) {	//첫 노드일 경우
		Single_head = temp->next;	//첫 노드가 가르키는 next==null을 head에 반환
	}
	else {	//첫 노드가 아닐 경우
		prev->next = temp->next;
	}
	free(temp);
}

void Single_printList() {		//출력
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
// 배열과 비교하여 장단점
/*
	장점 - 동적크기조절, 삽입삭제용이, 메모리할당(필요한만큼만 사용해 낭비없음)
	단점 - 인덱스없어 임의 접근 불가능, 추가메모리사용(다음노드를가리키는포인터), 포인터관리
*/

/*-----------------------이중 연결리스트 구현-------------------------------*/

typedef struct Double_Node {
	int Data;
	struct Double_Node* prev;
	struct Double_Node* next;
}Double_Node;

Double_Node* Double_Head = NULL;
Double_Node* Double_Tail = NULL;

Double_Node* Double_List_Create(int data) {//리스트 초기화 처음 생성
	Double_Node* newNode = (Double_Node*)malloc(sizeof(Double_Node));
	newNode->Data = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void Double_append(int data) {//리스트 추가
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

void Double_select(int data) {//리스트 검색
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
//기존 단일연결리스트와의 장단점
/*
	장점 - 이중으로 연결되어서 탐색이 절반정도 더 효율있다 1/2
	단점 - 탐색의 효율은 존재하나 이 탐색을 위한 알고리즘적 시스템이 필요
*/

/*---------------------------단일 원형 리스트-------------------------------*/
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
