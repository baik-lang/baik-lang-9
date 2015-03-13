// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinMasukan ()
{
  VAL_LABEL datx;

  VAL_LABEL valdat, tmpdat;
  
  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

		 datx.widget   = gtk_entry_new();
		 datx.isGUI    = 1;
		 datx.GUItype  = 5;    // Input - masukan - see ValLabel
		 datx.datatype = 40;   // widget

		 return datx;
}
