#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>
#include <Windows.h>

/*
	해싱
	해싱이란 지금까지 만들어진 자료구조보단 조금 고 차원의 느낌의 자료구조이다.
	기존 자료구조는 탐색을하거나 인덱스값을 알아서 접근을 하는 방식이었다.
	즉 말그대로 데이터의 값을 알아야 접근이 가능한 자료구조의 형태였었다.

	하지만 해싱은 테이블을 만들어서 키값과 데이터값을 구분하여 필드의 형태로 저장을 진행하는데
	이 키값을 통해서 우리는 데이터의 값을 알아낼 수 있는것이다.

	사전을 생각해볼때
	키값은 영어단어가 될것이고 데이터값을 영어단어의 뜻이 될것이다.
	즉 우리는 일일이 인덱스를 통해서 찾거나 데이터값을 통해서 찾지 않아도
	키값에 들어갈 키값에 매칭이 될만한 값만을 통해서 충분히 데이터값을 도출해낼 수 있는것이다.

	사전을 만든다면 3가지가 필수인데
	새로운 항목을 사전에 삽입(add)
	탐색 키에 관련된 항목을 삭제(delete)
	탐색 키에 관련된 값을 탐색(search)

	그래서 이 해시는 배열의 상위호환인 것이다.
	배열은 인덱스를 알기만 한다면 그 안에 데이터값에 접근하기가 굉장히 빨라진다.
	마찬가지로 이 인덱스값을 좀더 추상화 시켜서 사용자의 입장에서 기억하기 쉽게 키로 추상시킨것

	실제 우리가 가지는 키들은 문자열이지만 이 문자열은 그값이 너무도 커서 이를 다시 적절한 정수 i로 쪼개줘야 한다.
	k=영어단어  ---->   해시함수h(x) ----> 해시주소(idx값) ---->  해시테이블 ht[M]  ----> 버킷내 슬롯(슬롯이 여러개일 경우도 존재)
	그럼 여기서 목적지에 도달하여 데이터를 파싱하는 구조인데 버킷내 슬롯이 여러개일경우는 키값이 겹치는경우이다.
	간혹 키값은 다르지만 해시함수에 연산에 의해서 해시주소가 같아지는 경우가 생긴다.
	h(k1) = h(k2) 이런경우 말이다. 그러면 주소값이 같아서 생기는걸 *충돌이라고 하며 충돌이 발생된 k1과 k2를 *동의어라고 한다.
	슬롯이 여러개라면 충돌이 발생할때 비어있는 슬롯에 저장하면 그만이지만 슬롯수보다 더 많은 충돌이 일어나게된다면
	*오버플로우가 발생하여 더이상 저장할 수 없는 상태가 된다.
	그래서 이런 방법들을 해결해야 한다.

	해시테이블은 배열만 존재하는게 아닌
	연결리스트(체이닝)
	트리구조
	집합(set), 맵(map)
	트라이(Trie)같은 자료구조들로도 충분히 해시함수로 도출해서 값들을 관리할 수 있다.
*/

//학교생활 기록부를 만들어서 해싱함수를 익혀보자
//생기부에는 주민등록번호, 학번, 이름, 주소와 같은 인적사항들이 있으며
//학번이 탐색키이다.
//01(학과)023(학과의 학생들의 번호) 라고 가정을 해보자
//h(01023) 을 도출할때 단순히 같은 학과 학생들만 저장하는 생기부라면 뒤에 023만을 도출하면 굉장히 간단할것이다.
//h(01023) = 23 그러면 테이블은 ht[23] = 주번,이름,주소 같은 인적사항들이 있을것이다.

typedef struct Hash_Student {
	int id;
	char name[50];		//이름
	char address[100];	//주소
	char ssn[20];		//주민등록번호
}Hash_Student;

//해싱함수
int Hash_Student_HasingFun(int key, int table_size) {
	//key값은 id로 학번임
	int result = key % table_size;
	if (result < 0 || result >= 100) {
		return -1;
	}
	return result;
}

