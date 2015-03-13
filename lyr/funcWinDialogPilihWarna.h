// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinDialogPilihWarna ()
{
  VAL_LABEL datx;

  GtkWidget *dialog=NULL;
  GtkResponseType result;
  GtkColorSelection *colorsel=NULL;

  int    size = 0;
  char   get_name[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&get_name, '\0', sizeof(get_name));

  dialog = gtk_color_selection_dialog_new("Pilih Warna");
  result = gtk_dialog_run(GTK_DIALOG(dialog));

  if(result == GTK_RESPONSE_OK) {
    colorsel = GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(dialog)->colorsel);
	gtk_color_selection_get_current_color(colorsel, &datx.color);
	strcpy(datx.str , "warna");

	// printf("datx dialog warna\n");
  } else {
    memset(&datx.color, '\0', sizeof(datx.color));
	strcpy(datx.str , "");
  }

  gtk_widget_destroy(dialog);

  datx.isGUI    = 1;
  datx.GUItype  = 16;   // color dialog
  datx.datatype = 43;   // Color

  return datx;

}
