#include <stdio.h>

int recursion_factorial(int n) {
	static int num = 0;		//정적 변수 스택프레임의 수
	int returnNum = 0;	//정적 변수 팩토리얼의 중간 값
	if (n == 1) {//반복문에서의 반복문을 멈출 조건식
		num += 1;
		printf("마지막 %d번째 스택프레임은 매개변수 n = %d를 반환한다.\n\n", num, n);
		return 1;
	}
	else {
		num += 1;
		printf("%d번째 스택프레임에서의 매개변수 값 n = %d\n", num, n);
		returnNum = n* recursion_factorial(n - 1);//반복문에서의 증감		
		num -= 1;
		printf("%d번째 스택프레임에서 반환 받아 나온 결과 %d * %d-1(%d) = %d\n", num, n, n,n-1,returnNum);
		return returnNum;
	}
}

int recursion_power(int x, int n) {	//거듭제곱 n이 0이되면 반환 조건식 n이 1씩 줄어드는 증감식
	if (n == 0)
		return 1;
	else if (n == 2) {
		return x * x;
	}
	else {
		return x * recursion_power(x, n - 1);
	}
}

double recursion_power2(double x, int n) {//거듭제곱을 짝수와 홀수로 나누어서 계산
	if (n == 0) return 1;
	else if ((n % 2) == 0)//짝수인 경우
		return recursion_power(x * x, n / 2);
	else//홀수인 경우
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

int recursion_fibonacci(int n) {	//피보나치 0 1 1 2 3 5 8 13	트리 구조의 스택프레임형식으로 짜여져 있다 i와 j를 기준으로 나뉘어진 느낌
	static int inum = 0, jnum = 0;
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	return (recursion_fibonacci(n - 1) + recursion_fibonacci(n - 2));	//왼쪽과 오른쪽이 i와 j인 느낌
}

void recursion_hanoi(int floor, char from, char tmp, char to) {//최소 이동횟수 2^n(원판개수)-1 2^3 - 1 = 7
	static int num = 0;
	if (floor == 1) {
		printf("%d. 원판 1을 %c에서 %c로 옮긴다.\n", ++num, from, to);
	}
	else {
		recursion_hanoi(floor - 1, from, to, tmp);		//처음	A->C  from->to
		printf("%d. 원판 %d를 %c에서 %c로 옮긴다.\n", ++num, floor, from, to);	//두번째 A->B from tmp
		recursion_hanoi(floor - 1, tmp, from, to);		//세번째	C->B  to tmp
	}
}

int recursive(int n) {
	printf("%d\n", n);
	if (n < 1) return 2;
	else return (2 * recursive(n - 1) + 1);
}