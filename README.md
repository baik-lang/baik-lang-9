# BAIK LANG

BAIK (Bahasa Anak Indonesia Untuk Komputer) adalah sebuah bahasa pemrograman dengan sintaks dasar berbahasa Indonesia.

## Instalasi

Sebelum memulai instalasi, pastikan paket pendukung telah terpasang. Untuk distribusi Linux, Anda dapat menggunakan perintah berikut untuk menginstal paket yang diperlukan:

```bash
$ sudo apt-get install libgtk-3-dev
```

Setelah itu, lakukan klon pada repositori ini:

```bash
$ git clone https://github.com/baik-lang/baik-lang-9
$ cd baik-lang-9
```

Kemudian, kompilasi dan pasang BAIK:

### Linux
```bash
$ chmod +x compile.sh
$ ./compile.sh
```

### CentOS
```bash
$ chmod +x compile.sh.centos
$ ./compile.sh.centos
```

### IGOS12
```bash
$ chmod +x compile.sh.igos12
$ ./compile.sh.igos12
```

### LNX Full GTK2
```bash
$ chmod +x compile_lnx_full_gtk2.sh
$ ./compile_lnx_full_gtk2.sh
```

### LNX Full GTK3
```bash
$ chmod +x compile_lnx_full_gtk3.sh
$ ./compile_lnx_full_gtk3.sh
```

### Full
```bash
$ chmod +x compile_lnx_full.sh
$ ./compile_lnx_full.sh
```

Setelah proses kompilasi selesai, pindahkan file yang dihasilkan ke direktori `/usr/local/bin` dengan perintah:

```bash
$ sudo cp -rf baik /usr/local/bin/baik
```

## Periksa Hasil Instalasi

Untuk memastikan bahwa BAIK telah terpasang dengan benar, jalankan perintah berikut:

```bash
$ baik -v
```
