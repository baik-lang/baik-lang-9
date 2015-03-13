// //////////////////////////////////////////////////////////////////////
// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2014
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// //////////////////////////////////////////////////////////////////////

// 2011/07/14

extern void BaikGarbageCollection(void);

gboolean win_delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
   return FALSE;
}

void win_destroy( GtkWidget *widget,
                     gpointer   data )
{
    // exit GTK
    gtk_main_quit ();

    BaikGarbageCollection();
    
    // clear source
    if(	pg.source  != NULL) {
      free (pg.source);
    }

    // exit main program
    exit(0);
}

GdkPixbuf *win_create_pixbuf(const gchar * filename)
{
   GdkPixbuf *pixbuf = NULL;
   GError    *error  = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if(!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

GtkWidget *png_label_box( GtkWidget *parent,
                              gchar     *filename,
                              gchar     *label_text )
{
        GtkWidget *box1  =NULL;
        GtkWidget *label =NULL;
        GtkWidget *gambar=NULL;
        GtkStyle  *style =NULL;

        /* Create box for png and label */
        box1 = gtk_hbox_new (FALSE, 0);
        gtk_container_set_border_width (GTK_CONTAINER (box1), 2);

        /* Get the style of the button to get the
         * background color. */
        style = gtk_widget_get_style(parent);

        /* Now on to the png stuff */
		gambar = gtk_image_new_from_file(filename);
        if(!gambar) {
          Error("gagal buka file gambar");
        }

        /* Create a label for the button */
        label = gtk_label_new (label_text);

        /* Pack the pixmap and label into the box */
        gtk_box_pack_start (GTK_BOX (box1),
                            gambar, FALSE, FALSE, 3);

        gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 3);

        gtk_widget_show(gambar);
        gtk_widget_show(label);

        return(box1);
}

// /////////////// General Popup Window - start
// Structure for Passing Data in GTK+ signal
typedef struct {
  char      *msg;
  char      *title;
  char      *logo;
} PopupData;

PopupData popupDat;

typedef struct {
  char      *name;
  char      *ver;
  char      *author;
  char      *comment;
  char      *www;
  char      *logo;
} AboutData;

AboutData aboutDat;

typedef struct {
  int    posSub;
  int    posSubBack;
  char   sub_name[MAX_STRING_LEN];
  char   param_source[MAX_STRING_LEN * 2];
  char   currentClass[MAX_STRING_LEN];
  
  VAL_LABEL valdat;
  VAL_LABEL tmpdat;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   dat_c[MAX_STRING_LEN];
} AksiFungsiData;

AksiFungsiData aksiDat;

typedef struct {
  int    posSub;
  int    posSubBack;
  char   sub_name[MAX_STRING_LEN];
  char   param_source[MAX_STRING_LEN * 2];
  char   currentClass[MAX_STRING_LEN];
  
  VAL_LABEL valdat;
  VAL_LABEL tmpdat;

  GtkWidget *widget;

} TimerData;

TimerData timerDat;



// //////////////////////////////////////

typedef struct 
{
  gchar *filename;
  gdouble font_size;

  gint lines_per_page;  
  gchar **lines;
  gint num_lines;
  gint num_pages;
} PrintData;

typedef struct
{
	GtkWidget *window, *chooser;
	PrintData *data;
} MyPrintWidget;

typedef struct {
  int    posSub;
  int    posSubBack;
  char   sub_name[MAX_STRING_LEN];
  char   param_source[MAX_STRING_LEN * 2];
  char   currentClass[MAX_STRING_LEN];
  
  VAL_LABEL valdat;
  VAL_LABEL tmpdat;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   dat_c[MAX_STRING_LEN];

  GtkWidget *window, *chooser;
  PrintData *data;

} AksiPrintData;

AksiPrintData printDat;

GtkPrintContext   *BAIK_Print_Context;
GtkPrintOperation *BAIK_Print_Operation;
int                BAIK_page_nr;


// ////////////////////////////////////////////////////////////////////
int Do_Detak_Waktu(TimerData *data) {

  TimerData *dat=NULL;
  int ret = 1; // TRUE

  dat = (TimerData *)malloc(sizeof(TimerData));

  if(data == NULL) {
    Error("Salah Do_Detak_Waktu\n");
  } else {
    //printf("----------- Do_Detak_Waktu \n");
	if(data->sub_name == NULL) {
		Error("salah : fungsi pada detak waktu NIL!");
	}

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;
	dat->tmpdat     = data->tmpdat;
	dat->valdat     = data->valdat;

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);
    // printf("inside SUB start : %d\n",dat->valdat.sub_pt_start);
    // printf("inside SUB end : %d\n",dat->valdat.sub_pt_end);

    // printf("start interprete sub params\n"); 

    memset(&tmp_source_lyr, '\0', sizeof(tmp_source_lyr));
    tmp_source_timer = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    InterpreterLyrParam(2, dat->posSub, dat->sub_name);

    pg.source = tmp_source_timer;
    pg.pt = dat->posSub;

    // printf("interpret sub param ok\n");

    pg.pt = dat->valdat.sub_pt_start;

    // throw out '{' symbol  
    getlex();

    // Interprete Timer SUB 
    ret = InterpreterTimerSub(dat->valdat.sub_pt_end, dat->sub_name);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
	tmp_source_timer = NULL;
  }

  return ret;

}


