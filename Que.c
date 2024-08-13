#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>

//순환 즉 연결리스트로 구현되어있기에 인덱스가 같은위치에 있다면 비어있다는걸 명시해야함
//Front==Rear일때 Empty라면 한칸은 무조건 비워줘야함
//Front==Rear일때 Full이라면 Empty를 확인할 수 없음
//또한 que[5]짜리에 1 2 3 4 5일경우 Front(0)==Rear(0)일때 출력은 1이되어야하는데 5가 출력되는 불상사 발생
//que[5] NL 1 2 3 4 Front(0) Rear(4)일경우 꽉차있음을 확인하고 Front++씩 하나씩 빼면
//que[5] NL NL NL NL NL Front(4) Rear(4)로 비어있음을 확인할 수 있음
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
	//0 5 or 1 0,2 1, 3 2, 4 3 일때
}

//삽입과 출력모두 인덱스의 위치를 바꾸고 데이터를 삽입
void enqueue(Que_Array* q, int Data) {
	if (Que_isFull(q)) {
		printf("큐가 모두 찼습니다.");
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
		printf("큐가 모두 비었습니다.");
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
		printf("큐가 비어있습니다.");
		return -1;
	}
	return q->Data[(q->Front + 1) % q->size];
}

void Que_Print(Que_Array *q) {
	printf("큐 상태 : [%d, %d, %d, %d, %d]", q->Data[0], q->Data[1], q->Data[2], q->Data[3], q->Data[4]);
	printf("\t\tFront : %d,  Rear : %d\n", q->Front, q->Rear);
}

void Que_main() {
	Que_Array q;
	initQueue(&q);

}


/*-----------------------------이중입출력가능 deque----------------------*/
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

int DeQue_isEmpty(Deque_Model* dq) {		//순환이기에 같은위치에 인덱스가 있으면 비어있다고 가정
	return dq->Front == dq->Rear;
}

int DeQue_isFull(Deque_Model* dq) {			//순환이기에 한칸이 비어있어야함
	return ((dq->Front == 0 && dq->Rear == dq->size - 1) || (dq->Front == dq->Rear + 1));
}

//큐와 마찬가지로 인덱스 위치를 바꾸고 데이터를 삽입
void DeQue_addFront(Deque_Model* dq, int Data) {//앞쪽삽입
	if (DeQue_isFull(dq)) {
		printf("꽉차있습니다.");
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

void DeQue_addRear(Deque_Model* dq, int Data) {//뒤쪽삽입
	if (DeQue_isFull(dq)) {
		printf("꽉차있습니다.");
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

int DeQue_removeFront(Deque_Model* dq) {	//앞쪽으로 빠질때	

	if (DeQue_isEmpty(dq)) {//둘이 같은위치에 있을때		
		printf("비어있습니다.");
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

int DeQue_removeRear(Deque_Model* dq) {		//뒤쪽으로 빠질때
	if (DeQue_isEmpty(dq)) {//둘이 같은위치에 있을때		
		printf("비어있습니다.");
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