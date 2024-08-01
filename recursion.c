#include <stdio.h>

int recursion_factorial(int n) {
	static int num = 0;		//���� ���� ������������ ��
	int returnNum = 0;	//���� ���� ���丮���� �߰� ��
	if (n == 1) {//�ݺ��������� �ݺ����� ���� ���ǽ�
		num += 1;
		printf("������ %d��° ������������ �Ű����� n = %d�� ��ȯ�Ѵ�.\n\n", num, n);
		return 1;
	}
	else {
		num += 1;
		printf("%d��° ���������ӿ����� �Ű����� �� n = %d\n", num, n);
		returnNum = n* recursion_factorial(n - 1);//�ݺ��������� ����		
		num -= 1;
		printf("%d��° ���������ӿ��� ��ȯ �޾� ���� ��� %d * %d-1(%d) = %d\n", num, n, n,n-1,returnNum);
		return returnNum;
	}
}

int recursion_power(int x, int n) {	//�ŵ����� n�� 0�̵Ǹ� ��ȯ ���ǽ� n�� 1�� �پ��� ������
	if (n == 0)
		return 1;
	else if (n == 2) {
		return x * x;
	}
	else {
		return x * recursion_power(x, n - 1);
	}
}

double recursion_power2(double x, int n) {//�ŵ������� ¦���� Ȧ���� ����� ���
	if (n == 0) return 1;
	else if ((n % 2) == 0)//¦���� ���
		return recursion_power(x * x, n / 2);
	else//Ȧ���� ���
		return x * recursion_power2(x * x, (n - 1) / 2);
}

int fibonacci(int n) {
	int sum = 0;
	int i = 0, j = 1;
	for (int k = 0; k < n; k++) {
		sum = i + j;
		i = j;
		j = sum;
	}
	return sum;
}

int recursion_fibonacci(int n) {	//�Ǻ���ġ 0 1 1 2 3 5 8 13	Ʈ�� ������ ������������������ ¥���� �ִ� i�� j�� �������� �������� ����
	static int inum = 0, jnum = 0;
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	return (recursion_fibonacci(n - 1) + recursion_fibonacci(n - 2));	//���ʰ� �������� i�� j�� ����
}

void recursion_hanoi(int floor, char from, char tmp, char to) {//�ּ� �̵�Ƚ�� 2^n(���ǰ���)-1 2^3 - 1 = 7
	static int num = 0;
	if (floor == 1) {
		printf("%d. ���� 1�� %c���� %c�� �ű��.\n", ++num, from, to);
	}
	else {
		recursion_hanoi(floor - 1, from, to, tmp);		//ó��	A->C  from->to
		printf("%d. ���� %d�� %c���� %c�� �ű��.\n", ++num, floor, from, to);	//�ι�° A->B from tmp
		recursion_hanoi(floor - 1, tmp, from, to);		//����°	C->B  to tmp
	}
}

int recursive(int n) {
	printf("%d\n", n);
	if (n < 1) return 2;
	else return (2 * recursive(n - 1) + 1);
}