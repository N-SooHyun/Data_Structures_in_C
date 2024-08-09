#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	리스트를 이용하여 DBMS구현
	1. select기능, insert기능, delete기능, update기능
	학생 정보의 데이터 모델
*/

typedef struct {		//데이터 모델의 생김새
	int id;				//pk
	char name[50];
	char major[50];
}Student;

typedef struct {		//배열리스트의 데이터 모델
	int id;
	char name[50];
	char major[50];
}Student_ArrayList;

typedef struct {		//이중연결원형리스트 데이터모델
	int id;
	char name[50];
	char major[50];
	struct Student_DoubleList* next;
	struct Student_DoubleList* prev;
}Student_DoubleList;

/*----------------------------이중연결 원형 리스트--------------------------------*/
//모델 생성
Student_DoubleList* DBMS_Double_Head = NULL;
Student_DoubleList* DBMS_Double_Create_List(int id, char* name, char* major) {
	Student_DoubleList* newNode = (Student_DoubleList*)malloc(sizeof(Student_DoubleList));
	newNode->next = newNode;
	newNode->prev = newNode;
	newNode->id = id;
	for (int i = 0; *name != '\0'; i++) {
		newNode->name[i] = *name;
		name++;
	}
	for (int i = 0; *major != '\0'; i++) {
		newNode->major[i] = *major;
		major++;
	}
	return newNode;
}

//모델 삽입
void DMBS_Double_Insert(int id, char* name, char* major) {
	Student_DoubleList* newNode = DBMS_Double_Create_List(id, name, major);
	
	if (DBMS_Double_Head == NULL) {
		DBMS_Double_Head = newNode;
	}
	else {
		Student_DoubleList* tail = DBMS_Double_Head->prev;
		DBMS_Double_Head->prev = newNode;
		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = DBMS_Double_Head;
	}
}

//모델 탐색
Student_DoubleList* DBMS_Double_Select(int id){
	Student_DoubleList* temp = DBMS_Double_Head;
	if (DBMS_Double_Head == NULL) return NULL;

	do {
		if (id == temp->id) {
			return temp;
		}
		temp = temp->next;
	} while (temp != DBMS_Double_Head);
	return NULL;
}

//모델 삭제
void DMBS_Double_Delete(int id) {
	Student_DoubleList* temp = DBMS_Double_Select(id);
	if (temp == NULL) return NULL;
	Student_DoubleList* prev, * next;
	prev = temp->prev;
	next = temp->next;
	next->prev = prev;
	prev->next = next;
	free(temp);
}

//모델 업데이트
void DBMS_Double_Update(int id, int changeId) {
	Student_DoubleList* temp = DBMS_Double_Select(id);
	if (temp == NULL) return NULL;
	temp->id = changeId;
}

void DBMS_Double_List_print() {
	Student_DoubleList* temp = DBMS_Double_Head;
	while (temp->next != DBMS_Double_Head) {
		printf("id : %d\t", temp->id);
		temp = temp->next;
	}
	printf("id : %d  \n", temp->id);
}

void DBMS_Double_List_main() {
	DMBS_Double_Insert(1, "S", "컴");
	DMBS_Double_Insert(2, "S", "컴");
	DMBS_Double_Insert(3, "S", "컴");
	DMBS_Double_Insert(4, "S", "컴");

	DBMS_Double_List_print();

	DMBS_Double_Delete(3);
	DBMS_Double_Update(4, 3);

	DBMS_Double_List_print();
}


/*-------------------------배열리스트를 이용한 DBMS----------------------*/
typedef struct {		//실제 데이터를 가지는 구조체를 담는 배열리스트
	Student_ArrayList* array;
	int size;			//실제 데이터구조체를 가지고 있는 개수
	int capacity;		//실제 배열의 동적할당한 용량 추후 계속 realloc하여 늘렸다 줄였다 재할당
}ArrayList;

//실제 데이터를 가지는 구조체를 담는 배열리스트 초기화
//ArrayList라는 구조체 틀안에 array가 배열이 되어 동적으로 크기가 늘어났다 줄어들었다 하는 형태
Student_ArrayList* Arr_Create_List(int init_capacity) {
	ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
	list->array = (Student_ArrayList*)malloc(init_capacity * sizeof(Student_ArrayList));
	list->size = 0;
	list->capacity = init_capacity;
	return list;
}

