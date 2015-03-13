#include <string.h>

#define DEF_PAD 10
#define DEF_PAD_SMALL 5

#define TM_YEAR_BASE 1900

char TANGGAL_TERPILIH[64] = "";

typedef struct _CalendarData {
  GtkWidget *flag_checkboxes[5];
  gboolean  settings[5];
  GtkWidget *font_dialog;
  GtkWidget *window;
  GtkWidget *prev2_sig;
  GtkWidget *prev_sig;
  GtkWidget *last_sig;
  GtkWidget *month;
  VAL_LABEL datx; // target to write date
} CalendarData;

enum {
  calendar_show_header,
  calendar_show_days,
  calendar_month_change, 
  calendar_show_week,
  calendar_monday_first
};

/*
 * GtkCalendar
 */

void calendar_date_to_string (CalendarData *data,
			      char         *buffer,
			      gint          buff_len)
{
  GDate *date;
  guint year, month, day;

  gtk_calendar_get_date (GTK_CALENDAR(data->window),
			 &year, &month, &day);
  date = g_date_new_dmy (day, month + 1, year);
  g_date_strftime (buffer, buff_len-1, "%x", date);

  g_date_free (date);
}

void calendar_set_signal_strings (char         *sig_str,
				  CalendarData *data)
{
  gtk_label_set_text (GTK_LABEL (data->last_sig), sig_str);

  if(data->datx.GUItype == 4) {          // Target is Label
	gtk_label_set_text (GTK_LABEL (data->datx.widget), sig_str);
  } else if(data->datx.GUItype == 5) {   // Target is Input Text
    gtk_entry_set_text(GTK_ENTRY(data->datx.widget), sig_str);
  } else if(data->datx.datatype == 3) {  // Target is String Variable
	strcpy(data->datx.str, sig_str);
  }

}

void calendar_month_changed (GtkWidget    *widget,
                             CalendarData *data)
{
  char buffer[256] = "bulan_berubah: ";

  calendar_date_to_string (data, buffer+15, 256-15);
  calendar_set_signal_strings (buffer, data);
}

void calendar_day_selected (GtkWidget    *widget,
                            CalendarData *data)
{
  char buffer[64]  = "";
  char buffer2[64] = "";

  calendar_date_to_string (data, buffer, 64);
  calendar_date_to_string (data, buffer2, 64);

  calendar_date_to_string (data, TANGGAL_TERPILIH, 64);
  
  calendar_set_signal_strings (buffer, data);

  // printf("%s\n", buffer2); // set into global will be OK
}

void calendar_prev_month (GtkWidget    *widget,
                          CalendarData *data)
{
  char buffer[256] = "bulan_lalu: ";

  calendar_date_to_string (data, buffer+12, 256-12);
  calendar_set_signal_strings (buffer, data);
}

void calendar_next_month( GtkWidget    *widget,
                            CalendarData *data )
{
  char buffer[256] = "bulan_depan: ";

  calendar_date_to_string (data, buffer+12, 256-12);
  calendar_set_signal_strings (buffer, data);
}

void calendar_prev_year( GtkWidget    *widget,
                            CalendarData *data )
{
  char buffer[256] = "tahun_lalu: ";

  calendar_date_to_string (data, buffer+11, 256-11);
  calendar_set_signal_strings (buffer, data);
}

void calendar_next_year( GtkWidget    *widget,
                            CalendarData *data )
{
  char buffer[256] = "tahun_depan: ";

  calendar_date_to_string (data, buffer+11, 256-11);
  calendar_set_signal_strings (buffer, data);
}


void calendar_set_flags( CalendarData *calendar )
{
  gint i;
  gint options=0;
  for (i=0;i<3;i++) 
    if (calendar->settings[i])
      {
	    options=options + (1<<i);
      }
  if (calendar->window)
    gtk_calendar_set_display_options (GTK_CALENDAR (calendar->window), options);
}

void calendar_toggle_flag( GtkWidget    *toggle,
                           CalendarData *calendar )
{
  gint i;
  gint j;
  j=0;
  for (i=0; i<3; i++)
    if (calendar->flag_checkboxes[i] == toggle)
      j = i;

  calendar->settings[j]=!calendar->settings[j];
  calendar_set_flags(calendar);
  
}

