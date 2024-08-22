#pragma once

typedef struct Linked_Child_List {		//자식노드들을 가지는 연결리스트
	struct Linked_File_Node* child;		//실제 자식노드의 구조체
	struct Linked_Child_List* next;		//부모의 다음 자식 가리키는 구조체
}Linked_Child_List;

typedef struct Linked_File_Node {
	char* File_Name;
	char* File_Date;
	char* File_Type;
	int type;		//0=dir, 1=txt
	struct Linked_Child_List* child_list;	//자식 노드들의 리스트	연결리스트의 헤드부분
	int size;		//현재 자식 노드의 수
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