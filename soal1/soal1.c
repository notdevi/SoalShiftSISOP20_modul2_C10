#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int cek_bintang(char source[])
{
  if (source[0] == '*') return 1;

  return 0;
}

int isDigit(char source[]) {
  for (int i = 0; i < strlen(source); i++)
    if (source[i] < '0' || source[i] > '9')
      return 0;

  return 1;
}


int main(int argc, char **argv) {
    int detik_skrng, menit_skrng, jam_skrng;
    if(argc == 5) {
        int argument[4];
        for (int x = 1; x < 4; x++) {
            if (isDigit(argv[x])) {
                argument[x] = atoi(argv[x]);
                if(argument[x] < 0)
                    printf("argument %d bukan angka\n", x);
            }
            else if (cek_bintang(argv[x]))
                argument[x] = -1;
            else {
                printf("argument %d sesuai dengan yang diminta\n", x);
                exit(EXIT_FAILURE);
            }

            int cek = atoi(argv[x]);
            //cek range detik dan menit
            if ((x == 0 || x ==1) && (cek > 59 || cek < 0)) {
                printf("Argumen Tidak Sesuai Range yang Diminta\n");
                return 0;
            }
            //cek range jam
            if (x == 2 && (cek > 23 || cek < 0 )){
                printf("Argumen Tidak Sesuai Range yang Diminta\n");
                return 0;
            }
        }

        pid_t pid, sid;

        pid = fork();

        if (pid < 0)
            exit(EXIT_FAILURE);

        if (pid > 0) 
            exit(EXIT_SUCCESS);

        umask(0);

        sid = setsid();
        if (sid < 0)
            exit(EXIT_FAILURE);

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        while (1)  {
            time_t waktu;
            struct tm* now_tm;  

            waktu = time(NULL);
            now_tm = localtime(&waktu);
            
            detik_skrng = now_tm->tm_sec;
            menit_skrng = now_tm->tm_min;
            jam_skrng = now_tm->tm_hour;

            if ((detik_skrng == argument[1] || argument[1] == -1) 
                && (menit_skrng == argument[2] || argument[2] == -1) 
                    && (jam_skrng || argument[3] == -1)) {
                        pid_t child_id;
                        child_id = fork();

                        int sts;

                        if (child_id == 0) {    
                            char *argexec[] = {"bash", argv[4], NULL};
                            execv("/bin/bash", argexec);
                        }
                    }

                sleep(1);
            }
        }
    else {
            printf("argument is not valid!\n");
            exit(EXIT_FAILURE);
    }
}