// ////////////////////////////////////////////////////////////////////

void Do_AksiFungsi(GtkWidget *widget, AksiFungsiData *data) {

  AksiFungsiData *dat=NULL;

  dat = (AksiFungsiData *)malloc(sizeof(AksiFungsiData));

  if(data == NULL) {
    printf("Salah Aksi_Fungsi\n");
  } else {
    // printf("----------- Aksi Fungsi \n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;
	dat->valdat     = data->valdat;

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);

	
    // printf("start interprete sub params\n"); 

    memset(&tmp_source_lyr, '\0', sizeof(tmp_source_lyr));
    tmp_source_lyr = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    //InterpreterParam(2, dat->posSub, dat->sub_name);
    InterpreterLyrParam(2, dat->posSub, dat->sub_name);

	//printf("++++++++++++++ interpret Lyr Param OK\n");

    pg.source = tmp_source_lyr;
    pg.pt = dat->posSub;

    // printf("interpret sub param ok\n");

    pg.pt = dat->valdat.sub_pt_start;

    // throw out '{' symbol  
    getlex();

    // Interprete SUB 
    InterpreterLyrSub(dat->valdat.sub_pt_end, dat->sub_name);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
  }

}


void Do_AksiBendaFungsi(GtkWidget *widget, AksiFungsiData *data) {

  AksiFungsiData *dat=NULL;

  dat = (AksiFungsiData *)malloc(sizeof(AksiFungsiData));

  if(data == NULL) {
    printf("Salah Aksi_Fungsi\n");
  } else {
    // printf("----------- Aksi Fungsi \n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;
	dat->valdat     = data->valdat;
	dat->tmpdat     = data->tmpdat;

	strcpy(dat->dat_a  , data->dat_a); // obj name
	strcpy(dat->dat_b  , data->dat_b); // obj function
	strcpy(dat->dat_c  , data->dat_c); // obj param

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);


    //printf("start interprete sub params\n");

    memset(&tmp_source_lyr, '\0', sizeof(tmp_source_lyr));
    tmp_source_lyr = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    // Interpreter(6, dat->posSub, dat->dat_a);
	InterpreterClassParam(2, dat->posSub, dat->dat_a);  // dat_a is Object Name

    // printf("interpret sub param ok\n");

    pg.source = tmp_source_lyr;
    //pg.pt = dat->posSub;

    /* printf("-----------\n");               */
    /* put pointer to function start point    */   
    pg.pt = dat->tmpdat.sub_pt_start;

    /* throw out '{' symbol                   */
    getlex();

    /* Interprete Class SUB                   */
    // pass class name
    InterpreterClassSub(dat->tmpdat.sub_pt_end, dat->dat_a);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
  }

}


void Do_AksiFungsiMouse(GtkWidget *widget, GdkEventButton *event, AksiFungsiData *data) {

  AksiFungsiData *dat=NULL;

  dat = (AksiFungsiData *)malloc(sizeof(AksiFungsiData));

  // printf("x %d y %d \n", (int)event->x , (int)event->y );
  MOUSE_POS_X  = (int)event->x;
  MOUSE_POS_Y  = (int)event->y;
  MOUSE_TIME   = (int)event->time;
  MOUSE_BUTTON = (int)event->button;

  if(data == NULL) {
    printf("Salah Aksi_Fungsi\n");
  } else {
    // printf("----------- Aksi Fungsi Mouse \n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;
	dat->valdat     = data->valdat;

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);

    // printf("start interprete sub params\n"); 

    memset(&tmp_source_lyr, '\0', sizeof(tmp_source_lyr));
    tmp_source_lyr = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    //InterpreterParam(2, dat->posSub, dat->sub_name);
    InterpreterLyrParam(2, dat->posSub, dat->sub_name);

    // printf("interprete param ok\n");

    pg.source = tmp_source_lyr;
    pg.pt = dat->posSub;

    // printf("interpret sub param ok\n");

    pg.pt = dat->valdat.sub_pt_start;

    // throw out '{' symbol  
    getlex();

    // Interprete SUB 
    InterpreterLyrSub(dat->valdat.sub_pt_end, dat->sub_name);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
  }

}


