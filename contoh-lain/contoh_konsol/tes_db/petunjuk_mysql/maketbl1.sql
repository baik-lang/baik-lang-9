CREATE TABLE tbl_barang (
 nomer         MEDIUMINT NOT NULL AUTO_INCREMENT,
 nama          VARCHAR(32) NOT NULL,
 merek         VARCHAR(32) NOT NULL,
 harga_dasar   INTEGER,
 tanggal_masuk VARCHAR(16),
 jumlah        INTEGER,
 PRIMARY KEY(nomer)
);
