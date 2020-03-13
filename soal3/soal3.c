#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
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
				chdir("/home/devi/modul2");
				char *zip[] = {"unzip", "/home/devi/modul2/jpg.zip", NULL};
				execv("/usr/bin/unzip", zip);
			} else {
			// parent 3
				while ((wait(&status2)) > 0);
				struct dirent *drct;
				DIR *dir = opendir("/home/devi/modul2/jpg");

				if (dir == NULL) {	
					return 0;
				}
	
				while ((drct = readdir(dir)) != NULL) {
					char path[100];		
					struct stat filetype;
					if (strcmp(drct->d_name, ".") == 0 || strcmp(drct->d_name, "..") == 0) {		
						continue;
					} else {
						strcpy(path, "/home/devi/modul2/jpg/");
						strcat(path, drct->d_name);

						if (stat(path, &filetype) == 0) {
							if (filetype.st_mode & S_IFDIR) {
								if (child_1 = fork() == 0) {
									char *move1[] = {"mv", path, "/home/devi/modul2/indomie/", NULL};
									execv("/bin/mv", move1);
								}
							} else {
								if (child_1 = fork() == 0) {
									char *move2[] = {"mv", path, "/home/devi/modul2/sedaap/", NULL};
									execv("/bin/mv", move2);
								} 
							}
						}
					}
				}
				closedir(dir); 
		
				struct dirent *makefile;
				DIR *file = opendir("/home/devi/modul2/indomie");
		
				while ((makefile = readdir(file)) != NULL) {
					char location[100];
					if (strcmp(makefile->d_name, ".") == 0 || strcmp(makefile->d_name, "..") == 0) {		
						continue;
					} else {
						strcpy(location, "/home/devi/modul2/indomie/");
						strcat(location, makefile->d_name);
			
						if (child_1 = fork() > 0) {
							chdir(location);
							char *mktxt1[] = {"touch", "coba1.txt", NULL};
							execv("/bin/touch", mktxt1);
						} sleep(3);
						if (child_1 = fork() > 0) {
							chdir(location);
							char *mktxt2[] = {"touch", "coba2.txt", NULL};
							execv("/bin/touch", mktxt2);
						}
					}
				}
				closedir(file);					
			}
		}
	}  
}