gboolean Do_AksiFungsiTreeMouse(GtkWidget *widget, GdkEventButton *event, AksiFungsiData *data) {

  AksiFungsiData *dat=NULL;

  // only handle right click :)
  if (event->type == GDK_BUTTON_PRESS && event->button == 3)
  {

    dat = (AksiFungsiData *)malloc(sizeof(AksiFungsiData));

    // printf("x %d y %d \n", (int)event->x , (int)event->y );
    MOUSE_POS_X  = (int)event->x;
    MOUSE_POS_Y  = (int)event->y;
    MOUSE_TIME   = (int)event->time;
    MOUSE_BUTTON = (int)event->button;

    if(data == NULL) {
      printf("Salah Aksi_Fungsi\n");
    } else {
      // printf("----------- Aksi Fungsi Tree Mouse \n");

	  strcpy(dat->sub_name     , data->sub_name);
	  strcpy(dat->param_source , data->param_source);
	  strcpy(dat->currentClass , data->currentClass);
	  dat->posSub     = data->posSub;
	  dat->posSubBack = data->posSubBack;
	  dat->valdat     = data->valdat;

	  // printf("do sub_name: %s\n", data->sub_name);
	  // printf("do param_source: %s\n", data->param_source);
	  // printf("do currentClass: %s\n", data->currentClass);
	  // printf("do posSub: %d\n", data->posSub);
	  // printf("do posSubBack: %d\n", data->posSubBack);

      // printf("start interprete sub params\n"); 

      memset(&tmp_source_lyr, '\0', sizeof(tmp_source_lyr));
      tmp_source_lyr = pg.source;
        
      pg.source = dat->param_source;
      pg.pt = 0;

      //InterpreterParam(2, dat->posSub, dat->sub_name);
      InterpreterLyrParam(2, dat->posSub, dat->sub_name);

      // printf("interprete param ok\n");

      pg.source = tmp_source_lyr;
      pg.pt = dat->posSub;

      // printf("interpret sub param ok\n");

      pg.pt = dat->valdat.sub_pt_start;

      // throw out '{' symbol  
      getlex();

      // Interprete SUB 
      InterpreterLyrSub(dat->valdat.sub_pt_end, dat->sub_name);

      // printf("interpret sub OK\n");

    }

    if(dat != NULL) {
      free ( dat );
    }

    return TRUE; /* we handled this */
  }

  return FALSE; /* we did not handle this */

}



void Do_AksiBendaFungsiMouse(GtkWidget *widget, GdkEventButton *event, AksiFungsiData *data) {

  AksiFungsiData *dat=NULL;

  dat = (AksiFungsiData *)malloc(sizeof(AksiFungsiData));

  MOUSE_POS_X  = (int)event->x;
  MOUSE_POS_Y  = (int)event->y;
  MOUSE_TIME   = (int)event->time;
  MOUSE_BUTTON = (int)event->button;

  if(data == NULL) {
    printf("Salah Aksi_Fungsi\n");
  } else {
    // printf("----------- Aksi Fungsi \n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;
	dat->valdat     = data->valdat;
	dat->tmpdat     = data->tmpdat;

	strcpy(dat->dat_a  , data->dat_a); // obj name
	strcpy(dat->dat_b  , data->dat_b); // obj function
	strcpy(dat->dat_c  , data->dat_c); // obj param

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);


    //printf("start interprete sub params\n");

    memset(&tmp_source, '\0', sizeof(tmp_source));
    tmp_source = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    // Interpreter(6, dat->posSub, dat->dat_a);
	InterpreterClassParam(2, dat->posSub, dat->dat_a);  // dat_a is Object Name

    // printf("interpret sub param ok\n");

    pg.source = tmp_source;
    //pg.pt = dat->posSub;

    /* printf("-----------\n");               */
    /* put pointer to function start point    */   
    pg.pt = dat->tmpdat.sub_pt_start;

    /* throw out '{' symbol                   */
    getlex();

    /* Interprete Class SUB                   */
    // pass class name
    InterpreterClassSub(dat->tmpdat.sub_pt_end, dat->dat_a);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
  }

}



