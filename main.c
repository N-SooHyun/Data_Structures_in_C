#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>
#include <Windows.h>


#define MAX_SIZE_DATA 100 
#define MAX_SIZE 10

typedef struct ArrayDynamicModel {
	char data;
	struct ArrayDynamicModel* list;
	int size;	//속해있는 배열에 개수
	int capacity;	//최대용량
}ArrayDynamicModel;


int main(int argc, char* argv[]) {
	//Array_File_Tree_main();
	//Priority_Arr_Que_main();
	//Priority_Linked_Que_main();
	//Priority_Heap_Arr_main();
	Priority_Heap_Linked_Que_main();
}

