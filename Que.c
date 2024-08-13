#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>

//��ȯ �� ���Ḯ��Ʈ�� �����Ǿ��ֱ⿡ �ε����� ������ġ�� �ִٸ� ����ִٴ°� ����ؾ���
//Front==Rear�϶� Empty��� ��ĭ�� ������ ��������
//Front==Rear�϶� Full�̶�� Empty�� Ȯ���� �� ����
//���� que[5]¥���� 1 2 3 4 5�ϰ�� Front(0)==Rear(0)�϶� ����� 1�̵Ǿ���ϴµ� 5�� ��µǴ� �һ�� �߻�
//que[5] NL 1 2 3 4 Front(0) Rear(4)�ϰ�� ���������� Ȯ���ϰ� Front++�� �ϳ��� ����
//que[5] NL NL NL NL NL Front(4) Rear(4)�� ��������� Ȯ���� �� ����
typedef struct {
	int Data[5];
	int size;
	int Front;
	int Rear;
}Que_Array;

void initQueue(Que_Array* q) {
	q->Front = 0;
	q->Rear = 0;
}

int Que_isEmpty(Que_Array* q) {
	return q->Front == q->Rear;
}

int Que_isFull(Que_Array* q) {
	return (q->Front==0 && q->Rear==q->size-1) || (q->Front == q->Rear+1); 
	//0 5 or 1 0,2 1, 3 2, 4 3 �϶�
}

//���԰� ��¸�� �ε����� ��ġ�� �ٲٰ� �����͸� ����
void enqueue(Que_Array* q, int Data) {
	if (Que_isFull(q)) {
		printf("ť�� ��� á���ϴ�.");
		return;
	}
	
	if (q->Rear == q->size - 1) {
		q->Rear = 0;
	}
	else {
		q->Rear++;
	}
	q->Data[q->Rear] = Data;
	/*
	q->Rear = (q->Rear + 1) % q->size;
	q->Data[q ->Rear] = Data;
	*/
}

int dequeue(Que_Array* q) {
	if (Que_isEmpty(q)) {
		printf("ť�� ��� ������ϴ�.");
		return -1;
	}
	if (q->Front == q->size - 1) {
		q->Front = 0;
	}
	else {
		q->Front++;
	}
	/*
	q->Front = (q->Front + 1) % q->size;
	*/
	return q->Data[q->Front];
}

int peek(Que_Array* q) {
	if (Que_isEmpty(q)) {
		printf("ť�� ����ֽ��ϴ�.");
		return -1;
	}
	return q->Data[(q->Front + 1) % q->size];
}

void Que_Print(Que_Array *q) {
	printf("ť ���� : [%d, %d, %d, %d, %d]", q->Data[0], q->Data[1], q->Data[2], q->Data[3], q->Data[4]);
	printf("\t\tFront : %d,  Rear : %d\n", q->Front, q->Rear);
}

void Que_main() {
	Que_Array q;
	initQueue(&q);

}


/*-----------------------------��������°��� deque----------------------*/
typedef struct {
	int Data[6];
	int size;
	int Front;
	int Rear;
}Deque_Model;

void initDeque(Deque_Model* dq) {
	dq->size = sizeof(dq->Data) / sizeof(int);
	dq->Front = dq->Rear = 0;
}

int DeQue_isEmpty(Deque_Model* dq) {		//��ȯ�̱⿡ ������ġ�� �ε����� ������ ����ִٰ� ����
	return dq->Front == dq->Rear;
}

int DeQue_isFull(Deque_Model* dq) {			//��ȯ�̱⿡ ��ĭ�� ����־����
	return ((dq->Front == 0 && dq->Rear == dq->size - 1) || (dq->Front == dq->Rear + 1));
}

//ť�� ���������� �ε��� ��ġ�� �ٲٰ� �����͸� ����
void DeQue_addFront(Deque_Model* dq, int Data) {//���ʻ���
	if (DeQue_isFull(dq)) {
		printf("�����ֽ��ϴ�.");
		return;
	}
	
	if (dq->Front == 0) {
		dq->Front = dq->size - 1;
	}
	else {
		dq->Front--;
	}
	dq->Data[dq->Front] = Data;
}

void DeQue_addRear(Deque_Model* dq, int Data) {//���ʻ���
	if (DeQue_isFull(dq)) {
		printf("�����ֽ��ϴ�.");
		return;
	}
	
	if (dq->Rear == dq->size - 1) {
		dq->Rear = 0;
	}
	else {
		dq->Rear++;
	}
	dq->Data[dq->Rear] = Data;
}

int DeQue_removeFront(Deque_Model* dq) {	//�������� ������	

	if (DeQue_isEmpty(dq)) {//���� ������ġ�� ������		
		printf("����ֽ��ϴ�.");
		return -1;
	}
	int Data = dq->Data[dq->Front]; 
	dq->Data[dq->Front] = -1;
	if (dq->Front == dq->size - 1) {
		dq->Front = 0;
	}
	else {
		dq->Front++;
	}
	return Data;
}

int DeQue_removeRear(Deque_Model* dq) {		//�������� ������
	if (DeQue_isEmpty(dq)) {//���� ������ġ�� ������		
		printf("����ֽ��ϴ�.");
		return -1;
	}

	int Data = dq->Data[dq->Rear];
	dq->Data[dq->Front] = -1;
	if (dq->Rear == 0) {
		dq->Rear = dq->size - 1;
	}
	else {
		dq->Rear--;
	}
	return Data;
}

void DeQue_Print(Deque_Model* dq) {
	printf("DeQue[");
	for (int i = 0; i < dq->size; i++) {
		if (dq->Data[i] <= -1) {
			printf(" NL");
		}
		else
			printf(" %d", dq->Data[i]);
	}
	printf("]\n");
}

void DeQue_main() {
	Deque_Model dq;
	initDeque(&dq);

	DeQue_addFront(&dq, 1);
	DeQue_Print(&dq);
	DeQue_addFront(&dq, 1);
	DeQue_Print(&dq);

	DeQue_addRear(&dq, 2);
	DeQue_Print(&dq);
	DeQue_addRear(&dq, 2);
	DeQue_Print(&dq);
	DeQue_addRear(&dq, 2);
	DeQue_Print(&dq);
	printf("\n");

	DeQue_removeFront(&dq);
	DeQue_Print(&dq);
	DeQue_removeFront(&dq);
	DeQue_Print(&dq);
	DeQue_removeFront(&dq);
	DeQue_Print(&dq);
	DeQue_removeFront(&dq);
	DeQue_Print(&dq);
	DeQue_removeFront(&dq);
	DeQue_Print(&dq);

}