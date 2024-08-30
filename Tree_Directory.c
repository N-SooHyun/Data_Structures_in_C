#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
//#include "Tree_Directory.h">

#define FILE_NAME_MAX_SIZE 20
//트리 구조를 이용한 파일 탐색기
//파일 탐색기는 2진으로 딱 떨어지는구조가 아닌 변수형 트리이기때문에
//동적배열을 사용하거나 연결리스트를 이용해야한다.

//1. 연결리스트를 이용한 구조체의 모델
typedef struct Linked_Child_List {		//자식노드들을 가지는 연결리스트
	struct Linked_File_Node* child;		//실제 자식노드의 구조체
	struct Linked_File_Node* parent;	//나의 부모
	struct Linked_Child_List* next;		//형제들중 내 직속동생	동생이없다면 막내
	struct Linked_Child_List* prev;		//형제들중 내 직속형		형이없다면 첫째
}Linked_Child_List;

typedef struct Linked_File_Node {
	char File_Name[FILE_NAME_MAX_SIZE];
	char* File_Date;
	char* File_Type;
	int type;		//0=dir, 1=txt
	struct Linked_Child_List* parent_list;  //자신이 속한 부모의 리스트
	struct Linked_Child_List* child_list;	//자식 노드들의 리스트	연결리스트의 헤드부분
	int size;		//현재 자식 노드의 수
}Linked_File_Node;
/*
	부모 노드 -> 자식리스트 -> 자식파일노드와 더불어 다음 자식리스트를 가리킴
	부모 -> 자식1 -> 자식2 -> 자식3 -> 자식4
	이런 느낌
	자식1 -> 손자1 -> 손자2 ->손자3 			
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

//자식리스트 생성
Linked_Child_List* Linked_Create_Child_List(Linked_File_Node* currentParent, Linked_Child_List* currentNode, char name[], int type) {
	currentNode = (Linked_Child_List*)malloc(sizeof(Linked_Child_List));		//자식연결노드 메모리 공간 할당
	currentNode->next = NULL;													//막내라서 다음 형 없음
	currentNode->child = Linked_Create_File_Node(name, type, currentNode);					//자식연결노드에 진짜 자식데이터를 생성
	currentNode->prev = NULL;
	currentNode->parent = currentParent;		//자식리스트를 가지는 부모는 현재의 노드가 됨
	return currentNode;
}

//자식리스트 삽입
Linked_Child_List* Linked_Insert_File_Node(char name[], int type, Linked_File_Node* currentNode, Linked_Child_List* currentChildList) {
	if (currentChildList == NULL) {//자식 dir가 아무것도 없을때
		currentChildList = Linked_Create_Child_List(currentNode, currentChildList, name, type);
		return currentChildList;
	}
	//재귀함수의 조건식 연결리스트의 끝자락으로 더이상의 자식노드가 없을때
	if (currentChildList->next == NULL) {
		currentChildList->next = Linked_Insert_File_Node(name, type, currentNode,currentChildList->next);
		currentChildList->next->prev = currentChildList;	//이중연결
		return currentChildList;
	}
	else {
		Linked_Insert_File_Node(name, type, currentNode, currentChildList->next);
		return currentChildList;
	}
}

//자식탐색
Linked_Child_List* Linked_Select_File_Node(char name[], Linked_Child_List* childListNode) {
	if (childListNode == NULL) return NULL;

	if (strcmp(name, childListNode->child->File_Name) == 0) {
		//파일 찾음
		return childListNode;
	}
	else {
		//파일 못찾음
		childListNode = Linked_Select_File_Node(name, childListNode->next);
		return childListNode;
	}
}

Linked_Child_List* Linked_Delete_Child_List(Linked_Child_List* childListNode, Linked_File_Node* parent);
Linked_File_Node* Linked_Delete_File_Node(Linked_File_Node* childNode);

//트리삭제 자식1을 삭제할경우 자식1에 속한 모든 자식 손자는 전부 삭제되어야함
//자식 노드 삭제
Linked_File_Node* Linked_Delete_File_Node(Linked_File_Node* childNode) {
	//자식리스트를 소유하고 있는가? 없다면 자식이 없음
	if (childNode == NULL) {
		return NULL;
	}

	if (childNode->child_list != NULL) {//자식리스트 존재
		Linked_Delete_Child_List(childNode->child_list, childNode);
		childNode->child_list = NULL; 
	}

	//현재 노드 제거
	free(childNode);
	return NULL;
}

//자식리스트 삭제
Linked_Child_List* Linked_Delete_Child_List(Linked_Child_List* childListNode, Linked_File_Node* parent) {	
	//자식이 더 존재하는가?에 대해서 확인절차를 거치고 재귀를 진행
	if (childListNode == NULL) {	//자식이 없음 리스트가 없기에
		return NULL;
	}
	
	//자식이 존재
	Linked_Delete_File_Node(childListNode->child);
	childListNode->child = NULL;

	//A B C의 자식리스트가 연결된 가운데 B리스트를 제거한다면 A와 C가 연결되어야 한다.
	//case3가지 head인 A가없는경우 mid인B가없는경우 tail인C가 없는경우
	//case1 A가없는경우 B의 prev=null으로 해준뒤 부모가 B를 가리키게 만들어야함
	//case2 B가없는경우 A의 next=b->next로 해주면 끝
	//case3 C가없는경우 b->next=NULL;만 해주면됨

	//case3		자식이 한개인경우도 포함
	if (childListNode->next == NULL) {
		if (childListNode->prev != NULL) {
			childListNode->prev->next = NULL;//앞에 직속형제가 있는경우 NULL값으로 잊으라고 함
		}
		else {//첫째이면서 자식이 혼자인경우
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
		childListNode->next->prev = NULL;//B가 head가 됨
		parent->child_list = childListNode->next;//B가
		free(childListNode);
	}
	
}


//자식리스트 모두 보여주기
int Linked_File_print(Linked_File_Node* root) {		
	if (root->child_list == NULL) {//자식이 한명도 없을경우
		printf("하위 폴더 없음"); 
		return 0;	//하위폴더 없음F
	}
	Linked_Child_List* current_child_list = root->child_list;
	while (current_child_list->next!=NULL) {
		printf("%s  ", current_child_list->child->File_Name);
		current_child_list = current_child_list->next;
	}
	printf("%s  ", current_child_list->child->File_Name);
	return 1;		//하위폴더 존재T
}


/*------------------------UI부분 함수---------------------------------------*/


