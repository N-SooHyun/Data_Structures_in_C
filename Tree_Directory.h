#pragma once

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

Linked_File_Node* Linked_Create_File_Node(char* name, int type);
Linked_Child_List* Linked_Create_Child_List(Linked_Child_List* NodeList, char* name, int type);
Linked_Child_List* Linked_Insert_File_Node(char* name, int type, Linked_Child_List* currentNodeList);
void Linked_File_print(Linked_File_Node* root);
Linked_File_Node* Linked_UI_Create_Root();
void Linked_Input_File_Name(char arr_FileName[]);
void Linked_dir_list(Linked_File_Node* root);
void Linked_Access_Dir(Linked_File_Node* node);
void Linked_File_Tree_main();