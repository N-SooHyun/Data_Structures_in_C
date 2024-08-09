#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	����Ʈ�� �̿��Ͽ� DBMS����
	1. select���, insert���, delete���, update���
	�л� ������ ������ ��
*/

typedef struct {		//������ ���� �����
	int id;				//pk
	char name[50];
	char major[50];
}Student;

typedef struct {		//�迭����Ʈ�� ������ ��
	int id;
	char name[50];
	char major[50];
}Student_ArrayList;

typedef struct {		//���߿����������Ʈ �����͸�
	int id;
	char name[50];
	char major[50];
	struct Student_DoubleList* next;
	struct Student_DoubleList* prev;
}Student_DoubleList;

/*----------------------------���߿��� ���� ����Ʈ--------------------------------*/
//�� ����
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

//�� ����
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

//�� Ž��
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

//�� ����
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

//�� ������Ʈ
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
	DMBS_Double_Insert(1, "S", "��");
	DMBS_Double_Insert(2, "S", "��");
	DMBS_Double_Insert(3, "S", "��");
	DMBS_Double_Insert(4, "S", "��");

	DBMS_Double_List_print();

	DMBS_Double_Delete(3);
	DBMS_Double_Update(4, 3);

	DBMS_Double_List_print();
}


/*-------------------------�迭����Ʈ�� �̿��� DBMS----------------------*/
typedef struct {		//���� �����͸� ������ ����ü�� ��� �迭����Ʈ
	Student_ArrayList* array;
	int size;			//���� �����ͱ���ü�� ������ �ִ� ����
	int capacity;		//���� �迭�� �����Ҵ��� �뷮 ���� ��� realloc�Ͽ� �÷ȴ� �ٿ��� ���Ҵ�
}ArrayList;

//���� �����͸� ������ ����ü�� ��� �迭����Ʈ �ʱ�ȭ
//ArrayList��� ����ü Ʋ�ȿ� array�� �迭�� �Ǿ� �������� ũ�Ⱑ �þ�� �پ����� �ϴ� ����
Student_ArrayList* Arr_Create_List(int init_capacity) {
	ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
	list->array = (Student_ArrayList*)malloc(init_capacity * sizeof(Student_ArrayList));
	list->size = 0;
	list->capacity = init_capacity;
	return list;
}

//�뷮�� �� ����� Ȥ�� �뷮�� �ٿ����ϴ°�� ���Ҵ� �Լ�
void Arr_Add_Resize_ArrayList(ArrayList* list) {
	list->capacity *= 2;		//�߰����� �����Ҵ��� �������� 2���� ������ �̸� Ȯ���س���
								//realloc�Լ��� �޸𸮸� ���Ҵ��� �����ϴ°� ������ ������ �� �ֱ� ����
	list->array = (Student_ArrayList*)realloc(list->array, list->capacity * sizeof(Student_ArrayList));
}

//�迭 �߰� Insert
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

//�迭 Ž�� Select
int Arr_Select(ArrayList* list, int id) {
	for (int i = 0; i < list->size; i++) {
		if (list->array[i].id == id)
			return i;//�ε��� ��ġ�� �˷��� �ε��� ��ġ�� �˸� ������ ������ ���� ������ ������
	}
	return NULL;
}

//�迭 ���� Delete
//�̰� �߿��� ���� ���Ḯ��Ʈ�� �ܼ��� ���Ḹ �ٲٸ� �Ǿ�����
//�迭����Ʈ������ ������ �������� �޸𸮸� �ٽ� ������ ���ġ�� �����ؾ��ϱ� ����
void Arr_Delete(ArrayList* list, int id) {
	int idx = Arr_Select(list, id);
	for (int i = idx; i < list->size-1; i++) {
		list->array[i] = list->array[i+1];
	}
	list->size--;
}

//�迭 ���� ���̱� �Ⱦ��� ���� ��ݳ�
void Arr_Sub_Resize_ArrayList(ArrayList* list) {
	if (list->size == list->capacity)
		return NULL;
	else {
		list->capacity = list->size;
		list->array = (Student_ArrayList*)realloc(list->array, list->capacity * sizeof(Student_ArrayList));
	}
}

//�迭 ������Ʈ Update
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

//�迭 ���
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

	printf("�迭����Ʈ ũ�� : %d\n", list->capacity);
	Arr_Sub_Resize_ArrayList(list);
	printf("�迭����Ʈ ���� ũ�� : %d\n", list->capacity);
}