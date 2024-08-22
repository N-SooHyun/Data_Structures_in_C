#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
#include <math.h>
#include<time.h>

/*
	Ʈ�� ���� ������ ����
	���������δ� �������� ����������
	�������δ� ���� ���������̴�.
	<Ʈ�� ����>
	�Ϲ�Ʈ��-�ڽ� ����� ũ�Ⱑ �������� �ʴ� Ʈ��
	����(Binary)Ʈ��-�ڽ� ����� ũ�Ⱑ �ִ� 2���� Ʈ��
	����(Ternary)Ʈ��-�ڽ� ����� ũ�Ⱑ �ִ� 3���� Ʈ��
	��� 4 5 6���ε� ���� ����
	<Ʈ�� ���>
	����(����), �θ�-�ڽ�(root,�ڽ�,���� ��), �ܸ����(�ڽĳ�尡���³��), ��ܸ�(�ݴ�)
	<���� Ʈ�� Ư¡ or Ʈ���� ������ Ư¡>
	root�� �Ѱ������ǵǸ� �θ���� �ݵ�� �Ѱ��̱⿡
	��尳�� - 1 = ����
	���� == �ּ� ��� ����, ����Ʈ���ΰ�� �ִ����� 2^����-1�� ����
	���� : ����3¥�� ����Ʈ�� �ִ��� = (2^1-1)+(2^2-1)+(2^3-1)=(1)+(2)+(4)=7

	<�ڵ屸��>
	�迭ǥ���� - ���������� ���� ������ ���
	arr[7]�� �ִٰ� �����ҽ� arr[0]-root, arr[1,2]-root�ڽ�, arr[3,4]-1���ڽ�,arr[5,6]-2���ڽ�
	3���� ������ ����Ǿ� �������� ������
	�ڽ�(5)�� �θ���� ã�� ���� - i=5  i-1/2 = (5-1/2=2)  or i=6  i-1/2 = (6-1/2=2)
	�ڽ�(3)�� ���� �ڽ��� ã�°��� - i=3	2i + 1
	�ڽ���(3) ������ �ڽ��� ã�°��� - i=3  2i +2
	��ũǥ���� - ��ũ����Ʈ�� ����ϰ� ����ü�� �����ڽĳ�� �������ڽĳ���� ����ü�����͸� Ȱ��
*/

/*-------------------------�迭ǥ�������� ������ search Ž�� Ʈ��-----------------------------*/
// 0~100������ ���� 7���� ������ ǥ��
#define MAX_SIZE 31
int tree[MAX_SIZE];

void Array_Tree_init() {//Ʈ�� �ʱ�ȭ
	for (int i = 0; i < MAX_SIZE; i++)
		tree[i] = -1;
}

void Array_Tree_insert(int data, int index) {
	if (index >= MAX_SIZE){
		printf("Ʈ���� ���� á���ϴ�. %d���� ������ �Ұ����մϴ�.\n",data);
		return;
	}

	//���Խ� ������ ������ �������� ū���̶�� ��Ģ�� ���صΰ� ���Խ� ��͸� ���ؼ� ����
	if (tree[index] == -1) {
		tree[index] = data;
	}
	else if (data < tree[index]) {
		Array_Tree_insert(data, 2 * index + 1);
		//���� ����� ������ ������ �������� �� ���� ���� 2(�������)*(��������ġ)+1 = 2i+1
	}
	else if (data > tree[index]) {
		Array_Tree_insert(data, 2 * index + 2);
		//���� ����� ������ ũ�� ���������� �� ���� ���� 2(�������)*(��������ġ)+2 = 2i+2
	}
	return;
}

int Array_Tree_level() {
	//����� ������ �˸� ����(��)�� �� �� ����
	//���̸� �˸� ����� ������ �� �� ���� 2^����-1
	//����=h      h=log2(n+1)-1  = 2 ��� 0 1 2 -> 3���̵�(n=7�Ͻ�)
	//n=8�Ͻÿ��� 4���̵Ǿ���ϳ� h=log2(8+1)-1 = 2�� �� ������ ��������Ʈ���� �� ä������ �ʾƼ���n=15���Ǹ�h=3�̵�
	//���� ������ �ȴٸ� Ư�� �������� �ִ� ����� ������ �� �� ����(�ŵ�����������)
	//h=2�ΰ�� 2^0 = 1(root�Ѱ�), 2^1=2(1�� �ڽ�2��), 2^2(2�� �ڽ� 4��)
	//log��������� 2^n = index;�̴ϱ� 
	// 2^n/2 = index/2;�ϸ� n�� ã�� �� �ִ�. �̰� log2(n) = index; ��

	double level = log2(MAX_SIZE + 1) - 1;
	int floor = (int)ceil(level);//�ø�����
	return floor;//���� ��ȯ
}

