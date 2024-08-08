#include <stdio.h>
#include <stdlib.h>
#define ROWS 3
#define COLS 3

#define MAX_TERMS 10
typedef struct {
	int row;
	int col;
	int value;
}element;

typedef struct {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}SparseMatrix;

/*
	<배열 자료구조의 희소행렬> 
	희소행렬 메모리 영역에 실존하는 데이터(!0)가 0보다 적을 경우 희소행렬 데이터 영역이라 한다.
	그래서 메모리 영역에 실존하는 데이터보다 쓰이지 않는 데이터 0이 존재하기 때문에 메모리 낭비가 발생
	고로 희소 행렬을 처리하기 위해서는 1000의 공간확보된 메모리 영역을 600이라는 공간이 확보된 메모리에 실제 데이터를 집어넣고
	400이라는 낭비되는 데이터를 즉 리소스를 반납하는 행위
	-사용법
	coo방식(0이 아닌 데이터만 별도의 배열에 저장하고 그 다음 또 별도의 배열에 그 데이터의 본래 위치(index)를 저장)
	총 배열이 3개가 존재(1. 희소행렬배열, 2. 0이 아닌 데이터 배열, 3. 데이터의 위치를 담는 배열)-값배열, 행인덱스배열, 열인덱스배열 
	csr방식(기존 coo방식은 행위치 열위치를 담는 배열에 중복이 발생함 예시로 10X10배열에 3행에 데이터가 몰려있을경우
	행위치는 3,3,3,3,3... 이런식으로 중복이 발생그걸 없애는 방식을 채택한것이 csr방식)-값배열, 열인덱스배열, 행포인터배열
	csc방식(행포인터방식이었던 csr에서 열 포인터방식으로 바뀜) -값배열, 행인덱스배열, 열포인터배열
	-햇갈릴 수 있는 점
	도서관에 1000에 공간에 비해 책은 30개 있다고 가정하면 엄청난 희소행렬이 발생하였기에 1000에 공간을 없애고 대신해서 새로운 책장을
	만들었다고 생각하면 편하다 우리가 접근하는 random memory accesse인 ram에 저장된 메모리는 값 데이터들이 랜덤으로 뿌려져 있기에
	우리는 이 희소행렬이 발생한 메모리 공간에서 데이터의 위치정보와 값만을 추출하여 새로운 책장을 만드는 것이다.
	그렇게 된다면 할당하고 만들어둔 메모리공간은 해제되게 되고 해제되게 된 공간은 모든 데이터가 사라지게 된다.
*/

SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
	SparseMatrix c;
	int ca = 0, cb = 0, cc = 0;
	if (a.rows != b.rows || a.cols != b.cols) {
		fprintf(stderr, "희소행렬 크기에러\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while (ca < a.terms && cb < b.terms) {
		int inda = a.data[ca].row * a.cols + a.data[ca].col;
		int indb = b.data[cb].row * b.cols + b.data[cb].col;
		if (inda < indb) {
			c.data[cc++] = a.data[ca++];
		}
		else if (inda == indb) {
			c.data[cc].row = a.data[ca].row;
			c.data[cc].col = a.data[ca].col;
			c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
		}
		else
			c.data[cc++] = b.data[cb++];
	}
	for (; ca < a.terms; ca++)
		c.data[cc++] = a.data[ca++];
	for (; cb < b.terms; cb++)
		c.data[cc++] = b.data[cb++];
	c.terms = cc;
	return c;
}
