# BAIK LANG
BAIK (Bahasa Anak Indonesia Untuk Komputer) adalah sebuah bahasa dengan sintak dasar bahasa Indonesia.

## Memasang
Untuk memasang, silahkan install paket pendukung terlebih dahulu
```
$ sudo apt-get install libgtk-3-dev
```
Lalu klon repo ini
```shell
$ git clone https://github.com/baik-lang/baik-lang-9
$ cd baik-lang-9
```
Lalu compile dan pasang
- Linux
```shell
$ chmod +x compile.sh
$ ./compile.sh
```

- CentOS
```shell
$ chmod +x compile.sh.centos
$ ./compile.sh.centos
```

- IGOS12
```shell
$ chmod +x compile.sh.igos12
$ ./compile.sh.igos12
```

- LNX Full GTK2
```shell
$ chmod +x compile_lnx_full_gtk2.sh
$ ./compile_lnx_full_gtk2.sh
```
- LNX Full GTK3
```shell
$ chmod +x compile_lnx_full_gtk3.sh
$ ./compile_lnx_full_gtk3.sh
```

- Full
```shell
$ chmod +x compile_lnx_full.sh
$ ./compile_lnx_full.sh
```

Jika sudah di compile lalu kita pindahkan file ke ```/usr/local/bin``` 
```shell
$ sudo cp -rf baik /usr/local/bin/baik
```

## Penggunaan
Cek jika paket sudah dipasang
```shell
$ baik -v
```
