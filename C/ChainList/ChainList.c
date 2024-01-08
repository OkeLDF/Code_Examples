#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// LISTA ENCADEADA:

typedef union{
	int i;
	double f;
	char c;
	void* p;
}Value;

typedef struct ChainList{
	Value value;
	struct ChainList *next;
} List;

void displayList(List *start){
	List *current=start;
	printf("\033[93mList\033[m in <0x%x>:\n{\n", start);
	for(; current!=NULL; current=current->next){
		printf("  \033[91mint:\033[m %10i    \033[92mchar:\033[m '%c'    \033[94mfloat:\033[m %f",
			current->value.i, (current->value.c>32)?current->value.c:' ', current->value.f);
		
		if(current->next) printf("\033[90m;\033[m\n");
	}
	printf("\n}\n");
}

int sqr(List element){
	return element.value.i * element.value.i;
}

void mapInt(List *start, int (*function_ptr)(List)){
	List *current=start;
	for(; current!=NULL; current=current->next){
		current->value.i = function_ptr(*current);
	}
}

void mapFloat(List *start, float (*function_ptr)(List)){
	List *current=start;
	for(; current!=NULL; current=current->next){
		current->value.f = function_ptr(*current);
	}
}

void mapChar(List *start, char (*function_ptr)(List)){
	List *current=start;
	for(; current!=NULL; current=current->next){
		current->value.f = function_ptr(*current);
	}
}

List* newList(char format, ...){
	List* newborn;
	newborn = (List*) malloc(sizeof(List));

	va_list list;
	va_start(list, format);
	
	switch(format){
		case 'i': newborn->value.i = va_arg(list, int); break;
		case 'f': newborn->value.f = va_arg(list, double); break;
		case 'c': newborn->value.c = va_arg(list, int); break;
		case 'p': newborn->value.p = va_arg(list, void*); break;
	}
	
	va_end(list);
	
	newborn->next = NULL;
	return newborn;
}

void delList(List* start){
	if(start->next) delList(start->next);
	free(start);
}

// TESTES e MAIN:

void test1(){
	// uso do atributo 'value'
	
	List t;
	int x = 8;
	
	t.value.i = x;
	x++;
	puts("\nTest 1: ---\n");
	printf("%i\n", t.value);
}

void test2(){
	List t1 = {1, NULL};
	List t2 = {'a', NULL};
	List t3 = {0, NULL};
	t3.value.f = 2.5;
	
	puts("\nTest 2: ---\n");
	printf("%i %c %f\n\n", t1.value, t2.value, t3.value.f);
	
	t1.next = &t2;
	t2.next = &t3;
	
	displayList(&t1);
}

void test3(){
	List t1 = {8, NULL};
	List t2 = {15, NULL};
	List t3 = {64, NULL};
	
	puts("\nTest 3: ---\n");
	
	
	t1.next = &t2;
	t2.next = &t3;
	
	puts("Before mapInt (square terms):\n");
	displayList(&t1);
	
	mapInt(&t1, sqr);
	
	puts("\nAfter mapInt (square terms):\n");
	displayList(&t1);
}

void test4(){
	int i = 0;
	char nome[] = "Otavio";
	List *current = NULL;
	List *start = NULL;
	List *next = NULL;
	
	puts("\nTest 4: ---\n");
	
	for(; i<6; i++, current=next){
		next = newList('c', nome[i]);
		if(start==NULL) start = next;
		if(current!=NULL) current->next = next;
	}
	
	displayList(start);
	delList(start);
}

int main(){
	test1();
	test2();
	test3();
	test4();
	return 0;
}