//용량이 다 찬경우 혹은 용량을 줄여야하는경우 재할당 함수
void Arr_Add_Resize_ArrayList(ArrayList* list) {
	list->capacity *= 2;		//추가적인 동적할당을 막기위해 2배의 공간을 미리 확보해놓음
								//realloc함수로 메모리를 재할당해 복사하는건 성능이 떨어질 수 있기 때문
	list->array = (Student_ArrayList*)realloc(list->array, list->capacity * sizeof(Student_ArrayList));
}

//배열 추가 Insert
void Arr_Insert(ArrayList* list, int id, char* name, char* major) {
	if (list->size == list->capacity) {
		Arr_Add_Resize_ArrayList(list);
	}
	list->array[list->size].id = id;
	for (int i = 0; ; i++) {
		list->array[list->size].name[i] = *name;
		name++;
		if (*name == '\0') {
			list->array[list->size].name[++i] = *name;
			break;
		}
	}
	for (int i = 0; ; i++) {
		list->array[list->size].major[i] = *major;
		major++;
		if (*major == '\0') {
			list->array[list->size].major[++i] = *major;
			break;
		}
	}
	list->size++;
}

//배열 탐색 Select
int Arr_Select(ArrayList* list, int id) {
	for (int i = 0; i < list->size; i++) {
		if (list->array[i].id == id)
			return i;//인덱스 위치를 알려줌 인덱스 위치만 알면 접근은 굉장히 빠른 장점이 있으니
	}
	return NULL;
}

//배열 삭제 Delete
//이게 중요함 기존 연결리스트는 단순히 연결만 바꾸면 되었지만
//배열리스트에서의 삭제는 순차적인 메모리를 다시 앞으로 재배치를 진행해야하기 때문
void Arr_Delete(ArrayList* list, int id) {
	int idx = Arr_Select(list, id);
	for (int i = idx; i < list->size-1; i++) {
		list->array[i] = list->array[i+1];
	}
	list->size--;
}

//배열 동적 줄이기 안쓰는 공간 재반납
void Arr_Sub_Resize_ArrayList(ArrayList* list) {
	if (list->size == list->capacity)
		return NULL;
	else {
		list->capacity = list->size;
		list->array = (Student_ArrayList*)realloc(list->array, list->capacity * sizeof(Student_ArrayList));
	}
}

//배열 업데이트 Update
void Arr_Update(ArrayList* list, int id, int chid,char* name, char *major) {
	int idx = Arr_Select(list, id);
	list->array[idx].id = chid;
	for (int i = 0; ; i++) {
		list->array[idx].name[i] = *name;
		name++;
		if (*name == '\0') {
			list->array[idx].name[++i] = *name;
			break;
		}
	}
	for (int i = 0; ; i++) {
		list->array[idx].major[i] = *major;
		major++;
		if (*major == '\0') {
			list->array[idx].major[++i] = *major;
			break;
		}
	}
}

//배열 출력
void Arr_print(ArrayList* list) {
	for (int i = 0; i < list->size; i++) {
		printf("id : %d\tname : %s\tmajor : %s\n", list->array[i].id, list->array[i].name, list->array[i].major);
	}
	printf("\n");
}

void DBMS_Arr_main() {
	ArrayList* list = Arr_Create_List(5);
	Arr_Insert(list, 1, "SooHyun1", "com");
	Arr_Insert(list, 2, "SooHyun2", "com");
	Arr_Insert(list, 3, "SooHyun3", "com");
	Arr_Insert(list, 4, "SooHyun4", "com");

	Arr_print(list);

	Arr_Delete(list, 2);
	Arr_print(list);
	Arr_Update(list, 3, 2, "SooHyun2", "com");
	Arr_Update(list, 4, 3, "SooHyun3", "com");
	Arr_print(list);

	printf("배열리스트 크기 : %d\n", list->capacity);
	Arr_Sub_Resize_ArrayList(list);
	printf("배열리스트 줄인 크기 : %d\n", list->capacity);
}