//학생 추가
void Hash_Student_Insert(Hash_Student** hashTable, int id, char* name, char* address, char* ssn, int table_size) {
	Hash_Student* newStudent = (Hash_Student*)malloc(sizeof(Hash_Student));
	newStudent->id = id;
	strcpy_s(newStudent->name, sizeof(name), name);
	strcpy_s(newStudent->address, sizeof(address), address);
	strcpy_s(newStudent->ssn, sizeof(ssn), ssn);

	
	int index = Hash_Student_HasingFun(id, table_size);

	//충돌발생시
	while (hashTable[index] != NULL && hashTable[index]->id != -1) {
		index = (index + 1) % table_size;	//다음 인덱스에 적재 다른 슬롯이 없는 관계로 아마 다음 인덱스에 적재될것
	}

	hashTable[index] = newStudent;
}

//학생 검색
Hash_Student* Hash_Student_Search(Hash_Student** table, int id, int table_size) {
	int index = Hash_Student_HasingFun(id, table_size); 

	//해당 인덱스에서 학생 정보 검색
	while (table[index] != NULL) {
		if (table[index]->id == id) {
			return table[index];
		}
		index = (index + 1) % table_size;//충돌이 일어났을경우를 처리해줌
	}
	return NULL;
}

//학생삭제
void Hash_Student_Delete(Hash_Student** table, int id, int table_size) {
	int index = Hash_Student_HasingFun(id, table_size);

	while (table[index] != NULL) {
		if (table[index]->id == id) {
			free(table[index]);	//메모리해제
			table[index] = NULL;
			return;
		}
		index = (index + 1) % table_size; //충돌탐색
	}
	printf("삭제할 학생이 없습니다.\n");
}


void Hash_Student_main() {
	int table_size = 100;
	Hash_Student** hashTable = (Hash_Student**)malloc(sizeof(Hash_Student*) * table_size);
	Hash_Student* searchStudent;
	for (int i = 0; i < table_size; i++) hashTable[i] = NULL;

	//학생 추가
	Hash_Student_Insert(hashTable, 12001, "홍길동", "용현동", "12", table_size);
	Hash_Student_Insert(hashTable, 12002, "김민수", "용현동", "13", table_size);
	Hash_Student_Insert(hashTable, 12003, "신짱구", "용현동", "14", table_size);
	Hash_Student_Insert(hashTable, 12004, "김철수", "용현동", "15", table_size);

	//학생 검색
	searchStudent = Hash_Student_Search(hashTable, 12003, table_size);
	printf("학생정보 :%d, %s, %s, %s\n", searchStudent->id, searchStudent->name, searchStudent->address, searchStudent->ssn);

	//학생 삭제
	Hash_Student_Delete(hashTable, 12004, table_size);

	//학생 검색
	searchStudent = Hash_Student_Search(hashTable, 12004, table_size);
	searchStudent != NULL ? printf("학생정보 :%d, %s, %s, %s\n", searchStudent->id, searchStudent->name, searchStudent->address, searchStudent->ssn)
							: printf("찾으시는 학생이 없습니다.");
}


//지금 이 생기부 해싱구조는 슬롯이 1개만 가지고 있기에 충돌이 발생하면 인덱스를 밑으로 옮기는 방법을 이용했다
//그러면 충돌이 발생하면 발생할수록 데이터의 공간은 줄어들 수 밖에 없을것이다.
//그러면 슬롯을 한번 증가시켜보도록 하자
//지금 구조는 1차원 배열의 구조이니 2차원 배열의 구조로 열의 크기를 늘리면 슬롯또한 증가할것이다.
//그리고 연결리스트를 이용해서도 슬롯을 늘릴 수 있다.

