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
	struct Linked_File_Node* parent;	//���� �θ�
	struct Linked_Child_List* next;		//�������� �� ���ӵ���	�����̾��ٸ� ����
	struct Linked_Child_List* prev;		//�������� �� ������		���̾��ٸ� ù°
}Linked_Child_List;

typedef struct Linked_File_Node {
	char File_Name[FILE_NAME_MAX_SIZE];
	char* File_Date;
	char* File_Type;
	int type;		//0=dir, 1=txt
	struct Linked_Child_List* parent_list;  //�ڽ��� ���� �θ��� ����Ʈ
	struct Linked_Child_List* child_list;	//�ڽ� ������ ����Ʈ	���Ḯ��Ʈ�� ���κ�
	int size;		//���� �ڽ� ����� ��
}Linked_File_Node;
/*
	�θ� ��� -> �ڽĸ���Ʈ -> �ڽ����ϳ��� ���Ҿ� ���� �ڽĸ���Ʈ�� ����Ŵ
	�θ� -> �ڽ�1 -> �ڽ�2 -> �ڽ�3 -> �ڽ�4
	�̷� ����
	�ڽ�1 -> ����1 -> ����2 ->����3 			
*/
Linked_File_Node* Linked_Create_File_Node(char name[], int type, Linked_Child_List* Parent) {
	Linked_File_Node* newNode = (Linked_File_Node*)malloc(sizeof(Linked_File_Node));
	strcpy_s(newNode->File_Name, sizeof(newNode->File_Name), name);
	newNode->type = type;
	newNode->File_Type = type == 0 ? "dir" : "txt";
	newNode->size = 0;
	newNode->child_list = NULL;
	newNode->parent_list = Parent;
	return newNode;
}

//�ڽĸ���Ʈ ����
Linked_Child_List* Linked_Create_Child_List(Linked_File_Node* currentParent, Linked_Child_List* currentNode, char name[], int type) {
	currentNode = (Linked_Child_List*)malloc(sizeof(Linked_Child_List));		//�ڽĿ����� �޸� ���� �Ҵ�
	currentNode->next = NULL;													//������ ���� �� ����
	currentNode->child = Linked_Create_File_Node(name, type, currentNode);					//�ڽĿ����忡 ��¥ �ڽĵ����͸� ����
	currentNode->prev = NULL;
	currentNode->parent = currentParent;		//�ڽĸ���Ʈ�� ������ �θ�� ������ ��尡 ��
	return currentNode;
}

//�ڽĸ���Ʈ ����
Linked_Child_List* Linked_Insert_File_Node(char name[], int type, Linked_File_Node* currentNode, Linked_Child_List* currentChildList) {
	if (currentChildList == NULL) {//�ڽ� dir�� �ƹ��͵� ������
		currentChildList = Linked_Create_Child_List(currentNode, currentChildList, name, type);
		return currentChildList;
	}
	//����Լ��� ���ǽ� ���Ḯ��Ʈ�� ���ڶ����� ���̻��� �ڽĳ�尡 ������
	if (currentChildList->next == NULL) {
		currentChildList->next = Linked_Insert_File_Node(name, type, currentNode,currentChildList->next);
		currentChildList->next->prev = currentChildList;	//���߿���
		return currentChildList;
	}
	else {
		Linked_Insert_File_Node(name, type, currentNode, currentChildList->next);
		return currentChildList;
	}
}

//�ڽ�Ž��
Linked_Child_List* Linked_Select_File_Node(char name[], Linked_Child_List* childListNode) {
	if (childListNode == NULL) return NULL;

	if (strcmp(name, childListNode->child->File_Name) == 0) {
		//���� ã��
		return childListNode;
	}
	else {
		//���� ��ã��
		childListNode = Linked_Select_File_Node(name, childListNode->next);
		return childListNode;
	}
}

Linked_Child_List* Linked_Delete_Child_List(Linked_Child_List* childListNode, Linked_File_Node* parent);
Linked_File_Node* Linked_Delete_File_Node(Linked_File_Node* childNode);

