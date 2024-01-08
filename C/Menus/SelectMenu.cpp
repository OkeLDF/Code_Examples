#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <conio.h>

char** strlist_alloc(int num_of_str, int sizeof_strings){
	char **StrList;
	
	StrList = (char**) malloc (num_of_str * sizeof(char*));
	if(!StrList) return NULL;
	
	for(int i=0; i < num_of_str; i++){
		StrList[i] = (char*) malloc (sizeof_strings * sizeof(char));
		if(!StrList[i]) return NULL;
	}
	
	return StrList;
}


char** new_ListofOptions(int sizeof_strings, int numof_options, ...){
	char** Options;
	int i;
	
	va_list ap;
	va_start(ap, numof_options);
	
	Options = strlist_alloc(numof_options, sizeof_strings);
	if(!Options) return NULL;
	
	for(i=0; i<numof_options; i++){
		strcpy(Options[i], va_arg(ap, char*));
	}
	
	va_end(ap);
	return Options;
}


void free_ListofOptions (char** ListofOptions, int num_of_str){
	if(ListofOptions){
		for(int i=0; i < num_of_str; i++){
			if(ListofOptions[i]) free(ListofOptions[i]);
		}
		free(ListofOptions);
	}
}

int selection_menu(int numof_options, const char* Header, void (*Body_printfunc)(void), char **Options, const char* Footer){
	char key=' ';
	int select=0;
	
	if(!Options) return -1;
	
	while(1){
		system("cls");
		
		if(Header) printf("\n %s\n\n", Header);
		
		if(Body_printfunc) Body_printfunc();
		
		for(int i=0; i<numof_options; i++){
			printf(" \033[%sm ", (select % numof_options == i)? "44" : "37");
			printf("%s \033[m\n", Options[i]);
		}
		
		if(Footer) printf("\n %s\n", Footer);
		
		key=getch();
		switch(key){
			case 'M': // Seta para Direita
			case 'P': // Seta para Baixo
				select++; break;
			
			case 'K': // Seta para Esquerda
			case 'H': // Seta para Cima
				select--; break;
			
			case ' ':
			case 13: // Enter
				return select;
		}
		
		if(select>numof_options-1) select=0;
		if(select<0) select=numof_options-1;
	}
}

void printer(){
	puts(" Description, body, or anything else\n");
}

int main(){
	int C_MAX = 20;
	int NUM_OF_OP = 4;
	int selected;
	char **Options = new_ListofOptions(C_MAX, NUM_OF_OP, "0) zero", "1) um", "2) dois", "3) tres");
	
	selected = selection_menu(NUM_OF_OP, "Title", printer, Options, "Footer");
	
	switch(selected){
		case 0: puts("\n Hello World"); break;
		
		case 1: puts("\n selecionastes o 'Um'"); break; 
		
		case 2: puts("\n oNI-san >.<"); break;
		
		case 3: puts("\n Bye bye, World"); break;
		
		default: fprintf(stderr, "\nErro.\n");
	}
	
	free_ListofOptions(Options, NUM_OF_OP);
	return 0;
}