void Do_AksiFungsiKeyboard(GtkWidget *widget, GdkEventKey *event, AksiFungsiData *data) {

  AksiFungsiData *dat=NULL;

  dat = (AksiFungsiData *)malloc(sizeof(AksiFungsiData));

  KEYBOARD_VALUE = (int)event->keyval;
  KEYBOARD_STATE = (int)event->state;
  KEYBOARD_STRING = NULL;
  KEYBOARD_STRING = (char *)malloc(sizeof (char *));
  KEYBOARD_STRING = event->string;

  if(data == NULL) {
    printf("Salah Aksi_Fungsi\n");
  } else {
    // printf("----------- Aksi Fungsi \n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;
	dat->valdat     = data->valdat;

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);

    // printf("start interprete sub params\n"); 

    memset(&tmp_source_lyr, '\0', sizeof(tmp_source_lyr));
    tmp_source_lyr = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    //InterpreterParam(2, dat->posSub, dat->sub_name);
    InterpreterLyrParam(2, dat->posSub, dat->sub_name);

    // printf("interprete param ok\n");

    pg.source = tmp_source_lyr;
    pg.pt = dat->posSub;

    // printf("interpret sub param ok\n");

    pg.pt = dat->valdat.sub_pt_start;

    // throw out '{' symbol  
    getlex();

    // Interprete SUB 
    InterpreterLyrSub(dat->valdat.sub_pt_end, dat->sub_name);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
  }

}

// ///////////////////////////////////////////////////////////////////////////////////
// Aksi Fungsi Ekspos
// ///////////////////////////////////////////////////////////////////////////////////
void Do_AksiFungsiEkspos(GtkWidget *widget, GdkEventExpose *event, AksiFungsiData *data) {

  AksiFungsiData *dat=NULL;

  EKSPOS_POS_X  = (int)event->area.x;
  EKSPOS_POS_Y  = (int)event->area.y;
  EKSPOS_WIDTH  = (int)event->area.width;
  EKSPOS_HEIGHT = (int)event->area.height;

  dat = (AksiFungsiData *)malloc(sizeof(AksiFungsiData));

  if(data == NULL) {
    printf("Salah Aksi_FungsiEkspos\n");
  } else {
    // printf("----------- Aksi Fungsi Ekspos\n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;
	dat->valdat     = data->valdat;

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);

    // printf("start interprete sub params\n"); 

    memset(&tmp_source_lyr_gmb, '\0', sizeof(tmp_source_lyr_gmb));
    tmp_source_lyr_gmb = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    //InterpreterParam(2, dat->posSub, dat->sub_name);
    InterpreterLyrParam(2, dat->posSub, dat->sub_name);

    // printf("interprete param ok\n");

    pg.source = tmp_source_lyr_gmb;
    pg.pt = dat->posSub;

    // printf("interpret sub param ok\n");

    pg.pt = dat->valdat.sub_pt_start;

    // throw out '{' symbol  
    getlex();

    // Interprete SUB 
    InterpreterLyrSub(dat->valdat.sub_pt_end, dat->sub_name);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
	tmp_source_lyr_gmb = NULL;
  }

}

// ///////////////////////////////////////////////////////////////////////////////////
// Aksi Fungsi Atur / Configure
// ///////////////////////////////////////////////////////////////////////////////////
void Do_AksiFungsiAtur(GtkWidget *widget, GdkEventConfigure *event, AksiFungsiData *data) {

  AksiFungsiData *dat=NULL;

  dat = (AksiFungsiData *)malloc(sizeof(AksiFungsiData));

  if(data == NULL) {
    printf("Salah Aksi_FungsiAtur\n");
  } else {
    // printf("----------- Aksi Fungsi Atur\n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;
	dat->valdat     = data->valdat;

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);

    // printf("start interprete sub params\n"); 

    memset(&tmp_source_lyr_gmb, '\0', sizeof(tmp_source_lyr_gmb));
    tmp_source_lyr_gmb = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    //InterpreterParam(2, dat->posSub, dat->sub_name);
    InterpreterLyrParam(2, dat->posSub, dat->sub_name);

    // printf("interprete param ok\n");

    pg.source = tmp_source_lyr_gmb;
    pg.pt = dat->posSub;

    // printf("interpret sub param ok\n");

    pg.pt = dat->valdat.sub_pt_start;

    // throw out '{' symbol  
    getlex();

    // Interprete SUB 
    InterpreterLyrSub(dat->valdat.sub_pt_end, dat->sub_name);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
  }

}

