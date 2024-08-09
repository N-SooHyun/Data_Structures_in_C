#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>

#define MAX_STACK_SIZE 100

typedef struct {
	int stack[MAX_STACK_SIZE];
	char* Data[MAX_STACK_SIZE];
	int top;
}Stack;

//스택 초기화
void initStack(Stack* s) {
	s->top = -1;
}

//스택 확인
int Stack_isEmpty(Stack* s) {
	return s->top == -1;
}

//스택 가득 찼는지 확인
int Stack_isFull(Stack* s) {
	return s->top == MAX_STACK_SIZE;
}

//스택에 데이터 추가
void Stack_pushData(Stack* s, char *cData){
	if (Stack_isFull(s)) {
		printf("스택이 가득 차있어요");
		exit(1);
	}
	//s->stack[++(s->top)] = Data;
	s->top++;
	s->Data[s->top] = _strdup(cData);
}

//스택에서 데이터 꺼내기
char* Stack_popData(Stack* s) {
	if (Stack_isEmpty(s)) {
		printf("스택이 비어있어요");
		exit(1);
	}
	char* Data = s->Data[s->top];
	s->Data[s->top] = NULL;
	(s->top)--;
	return Data;
}

//스택의 가장위에 있는 데이터 조회하기
char* Stack_Check(Stack* s) {
	if (Stack_isEmpty(s)) {
		printf("조회한 스택이 비어있다.");
		exit(1);
	}
	return s->Data[s->top];
}

/*-------------------------기본적인 스택의 구현---------------------------*/
//스택을 이용한 홈페이지 뒤로가기 앞으로가기
void Web_forward_back(Stack *s) {
	int select;
	printf("검색창 : ");
	char URL[100];
	gets_s(URL, sizeof(URL));
	Stack_pushData(s, URL);
	
	while (1) {
		system("cls");
		printf("-------------------%s------------------\n", Stack_Check(s));
		printf("1. 뒤로가기, 2.검색, 0. 종료\n");
		scanf_s("%d", &select);
		while (getchar() != '\n');
		switch (select) {
			case 1:
				Stack_popData(s);
				break;
			case 2:
				printf("검색창 : ");
				gets_s(URL, sizeof(URL));
				Stack_pushData(s, URL);
				break;
			case 0:
				printf("종료");
				exit(1);
				break;
			default :
				printf("잘못누름");
				break;
		}
	}
}

//스택실행 메인 함수
void Stack_main() {
	Stack s;
	initStack(&s);
	Web_forward_back(&s);
}