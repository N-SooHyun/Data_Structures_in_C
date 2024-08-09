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

//���� �ʱ�ȭ
void initStack(Stack* s) {
	s->top = -1;
}

//���� Ȯ��
int Stack_isEmpty(Stack* s) {
	return s->top == -1;
}

//���� ���� á���� Ȯ��
int Stack_isFull(Stack* s) {
	return s->top == MAX_STACK_SIZE;
}

//���ÿ� ������ �߰�
void Stack_pushData(Stack* s, char *cData){
	if (Stack_isFull(s)) {
		printf("������ ���� ���־��");
		exit(1);
	}
	//s->stack[++(s->top)] = Data;
	s->top++;
	s->Data[s->top] = _strdup(cData);
}

//���ÿ��� ������ ������
char* Stack_popData(Stack* s) {
	if (Stack_isEmpty(s)) {
		printf("������ ����־��");
		exit(1);
	}
	char* Data = s->Data[s->top];
	s->Data[s->top] = NULL;
	(s->top)--;
	return Data;
}

//������ �������� �ִ� ������ ��ȸ�ϱ�
char* Stack_Check(Stack* s) {
	if (Stack_isEmpty(s)) {
		printf("��ȸ�� ������ ����ִ�.");
		exit(1);
	}
	return s->Data[s->top];
}

/*-------------------------�⺻���� ������ ����---------------------------*/
//������ �̿��� Ȩ������ �ڷΰ��� �����ΰ���
void Web_forward_back(Stack *s) {
	int select;
	printf("�˻�â : ");
	char URL[100];
	gets_s(URL, sizeof(URL));
	Stack_pushData(s, URL);
	
	while (1) {
		system("cls");
		printf("-------------------%s------------------\n", Stack_Check(s));
		printf("1. �ڷΰ���, 2.�˻�, 0. ����\n");
		scanf_s("%d", &select);
		while (getchar() != '\n');
		switch (select) {
			case 1:
				Stack_popData(s);
				break;
			case 2:
				printf("�˻�â : ");
				gets_s(URL, sizeof(URL));
				Stack_pushData(s, URL);
				break;
			case 0:
				printf("����");
				exit(1);
				break;
			default :
				printf("�߸�����");
				break;
		}
	}
}

//���ý��� ���� �Լ�
void Stack_main() {
	Stack s;
	initStack(&s);
	Web_forward_back(&s);
}