//��ȸ�� ���� Ʈ���� �ִ� ��� ��带 �湮�ؼ� ���� ã�°� �ǹ�

void Array_Tree_preorder_traverse(int index) {//���� ��ȸ
	//root���� ���ʼ����� Ž�� 0 1 3 7 8 4 9 10 ������
	if (index >= MAX_SIZE || tree[index] == -1) return;
	printf("%d ", tree[index]); //���� ��� �湮
	Array_Tree_preorder_traverse(2 * index + 1);//���� �ڽ� ��� �湮
	Array_Tree_preorder_traverse(2 * index + 2);//������ �ڽ� ��� �湮
}

void Array_Tree_inorder_traverse(int index) {//���� ��ȸ
	//������������ root �����ʼ��� 7 3 8 1 9 4 10 0
	if (index >= MAX_SIZE || tree[index] == -1) return;
	Array_Tree_inorder_traverse(2 * index + 1);//���� �ڽ� ��� ���� �湮
	printf("%d ", tree[index]);	//���� ��� ���
	Array_Tree_inorder_traverse(2 * index + 2);//������ �ڽ� ��� ���� �湮
}

void Array_Tree_postorder_traverse(int index) {//���� ��ȸ
	//���� Ʈ���� ���� �湮 �� root 7 8 3 9 10 4 1 11 12 5
	if (index >= MAX_SIZE || tree[index] == -1) return;
	Array_Tree_postorder_traverse(2 * index + 1);//���� ���� �湮
	Array_Tree_postorder_traverse(2 * index + 2);//������ ���� �湮
	printf("%d ", tree[index]);//���� ��� ���
}

void Array_Tree_levelorder_traverse(int index) {//���� ��ȸ
	for (int i = index; i < MAX_SIZE; i++) {
		if (tree[i] != -1) 
			printf("%d ", tree[i]);
	}
}

void Array_Tree_reverse_levelorder_traverse(int index) {
	for (int i = MAX_SIZE-1; i <= index; i--) {
		if(tree[i] != -1)
			printf("%d ", tree[i]);
	}
}

int Array_Tree_Select(int data, int idx) {//ã���� �ϴ� ���� ã�� �Լ�
	if (idx >= MAX_SIZE || idx < 0) {
		printf("ã���� �ϴ� ���� ��忡 �����ϴ�.");
		return -1;
	}
	if (tree[idx] == data) {
		printf("%d ��忡 �����մϴ�.\n", idx);
		return idx;
	}
	else if (tree[idx] > data) {
		Array_Tree_Select(data, 2 * idx + 1);
	}
	else if (tree[idx] < data) {
		Array_Tree_Select(data, 2 * idx + 2);
	}
}

void Array_Tree_Delete(int data) {//ã���� �ϴ� ��带 ����
	//1. �ڽ��̾��³�� 2. �ڽ��� �Ѱ��� ��� 3. �ڽ��� �ΰ��� ���
	int idx = Array_Tree_Select(data, 0);
	if (idx == -1)return;
	
	//�ڽ��� ���� ���
	if (tree[2 * idx + 1] == -1 && tree[2 * idx + 2] == -1)
		tree[idx] = -1; //�ܼ� ��� ����
	//�ڽ��� �ϳ��� ���
	else if (tree[2 * idx + 1] == -1 || tree[2 * idx + 2] == -1) {
		int child_idx = (tree[2 * idx + 1] != -1 ? 2 * idx + 1 : 2 * idx + 2);
		tree[idx] = tree[child_idx];
		tree[child_idx] = -1;
	}
	//�ڽ��� �ΰ��� ���
	else if (tree[2 * idx + 1] != -1 && tree[2 * idx + 2] != -1) {
		int left_child_idx = 2 * idx + 1;
		int right_child_idx = 2 * idx + 2;
		int min_idx = right_child_idx;		//������ �ڽ��� �������� ���� ���� ��
		int max_idx = left_child_idx;		//���� �ڽ��� �������� ���� ū ��
		
		//�� �ΰ��� ������ ���Ѿ� Ʈ���� ũ�⸦ �������� �ʴ� ���� ���� ���ؼ� �������� Ʈ���� ���� �� ����
		//���Ƿ� �ƹ��� �θ�� �ø��� �Ǹ� �� ���������� �ڽĵ��� ���谡 ���� Ȥ�� ���������� ġ�������� ���� Ʈ��ũ�⸦ ��� �� ����
		
		//������ �ڽ��� �������� ���� ������
		while (tree[2 * min_idx + 1] != -1)//��� �������ڽ��� ���� ���� �ڽ��� Ž��
			min_idx = 2 * min_idx + 1;

		tree[idx] = tree[min_idx];	//ã�� ����� ���� ���� ��忡 ����

		//min_idx�� �̹� ������ ����� ���� ������ �ڽ��̱⶧���� 
		//������ �ڽ��� �ִ����������� ���θ� �Ǵ��ϸ� �ȴ�.
		if (tree[2 * min_idx + 2] != -1) {	//������ �ڽ��� �ִٸ�
			tree[min_idx] = tree[2 * min_idx + 2];
			tree[2 * min_idx + 2] = -1;
		}
		else {
			tree[min_idx] = -1;
		}
	}
}

