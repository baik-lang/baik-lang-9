// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinDialogPilihArsip ()
{
  VAL_LABEL datx;

  GtkWidget       *window=NULL;
  GtkWidget       *dialog=NULL;
  GtkResponseType result;
  GtkFileFilter   *filter=NULL;


  gchar     *filename=NULL;
  gchar     *folder=NULL;

  int    size = 0;
  char   get_name[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&get_name, '\0', sizeof(get_name));

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  dialog = gtk_file_chooser_dialog_new("Pilih Arsip",
	                                   GTK_WINDOW(window),
									   GTK_FILE_CHOOSER_ACTION_OPEN ||
									   GTK_FILE_CHOOSER_ACTION_SAVE,
									   GTK_STOCK_CANCEL,
									   GTK_RESPONSE_CANCEL,
									   GTK_STOCK_OPEN,
									   GTK_RESPONSE_ACCEPT,
									   NULL);

  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "Semua Arsip");
  gtk_file_filter_add_pattern(filter, "*");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

  result = gtk_dialog_run(GTK_DIALOG(dialog));

  if(result == GTK_RESPONSE_ACCEPT) {
    filename   = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    folder     = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(dialog));

     // printf("DialogArsip file %s\n", filename);
     // printf("DialogArsip folder %s\n", folder);

	strcpy(datx.str , filename);
	datx.filename = filename;
	datx.folder   = folder;

  } else {
	strcpy(datx.str , "");
	datx.filename = "";
	datx.folder   = "";

  }

  gtk_widget_destroy(dialog);

  datx.isGUI    = 1;
  datx.GUItype  = 17;   // filename
  datx.datatype = 44;   // File SelectionDialog

  // printf("Dialog File OK\n");

  return datx;

}