void Do_AksiBendaFungsiKeyboard(GtkWidget *widget, GdkEventKey *event, AksiFungsiData *data) {

  AksiFungsiData *dat=NULL;

  dat = (AksiFungsiData *)malloc(sizeof(AksiFungsiData));

  KEYBOARD_VALUE = (int)event->keyval;
  KEYBOARD_STATE = (int)event->state;
  KEYBOARD_STRING = NULL;
  KEYBOARD_STRING = (char *)malloc(sizeof (char *));
  KEYBOARD_STRING = event->string;

  if(data == NULL) {
    printf("Salah Aksi_Fungsi\n");
  } else {
    // printf("----------- Aksi Fungsi \n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;
	dat->valdat     = data->valdat;
	dat->tmpdat     = data->tmpdat;

	strcpy(dat->dat_a  , data->dat_a); // obj name
	strcpy(dat->dat_b  , data->dat_b); // obj function
	strcpy(dat->dat_c  , data->dat_c); // obj param

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);


    //printf("start interprete sub params\n");

    memset(&tmp_source, '\0', sizeof(tmp_source));
    tmp_source = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    // Interpreter(6, dat->posSub, dat->dat_a);
	InterpreterClassParam(2, dat->posSub, dat->dat_a);  // dat_a is Object Name

    // printf("interpret sub param ok\n");

    pg.source = tmp_source;
    //pg.pt = dat->posSub;

    /* printf("-----------\n");               */
    /* put pointer to function start point    */   
    pg.pt = dat->tmpdat.sub_pt_start;

    /* throw out '{' symbol                   */
    getlex();

    /* Interprete Class SUB                   */
    // pass class name
    InterpreterClassSub(dat->tmpdat.sub_pt_end, dat->dat_a);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
  }

}

void win_rambu_info(GtkWidget *widget, gpointer data)
{
  GtkWidget *window=NULL;
  GtkWidget *dialog=NULL;
  PopupData *dat=NULL;

  int isMalloc = 0;

  //memset(&dat, '\0', sizeof(dat));
  if(data != NULL) {
    //printf("- get data from Object\n");
    dat = gtk_object_get_data(GTK_OBJECT(data), "lbl_aksi_info");
  } else {
    //printf("- get data from Global\n");
	dat = (PopupData *)malloc(sizeof(PopupData));
	isMalloc = 1;
	dat->title = popupDat.title;
	dat->msg = popupDat.msg;
    if(popupDat.logo != NULL && strlen(popupDat.logo) > 3) {
	  dat->logo = popupDat.logo;
	} else
      dat->logo = NULL;
  }

  //printf("inside win_rambu_info\n");
  //printf("title %s\n", dat->title);
  //printf("msg %s\n", dat->msg);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  if(dat->logo != NULL && strlen(dat->logo) > 3) {
    gtk_window_set_icon(GTK_WINDOW(window), win_create_pixbuf(dat->logo));
  }

  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
			dat->msg, "Info");
  gtk_window_set_title(GTK_WINDOW(dialog), dat->title);
  gtk_dialog_run(GTK_DIALOG(dialog));

  if(isMalloc == 1 && dat != NULL) {
    free(dat);
  }

  gtk_widget_destroy(dialog);
  gtk_widget_destroy(window);
}

