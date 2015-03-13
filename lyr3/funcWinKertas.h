// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinKertas ()
{
  VAL_LABEL datx;
  memset(&datx, '\0', sizeof(datx));

		 // make new text area
		 datx.widget   = gtk_text_view_new();
		 gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(datx.widget)),"",-1);

         // make also eventbox for parent/base canvas
		 datx.eventbox = gtk_event_box_new();

		 datx.isGUI    = 1;
		 datx.GUItype  = 12;   // Kertas - Text Area - see ValLabel
		 datx.datatype = 40;   // widget

		 return datx;
}