void Array_Tree_print() {
	printf("���� Ž�� Ʈ�� �迭ǥ����\n");
	int level = Array_Tree_level();
	int idx = 0;
	for (int i = 0; i <= level; i++) {
		int start_index = (int)pow(2,i) - 1; //level�� ���۳�� pow�����Լ� 2^i
		int end_index = start_index + (int)pow(2, i);
		printf("%d�� ��� [ ", i);
		for (int j = start_index; j < end_index && j < MAX_SIZE; j++) {
			if (tree[j] != -1)
				printf("%d ", tree[j]);
			else
				printf("NL ");
		}
		printf("]\n");
	}
}

void Array_Tree_main() {
	srand((unsigned)time(NULL));
	int randNum;	//Ʈ�� ��� ����
	int* arrRandom;
	printf("����� ���� ���� ����(%d ����) : ", MAX_SIZE);
	scanf_s("%d", &randNum);

	if (randNum > MAX_SIZE) {
		printf("������ �ʹ� ���ƿ�.");
		return;
	}

	arrRandom = (int*)malloc(randNum * sizeof(int));
	Array_Tree_init();
	for (int i = 0; i < randNum; i++) {
		arrRandom[i] = rand() % 100;
		printf("���� %d\n", arrRandom[i]);
		Array_Tree_insert(arrRandom[i], 0);
	}

	printf("���� ��ȸ : ");
	Array_Tree_preorder_traverse(0);
	printf("\n");

	printf("���� ��ȸ : ");
	Array_Tree_inorder_traverse(0);
	printf("\n");

	printf("���� ��ȸ : ");
	Array_Tree_postorder_traverse(0);
	printf("\n");

	printf("���� ��ȸ : ");
	Array_Tree_levelorder_traverse(0);
	printf("\n");

	printf("������ ��ȸ : ");
	Array_Tree_reverse_levelorder_traverse(0);
	printf("\n");

	free(arrRandom);

	Array_Tree_print();

	int selectNum;
	printf("ã���� �ϴ� �� : ");
	scanf_s("%d", &selectNum);
	Array_Tree_Select(selectNum, 0);
	Array_Tree_print();

	printf("�����ϰ��� �ϴ� �� : ");
	scanf_s("%d", &selectNum);
	Array_Tree_Delete(selectNum);
	Array_Tree_print();
}

/*----------------------------------����ü ������ �̿��� Ʈ��--------------------------------*/
//1.�𵨻��� 2.������ 3.������ 4.����ȸ,Ž�� 5.�޸����� 6.������
typedef struct {
	int Data;
	struct Linked_Tree_Node* Left;
	struct Linked_Tree_Node* Right;
}Linked_Tree_Node;


Linked_Tree_Node* Create_Linked_Tree_Node(int data) {	//��� ����
	Linked_Tree_Node* newNode = (Linked_Tree_Node*)malloc(sizeof(Linked_Tree_Node));
	newNode->Data = data;
	newNode->Left = NULL;
	newNode->Right = NULL;
	return newNode;
}

Linked_Tree_Node* Linked_Tree_Insert_Node(Linked_Tree_Node* node, int data) {//��� ���� ��� ����
	if (node == NULL) {
		return Create_Linked_Tree_Node(data);
	}
	if (data < node->Data) {
		node->Left = Linked_Tree_Insert_Node(node->Left, data);//���� ���
	}
	else if (data > node->Data) {
		node->Right = Linked_Tree_Insert_Node(node->Right, data);//������ ���
	}
	return node;
}