void calendar_font_selection_ok (GtkWidget    *button,
                                 CalendarData *calendar)
{
  GtkRcStyle *style;
  char *font_name;
  GdkColor mycolor;
  GdkColor mycolor2;

  gdk_color_parse((gchar*) "aquamarine", &mycolor);
  gdk_color_parse((gchar*) "blue", &mycolor2);
  if (calendar->window)
    {
      font_name = gtk_font_selection_dialog_get_font_name (GTK_FONT_SELECTION_DIALOG(calendar->font_dialog));
      if (font_name) 
	{
	  style = gtk_rc_style_new ();
	  pango_font_description_free (style->font_desc);
	  style->font_desc = pango_font_description_from_string (font_name);
	  gtk_widget_modify_style (calendar->window, style);

	  gtk_widget_modify_bg(calendar->window, GTK_STATE_NORMAL, &mycolor);
	  gtk_widget_modify_fg(calendar->window, GTK_STATE_NORMAL, &mycolor2);
	  g_free (font_name);
	}
    }

  gtk_widget_destroy (calendar->font_dialog);
}

void calendar_select_font( GtkWidget    *button,
                           CalendarData *calendar )
{
  GtkWidget *window;

  if (!calendar->font_dialog) {
    window = gtk_font_selection_dialog_new ("Dialog Pilihan Huruf");
    g_return_if_fail(GTK_IS_FONT_SELECTION_DIALOG(window));
    calendar->font_dialog = window;
    
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);
    
    g_signal_connect (window, "destroy",
		      G_CALLBACK (gtk_widget_destroyed),
		      &calendar->font_dialog);
    
    g_signal_connect (GTK_FONT_SELECTION_DIALOG (window)->ok_button,
		      "clicked", G_CALLBACK (calendar_font_selection_ok),
		      calendar);
    g_signal_connect_swapped (GTK_FONT_SELECTION_DIALOG (window)->cancel_button,
			     "clicked", G_CALLBACK (gtk_widget_destroy), 
			     calendar->font_dialog);
  }
  window=calendar->font_dialog;
  if (!GTK_WIDGET_VISIBLE (window))
    gtk_widget_show (window);
  else
    gtk_widget_destroy (window);

}

