# SoalShiftSISOP20_modul2_C10
Praktikum Modul 2 Sistem Operasi 2020

### Nama Anggota Kelompok :
### 1. Devi Hainun Pasya (05111840000014)
### 2. Anggara Yuda Pratama (05111840000008)

### Daftar Soal
* [No. 1](https://github.com/notdevi/SoalShiftSISOP20_modul2_C10/#soal-no-1)
* [No. 2](https://github.com/notdevi/SoalShiftSISOP20_modul2_C10/#soal-no-2)
* [No. 3](https://github.com/notdevi/SoalShiftSISOP20_modul2_C10/#soal-no-3)

### Soal No. 1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash, dengan ketentuan :

(a) Program menerima 4 argumen berupa :
    - Detik : 0-59 atau * (any value) 
    - Menit : 0-59 atau * (any value) 
    - Jam : 0-23 atau * (any value)
    - Path file .sh
    
(b) Program akan mengeluarkan pesan error jika argumen tidak sesuai.

(c) Program hanya menerima 1 configuration cron.

(d) Program berjalan di background (daemon).

(e) Tidak boleh menggunakan fungsi system().


***soal1.c***

[kodingan](https://github.com/notdevi/SoalShiftSISOP20_modul2_C10/blob/master/soal1/soal1.c)

**PENJELASAN :**

### Soal No. 2
Kiwa udh jago, jadi dia bikin program :

(a) Kiwa membuat folder, didalamnya terdapat program C yang per 30 detik membuat sebuah folder dengan nama timestamp `[YYYY-mm-dd_HH:ii:ss]`.

(b) Tiap folder diisi dengan 20 gambar yang didownload dari `https://picsum.photos/`, dimana tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 pixel dimana t adalah detik Epoch Unix. Gambar diberi nama timestamp `[YYYY-mm-dd_HH:ii:ss]`.

(c) Setelah sebuah folder terisi 20 gambar, folder akan di `zip` dan folder akan di delete (sehingga hanya menyisakan `.zip`).

(d) Buat program "killer" yang siap di run (executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program akan menterminasi program utama, lalu mendelete dirinya sendiri.

(e) Program utama bisa di run dalam dua mode, yaitu **MODE_A** dijalankan dengan argumen `-a` dan **MODE_B** dijalankan dengan argumen `-b`. Ketika dijalankan dalam **MODE_A**, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk **MODE_B**, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai (semua folder terisi gambar, terzip lalu di delete). 

***soal2.c***

[kodingan](https://github.com/notdevi/SoalShiftSISOP20_modul2_C10/blob/master/soal2/soal2.c)

***soal2_killer***
[kodingan_killer](https://github.com/notdevi/SoalShiftSISOP20_modul2_C10/blob/master/soal2/soal2_killer.c)

**PENJELASAN :**

blm jalan.

### Soal No. 3
Beberapa tugas harus dikerjakan secara bersamaan :

(a) Program harus mmebuat dua direktori di **"home/[USER]/modul2/"**. Direktori pertama diberi nama **"indomie"**, kemudian 5 detik kemudian membuat direktori kedua bernama **"sedaap"**.

(b) Program harus meng-ekstrak file **jpg.zip** di direktori **"home/[USER]/modul2/"**.

(c) Setelah di ekstrak, hasil pada direktori **"home/[USER]/modul2/jpg/"** herus dipindahkan dengan pengelompokkan. File dipindahkan ke **"home/[USER]/modul2/sedaap/"** sedangkan direktori dipindahkan ke **"home/[USER]/modul2/indomie/"**.

(d) untuk setiap direktori yang dipindahkan ke **"home/[USER]/modul2/indomie"** harus membuat dua file kosong. File pertama diberi nama **coba1.txt**, 3 detik kemudian membuat file bernama **coba2.txt**.

***soal3.c***

[kodingan](https://github.com/notdevi/SoalShiftSISOP20_modul2_C10/blob/master/soal3/soal3.c)

**PENJELASAN :**

`fork()` pertama digunakan untuk melahirkan anak yang akan mengeksekusi perintah untuk membuat direktori bernama **'indomie'** pada folder modul 2. Parent akan melahirkan anak lain pada scope yang berbeda. Karena fungsi `mkdir()` tidak boleh digunakan, maka digunakan fungsi `exec`. fungsi `mkdir` dipanggil melalui `execv`. 

```c
child_1 = fork();
	if (child_1 < 0) {
		exit(EXIT_FAILURE);
	}
	
	if (child_1 == 0) {
	// child 1
		char *argv[] = {"mkdir", "-p", "/home/devi/modul2/indomie", NULL};
		execv("/bin/mkdir", argv);
  }
```
`fork()` kedua digunakan untuk melahirkan anak yang akan mengeksekusi perintah untuk membuat direktori bernama **'sedaap'** pada folder modul 2. Parent akan melahirkan anak lain pada scope yang berbeda. Karena fungsi `mkdir()` tidak boleh digunakan, maka digunakan fungsi `exec`. fungsi `mkdir` dipanggil melalui `execv`. 
untuk melakukan penjedaan selama 5 detik sebelum pembuatan folder **'sedaap'**, digunakan fungsi `sleep(5)`.
```c
child_1 = fork();
		if (child_1 == 0) {
		// child 2
			sleep(5);
			char *argv[] = {"mkdir", "-p", "/home/devi/modul2/sedaap", NULL};
			execv("/bin/mkdir", argv);
		} 
```
`fork()` kedua digunakan untuk melahirkan anak yang akan mengeksekusi perintah untuk mengekstrak file `zip` bernama **'jpg.zip'** pada folder modul 2. Parent akan melahirkan anak lain pada scope yang berbeda. Fungsi `unzip` dipanggil melalui `execv`. 
```c
		int status2;
		child_1 = fork();
		if (child_1 == 0) {
		// child 3
			//while (wait(&status) > 0);
			chdir("/home/devi/modul2");
			char *zip[] = {"unzip", "/home/devi/modul2/jpg.zip", NULL};
			execv("/usr/bin/unzip", zip);
		}
```
Perlu juga mendeclare `int status2;`, karena pengeksekusian dari parent process harus menunggu child process selesai terlebih dahulu. Dalam hal ini, untuk menyortir file, harus menunggu proses `unzip` selesai terlebih dahulu.

Kemudian parent process untuk menyortir file akan dieksekusi. 

Fungsi `while ((wait(&status2)) > 0);` dipanggil untuk menunggu child process. 
Proses penyortiran file dilakukan dengan pertama-tama membuka direktori jpg yang merupakan hasil ekstrak dari `zip`. Kemudian dilakukan pengecekkan, apabila isi direktori tersebut kosong, maka `return 0`.
```c
		while ((wait(&status2)) > 0);
		struct dirent *drct;
		DIR *dir = opendir("/home/devi/modul2/jpg");

		if (dir == NULL) {	
			return 0;
		}
```
Apabila direktori tidak kosong, maka proses sortir akan dijalankan.
Pertama buat array `path[100]` yang digunakan untuk menampung path dari masing-masing file/direktori yang berada dalam folder jpg.
Kemudian buat `struct` yang menyimpan tipe file. Karena direktori "." dan ".." tidak termasuk, maka perlu dilakukan pengecekkan direktori dengan menggunakan fungsi `strcmp`, apabila perbedaannya = 0, maka `continue`, direkrori tidak ikut di sortir. 
```c
	while ((drct = readdir(dir)) != NULL) {
		char path[100];		
		struct stat filetype;
		if (strcmp(drct->d_name, ".") == 0 || strcmp(drct->d_name, "..") == 0) {		
			continue;
		} 
```
Kemudian path dari masing-masing file/direktori dimasukkan ke array `path` dengan mengcopy (`strcpy`) path folder jpg, lalu ditambahkan dengan direktori/file name menggunakan `strcat`.
```c
          else {
		strcpy(path, "/home/devi/modul2/jpg/");
		strcat(path, drct->d_name);
```
Lalu dilakukan proses pengecekkan dengan menggunakan `filetype.st_mode & S_IFDIR`, apabila type file merupakan direktori, akan di move ke direktori **'indomie'**. Pemindahan menggunakan command `mv` yang dipanggil dengan `execv`.  
```c
	if (stat(path, &filetype) == 0) {
		if (filetype.st_mode & S_IFDIR) {
			if (child_1 = fork() == 0) {
				char *move1[] = {"mv", path, "/home/devi/modul2/indomie/", NULL};
				execv("/bin/mv", move1);
			}
```
Setelah semua direktori di dalam folder jpg masuk ke direktori indomie, maka sisanya akan dimasukkan ke direktori **'sedaap'**. Karena diawal kita membuka direktori jpg, maka sekarang ditutup dengan fungsi `closedir`.
```c
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
```
Untuk membuat file `coba1.txt` dan `coba2.txt` kurang lebih sama dengan proses sortir file. Pertama open direktori indomie, karena direktori yang akan diisi berada didalamnya. Kemudian lakukan komparasi untuk meng-exclude direktori "." dan "..".
```c
struct dirent *makefile;
DIR *file = opendir("/home/devi/modul2/indomie");
		
while ((makefile = readdir(file)) != NULL) {
	char location[100];
	if (strcmp(makefile->d_name, ".") == 0 || strcmp(makefile->d_name, "..") == 0) {		
		continue;
	} 
```
kemudian path dari masing-masing direktori didalam folder indomie dimasukkan ke array `location`.
```c
          else {
		strcpy(location, "/home/devi/modul2/indomie/");
		strcat(location, makefile->d_name);
```
Kemudian dilakukan pemindahan direktori ke direktori yang akan diisi file `.txt` dengan menggunakan fungsi `chdir`. Setelah itu dijalankan command untuk membuat file `coba1.txt` yaitu `touch` yang dipanggil melalui `execv`. Karena pembuatan file antara coba1 dan coba2 perlu dijeda, maka digunakan fungsi `sleep(3);`. Lalu buat file `coba2.txt` dengan cara yang sama. 
```c
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
```
Kemudian tutup directory dengan fungsi `closedir`.




