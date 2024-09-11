#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>
#include <Windows.h>

/*
	�ؽ�
	�ؽ��̶� ���ݱ��� ������� �ڷᱸ������ ���� �� ������ ������ �ڷᱸ���̴�.
	���� �ڷᱸ���� Ž�����ϰų� �ε������� �˾Ƽ� ������ �ϴ� ����̾���.
	�� ���״�� �������� ���� �˾ƾ� ������ ������ �ڷᱸ���� ���¿�����.

	������ �ؽ��� ���̺��� ���� Ű���� �����Ͱ��� �����Ͽ� �ʵ��� ���·� ������ �����ϴµ�
	�� Ű���� ���ؼ� �츮�� �������� ���� �˾Ƴ� �� �ִ°��̴�.

	������ �����غ���
	Ű���� ����ܾ �ɰ��̰� �����Ͱ��� ����ܾ��� ���� �ɰ��̴�.
	�� �츮�� ������ �ε����� ���ؼ� ã�ų� �����Ͱ��� ���ؼ� ã�� �ʾƵ�
	Ű���� �� Ű���� ��Ī�� �ɸ��� ������ ���ؼ� ����� �����Ͱ��� �����س� �� �ִ°��̴�.

	������ ����ٸ� 3������ �ʼ��ε�
	���ο� �׸��� ������ ����(add)
	Ž�� Ű�� ���õ� �׸��� ����(delete)
	Ž�� Ű�� ���õ� ���� Ž��(search)

	�׷��� �� �ؽô� �迭�� ����ȣȯ�� ���̴�.
	�迭�� �ε����� �˱⸸ �Ѵٸ� �� �ȿ� �����Ͱ��� �����ϱⰡ ������ ��������.
	���������� �� �ε������� ���� �߻�ȭ ���Ѽ� ������� ���忡�� ����ϱ� ���� Ű�� �߻��Ų��

	���� �츮�� ������ Ű���� ���ڿ������� �� ���ڿ��� �װ��� �ʹ��� Ŀ�� �̸� �ٽ� ������ ���� i�� �ɰ���� �Ѵ�.
	k=����ܾ�  ---->   �ؽ��Լ�h(x) ----> �ؽ��ּ�(idx��) ---->  �ؽ����̺� ht[M]  ----> ��Ŷ�� ����(������ �������� ��쵵 ����)
	�׷� ���⼭ �������� �����Ͽ� �����͸� �Ľ��ϴ� �����ε� ��Ŷ�� ������ �������ϰ��� Ű���� ��ġ�°���̴�.
	��Ȥ Ű���� �ٸ����� �ؽ��Լ��� ���꿡 ���ؼ� �ؽ��ּҰ� �������� ��찡 �����.
	h(k1) = h(k2) �̷���� ���̴�. �׷��� �ּҰ��� ���Ƽ� ����°� *�浹�̶�� �ϸ� �浹�� �߻��� k1�� k2�� *���Ǿ��� �Ѵ�.
	������ ��������� �浹�� �߻��Ҷ� ����ִ� ���Կ� �����ϸ� �׸������� ���Լ����� �� ���� �浹�� �Ͼ�Եȴٸ�
	*�����÷ο찡 �߻��Ͽ� ���̻� ������ �� ���� ���°� �ȴ�.
	�׷��� �̷� ������� �ذ��ؾ� �Ѵ�.

	�ؽ����̺��� �迭�� �����ϴ°� �ƴ�
	���Ḯ��Ʈ(ü�̴�)
	Ʈ������
	����(set), ��(map)
	Ʈ����(Trie)���� �ڷᱸ����ε� ����� �ؽ��Լ��� �����ؼ� ������ ������ �� �ִ�.
*/

//�б���Ȱ ��Ϻθ� ���� �ؽ��Լ��� ��������
//����ο��� �ֹε�Ϲ�ȣ, �й�, �̸�, �ּҿ� ���� �������׵��� ������
//�й��� Ž��Ű�̴�.
//01(�а�)023(�а��� �л����� ��ȣ) ��� ������ �غ���
//h(01023) �� �����Ҷ� �ܼ��� ���� �а� �л��鸸 �����ϴ� ����ζ�� �ڿ� 023���� �����ϸ� ������ �����Ұ��̴�.
//h(01023) = 23 �׷��� ���̺��� ht[23] = �ֹ�,�̸�,�ּ� ���� �������׵��� �������̴�.

typedef struct Hash_Student {
	int id;
	char name[50];		//�̸�
	char address[100];	//�ּ�
	char ssn[20];		//�ֹε�Ϲ�ȣ
}Hash_Student;

