#include <stdio.h>

enum {SOMA, MULT};

int soma(int x, int y){
	return x + y;
}

int mult(int x, int y){
	return x * y;
}

int main(){
	int (*op[])(int, int)={
		soma, mult
	};
	printf("%d ", op[SOMA](2,3));
	printf("%d", op[MULT](2,3));
	return 0;
}