//학생 추가
void Hash_Student_Slot_insert(Hash_Student** table, int id, char* name, char* address, char* ssn, int table_size, int slot_size) {
	//행찾기
	int index = Hash_Student_HasingFun(id, table_size);

	//열찾기
	for (int i = 0; i < slot_size; i++) {
		if (table[index][i].id < 0) {//빈슬롯임을 알 수 있음
			table[index][i].id = id;
			strcpy_s(table[index][i].name, sizeof(table[index][i].name), name);
			strcpy_s(table[index][i].address, sizeof(table[index][i].address), address);
			strcpy_s(table[index][i].ssn, sizeof(table[index][i].ssn), ssn);
			printf("데이터 삽입 완료 [%d][%d]\n", index, i);
			return;
		}
	}
	printf("빈 슬롯이 가득 차있습니다.(오버플로우)\n");
}

//학생 검색
Hash_Student* Hash_Student_Slot_search(Hash_Student** table, int id, int table_size, int slot_size) {
	//행찾기
	int index = Hash_Student_HasingFun(table, id, table_size);

	//열찾기
	for (int i = 0; i < slot_size; i++) {
		if (table[index][i].id >= 0 && table[index][i].id == id) {
			return &table[index][i];
		}
	}

	//학생을 찾지 못했을경우
	return NULL;
}

