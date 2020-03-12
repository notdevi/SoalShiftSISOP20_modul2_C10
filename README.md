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
    i. Detik : 0-59 atau * (any value)
    ii. Menit : 0-59 atau * (any value)
    iii. Jam : 0-23 atau * (any value)
    iv. Path file .sh
    
(b) Program akan mengeluarkan pesan error jika argumen tidak sesuai.

(c) Program hanya menerima 1 configuration cron

(d) Program berjalan di background (daemon)

(e) Tidak boleh menggunakan fungsi system()

**KODINGAN :**
***soal1.c***
```c
ea blm ajg
```
**PENJELASAN :**

### Soal No. 2
Kiwa udh jago, jadi dia bikin program :
(a) Kiwa membuat folder, didalamnya terdapat program C yang per 30 detik membuat sebuah folder dengan nama timestamp `[YYYY-mm-dd_HH:ii:ss]`.

(b) Tiap folder diisi dengan 20 gambar yang didownload dari `https://picsum.photos/`, dimana tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 pixel dimana t adalah detik Epoch Unix. Gambar diberi nama timestamp `[YYYY-mm-dd_HH:ii:ss]`.

(c) Setelah sebuah folder terisi 20 gambar, folder akan di `zip` dan folder akan di delete (sehingga hanya menyisakan `.zip`).

(d) Buat program "killer" yang siap di run (executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program akan menterminasi program utama, lalu mendelete dirinya sendiri.

(e) Program utama bisa di run dalam dua mode, yaitu **MODE_A** dijalankan dengan argumen -a dan **MODE_B** dijalankan dengan argumen -b. Ketika dijalankan dalam **MODE_A**, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk **MODE_B**, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai (semua folder terisi gambar, terzip lalu di delete). 

**KODINGAN :**
***soal2.c***
```c
ea blm bgst
```
**PENJELASAN :**

### Soal No. 3
Beberapa tugas harus dikerjakan secara bersamaan :
(a) Program harus mmebuat dua direktori di **"home/[USER]/modul2/"**. Direktori pertama diberi nama **"indomie"**, kemudian 5 detik kemudian membuat direktori kedua bernama **"sedaap"**.

(b) Program harus meng-ekstrak file **jpg.zip** di direktori **"home/[USER]/modul2/"**.

(c) Setelah di ekstrak, hasil pada direktori **"home/[USER]/modul2/jpg/"** herus dipindahkan dengan pengelompokkan. File dipindahkan ke **"home/[USER]/modul2/sedaap/"** sedangkan direktori dipindahkan ke **"home/[USER]/modul2/indomie/"**.

(d) untuk setiap direktori yang dipindahkan ke **"home/[USER]/modul2/indomie"** harus membuat dua file kosong. File pertama diberi nama **coba1.txt**, 3 detik kemudian membuat file bernama **coba2.txt**.

**KODINGAN :** 
***soal3.c***
```c
ea blm jancuks
```
**PENJELASAN :**



