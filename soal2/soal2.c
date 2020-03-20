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
#include <time.h>

char filename[80];

char *times(){
	int jam, menit, detik, hari, bulan, tahun;
  	time_t rawtime = time(NULL);
  	struct tm tm = *localtime(&rawtime);

  	jam = tm.tm_hour;
  	menit = tm.tm_min;
  	detik = tm.tm_sec;
  	hari = tm.tm_mday;
  	bulan = tm.tm_mon+1;
  	tahun = tm.tm_year+1900;

  	sprintf(filename, "%02d-%02d-%d_%02d:%02d:%02d",
          	hari, bulan, tahun, jam, menit, detik);

  return filename;
}

int main(int argc, char const *argv[]) {
	FILE * killer;
	killer = fopen("soal2_killer.sh", "w");

	if(argc == 2){
		if(strcmp(argv[1], "-a") == 0) {
			fprintf(killer, "#!/bin/bash\nkillall soal2\n");
			fprintf(killer, "rm $0");
		}
		else if(strcmp(argv[1], "-b") == 0) {
			fprintf(killer, "#!/bin/bash\nkill %d\n", getpid());
			fprintf(killer, "rm $0");
		} else {
			printf("maaf tidak bisa dikabulkan, gunakan -a atau -b\n");
			exit(0);
		}
	} else {
		printf("maaf tidak bisa dikabulkan, gunakan hanya 2 argumen\n");
		exit(0);
	}

	pid_t pid, sid, child_1, child_2, child_3, child_4;

	pid = fork();

	if(pid < 0) {
		exit(EXIT_FAILURE);
	} 
	if(pid > 0) {
		exit(EXIT_SUCCESS);
	}
	
	umask(0);

	sid = setsid();
	if(sid < 0) {
		exit(EXIT_FAILURE);
	} 
	if((chdir("/home/devi/")) < 0) {
		exit(EXIT_FAILURE);
	}

  	close(STDIN_FILENO);
  	close(STDOUT_FILENO);
  	close(STDERR_FILENO);

	while(1) {
	int files = 0, status, jam, menit, detik, hari, bulan, tahun;
	char dirname[80] = "/home/devi/", zipname[100],
	     picsize[100], fordir[100], folder[80];

	strcpy(folder, times());
	strcat(dirname, folder);

	child_1 = fork();
	if(child_1 == 0) {
		char *makedir[] = {"mkdir", "-p", dirname, NULL};
		execv("/bin/mkdir", makedir);
	}

	unsigned long epoch = time(NULL), 
		      size = (epoch%1000)+100;
	sprintf(picsize, "%lu", (epoch%1000)+100);

	while((waitpid(child_1, &status, 0)) > 0);

	child_2 = fork();
	if(child_2 == 0) {
		for(int i = 1; i <= 20; i++) {
			unsigned long epoch = time(NULL), 
		                      size = (epoch%1000)+100;
			sprintf(picsize, "%lu", (epoch%1000)+100);

			char url[100] = "https://picsum.photos/";
			strcat(url, picsize);

			strcpy(fordir, dirname);
			strcat(fordir, "/");
			strcat(fordir, times());

			child_3 = fork();
			if(child_3 == 0) {
				char *donlot[] = {"wget", url, "-O", fordir, NULL};
				execv("/usr/bin/wget", donlot);
			}
			sleep(5);
		}
		
		strcpy(zipname, folder);
		strcat(zipname, ".zip");

		while((waitpid(child_2, &status, 0)) > 0);

		child_4 = fork();
		if(child_4 == 0) {
			char *rmv[] = {"zip", "-rm", zipname, folder, NULL};
			execv("/usr/bin/zip", rmv);
		}
	}
	sleep(30);
	}
}