//Ʈ������ �ڽ�1�� �����Ұ�� �ڽ�1�� ���� ��� �ڽ� ���ڴ� ���� �����Ǿ����
//�ڽ� ��� ����
Linked_File_Node* Linked_Delete_File_Node(Linked_File_Node* childNode) {
	//�ڽĸ���Ʈ�� �����ϰ� �ִ°�? ���ٸ� �ڽ��� ����
	if (childNode == NULL) {
		return NULL;
	}

	if (childNode->child_list != NULL) {//�ڽĸ���Ʈ ����
		Linked_Delete_Child_List(childNode->child_list, childNode);
		childNode->child_list = NULL; 
	}

	//���� ��� ����
	free(childNode);
	return NULL;
}

//�ڽĸ���Ʈ ����
Linked_Child_List* Linked_Delete_Child_List(Linked_Child_List* childListNode, Linked_File_Node* parent) {	
	//�ڽ��� �� �����ϴ°�?�� ���ؼ� Ȯ�������� ��ġ�� ��͸� ����
	if (childListNode == NULL) {	//�ڽ��� ���� ����Ʈ�� ���⿡
		return NULL;
	}
	
	//�ڽ��� ����
	Linked_Delete_File_Node(childListNode->child);
	childListNode->child = NULL;

	//A B C�� �ڽĸ���Ʈ�� ����� ��� B����Ʈ�� �����Ѵٸ� A�� C�� ����Ǿ�� �Ѵ�.
	//case3���� head�� A�����°�� mid��B�����°�� tail��C�� ���°��
	//case1 A�����°�� B�� prev=null���� ���ص� �θ� B�� ����Ű�� ��������
	//case2 B�����°�� A�� next=b->next�� ���ָ� ��
	//case3 C�����°�� b->next=NULL;�� ���ָ��

	//case3		�ڽ��� �Ѱ��ΰ�쵵 ����
	if (childListNode->next == NULL) {
		if (childListNode->prev != NULL) {
			childListNode->prev->next = NULL;//�տ� ���������� �ִ°�� NULL������ ������� ��
		}
		else {//ù°�̸鼭 �ڽ��� ȥ���ΰ��
			parent->child_list = NULL;
		}
		free(childListNode);
	}
	//case2
	else if(childListNode->next != NULL && childListNode->prev != NULL){
		childListNode->prev->next = childListNode->next;
		free(childListNode);
	}
	//case1
	else if (childListNode->prev == NULL && childListNode->next != NULL) {
		childListNode->next->prev = NULL;//B�� head�� ��
		parent->child_list = childListNode->next;//B��
		free(childListNode);
	}
	
}


