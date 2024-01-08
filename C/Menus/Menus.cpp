#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define C_MAX 20
#define NUM_OF_OP 4

char** strlist_alloc(int num_of_str, int char_max){
	char **StrList;
	
	StrList = (char**) malloc (num_of_str * sizeof(char*));
	if(!StrList) return NULL;
	
	for(int i=0; i < num_of_str; i++){
		StrList[i] = (char*) malloc (char_max * sizeof(char));
		if(!StrList[i]) return NULL;
	}
	
	return StrList;
}


void free_strlist (char** StrList, int num_of_str){
	if(StrList){
		for(int i=0; i < num_of_str; i++){
			if(StrList[i]) free(StrList[i]);
		}
		free(StrList);
	}
}


void list_options(int select, int num_of_options, char **options){
	for(int i=0; i<num_of_options; i++){
		printf(" %c ", (select % num_of_options == i)? '>' : ' ');
		printf("%s\n", options[i]);
	}
}


int selection_menu(int num_of_options, const char *Title, char **Options){
	char key=' ';
	int select=0;
	
	while(1){
		system("cls");
		printf("\n %s\n\n", Title);
		list_options(select, num_of_options, Options);
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
		
		if(select>num_of_options-1) select=0;
		if(select<0) select=num_of_options-1;
	}
}


int string_menu(int num_of_options, int opt_char_max, const char *Title, char **Options){
	char *Command;
	
	system("cls");
	printf("\n %s\n\n", Title);
	for(int i=0; i < num_of_options; i++){
		printf(" %s\n", Options[i]);
	}
	printf("\n Comm: ");
	
	Command = (char*) malloc(opt_char_max * sizeof(char));
	fgets(Command, opt_char_max*sizeof(char), stdin);
	Command[strcspn(Command, "\n")] = 0;
	
	for(int i=0; i < num_of_options; i++){
		if(strcmpi(Options[i], Command)==0) return i;
	}
	
	printf("\n > Invalido!\n");
	return -1;
}


int numeric_menu(int num_of_options, const char *Title, char **Options){
	int r;
	
	system("cls");
	printf("\n %s\n\n", Title);
	for(int i=0; i < num_of_options; i++){
		printf(" (%d) %s\n", i, Options[i]);
	}
	printf("\n R: ");
	
	if(!scanf("%d", &r)){
		printf("\n > Invalido!\n");
		return -1;
	}
	
	if(r > num_of_options || r < 0){
		printf("\n > Invalido!\n");
		return -1;
	}
	
	return r;
}


int main(){
	char **Options;
	char *Title;
	int elect;
	
	Options = strlist_alloc(NUM_OF_OP, C_MAX);
	Title = (char*) malloc(C_MAX * sizeof(char));
	
	strcpy(Title, "Use as setas...");
	strcpy(Options[0], "MENU SELECAO");
	strcpy(Options[1], "MENU STRING");
	strcpy(Options[2], "MENU NUMERICO");
	strcpy(Options[3], "EXIT");
	
	elect = selection_menu(NUM_OF_OP, Title, Options);
	
	switch(elect){
		case 0: printf("\n >>> %d\n",selection_menu(NUM_OF_OP, "Use as setas...", Options)); break; // SELECAO
		
		case 1: printf("\n >>> %d\n", string_menu(NUM_OF_OP, C_MAX, "Digite a opcao...", Options)); break; // STRING
		
		case 2: printf("\n >>> %d\n", numeric_menu(NUM_OF_OP, "Digite o numero...", Options));break; // NUMERICO
		
		case 3: break;
	}
	
	free(Title);
	free_strlist(Options, NUM_OF_OP);
	return 0;
}
