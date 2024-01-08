#include <unistd.h>
#include <stdio.h>

int main(){
	execl(
		"C:\\C\\samples\\CommandLineOptions\\speak",
		"speak",
		"-c33",
		"-v",
		"HelloWorld!",
		NULL
	);
	
	puts("this will not be printed");
	// because execl stops this process to start another
}