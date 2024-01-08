#include <stdio.h>
#include <unistd.h>
#include <string.h>

void error(char str[]){
	fprintf(stderr, "\033[31mError: %s.\033[m", str);
	exit(1);
}

int is_color(char* color){
	switch(color[0]){
		case '3':
		case '4':
		case '9':
			if(!strchr("01234567", color[1])) return 0;
			break;
		
		case '1':
			if(color[1] != '0') return 0;
			if(!strchr("01234567", color[2])) return 0;
			break;
		
		default: return 0;
	}
	return 1;
}

int main(int argc, char* argv[]){
	char c;
	char *color;
	color="37";
	int k;
	
	while((c = getopt(argc, argv, "hvc:")) != EOF){
		switch(c){
			case 'h':
				puts("\033[mprints a formated string.");
				puts("Usage: speak -<option> <string>\n");
				puts("Command line options:");
				puts("    -c: prints with color; the deafult color is 37. The valid colors are:");
				int i, j;
				for(i=0; i<=7; i++){
					printf("      ");
					for(j=3; j<=10; j++){
						printf("  \033[%d%dm%d%d\033[m", j, i, j, i);
						if(j==4) j=8;
					}
					puts("");
				}
				puts("\n    -h: prints this help.");
				return 0;
			
			case 'v':
				for(k=0; k<argc; k++){
					puts(argv[k]);
				}
				break;
				
			case 'c':
				color = optarg;
				if(!is_color(color)) error("Not a valid color");
				break;
		
			default: break;
		}
	}
	argc-=optind;
	argv+=optind;
	
	printf("\033[%sm%s\033[m", color, argv[0]);
}