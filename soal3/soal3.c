#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>

int main(){
	pid_t child_1;
	int status;

	child_1 = fork();
	if (child_1 < 0) {
		exit(EXIT_FAILURE);
	}
	
	if (child_1 == 0) {
	// child 1
		char *argv[] = {"mkdir", "-p", "/home/devi/modul2/indomie", NULL};
		execv("/bin/mkdir", argv);
	} else if (child_1 > 0) {
	// parent 1
		//int status1;
		child_1 = fork();
		if (child_1 == 0) {
		// child 2
			sleep(5);
			char *argv[] = {"mkdir", "-p", "/home/devi/modul2/sedaap", NULL};
			execv("/bin/mkdir", argv);
		} else if (child_1 > 0) {
		// parent 2
			int status2;
			child_1 = fork();
			if (child_1 == 0) {
			// child 3
				//while (wait(&status) > 0);
				char *zip[] = {"unzip", "/home/devi/modul2/jpg.zip", NULL};
				execv("/usr/bin/unzip", zip);
			} else {
			// parent 3
				while (wait(&status2) > 0);
				char *move1[] = {"mv", "/home/devi/modul2/jpg/*/", "/home/devi/modul2/indomie/", NULL};
				execv("/bin/mv", move1);	
				//char *move2[] = {"mv", "/home/devi/modul2/jpg/", "/home/devi/modul2/sedaap/", NULL};
				//execv("/bin/mv", move2); 
			}	 
		}
	} 
}
