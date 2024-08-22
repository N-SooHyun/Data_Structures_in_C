#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
//#include "Tree_Directory.h">

#define FILE_NAME_MAX_SIZE 20
//Ʈ�� ������ �̿��� ���� Ž����
//���� Ž����� 2������ �� �������±����� �ƴ� ������ Ʈ���̱⶧����
//�����迭�� ����ϰų� ���Ḯ��Ʈ�� �̿��ؾ��Ѵ�.

//1. ���Ḯ��Ʈ�� �̿��� ����ü�� ��
typedef struct Linked_Child_List {		//�ڽĳ����� ������ ���Ḯ��Ʈ
	struct Linked_File_Node* child;		//���� �ڽĳ���� ����ü
	struct Linked_Child_List* next;		//�θ��� ���� �ڽ� ����Ű�� ����ü
}Linked_Child_List;

typedef struct Linked_File_Node {
	char* File_Name;
	char* File_Date;
	char* File_Type;
	int type;		//0=dir, 1=txt
	struct Linked_Child_List* child_list;	//�ڽ� ������ ����Ʈ	���Ḯ��Ʈ�� ���κ�
	int size;		//���� �ڽ� ����� ��
}Linked_File_Node;
/*
	�θ� ��� -> �ڽĸ���Ʈ -> �ڽ����ϳ��� ���Ҿ� ���� �ڽĸ���Ʈ�� ����Ŵ
	�θ� -> �ڽ�1 -> �ڽ�2 -> �ڽ�3 -> �ڽ�4
	�̷� ����
	�ڽ�1 -> ����1 -> ����2 ->����3 			
*/
Linked_File_Node* Linked_Create_File_Node(char* name, int type) {
	Linked_File_Node* newNode = (Linked_File_Node*)malloc(sizeof(Linked_File_Node));
	newNode->File_Name = name;
	newNode->type = type;
	newNode->File_Type = type == 0 ? "dir" : "txt";
	newNode->size = 0;
	newNode->child_list = NULL;
	return newNode;
}

//�ڽĸ���Ʈ ����
Linked_Child_List* Linked_Create_Child_List(Linked_Child_List* NodeList, char* name, int type) {
	NodeList = (Linked_Child_List*)malloc(sizeof(Linked_Child_List));		//�ڽĿ����� �޸� ���� �Ҵ�
	NodeList->next = NULL;													//����ڽ��� ����Ŷ� �ڽ��� �Ѹ�
	NodeList->child = Linked_Create_File_Node(name, type);					//�ڽĿ����忡 ��¥ �ڽĵ����͸� ����													//�ڽĳ���� �������
	return NodeList;
}

//�ڽĸ���Ʈ ����
Linked_Child_List* Linked_Insert_File_Node(char* name, int type, Linked_Child_List* currentNodeList) {
	if (currentNodeList == NULL) {//�ڽ� dir�� �ƹ��͵� ������
		return Linked_Create_Child_List(currentNodeList, name, type);
	}
	//����Լ��� ���ǽ� ���Ḯ��Ʈ�� ���ڶ����� ���̻��� �ڽĳ�尡 ������
	if (currentNodeList->next == NULL) {
		currentNodeList->next = Linked_Insert_File_Node(name, type, currentNodeList->next);
		return currentNodeList;
	}
	//�ڽĳ�尡 �Ѱ� �̻��϶� ����Լ��� �ݺ����ǽ�
	Linked_Insert_File_Node(name, type, currentNodeList->next);
}

//�ڽĸ���Ʈ ��� �����ֱ�
int Linked_File_print(Linked_File_Node* root) {		
	if (root->child_list == NULL) {//�ڽ��� �Ѹ� �������
		printf("���� ���� ����\n"); 
		return 0;	//�������� ����F
	}
	Linked_Child_List* current_child_list = root->child_list;
	while (current_child_list->next!=NULL) {
		printf("%s\n", current_child_list->child->File_Name);
		current_child_list = current_child_list->next;		
	}
	printf("%s\n", current_child_list->child->File_Name);
	return 1;		//�������� ����T
}
/*------------------------UI�κ� �Լ�---------------------------------------*/


//���ϸ� �޾ƿ���
void Linked_Input_File_Name(char arr_FileName[]) {
	int size = FILE_NAME_MAX_SIZE;
	char ch;
	int i;
	//while (getchar() != '\n');
	while (1) {
		printf("������ �̸��� �˷��ּ���(20��) : ");
		i = 0;
		memset(arr_FileName, '\0', size);
		

		while ((ch = getchar()) != '\n' && ch != EOF) {
			if (i < size - 1) {
				arr_FileName[i++] = ch;
			}
			else {
				printf("�̸����� �ʹ� ����(20��)\n");
				while (getchar() != '\n');		//�����ִ� �Է¹��۸� ���� ������
				i = 0;
				memset(arr_FileName, '\0', size);
				break;//�ٽ� �Է��� �ޱ����� �ݺ��� ��������
			}
		}
		if (i > 0 && i < size) {
			arr_FileName[i] = '\0';
			break;
		}
		else {
			printf("�ٽ� �Է� ���ּ���\n");
		}
	}
}