void win_rambu_error(GtkWidget *widget, gpointer data)
{
  GtkWidget *window=NULL;
  GtkWidget *dialog=NULL;
  PopupData *dat=NULL;

  int isMalloc = 0;

  //memset(&dat, '\0', sizeof(dat));
  if(data != NULL) {
    //printf("- get data from Object\n");
    dat = gtk_object_get_data(GTK_OBJECT(data), "lbl_aksi_error");
  } else {
    //printf("- get data from Global\n");
	dat = (PopupData *)malloc(sizeof(PopupData));
	isMalloc = 1;
	dat->title = popupDat.title;
	dat->msg = popupDat.msg;
    if(popupDat.logo != NULL && strlen(popupDat.logo) > 3) {
	  dat->logo = popupDat.logo;
	} else
      dat->logo = NULL;
  }

  //printf("inside win_rambu_error\n");
  //printf("title %s\n", dat->title);
  //printf("msg %s\n", dat->msg);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  if(dat->logo != NULL && strlen(dat->logo) > 3) {
    gtk_window_set_icon(GTK_WINDOW(window), win_create_pixbuf(dat->logo));
  }

  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "%s",dat->msg);
  gtk_window_set_title(GTK_WINDOW(dialog), dat->title);
  gtk_dialog_run(GTK_DIALOG(dialog));

  if(isMalloc == 1 && dat != NULL) {
    free(dat);
  }

  gtk_widget_destroy(dialog);
  gtk_widget_destroy(window);
}

void win_rambu_question(GtkWidget *widget, gpointer data)
{
  GtkWidget *window=NULL;
  GtkWidget *dialog=NULL;

  GtkResponseType result;
  PopupData dat;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  dat = *(PopupData *)data;

  if(dat.logo != NULL) {
    gtk_window_set_icon(GTK_WINDOW(window), win_create_pixbuf(dat.logo));
  }

  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            "%s",dat.msg);
  gtk_window_set_title(GTK_WINDOW(dialog), dat.title);

  result = gtk_dialog_run(GTK_DIALOG(dialog));

  if (result == GTK_RESPONSE_YES)
  {
     printf("YES clicked\n");
  } else if(result == GTK_RESPONSE_NO) {
     printf("NO clicked\n");
  } 

  gtk_widget_destroy(dialog);
}

void win_rambu_warning(GtkWidget *widget, gpointer data)
{
  GtkWidget *window=NULL;
  GtkWidget *dialog=NULL;
  PopupData *dat=NULL;

  int isMalloc = 0;

  //memset(&dat, '\0', sizeof(dat));
  if(data != NULL) {
    //printf("- get data from Object\n");
    dat = gtk_object_get_data(GTK_OBJECT(data), "lbl_aksi_warn");
  } else {
    //printf("- get data from Global\n");
	dat = (PopupData *)malloc(sizeof(PopupData));
	isMalloc = 1;
	dat->title = popupDat.title;
	dat->msg = popupDat.msg;
    if(popupDat.logo != NULL && strlen(popupDat.logo) > 3) {
	  dat->logo = popupDat.logo;
	} else
      dat->logo = NULL;
  }

  //printf("inside win_rambu_warning\n");
  //printf("title %s\n", dat->title);
  //printf("msg %s\n", dat->msg);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  if(dat->logo != NULL && strlen(dat->logo) > 3) {
    gtk_window_set_icon(GTK_WINDOW(window), win_create_pixbuf(dat->logo));
  }


  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "%s",dat->msg);
  gtk_window_set_title(GTK_WINDOW(dialog), dat->title);
  gtk_dialog_run(GTK_DIALOG(dialog));

  if(isMalloc == 1 && dat != NULL) {
    free(dat);
  }

  gtk_widget_destroy(dialog);
  gtk_widget_destroy(window);
}

// /////////////// General Popup Window - end

void win_lencana_jatidiri(GtkWidget *widget, AboutData *data)
{
  GtkWidget      *dialog=NULL;
  GtkAboutDialog *about=NULL;
  AboutData      *dat=NULL;

  //memset(&dat, '\0', sizeof(dat));
  if(data != NULL) {
    // printf("- get data from Object\n");
	dat = (AboutData *)malloc(sizeof(AboutData));
	dat->name    = data->name;
	dat->ver     = data->ver;
	dat->author  = data->author;
	dat->comment = data->comment;
	dat->www     = data->www;
	dat->logo    = data->logo;

  } else {
    Error("Salah parameter untuk aksi_jatidiri\n");
  }

  // printf("inside jatidiri\n");
  // printf("name %s\n", dat->name);
  // printf("ver %s\n", dat->ver);

  dialog = gtk_about_dialog_new();
  about  = GTK_ABOUT_DIALOG(dialog);

  gtk_about_dialog_set_name(about,    dat->name);
  gtk_about_dialog_set_version(about, dat->ver);
  gtk_about_dialog_set_copyright(about, dat->author);
  gtk_about_dialog_set_comments(about, dat->comment);
  gtk_about_dialog_set_website(about,  dat->www);

  if(dat->logo != NULL && strlen(dat->logo) > 3) {
    gtk_window_set_icon(GTK_WINDOW(dialog), win_create_pixbuf(dat->logo));
    gtk_about_dialog_set_logo(about, win_create_pixbuf(dat->logo) );
  }

  if(dat != NULL) {
    free(dat);
  }

  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);

}