//�ؽ��Լ�
int Hash_Student_HasingFun(int key, int table_size) {
	//key���� id�� �й���
	int result = key % table_size;
	if (result < 0 || result >= 100) {
		return -1;
	}
	return result;
}

//�л� �߰�
void Hash_Student_Insert(Hash_Student** hashTable, int id, char* name, char* address, char* ssn, int table_size) {
	Hash_Student* newStudent = (Hash_Student*)malloc(sizeof(Hash_Student));
	newStudent->id = id;
	strcpy_s(newStudent->name, sizeof(name), name);
	strcpy_s(newStudent->address, sizeof(address), address);
	strcpy_s(newStudent->ssn, sizeof(ssn), ssn);

	
	int index = Hash_Student_HasingFun(id, table_size);

	//�浹�߻���
	while (hashTable[index] != NULL && hashTable[index]->id != -1) {
		index = (index + 1) % table_size;	//���� �ε����� ���� �ٸ� ������ ���� ����� �Ƹ� ���� �ε����� ����ɰ�
	}

	hashTable[index] = newStudent;
}

//�л� �˻�
Hash_Student* Hash_Student_Search(Hash_Student** table, int id, int table_size) {
	int index = Hash_Student_HasingFun(id, table_size); 

	//�ش� �ε������� �л� ���� �˻�
	while (table[index] != NULL) {
		if (table[index]->id == id) {
			return table[index];
		}
		index = (index + 1) % table_size;//�浹�� �Ͼ����츦 ó������
	}
	return NULL;
}

//�л�����
void Hash_Student_Delete(Hash_Student** table, int id, int table_size) {
	int index = Hash_Student_HasingFun(id, table_size);

	while (table[index] != NULL) {
		if (table[index]->id == id) {
			free(table[index]);	//�޸�����
			table[index] = NULL;
			return;
		}
		index = (index + 1) % table_size; //�浹Ž��
	}
	printf("������ �л��� �����ϴ�.\n");
}


void Hash_Student_main() {
	int table_size = 100;
	Hash_Student** hashTable = (Hash_Student**)malloc(sizeof(Hash_Student*) * table_size);
	Hash_Student* searchStudent;
	for (int i = 0; i < table_size; i++) hashTable[i] = NULL;

	//�л� �߰�
	Hash_Student_Insert(hashTable, 12001, "ȫ�浿", "������", "12", table_size);
	Hash_Student_Insert(hashTable, 12002, "��μ�", "������", "13", table_size);
	Hash_Student_Insert(hashTable, 12003, "��¯��", "������", "14", table_size);
	Hash_Student_Insert(hashTable, 12004, "��ö��", "������", "15", table_size);

	//�л� �˻�
	searchStudent = Hash_Student_Search(hashTable, 12003, table_size);
	printf("�л����� :%d, %s, %s, %s\n", searchStudent->id, searchStudent->name, searchStudent->address, searchStudent->ssn);

	//�л� ����
	Hash_Student_Delete(hashTable, 12004, table_size);

	//�л� �˻�
	searchStudent = Hash_Student_Search(hashTable, 12004, table_size);
	searchStudent != NULL ? printf("�л����� :%d, %s, %s, %s\n", searchStudent->id, searchStudent->name, searchStudent->address, searchStudent->ssn)
							: printf("ã���ô� �л��� �����ϴ�.");
}


//���� �� ����� �ؽ̱����� ������ 1���� ������ �ֱ⿡ �浹�� �߻��ϸ� �ε����� ������ �ű�� ����� �̿��ߴ�
//�׷��� �浹�� �߻��ϸ� �߻��Ҽ��� �������� ������ �پ�� �� �ۿ� �������̴�.
//�׷��� ������ �ѹ� �������Ѻ����� ����
//���� ������ 1���� �迭�� �����̴� 2���� �迭�� ������ ���� ũ�⸦ �ø��� ���Զ��� �����Ұ��̴�.
//�׸��� ���Ḯ��Ʈ�� �̿��ؼ��� ������ �ø� �� �ִ�.

//�л� �߰�
void Hash_Student_Slot_insert(Hash_Student** table, int id, char* name, char* address, char* ssn, int table_size, int slot_size) {
	//��ã��
	int index = Hash_Student_HasingFun(id, table_size);

	//��ã��
	for (int i = 0; i < slot_size; i++) {
		if (table[index][i].id < 0) {//�󽽷����� �� �� ����
			table[index][i].id = id;
			strcpy_s(table[index][i].name, sizeof(table[index][i].name), name);
			strcpy_s(table[index][i].address, sizeof(table[index][i].address), address);
			strcpy_s(table[index][i].ssn, sizeof(table[index][i].ssn), ssn);
			printf("������ ���� �Ϸ� [%d][%d]\n", index, i);
			return;
		}
	}
	printf("�� ������ ���� ���ֽ��ϴ�.(�����÷ο�)\n");
}

