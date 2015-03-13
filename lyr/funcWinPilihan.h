// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinPilihan ()
{
  VAL_LABEL datx;

  
  memset(&datx, '\0', sizeof(datx));


		 datx.widget   = gtk_combo_box_entry_new_text ();
                 // make also eventbox for parent/base canvas
		 datx.eventbox = gtk_event_box_new();

		 datx.isGUI    = 1;
		 datx.GUItype  = 6;    // Combo Text - pilihan - see ValLabel
		 datx.datatype = 40;   // widget

		 return datx;
}


