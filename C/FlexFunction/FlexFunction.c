#include <stdio.h>
#include <stdarg.h>

int soma(int numof_args, ...){
	int acumul=0, i;
	
	va_list ap;
	va_start(ap, numof_args);
	
	for(i=0; i<numof_args; i++){
		acumul += va_arg(ap, int);
	}
	
	va_end(ap);
	return acumul;
}

int main(){
	printf("%i", soma(6, 1,2,3,4,5,6));
	return 0;
}