//�������� ����
void Linked_Make_Dir(Linked_File_Node* node, char FileName[]) {
	int type;
	Linked_Input_File_Name(FileName);//���ϸ� �޾ƿ���
	while (1) {
		printf("Ÿ���� �����ΰ���(0:dir, 1:txt) : ");
		scanf_s("%d", &type);
		while (getchar() != '\n');//�Է¹��� �����
		if (type == 0 || type == 1) break;
		printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���\n");
	}

	Linked_Insert_File_Node(FileName, type, node->child_list);
}

//���� �κ�
Linked_File_Node* Linked_UI_Create_Root(char arr_FileName[]) {
	printf("���� Ž����\n");
	printf("����� ���� ");
	Linked_Input_File_Name(arr_FileName);
	Linked_File_Node* root = Linked_Create_File_Node(arr_FileName, 0);
	return root;
}

//���� ����Ʈ
void Linked_dir_list(Linked_File_Node* root, char FileName[]) {
	int selectNum;
	int roof = 1;
	boolean child_dir;	//������������
	system("cls");
	while (roof) {
		printf("<���� ���� : %s>\n", root->File_Name);
		printf("���� ���� ����Ʈ : ");
		child_dir = Linked_File_print(root);
		printf("1. ��������, 2. ��������, 3. ��������, 4. ���������� ���ư���, 5. ����: ");
		scanf_s("%d", &selectNum);
		while (getchar() != '\n');
		switch (selectNum) {
			case 1:
				if (child_dir) {
					//Linked_Access_Dir(root, FileName);
					break;
				}
				system("cls");
				printf("���� ������ �����ϴ�.\n");
				break;
			case 2:
				//��������
				Linked_Make_Dir(root, FileName);
				break;
			case 3:
				//��������
				break;
			case 4:
				//���������� ���ư���
				break;
			case 5:
				roof = 0;
				break;
			default:
				printf("�ٽ� �Է����ּ���\n\n");
				break;
		}
	}
}

//�̸����� ����
void Linked_Access_Dir(Linked_File_Node* node) {
	system("cls");
	printf("���� ����Ʈ : %s\n", node->File_Name);
	printf("�����ϰ��� �ϴ� ���丮 : ");
}



void Linked_File_Tree_main() {
	Linked_File_Node* root;
	Linked_Child_List* currentNodeList;//���� �θ����� �ڽ� ����Ʈ
	Linked_Child_List* Child_Head;	//�ڽĳ���� ���
	char arr_FileName[FILE_NAME_MAX_SIZE];
	int selectNum;
	int roof = 1;

	//ó�� UI �������� root �����ϱ�
	root = Linked_UI_Create_Root(arr_FileName);	//�������� ����

	Linked_dir_list(root, arr_FileName);

}










//------------------------------------------------------------------------------------------------------------------------------------------------------------
//2. �����迭�� �̿��� ����ü�� ��
typedef struct Array_File_Node {
	char* File_Name;
	char* File_Date;
	char* File_Type;		//dir or txt
	int type;		//0�̸� ���丮 1�̸� ����
	struct Array_File_Node** child_arr;		//�ڽ� ������ ����Ű�� ������ �迭
	int child_count;		//���� �ڽĳ���� ��
	int child_capacity;		//�迭�� ���� �뷮
}Array_File_Node;
//�ڽĳ����� ����Ű�� �����͹迭�� �������� ũ�⸦ �ø��ų� �ٿ��� �ڽĳ����� �Ҵ��ϴ� ���
Array_File_Node* Array_Create_File_Node(char* name, int type) {
	Array_File_Node* newNode = (Array_File_Node*)malloc(sizeof(Array_File_Node));
	newNode->File_Name = name;
	newNode->type = type;		//0=dir, 1=txt
	newNode->File_Type = type == 0 ? "dir" : "txt";
	newNode->child_count = 0;
	newNode->child_capacity = 2;	//�ʱ� �뷮
	newNode->child_arr = (Array_File_Node**)malloc(newNode->child_capacity * sizeof(Array_File_Node*));
	return newNode;
}
//�ڽ��� �뷮�� ���� �� �ʿ��Ѱ�� �������� �÷��ִ� ����
void Array_Add_Child(Array_File_Node* parent, Array_File_Node* child) {
	if (parent->child_count >= parent->child_capacity) {//��������� �÷������
		parent->child_capacity *= 2; //�ι� �÷���
		parent->child_arr = (Array_File_Node**)realloc(parent->child_arr, parent->child_capacity * sizeof(Array_File_Node*)); 
	}
	parent->child_arr[parent->child_count++] = child;
}

void Array_File_Tree_main() {
	printf("�����迭 Ʈ�� ���� Ž����");
}


void File_main() {
	int selectNum;
	printf("1. �����迭 Ʈ��, 2. ���Ḯ��Ʈ Ʈ��: ");
	scanf_s("%d", &selectNum);

	switch (selectNum) {
		case 1:
			Array_File_Tree_main();
			break;
		case 2:
			Linked_File_Tree_main();
			break;
		default:
			printf("�߸� �Է�");
	}


}