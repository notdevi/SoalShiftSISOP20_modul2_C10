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
#include <ctype.h>

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

int main(int argc, char *argv[]) {
    int detik_skrng, menit_skrng, jam_skrng;
    int cek1 = 0, cek2 = 0, cek3 = 0, cek4 = 0;

    if(argc == 5) {
        int argument[4], x;
        for (x = 1; x < 4; x++) {
            if (isDigit(argv[x])) {
                argument[x] = atoi(argv[x]);
                if(argument[x] < 0)
                    printf("argument %d is not valid\n", x);
            }
            else if (cek_bintang(argv[x]))
                argument[x] = -1;
            else {
                printf("argument %d tidak sesuai dengan yang diminta\n", x);
                exit(EXIT_FAILURE);
            }
        }

        if (argument[1] < 0 || argument[1] > 59 || 
                argument[2] < 0 || argument[2] > 59 || 
                    argument[3] < 0|| argument[3] > 23) {
            printf("argumentt tidak valid\n");
            exit(EXIT_FAILURE);
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

        if ((chdir("/")) < 0) {
            exit(EXIT_FAILURE);
        }   
        
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        while(1){
            time_t waktu = time(NULL);              //struct bawaan c utk waktu sekarang
            struct tm *now_tm = localtime(&waktu);  //buat mengetahui waktu sekarang

            detik_skrng = now_tm->tm_sec;
            menit_skrng = now_tm->tm_min;
            jam_skrng = now_tm->tm_hour;

            if((detik_skrng == argument[1] || argument[1] == -1)
                && (menit_skrng == argument[2] || argument[2] == -1)
                    && (jam_skrng == argument[3] || argument[3] == -1)) {
                        pid_t child_id;
                        child_id = fork();

                        if (child_id < 0) {
                            printf("fail to fork");
                            exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
                        }

                        if (child_id == 0) {    
                            char *trm[] = {"bash", argv[4], NULL};
                            execv("/bin/bash", trm);
                        }
                    }
            sleep(1);    //delay selama 1 detik
        }  
    }
    
    else {      //ketika tidak masuk syarat jumlah argument yg diminta yaitu harus 5
        printf("argument yang dimasukkan tidak sesuai dengan jumlah yang diminta\n");
        exit(EXIT_FAILURE);
    }
}