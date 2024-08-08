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
	<�迭 �ڷᱸ���� ������> 
	������ �޸� ������ �����ϴ� ������(!0)�� 0���� ���� ��� ������ ������ �����̶� �Ѵ�.
	�׷��� �޸� ������ �����ϴ� �����ͺ��� ������ �ʴ� ������ 0�� �����ϱ� ������ �޸� ���� �߻�
	��� ��� ����� ó���ϱ� ���ؼ��� 1000�� ����Ȯ���� �޸� ������ 600�̶�� ������ Ȯ���� �޸𸮿� ���� �����͸� ����ְ�
	400�̶�� ����Ǵ� �����͸� �� ���ҽ��� �ݳ��ϴ� ����
	-����
	coo���(0�� �ƴ� �����͸� ������ �迭�� �����ϰ� �� ���� �� ������ �迭�� �� �������� ���� ��ġ(index)�� ����)
	�� �迭�� 3���� ����(1. �����Ĺ迭, 2. 0�� �ƴ� ������ �迭, 3. �������� ��ġ�� ��� �迭)-���迭, ���ε����迭, ���ε����迭 
	csr���(���� coo����� ����ġ ����ġ�� ��� �迭�� �ߺ��� �߻��� ���÷� 10X10�迭�� 3�࿡ �����Ͱ� �����������
	����ġ�� 3,3,3,3,3... �̷������� �ߺ��� �߻��װ� ���ִ� ����� ä���Ѱ��� csr���)-���迭, ���ε����迭, �������͹迭
	csc���(�������͹���̾��� csr���� �� �����͹������ �ٲ�) -���迭, ���ε����迭, �������͹迭
	-�ް��� �� �ִ� ��
	�������� 1000�� ������ ���� å�� 30�� �ִٰ� �����ϸ� ��û�� �������� �߻��Ͽ��⿡ 1000�� ������ ���ְ� ����ؼ� ���ο� å����
	������ٰ� �����ϸ� ���ϴ� �츮�� �����ϴ� random memory accesse�� ram�� ����� �޸𸮴� �� �����͵��� �������� �ѷ��� �ֱ⿡
	�츮�� �� �������� �߻��� �޸� �������� �������� ��ġ������ ������ �����Ͽ� ���ο� å���� ����� ���̴�.
	�׷��� �ȴٸ� �Ҵ��ϰ� ������ �޸𸮰����� �����ǰ� �ǰ� �����ǰ� �� ������ ��� �����Ͱ� ������� �ȴ�.
*/

SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
	SparseMatrix c;
	int ca = 0, cb = 0, cc = 0;
	if (a.rows != b.rows || a.cols != b.cols) {
		fprintf(stderr, "������ ũ�⿡��\n");
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