void create_tanggalan_baik(VAL_LABEL dat_in, char logofile[MAX_STRING_LEN])
{
  GtkWidget *window;
  GtkWidget *vbox, *vbox2, *vbox3;
  GtkWidget *hbox;
  GtkWidget *hbbox;
  GtkWidget *calendar;
  GtkWidget *toggle;
  GtkWidget *button;
  GtkWidget *frame;
  GtkWidget *separator;
  GtkWidget *label;
  GtkWidget *bbox;
  static CalendarData calendar_data;
  gint i;
  GdkColor mycolor;
  GdkColor mycolor2;

  struct {
    char *label;
  } flags[] =
    {
      { "Titel Perubah Tanggalan" },
      { "Tampil Nama Hari" },
      { "Tanpa Perubah Tanggalan" }
    };

  
  calendar_data.window = NULL;
  calendar_data.font_dialog = NULL;

  for (i=0; i<3; i++) {
    calendar_data.settings[i]=0;
  }

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Tanggalan BAIK");

  if(strlen(logofile) > 3) {
    gtk_window_set_icon(GTK_WINDOW(window), win_create_pixbuf(logofile));
  }

  gtk_container_set_border_width (GTK_CONTAINER (window), 5);
  g_signal_connect (window, "destroy",
                   G_CALLBACK (gtk_widget_destroyed),
				   &window);

  g_signal_connect (window, "delete-event",
		    G_CALLBACK (gtk_false),
		    NULL);
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);

  vbox = gtk_vbox_new (FALSE, DEF_PAD);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  /*
   * The top part of the window, Calendar, flags and fontsel.
   */

  hbox = gtk_hbox_new(FALSE, DEF_PAD);
  gtk_box_pack_start (GTK_BOX(vbox), hbox, TRUE, TRUE, DEF_PAD);
  hbbox = gtk_hbutton_box_new();
  gtk_box_pack_start(GTK_BOX(hbox), hbbox, FALSE, FALSE, DEF_PAD);
  gtk_button_box_set_layout(GTK_BUTTON_BOX(hbbox), GTK_BUTTONBOX_SPREAD);
  gtk_box_set_spacing(GTK_BOX(hbbox), 5);

  /* Calendar widget */
  frame = gtk_frame_new("Tanggalan");
  gtk_box_pack_start(GTK_BOX(hbbox), frame, FALSE, TRUE, DEF_PAD);

  calendar=gtk_calendar_new();
  gdk_color_parse((gchar*) "aquamarine", &mycolor);
  gdk_color_parse((gchar*) "blue", &mycolor2);
  gtk_widget_modify_bg(calendar, GTK_STATE_NORMAL, &mycolor);
  gtk_widget_modify_fg(calendar, GTK_STATE_NORMAL, &mycolor2);

  calendar_data.window = calendar;
  calendar_set_flags(&calendar_data);
  // gtk_calendar_mark_day (GTK_CALENDAR (calendar), 19);	
  gtk_container_add (GTK_CONTAINER (frame), calendar);
  g_signal_connect (calendar, "month_changed", 
		    G_CALLBACK (calendar_month_changed),
		    &calendar_data);
  g_signal_connect (calendar, "day_selected", 
		    G_CALLBACK (calendar_day_selected),
		    &calendar_data);
  g_signal_connect (calendar, "prev_month", 
		    G_CALLBACK (calendar_prev_month),
		    &calendar_data);
  g_signal_connect (calendar, "next_month", 
		    G_CALLBACK (calendar_next_month),
		    &calendar_data);
  g_signal_connect (calendar, "prev_year", 
		    G_CALLBACK (calendar_prev_year),
		    &calendar_data);
  g_signal_connect (calendar, "next_year", 
		    G_CALLBACK (calendar_next_year),
		    &calendar_data);


  separator = gtk_vseparator_new ();
  gtk_box_pack_start (GTK_BOX (hbox), separator, FALSE, TRUE, 0);

  vbox2 = gtk_vbox_new(FALSE, DEF_PAD);
  gtk_box_pack_start(GTK_BOX(hbox), vbox2, FALSE, FALSE, DEF_PAD);
  
  /* Build the Right frame with the flags in */ 

  frame = gtk_frame_new("Opsi Tampilan");
  gtk_box_pack_start(GTK_BOX(vbox2), frame, TRUE, TRUE, DEF_PAD);
  vbox3 = gtk_vbox_new(TRUE, DEF_PAD_SMALL);
  gtk_container_add(GTK_CONTAINER(frame), vbox3);

  for (i = 0; i < 3; i++)
    {
      toggle = gtk_check_button_new_with_label(flags[i].label);
	  //if(i == 0) {
      //  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle), TRUE);     // 0th is selected by default
	  //  calendar_toggle_flag(GTK_WIDGET(toggle), &calendar_data);
	  //}
      g_signal_connect (toggle,
			"toggled",
			G_CALLBACK(calendar_toggle_flag),
			&calendar_data);
      gtk_box_pack_start (GTK_BOX (vbox3), toggle, TRUE, TRUE, 0);
      calendar_data.flag_checkboxes[i]=toggle;
    }

  /* Build the right font-button */ 
  button = gtk_button_new_with_label("Jenis Huruf...");
  g_signal_connect (button,
		    "clicked",
		    G_CALLBACK(calendar_select_font),
		    &calendar_data);
  gtk_box_pack_start (GTK_BOX (vbox2), button, FALSE, FALSE, 0);

  /*
   *  Build the Signal-event part.
   */


  frame = gtk_frame_new("Tanggal Terpilih");
  gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, DEF_PAD);

  vbox2 = gtk_vbox_new(TRUE, DEF_PAD_SMALL);
  gtk_container_add(GTK_CONTAINER(frame), vbox2);
  
  hbox = gtk_hbox_new (FALSE, 3);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox, FALSE, TRUE, 0);
  label = gtk_label_new ("");
  gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &mycolor2);
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, TRUE, 0);
  calendar_data.last_sig = gtk_label_new ("");
  gtk_widget_modify_fg(calendar_data.last_sig, GTK_STATE_NORMAL, &mycolor2);
  gtk_box_pack_start (GTK_BOX (hbox), calendar_data.last_sig, FALSE, TRUE, 0);

  // set target for GUI widget or string
  calendar_data.datx   = dat_in;

  bbox = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (vbox), bbox, FALSE, FALSE, 0);
  gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);

  button = gtk_button_new_with_label ("Tutup");
  g_signal_connect_swapped (button, "clicked", 
                   G_CALLBACK (gtk_widget_destroy),
				   window);

  gtk_container_add (GTK_CONTAINER (bbox), button);
  GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default (button);

  gtk_widget_show_all(window);

}