//파일명 받아오기
void Linked_Input_File_Name(char arr_FileName[]) {
	int size = FILE_NAME_MAX_SIZE;
	char ch;
	int i;
	//while (getchar() != '\n');
	while (1) {
		printf("폴더의 이름을 알려주세요(20자) : ");
		i = 0;
		memset(arr_FileName, '\0', size);
		

		while ((ch = getchar()) != '\n' && ch != EOF) {
			if (i < size - 1) {
				arr_FileName[i++] = ch;
			}
			else {
				printf("이름값이 너무 길어요(20자)\n");
				while (getchar() != '\n');		//남아있는 입력버퍼를 전부 버려줌
				i = 0;
				memset(arr_FileName, '\0', size);
				break;//다시 입력을 받기위해 반복문 빠져나감
			}
		}
		if (i > 0 && i < size) {
			arr_FileName[i] = '\0';
			break;
		}
		else {
			printf("다시 입력 해주세요\n");
		}
	}
}

//폴더 삭제
void Linked_Delete_Dir(Linked_File_Node* parent, char FileName[]) {
	Linked_Child_List* child;
	while (1) {
		Linked_Input_File_Name(FileName);//파일명 받아오기
		child = Linked_Select_File_Node(FileName, parent->child_list);
		if (child == NULL) {
			printf("찾을 수 없는 하위 디렉토리 입니다.");
			printf("다시 입력하세요\n");
		}
		else break;
	}
	Linked_Delete_Child_List(child, parent);
}

//하위폴더 생성
Linked_Child_List* Linked_Make_Dir(Linked_File_Node* parent, char FileName[]) {
	int type;
	Linked_Input_File_Name(FileName);//파일명 받아오기
	while (1) {
		printf("타입은 무엇인가요(0:dir, 1:txt) : ");
		scanf_s("%d", &type);
		while (getchar() != '\n');//입력버퍼 지우기
		if (type == 0 || type == 1) break;
		printf("잘못 입력하셨습니다. 다시 입력해주세요\n");
	}

	return Linked_Insert_File_Node(FileName, type, parent, parent->child_list);
}

//이름으로 진입
Linked_File_Node* Linked_Access_Dir(Linked_File_Node* ParentNode, char FileName[]) {
	Linked_Child_List* ChildNode;
	while (1) {
		Linked_Input_File_Name(FileName);//파일명 받아오기
		ChildNode = Linked_Select_File_Node(FileName, ParentNode->child_list);
		if (ChildNode == NULL) {
			printf("찾을 수 없는 하위 디렉토리 입니다. ");
			printf("다시 입력하세요");
		}
		else break;
	}
	return ChildNode->child;
}

//시작 부분
Linked_File_Node* Linked_UI_Create_Root(char arr_FileName[]) {
	printf("파일 탐색기\n");
	printf("만들고 싶은 ");
	Linked_Input_File_Name(arr_FileName);
	Linked_File_Node* root = Linked_Create_File_Node(arr_FileName, 0, NULL);
	return root;
}

//상위폴더로 돌아가기
Linked_File_Node* Linked_dir_return(Linked_File_Node* ParentNode) {
	Linked_Child_List* returnNode = ParentNode->parent_list;
	if (returnNode == NULL) {
		printf("더 이상의 상위 폴더가 없습니다. 이미 최상위 폴더에 있습니다.\n");
		return ParentNode;
	}
	return returnNode->parent;
}

