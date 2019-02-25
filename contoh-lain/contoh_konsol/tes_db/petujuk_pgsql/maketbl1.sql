CREATE TABLE tbl_barang (
 nomer         INTEGER NOT NULL,
 nama          VARCHAR(32) NOT NULL,
 merek         VARCHAR(32) NOT NULL,
 harga_dasar   INTEGER,
 tanggal_masuk VARCHAR(16),
 jumlah        INTEGER,
 PRIMARY KEY(nomer)
);