// /////////////////////////////////////////////////////////////////////////////////

static void Do_AksiSiapPrint (GtkPrintOperation *operation, 
	                          GtkPrintContext   *context,
	                          AksiPrintData *data)
{

  AksiPrintData *dat=NULL;

  dat = (AksiPrintData *)malloc(sizeof(AksiPrintData));

  BAIK_Print_Context = NULL;
  BAIK_Print_Operation = NULL;

  if(data == NULL) {
    printf("Salah Aksi_SiapCetak\n");
  } else {
    // printf("----------- Aksi Siap Cetak \n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;

	dat->valdat     = data->valdat;
    dat->valdat.sub_pt_end = data->valdat.sub_pt_end;

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);

	// set context
	// printf("set BAIK_Print_Context ...\n"); 
	BAIK_Print_Context = context;
	// printf("set BAIK_Print_Operation ...\n"); 
	BAIK_Print_Operation = operation;

    memset(&tmp_source_lyr, '\0', sizeof(tmp_source_lyr));
    tmp_source_lyr = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    //InterpreterParam(2, dat->posSub, dat->sub_name);
    InterpreterLyrParam(2, dat->posSub, dat->sub_name);

    pg.source = tmp_source_lyr;
    pg.pt = dat->posSub;

    // printf("interpret sub param ok\n");

    pg.pt = dat->valdat.sub_pt_start;

    // throw out '{' symbol  
    getlex();

    // Interprete SUB 
    InterpreterLyrSub(dat->valdat.sub_pt_end, dat->sub_name);

    // printf("interpret sub OK\n");

	// reset context
	// printf("return BAIK_Print_Context ...\n"); 
	context = BAIK_Print_Context;
	// printf("return BAIK_Print_Operation ...\n"); 
	operation = BAIK_Print_Operation;

  }

  if(dat != NULL) {
    free ( dat );
  }

}



gboolean Do_AksiPrintTeks (GtkPrintOperation *operation, 
	                          GtkPrintContext   *context,
                              int                page_nr,
	                          AksiPrintData *data)
{

  AksiPrintData *dat=NULL;

  dat = (AksiPrintData *)malloc(sizeof(AksiPrintData));

  BAIK_page_nr = page_nr;
  // printf("page_nr %d \n", page_nr);

  if(data == NULL) {
    printf("Salah Aksi_CetakTeks\n");

  } else {
    // printf("----------- Aksi Cetak Teks \n");

	strcpy(dat->sub_name     , data->sub_name);
	strcpy(dat->param_source , data->param_source);
	strcpy(dat->currentClass , data->currentClass);
	dat->posSub     = data->posSub;
	dat->posSubBack = data->posSubBack;

	dat->valdat     = data->valdat;
    dat->valdat.sub_pt_end = data->valdat.sub_pt_end;

	// printf("do sub_name: %s\n", data->sub_name);
	// printf("do param_source: %s\n", data->param_source);
	// printf("do currentClass: %s\n", data->currentClass);
	// printf("do posSub: %d\n", data->posSub);
	// printf("do posSubBack: %d\n", data->posSubBack);
	// printf("do sub_pt_end: %d\n", dat->valdat.sub_pt_end);

	// set context
	// printf("set BAIK_Print_Context ...\n"); 
	BAIK_Print_Context = context;

    memset(&tmp_source_lyr, '\0', sizeof(tmp_source_lyr));
    tmp_source_lyr = pg.source;
        
    pg.source = dat->param_source;
    pg.pt = 0;

    //InterpreterParam(2, dat->posSub, dat->sub_name);
    InterpreterLyrParam(2, dat->posSub, dat->sub_name);

    pg.source = tmp_source_lyr;
    pg.pt = dat->posSub;

    // printf("interpret sub param ok\n");

    pg.pt = dat->valdat.sub_pt_start;

    // throw out '{' symbol  
    getlex();

    // Interprete SUB 
    InterpreterLyrSub(dat->valdat.sub_pt_end, dat->sub_name);

    // printf("interpret sub OK\n");

  }

  if(dat != NULL) {
    free ( dat );
  }

  return FALSE;

}