//폴더 리스트
void Linked_dir_list(Linked_File_Node* root, char FileName[]) {
	int selectNum;
	int roof = 1;
	boolean child_dir;	//하위폴더여부
	Linked_File_Node* HeadRoot = root;	//최상위 헤드폴더
	Linked_File_Node* ParentNode = root;		//현재 부모 노드
	Linked_File_Node* TempNode;				
	Linked_Child_List* ChildNode = root->child_list;		//현재 자식 노드
	while (roof) {
		system("cls");
		printf("<상위 폴더 : %s>\n", ParentNode->File_Name);
		printf("하위 폴더 리스트 : ");
		child_dir = Linked_File_print(ParentNode);
		printf("\n");
		printf("1. 폴더진입, 2. 폴더생성, 3. 폴더삭제, 4. 상위폴더로 돌아가기, 5. 종료: ");
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
				printf("하위 폴더가 없습니다.\n");
				break;
			case 2:
				//폴더생성
				ParentNode->child_list = Linked_Make_Dir(ParentNode, FileName);
				break;
			case 3:
				//폴더삭제
				if (child_dir) {
					Linked_Delete_Dir(ParentNode, FileName);
					break;
				}
				printf("하위 폴더가 없습니다.\n");
				break;
			case 4:
				ParentNode = Linked_dir_return(ParentNode);
				break;
			case 5:
				roof = 0;
				break;
			default:
				printf("다시 입력해주세요\n\n");
				break;
		}
	}
}


void Linked_File_Tree_main() {
	Linked_File_Node* root;
	Linked_Child_List* currentNodeList;//현재 부모노드의 자식 리스트
	Linked_Child_List* Child_Head;	//자식노드의 헤드
	char arr_FileName[FILE_NAME_MAX_SIZE];
	int selectNum;
	int roof = 1;

	//처음 UI 상위폴더 root 생성하기
	root = Linked_UI_Create_Root(arr_FileName);	//상위폴더 생성

	Linked_dir_list(root, arr_FileName);

}









//------------------------------------------------------------------------------------------------------------------------------------------------------------
//2. 동적배열을 이용한 구조체의 모델
typedef struct Array_File_Node{
	char File_Name[FILE_NAME_MAX_SIZE];
	char* File_Date;
	char* File_Type;		//dir or txt
	int type;		//0이면 디렉토리 1이면 파일
	struct Array_File_Node** child_arr;		//자식 노드들을 가리키는 포인터 배열
	int child_count;		//현재 자식노드의 수
	int child_capacity;		//배열의 현재 용량
}Array_File_Node;

//자식노드들을 가리키는 포인터배열을 동적으로 크기를 늘리거나 줄여서 자식노드들을 할당하는 방식
Array_File_Node* Array_Create_File_Node(char name[], int type) {
	Array_File_Node* newNode = (Array_File_Node*)malloc(sizeof(Array_File_Node));
	strcpy_s(newNode->File_Name, sizeof(newNode->File_Name), name);
	newNode->type = type;		//0=dir, 1=txt
	newNode->File_Type = type == 0 ? "dir" : "txt";
	newNode->child_count = 0;
	newNode->child_capacity = 2;	//초기 용량
	newNode->child_arr = (Array_File_Node**)malloc(newNode->child_capacity * sizeof(Array_File_Node*));
	return newNode;
}
//자식이 용량에 비해 더 필요한경우 동적으로 늘려주는 역할
void Array_Add_Child(Array_File_Node* parent, Array_File_Node* child) {
	if (parent->child_count >= parent->child_capacity) {//가득찬경우 늘려줘야함
		parent->child_capacity *= 2; //두배 늘려줌
		parent->child_arr = (Array_File_Node**)realloc(parent->child_arr, parent->child_capacity * sizeof(Array_File_Node*)); 
	}
	parent->child_arr[parent->child_count++] = child;
}

void Array_File_Tree_main() {
	Array_File_Node root;
	root.File_Name[0] = "C:";
	root.child_capacity = 10;//용량 자식노드
	root.child_count = 0; //아직 자식노드 없음
	root.child_arr = (Array_File_Node**)malloc(sizeof(Array_File_Node*) * root.child_capacity);

	Array_File_Node newNode;
	newNode.File_Name[0] = "down";
	

	root.child_arr[0] = &newNode;

	printf("root의 주소 : %p\n", &root);
	printf("root의 자식 리스트의 주소 : %p\n", root.child_arr);
	printf("root의 자식 : %p\n", root.child_arr[0]);
}






















void File_main() {
	int selectNum;
	printf("1. 동적배열 트리, 2. 연결리스트 트리: ");
	scanf_s("%d", &selectNum);

	switch (selectNum) {
		case 1:
			Array_File_Tree_main();
			break;
		case 2:
			Linked_File_Tree_main();
			break;
		default:
			printf("잘못 입력");
	}


}