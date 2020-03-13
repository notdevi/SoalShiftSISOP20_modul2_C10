#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main(int arg, char* argmode[]) {
	if (arg != 2) {
		exit(EXIT_FAILURE);
	} 
	int mode;
	if (argmode[1][1] == "A") {
		mode = 1;
	} else if (argmode[1][1] == "B") {
		mode = 2;
	}
	
  	pid_t pid, sid;

	time_t rawtime;
	struct tm *info;
	char buffer[80], filename[80];

	time( &rawtime );
	info = localtime( &rawtime);

	strftime(buffer, 80, "%Y-%m-%d_%X", info);
	puts(buffer);
	sprintf(filename, "/home/devi/%s", buffer);
  	
	pid = fork();

 	if (pid < 0) {
    		exit(EXIT_FAILURE);
  	}

  	if (pid > 0) {
    		exit(EXIT_SUCCESS);
  	}

  	umask(0);

  	sid = setsid();
  	if (sid < 0) {
    		exit(EXIT_FAILURE);
  	}

 	if ((chdir("/")) < 0) {
    		exit(EXIT_FAILURE);
  	}

  	close(STDIN_FILENO);
  	close(STDOUT_FILENO);
  	close(STDERR_FILENO);

  	while (1) {
    		pid_t child_1;
		int status;

		child_1 = fork();

		if (child_1 == 0) {
			char *mkdirc[] = {"mkdir", "-p", "filename", NULL};
			execv("/bin/mkdir", mkdirc);
		} 
		if (child_1 == 0) {
			while ((wait(&status)) > 0);
			for(int i=1; i<=20; i++){
				time_t rawtime;
				struct tm *info;
				char url[100], filenm[100], buffer2[80];

				time( &rawtime );
				info = localtime( &rawtime);

				strftime(buffer2, 80, "%Y-%m-%d_%X", info);
				
				sprintf(url, "https://picsum.photos/%d", (((int)buffer2 % 1000) + 100));
				pid_t child_2;
				child_2 = fork();
				
				if (child_2 == 0) {
					char *download[] = {"wget", link, "-O", buffer2, "-o", "/dev/null", NULL};
					execv("/usr/bin/wget", download);
					exit(EXIT_SUCCESS);
				} 
			sleep(5);
			}
		int status2;
		while(wait(&status2) > 0);
		char *zip[] = {"zip", "-r", "filename", NULL};
		execv("usr/bin/zip", zip);
			
		pid_t child_3;
		child_3 = fork();
		if (child_3 == 0) {
			char *rmv[] = {"rm", "-rf", "filename", NULL};
			execv("/bin/rm", rmv); 
		}
	}
	sleep(30);
}