//�л� �˻�
Hash_Student* Hash_Student_Slot_search(Hash_Student** table, int id, int table_size, int slot_size) {
	//��ã��
	int index = Hash_Student_HasingFun(table, id, table_size);

	//��ã��
	for (int i = 0; i < slot_size; i++) {
		if (table[index][i].id >= 0 && table[index][i].id == id) {
			return &table[index][i];
		}
	}

	//�л��� ã�� ���������
	return NULL;
}

//�л� ����
void Hash_Student_Slot_delete(Hash_Student** table, int id, int table_size, int slot_size) {
	//��ã��
	int index = Hash_Student_HasingFun(id, table_size);

	//��ã��
	for (int i = 0; i < slot_size; i++) {
		if (table[index][i].id >= 0 && table[index][i].id == id) {
			table[index][i].id = -1;
			printf("���� �Ϸ� [%d][%d]\n", index, i);
			return;
		}
	}
	printf("������ �л��� ã�� ���߽��ϴ�.\n");	
}

void Hash_Student_Slot_main() {
	int table_size = 100;
	int slot_size = 5;
	Hash_Student** hashTable = (Hash_Student**)malloc(sizeof(Hash_Student*) * table_size);
	Hash_Student* student;
	for (int i = 0; i < table_size; i++) {
		hashTable[i] = (Hash_Student*)malloc(sizeof(Hash_Student) * slot_size);
		for (int j = 0; j < slot_size; j++) {
			hashTable[i][j].id = -1;
			
		}
	}

	//�л� �߰�
	Hash_Student_Slot_insert(hashTable, 12001, "ȫ�浿", "��", "11-11", table_size, slot_size);
	Hash_Student_Slot_insert(hashTable, 12002, "��μ�", "��", "11-11", table_size, slot_size);
	Hash_Student_Slot_insert(hashTable, 12003, "��浿", "��", "11-11", table_size, slot_size);
	Hash_Student_Slot_insert(hashTable, 12004, "��¯��", "��", "11-11", table_size, slot_size);
	Hash_Student_Slot_insert(hashTable, 32004, "��¯��2", "��", "11-11", table_size, slot_size);

	//�л�ã��
	student = Hash_Student_Slot_search(hashTable, 12004, table_size, slot_size);
	student != NULL ? printf("�л����� :%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
					: printf("ã���� �ϴ� �л��� �����ϴ�.\n");
	//�ٸ� �а� �л� ã��
	student = Hash_Student_Slot_search(hashTable, 32004, table_size, slot_size);
	student != NULL ? printf("�л����� :%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
					: printf("ã���� �ϴ� �л��� �����ϴ�.\n");
	//�л� ����
	Hash_Student_Slot_delete(hashTable, 12004, table_size, slot_size);

	//�ٽ� �л� ã��
	student = Hash_Student_Slot_search(hashTable, 12004, table_size, slot_size);
	student != NULL ? printf("�л����� :%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
					: printf("ã���� �ϴ� �л��� �����ϴ�.\n");
}



//�̹����� ���Ḯ��Ʈ(ü�̴�)�� �̿� �ؼ� Ű�� �Ľ�
typedef struct Hash_Student_Chaining {
	int id;
	char name[50];
	char address[100];
	char ssn[20];
	struct Hash_Student_Chaining* next;
}Hash_Student_Chaining;

//�л� ����
void Hash_Student_Chaining_insert(Hash_Student_Chaining** table, int id, char* name, char* address, char* ssn, int table_size) {
	Hash_Student_Chaining* newStudent = (Hash_Student_Chaining*)malloc(sizeof(Hash_Student_Chaining));
	newStudent->id = id;
	strcpy_s(newStudent->name, sizeof(newStudent->name), name);
	strcpy_s(newStudent->address, sizeof(newStudent->address), address);
	strcpy_s(newStudent->ssn, sizeof(newStudent->ssn), ssn);
	newStudent->next = NULL;	//���Կ���

	int index = Hash_Student_HasingFun(id, table_size);

	//���� ����
	if (table[index] == NULL) {
		table[index] = newStudent;
	}
	else {//�浹�� �Ͼ ���
		Hash_Student_Chaining* temp = table[index];
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newStudent;
	}
}

//�л��˻�
Hash_Student_Chaining* Hash_Student_Chaining_search(Hash_Student_Chaining** table, int id, int table_size) {
	int index = Hash_Student_HasingFun(id, table_size);

	if (index == -1 || table[index]==NULL) {
		return NULL;
	}
	
	Hash_Student_Chaining* temp = table[index];

	while (temp != NULL) {
		if (temp->id == id) {
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

//�л� ����
void Hash_Student_Chaining_delete(Hash_Student_Chaining** table, int id, int table_size) {
	int index = Hash_Student_HasingFun(id, table_size);

	if (index == -1 || table[index] == NULL) {
		printf("������ �л��� ã�� ���߽��ϴ�.\n");
		return;
	}

	Hash_Student_Chaining* temp = table[index];
	Hash_Student_Chaining* prev = NULL;

	while (temp != NULL && temp->id != id) {
		prev = temp;
		temp = temp->next;
	}

	//�л� ��ã��
	if (temp == NULL) {
		printf("������ �л��� ã�� ���߽��ϴ�.\n");
		return;
	}

	//�л�ã�� ������ 1���� ���
	if (prev == NULL) {
		table[index] = temp->next;
	}
	else {
		prev->next = temp->next;
	}

	free(temp);
}

void Hash_Student_Chaining_main() {
	int table_size = 100;
	Hash_Student_Chaining** hashTable = (Hash_Student_Chaining**)malloc(sizeof(Hash_Student_Chaining*) * table_size);
	Hash_Student_Chaining* student;

	for (int i = 0; i < table_size; i++) hashTable[i] = 0;

	//�л��߰�
	Hash_Student_Chaining_insert(hashTable, 12001, "ȫ�浿", "����", "12-12",table_size);
	Hash_Student_Chaining_insert(hashTable, 12002, "��μ�", "����", "12-12",table_size);
	Hash_Student_Chaining_insert(hashTable, 12003, "��ö��", "����", "12-12",table_size);
	
	//�л� ã��
	student = Hash_Student_Chaining_search(hashTable, 12003, table_size);
	student != NULL ? printf("%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
					: printf("ã���� �ϴ� �л��� �����ϴ�.\n");

	//�ߺ��ؽ��ּ� �л� �߰�
	Hash_Student_Chaining_insert(hashTable, 23003, "��ö��2", "����", "12-12", table_size);

	//�л�ã��
	student = Hash_Student_Chaining_search(hashTable, 23003, table_size);
	student != NULL ? printf("%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
		: printf("ã���� �ϴ� �л��� �����ϴ�.\n");

	Hash_Student_Chaining_delete(hashTable, 12003, table_size);

	//�л�ã��
	student = Hash_Student_Chaining_search(hashTable, 12003, table_size);
	student != NULL ? printf("%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
		: printf("ã���� �ϴ� �л��� �����ϴ�.\n");
	
}













































//�ؽ��Լ��� ������ �پ��ϴ�.
/*
	1. �����Լ� : ������ mod�� ����Ͽ� Ű % ���̺�ũ��� ���� �������� ����
	2. �����Լ� : XOR�� �̿���
	3. �߰������Լ�
	4. ��Ʈ������
	5. ���ںм����
	
	���ݱ����� ���ڸ� �ؽ��ϴ� ������̳�
	���ڿ��� Ű�ϰ�쵵 �и��� �����Ѵ�.
	�׷����� �⺻������ �ƽ�Ű �ڵ尪�� �ؽ��ּҷ� ����Ѵ�.

	���ݱ��� �츮�� �Ѱ� �� ����ã�� ����̴�
	h(k1) = h(k2) �̷������� �ؽ��ּҰ� ���Ƶ� ���� �ؽ��ּ��� ����ִ� ���Կ� ���� �ֱ⸸ �ϴ� ����� ä���ߴ�.
	������ ������ ���ְų� �ϰԵȴٸ� �����÷ο찡 ���� �Ǿ ��¿ �� ���� �� ��Ŷ�� ã�ƾ� �Ѵ�.
	�׷��� ���°� ����������̴�.

	�׷��� ������ ����������� ü�̴� ��� �ΰ����� ���� ����ؼ� ����.

	����������� ��� ����
	1. ��������� : �浹�� ������ ��Ŷ�� ���������� ã�� ��������� ����
	2. ��������� : ����������� ù�浹 1ĭ ���� 4ĭ ���� 9ĭ  (n^2)ĭ�� �̵�
	3. �����ؽ� : �浹�߻��� �ؽ��Լ� �ѹ� �� ����
	4. 2�� ����� �� �����ؽ��� ���� ���� �ִ�.
*/