int Linked_Tree_height(Linked_Tree_Node* root) {		//���� ������ Ž���ؼ� �ִ���� ���ϴ� ����Լ�
	if (root == NULL) return 0;
	int leftHeight = Linked_Tree_height(root->Left);
	int rightHeight = Linked_Tree_height(root->Right);
	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void Linked_Tree_current_level(Linked_Tree_Node* root, int level) {//���� ���� ���� ��� ��� ���
	//������ ����� ������ ������ 1:1, 2:2, 3:4, 4:8   �� 2^n�¾� �þ 2^0 2^1 2^2 2^3
	if (root == NULL) {
		printf("NL ");
		return;
	}
	if (level == 1)//���� �Ѱ� ��尡 �Ѱ� 2^0���� �ǹ�
		printf("%d ", root->Data);
	else if (level > 1) {//��尡 �ּ� 2�̻��̵�
		Linked_Tree_current_level(root->Left, level - 1);
		Linked_Tree_current_level(root->Right, level - 1);
	}	
}

void Linked_Tree_levelorder_Traversal(Linked_Tree_Node* root) {
	int Height = Linked_Tree_height(root);
	for (int i = 1; i <= Height; i++) {
		printf("%d�� ��� [ ", i - 1);
		Linked_Tree_current_level(root, i);
		printf("]\n");
	}
}

Linked_Tree_Node* Linked_Tree_select(Linked_Tree_Node* root, int data) {
	//��͸� �̿��� Ʈ���� Ž��
	if (root == NULL) {
		printf("ã���� �ϴ� ���� �����ϴ�.\n");
		return NULL;
	}
	if (root->Data == data) {
		return root;
	}
	else if (root->Data > data) {
		Linked_Tree_select(root->Left, data);
	}
	else if (root->Data < data) {
		Linked_Tree_select(root->Right, data);
	}
}

Linked_Tree_Node* Linked_Tree_Delete(Linked_Tree_Node* root, int data) {
	if (root == NULL) return root;

	if (root->Data > data) {
		root->Left = Linked_Tree_Delete(root->Left, data);
	}
	else if (root->Data < data) {
		root->Right = Linked_Tree_Delete(root->Right, data);
	}
	else {
		//�ڽĳ�尡 ���� ���
		if (root->Left == NULL && root->Right == NULL) {
			free(root);
			return NULL;
		}
		//�ڽĳ�尡 �Ѱ��ΰ��
		else if (root->Left == NULL) {
			Linked_Tree_Node* temp = root->Right;
			free(root);
			return temp;
		}
		else if (root->Right == NULL) {
			Linked_Tree_Node* temp = root->Left;
			free(root);
			return temp;
		}
		//�ڽĳ�尡 �ΰ��� ���
		//�θ� �Ǵ� ���� 1. ������ �ڽĳ�� ���� �ּҰ� 2. ���� �ڽĳ�� ���� �ִ밪
		else {
			Linked_Tree_Node* temp;
			temp = root->Right;
			while (temp->Left != NULL) {
				temp = temp->Left;
			}//���������� �θ��� ã�� �� ����
			root->Data = temp->Data;
			root->Right = Linked_Tree_Delete(root->Right, temp->Data);
		}
	}
	return root;
}



void Linked_Tree_preorder_traversal(Linked_Tree_Node* root) {//���� ��ȸ
	if (root == NULL)return;
	printf("%d ", root->Data);
	Linked_Tree_preorder_traversal(root->Left);
	Linked_Tree_preorder_traversal(root->Right);
}

void Linked_Tree_inorder_traversal(Linked_Tree_Node* root) {//���� ��ȸ
	if (root == NULL)return;
	Linked_Tree_inorder_traversal(root->Left);
	printf("%d ", root->Data);
	Linked_Tree_inorder_traversal(root->Right);
}

void Linked_Tree_postorder_traversal(Linked_Tree_Node* root) {//���� ��ȸ
	if (root == NULL)return;
	Linked_Tree_postorder_traversal(root->Left);
	Linked_Tree_postorder_traversal(root->Right);
	printf("%d ", root->Data);
}


void Linked_Tree_main() {
	Linked_Tree_Node* root = NULL;

	srand((unsigned)time(NULL));
	int randNum;	//Ʈ�� ��� ����
	int* arrRandom;
	printf("����� ���� ���� ���� : ");
	scanf_s("%d", &randNum);

	arrRandom = (int*)malloc(randNum * sizeof(int));
	for (int i = 0; i < randNum; i++) {
		arrRandom[i] = rand() % 100;
		printf("���� %d\n", arrRandom[i]);
		root = Linked_Tree_Insert_Node(root, arrRandom[i]);
	}

	printf("���� ��ȸ\n");
	Linked_Tree_levelorder_Traversal(root);
	printf("\n");

	printf("���� ��ȸ : ");
	Linked_Tree_preorder_traversal(root);
	printf("\n");

	printf("���� ��ȸ : ");
	Linked_Tree_inorder_traversal(root);
	printf("\n");

	printf("���� ��ȸ : ");
	Linked_Tree_postorder_traversal(root);
	printf("\n");

	int selectNum;
	Linked_Tree_Node* selectNode;
	/*printf("ã���� �ϴ� �� : ");
	scanf_s("%d", &selectNum);
	selectNode = Linked_Tree_select(root, selectNum);
	printf("%d\n", selectNode->Data);*/
	
	printf("�����ϰ��� �ϴ� �� : ");
	scanf_s("%d", &selectNum);
	root = Linked_Tree_Delete(root, selectNum);
	Linked_Tree_levelorder_Traversal(root);
}