//학생 삭제
void Hash_Student_Slot_delete(Hash_Student** table, int id, int table_size, int slot_size) {
	//행찾기
	int index = Hash_Student_HasingFun(id, table_size);

	//열찾기
	for (int i = 0; i < slot_size; i++) {
		if (table[index][i].id >= 0 && table[index][i].id == id) {
			table[index][i].id = -1;
			printf("제거 완료 [%d][%d]\n", index, i);
			return;
		}
	}
	printf("삭제할 학생을 찾지 못했습니다.\n");	
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

	//학생 추가
	Hash_Student_Slot_insert(hashTable, 12001, "홍길동", "용", "11-11", table_size, slot_size);
	Hash_Student_Slot_insert(hashTable, 12002, "김민수", "용", "11-11", table_size, slot_size);
	Hash_Student_Slot_insert(hashTable, 12003, "고길동", "용", "11-11", table_size, slot_size);
	Hash_Student_Slot_insert(hashTable, 12004, "신짱구", "용", "11-11", table_size, slot_size);
	Hash_Student_Slot_insert(hashTable, 32004, "신짱구2", "용", "11-11", table_size, slot_size);

	//학생찾기
	student = Hash_Student_Slot_search(hashTable, 12004, table_size, slot_size);
	student != NULL ? printf("학생정보 :%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
					: printf("찾고자 하는 학생이 없습니다.\n");
	//다른 학과 학생 찾기
	student = Hash_Student_Slot_search(hashTable, 32004, table_size, slot_size);
	student != NULL ? printf("학생정보 :%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
					: printf("찾고자 하는 학생이 없습니다.\n");
	//학생 제거
	Hash_Student_Slot_delete(hashTable, 12004, table_size, slot_size);

	//다시 학생 찾기
	student = Hash_Student_Slot_search(hashTable, 12004, table_size, slot_size);
	student != NULL ? printf("학생정보 :%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
					: printf("찾고자 하는 학생이 없습니다.\n");
}



//이번에는 연결리스트(체이닝)를 이용 해서 키값 파싱
typedef struct Hash_Student_Chaining {
	int id;
	char name[50];
	char address[100];
	char ssn[20];
	struct Hash_Student_Chaining* next;
}Hash_Student_Chaining;

//학생 삽입
void Hash_Student_Chaining_insert(Hash_Student_Chaining** table, int id, char* name, char* address, char* ssn, int table_size) {
	Hash_Student_Chaining* newStudent = (Hash_Student_Chaining*)malloc(sizeof(Hash_Student_Chaining));
	newStudent->id = id;
	strcpy_s(newStudent->name, sizeof(newStudent->name), name);
	strcpy_s(newStudent->address, sizeof(newStudent->address), address);
	strcpy_s(newStudent->ssn, sizeof(newStudent->ssn), ssn);
	newStudent->next = NULL;	//슬롯영역

	int index = Hash_Student_HasingFun(id, table_size);

	//삽입 절차
	if (table[index] == NULL) {
		table[index] = newStudent;
	}
	else {//충돌이 일어난 경우
		Hash_Student_Chaining* temp = table[index];
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newStudent;
	}
}

//학생검색
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

//학생 삭제
void Hash_Student_Chaining_delete(Hash_Student_Chaining** table, int id, int table_size) {
	int index = Hash_Student_HasingFun(id, table_size);

	if (index == -1 || table[index] == NULL) {
		printf("삭제할 학생을 찾지 못했습니다.\n");
		return;
	}

	Hash_Student_Chaining* temp = table[index];
	Hash_Student_Chaining* prev = NULL;

	while (temp != NULL && temp->id != id) {
		prev = temp;
		temp = temp->next;
	}

	//학생 못찾음
	if (temp == NULL) {
		printf("삭제할 학생을 찾지 못했습니다.\n");
		return;
	}

	//학생찾음 슬롯이 1개인 경우
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

	//학생추가
	Hash_Student_Chaining_insert(hashTable, 12001, "홍길동", "ㅇㅇ", "12-12",table_size);
	Hash_Student_Chaining_insert(hashTable, 12002, "김민수", "ㅇㅇ", "12-12",table_size);
	Hash_Student_Chaining_insert(hashTable, 12003, "김철수", "ㅇㅇ", "12-12",table_size);
	
	//학생 찾기
	student = Hash_Student_Chaining_search(hashTable, 12003, table_size);
	student != NULL ? printf("%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
					: printf("찾고자 하는 학생이 없습니다.\n");

	//중복해시주소 학생 추가
	Hash_Student_Chaining_insert(hashTable, 23003, "김철수2", "ㅇㅇ", "12-12", table_size);

	//학생찾기
	student = Hash_Student_Chaining_search(hashTable, 23003, table_size);
	student != NULL ? printf("%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
		: printf("찾고자 하는 학생이 없습니다.\n");

	Hash_Student_Chaining_delete(hashTable, 12003, table_size);

	//학생찾기
	student = Hash_Student_Chaining_search(hashTable, 12003, table_size);
	student != NULL ? printf("%d, %s, %s, %s\n", student->id, student->name, student->address, student->ssn)
		: printf("찾고자 하는 학생이 없습니다.\n");
	
}













































//해싱함수의 종류는 다양하다.
/*
	1. 제산함수 : 나머지 mod를 사용하여 키 % 테이블크기로 나눈 나머지로 구함
	2. 폴딩함수 : XOR을 이용함
	3. 중간제곱함수
	4. 비트추출방법
	5. 숫자분석방법
	
	지금까지는 숫자를 해싱하는 기법들이나
	문자열이 키일경우도 분명히 존재한다.
	그럴때는 기본적으로 아스키 코드값을 해시주소로 사용한다.

	지금까지 우리가 한건 빈 슬롯찾기 방식이다
	h(k1) = h(k2) 이런식으로 해시주소가 같아도 같은 해시주소의 비어있는 슬롯에 그저 넣기만 하는 방식을 채택했다.
	하지만 슬롯이 차있거나 하게된다면 오버플로우가 나게 되어서 어쩔 수 없이 빈 버킷을 찾아야 한다.
	그럴때 쓰는게 선형조사법이다.

	그래서 요즘은 선형조사법과 체이닝 기법 두가지를 같이 사용해서 쓴다.

	선형조사법의 기법 종류
	1. 선형조사법 : 충돌시 이후의 버킷을 순차적으로 찾고 비어있으면 삽입
	2. 이차조사법 : 제곱방식으로 첫충돌 1칸 다음 4칸 다음 9칸  (n^2)칸씩 이동
	3. 이중해싱 : 충돌발생시 해싱함수 한번 더 진행
	4. 2차 조사법 및 이중해싱의 변형 등이 있다.
*/