#include <unistd.h>
#include <stdio.h>

#include <errno.h>
#include <string.h>

int main(){
	char *args[]={
		"speak",
		"-c33",
		"-v",
		"HelloWorld!",
		NULL
	};
	
	puts("the name of the program is wrong, so it will cause an error:");
	
	if(execv("C:\\C\\samples\\CommandLineOptions\\spea", args)){
		printf("\033[31mError: %s\033[m", strerror(errno));
	}
	
	puts("\nthis should not be printed");
	// because execl stops this process to start another
}