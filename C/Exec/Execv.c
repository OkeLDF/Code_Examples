#include <unistd.h>
#include <stdio.h>

int main(){
	char *args[]={
		"speak",
		"-c33",
		"-v",
		"HelloWorld!",
		NULL
	};
	execv("C:\\Users\\otavi\\Documents\\GitHub\\Code_Examples\\C\\CommandLineOptions\\speak", args);
	
	puts("this will not be printed");
	// because execl stops this process to start another
}