#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_DATA 100 


int main(int argc, char* argv[]) {
	

	DBMS_Arr_main();

}

typedef struct {		//�迭����Ʈ�� ������ ��
	int id;
	char name[50];
	char major[50];
}Student_ArrayList;