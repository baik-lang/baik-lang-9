// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinDialogPilihHuruf ()
{
  VAL_LABEL datx;

  GtkWidget *dialog=NULL;
  GtkResponseType result;
  gchar     *fontname=NULL;

  int    size = 0;
  char   get_name[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&get_name, '\0', sizeof(get_name));

  dialog = gtk_font_selection_dialog_new("Pilih Huruf");
  result = gtk_dialog_run(GTK_DIALOG(dialog));

  if(result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY) {
    fontname = gtk_font_selection_dialog_get_font_name(GTK_FONT_SELECTION_DIALOG(dialog));
    // printf("DialogHuruf %s\n", fontname);

	strcpy(datx.str , fontname);
    datx.font_desc = pango_font_description_from_string(fontname);
  } else {
	strcpy(datx.str , "");
	datx.font_desc = NULL;
  }

  gtk_widget_destroy(dialog);

  datx.isGUI    = 1;
  datx.GUItype  = 15;   // font
  datx.datatype = 42;   // Font SelectionDialog

  return datx;

}