//�ڽĸ���Ʈ ��� �����ֱ�
int Linked_File_print(Linked_File_Node* root) {		
	if (root->child_list == NULL) {//�ڽ��� �Ѹ� �������
		printf("���� ���� ����"); 
		return 0;	//�������� ����F
	}
	Linked_Child_List* current_child_list = root->child_list;
	while (current_child_list->next!=NULL) {
		printf("%s  ", current_child_list->child->File_Name);
		current_child_list = current_child_list->next;
	}
	printf("%s  ", current_child_list->child->File_Name);
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

//���� ����
void Linked_Delete_Dir(Linked_File_Node* parent, char FileName[]) {
	Linked_Child_List* child;
	while (1) {
		Linked_Input_File_Name(FileName);//���ϸ� �޾ƿ���
		child = Linked_Select_File_Node(FileName, parent->child_list);
		if (child == NULL) {
			printf("ã�� �� ���� ���� ���丮 �Դϴ�.");
			printf("�ٽ� �Է��ϼ���\n");
		}
		else break;
	}
	Linked_Delete_Child_List(child, parent);
}

//�������� ����
Linked_Child_List* Linked_Make_Dir(Linked_File_Node* parent, char FileName[]) {
	int type;
	Linked_Input_File_Name(FileName);//���ϸ� �޾ƿ���
	while (1) {
		printf("Ÿ���� �����ΰ���(0:dir, 1:txt) : ");
		scanf_s("%d", &type);
		while (getchar() != '\n');//�Է¹��� �����
		if (type == 0 || type == 1) break;
		printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���\n");
	}

	return Linked_Insert_File_Node(FileName, type, parent, parent->child_list);
}

//�̸����� ����
Linked_File_Node* Linked_Access_Dir(Linked_File_Node* ParentNode, char FileName[]) {
	Linked_Child_List* ChildNode;
	while (1) {
		Linked_Input_File_Name(FileName);//���ϸ� �޾ƿ���
		ChildNode = Linked_Select_File_Node(FileName, ParentNode->child_list);
		if (ChildNode == NULL) {
			printf("ã�� �� ���� ���� ���丮 �Դϴ�. ");
			printf("�ٽ� �Է��ϼ���");
		}
		else break;
	}
	return ChildNode->child;
}

//���� �κ�
Linked_File_Node* Linked_UI_Create_Root(char arr_FileName[]) {
	printf("���� Ž����\n");
	printf("����� ���� ");
	Linked_Input_File_Name(arr_FileName);
	Linked_File_Node* root = Linked_Create_File_Node(arr_FileName, 0, NULL);
	return root;
}

//���������� ���ư���
Linked_File_Node* Linked_dir_return(Linked_File_Node* ParentNode) {
	Linked_Child_List* returnNode = ParentNode->parent_list;
	if (returnNode == NULL) {
		printf("�� �̻��� ���� ������ �����ϴ�. �̹� �ֻ��� ������ �ֽ��ϴ�.\n");
		return ParentNode;
	}
	return returnNode->parent;
}

//���� ����Ʈ
void Linked_dir_list(Linked_File_Node* root, char FileName[]) {
	int selectNum;
	int roof = 1;
	boolean child_dir;	//������������
	Linked_File_Node* HeadRoot = root;	//�ֻ��� �������
	Linked_File_Node* ParentNode = root;		//���� �θ� ���
	Linked_File_Node* TempNode;				
	Linked_Child_List* ChildNode = root->child_list;		//���� �ڽ� ���
	while (roof) {
		system("cls");
		printf("<���� ���� : %s>\n", ParentNode->File_Name);
		printf("���� ���� ����Ʈ : ");
		child_dir = Linked_File_print(ParentNode);
		printf("\n");
		printf("1. ��������, 2. ��������, 3. ��������, 4. ���������� ���ư���, 5. ����: ");
		scanf_s("%d", &selectNum);
		while (getchar() != '\n');
		switch (selectNum) {
			case 1:
				if (child_dir) {
					TempNode = Linked_Access_Dir(ParentNode, FileName);
					if (TempNode != NULL) {
						ParentNode = TempNode;
						TempNode = NULL;
					}
					break;
				}
				system("cls");
				printf("���� ������ �����ϴ�.\n");
				break;
			case 2:
				//��������
				ParentNode->child_list = Linked_Make_Dir(ParentNode, FileName);
				break;
			case 3:
				//��������
				if (child_dir) {
					Linked_Delete_Dir(ParentNode, FileName);
					break;
				}
				printf("���� ������ �����ϴ�.\n");
				break;
			case 4:
				ParentNode = Linked_dir_return(ParentNode);
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
typedef struct Array_File_Node{
	char File_Name[FILE_NAME_MAX_SIZE];
	char* File_Date;
	char* File_Type;		//dir or txt
	int type;		//0�̸� ���丮 1�̸� ����
	struct Array_File_Node** child_arr;		//�ڽ� ������ ����Ű�� ������ �迭
	int child_count;		//���� �ڽĳ���� ��
	int child_capacity;		//�迭�� ���� �뷮
}Array_File_Node;

//�ڽĳ����� ����Ű�� �����͹迭�� �������� ũ�⸦ �ø��ų� �ٿ��� �ڽĳ����� �Ҵ��ϴ� ���
Array_File_Node* Array_Create_File_Node(char name[], int type) {
	Array_File_Node* newNode = (Array_File_Node*)malloc(sizeof(Array_File_Node));
	strcpy_s(newNode->File_Name, sizeof(newNode->File_Name), name);
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
	Array_File_Node root;
	root.File_Name[0] = "C:";
	root.child_capacity = 10;//�뷮 �ڽĳ��
	root.child_count = 0; //���� �ڽĳ�� ����
	root.child_arr = (Array_File_Node**)malloc(sizeof(Array_File_Node*) * root.child_capacity);

	Array_File_Node newNode;
	newNode.File_Name[0] = "down";
	

	root.child_arr[0] = &newNode;

	printf("root�� �ּ� : %p\n", &root);
	printf("root�� �ڽ� ����Ʈ�� �ּ� : %p\n", root.child_arr);
	printf("root�� �ڽ� : %p\n", root.child_arr[0]);
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