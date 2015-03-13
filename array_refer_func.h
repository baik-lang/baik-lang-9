// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


// ////////////////////////////////////////////////////////////////
int get_int_array(VAL_LABEL valdat, long idx) {
  int ret = '\0';
  int myrenban = 0;
  
  // get valdat current stackid
  memset(&TmpIntBox.var.array_name, '\0', sizeof(TmpIntBox.var.array_name));
  strcpy(TmpIntBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_i;
  // printf("\n get renban %d\n", renban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpIntBox.val.stackid = myrenban;
    TmpIntBox.val.idx = idx;

    // get current int value
    intarryPos = int_findData(TmpIntBox.val);
    if(intarryPos < 0) {
      // printf("nilai untaian tidak ditemukan\n");
	  ret = '\r'; // for NULL
    } else {
      TmpIntBox.val = int_getElement(intarryPos);

      // get value
      ret = TmpIntBox.val.myint; 
      // int_push(TmpIntBox.val);
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 6;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

  return ret;
}

void del_int_array(VAL_LABEL valdat, long idx) {
  int ret = '\0';
  int myrenban = 0;
  
  // get valdat current stackid
  memset(&TmpIntBox.var.array_name, '\0', sizeof(TmpIntBox.var.array_name));
  strcpy(TmpIntBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_i;
  // printf("\n get renban %d\n", renban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpIntBox.val.stackid = myrenban;
    TmpIntBox.val.idx = idx;

    // get current int value
    intarryPos = int_findData(TmpIntBox.val);
    if(intarryPos < 0) {
      // printf("nilai untaian tidak ditemukan\n");
	  ret = '\r'; // for NULL
    } else {
	  // remove at pos
	  // printf("===del array int\n");
	  // int_printData();
      int_removeAt(intarryPos);
	  // int_printData();
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 6;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

}

void save_int_array(VAL_LABEL valdat, long idx, int val) {
  int ret = '\0';
  int myrenban = 0;
  
  // get valdat current stackid
  memset(&TmpIntBox.var.array_name, '\0', sizeof(TmpIntBox.var.array_name));
  strcpy(TmpIntBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_i;
  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpIntBox.val.stackid = myrenban;
    TmpIntBox.val.idx = idx;

    // get current int value
    intarryPos = int_findData(TmpIntBox.val);
    if(intarryPos < 0) {
	  // printf(" %s idx %d , new value: %d\n", valdat.array_name, idx, val);
      // set value
      TmpIntBox.val.myint = val; 
      int_addFirst(TmpIntBox.val);
    } else {
      // printf(" %s idx %d , value ALREADY inside\n", valdat.array_name, idx);
      TmpIntBox.val = int_getElement(intarryPos);
      // set value
      TmpIntBox.val.myint = val; 
      int_addFirst(TmpIntBox.val);
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 6;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

}

// ////////////////////////////////////////////////////////////////
double get_dbl_array(VAL_LABEL valdat, long idx) {
  double ret = '\0';
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpDblBox.var.array_name, '\0', sizeof(TmpDblBox.var.array_name));
  strcpy(TmpDblBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_d;
  // printf("\n get renban %d\n", renban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpDblBox.dbl.stackid = myrenban;
    TmpDblBox.dbl.idx = idx;

    // get current int value
    dblarryPos = dbl_findData(TmpDblBox.dbl);
    if(dblarryPos < 0) {
      // printf("nilai untaian tidak ditemukan\n");
	  ret = '\r'; // for NULL
    } else {
      TmpDblBox.dbl = dbl_getElement(dblarryPos);

      // get value
      ret = TmpDblBox.dbl.mydbl; 
      // int_push(TmpIntBox.val);
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 7;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

  return ret;
}

void del_dbl_array(VAL_LABEL valdat, long idx) {
  double ret = '\0';
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpDblBox.var.array_name, '\0', sizeof(TmpDblBox.var.array_name));
  strcpy(TmpDblBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_d;
  // printf("\n get renban %d\n", renban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpDblBox.dbl.stackid = myrenban;
    TmpDblBox.dbl.idx = idx;

    // get current int value
    dblarryPos = dbl_findData(TmpDblBox.dbl);
    if(dblarryPos < 0) {
      // printf("nilai untaian tidak ditemukan\n");
	  ret = '\r'; // for NULL
    } else {
	  // remove at pos
	  //printf("del array dbl\n");
	  //dbl_printData();
      dbl_removeAt(dblarryPos);
	  //dbl_printData();
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 7;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));
}

void save_dbl_array(VAL_LABEL valdat, long idx, double dbl) {
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpDblBox.var.array_name, '\0', sizeof(TmpDblBox.var.array_name));
  strcpy(TmpDblBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_d;
  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpDblBox.dbl.stackid = myrenban;
    TmpDblBox.dbl.idx = idx;

    // get current int value
    dblarryPos = dbl_findData(TmpDblBox.dbl);
    if(dblarryPos < 0) {
	  // printf(" %s idx %d , new value: %f\n", valdat.array_name, idx, dbl);
      // set value
      TmpDblBox.dbl.mydbl = dbl; 
      dbl_addFirst(TmpDblBox.dbl);
    } else {
      // printf(" %s idx %d , value ALREADY inside\n", valdat.array_name, idx);
      TmpDblBox.dbl = dbl_getElement(dblarryPos);
      // set value
      TmpDblBox.dbl.mydbl = dbl; 
      dbl_addFirst(TmpDblBox.dbl);
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 7;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

}



// //////////////////////////////////////////////////////////////////////
int get_str_array(VAL_LABEL valdat, long idx, char retVal[MAX_STRING_LEN * 2]) {
  int ret = '\0';
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
  strcpy(TmpStrBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_s;
  // printf("\n get renban %d\n", renban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpStrBox.str.stackid = myrenban;
    TmpStrBox.str.idx = idx;

    // get current str value
    strarryPos = string_findData(TmpStrBox.str);
    if(strarryPos < 0) {
      // printf("nilai untaian tidak ditemukan\n");
	  ret = 0; // for not found
    } else {
      TmpStrBox.str = string_getElement(strarryPos);
	  // printf("get str value : %s\n", TmpStrBox.str.mystring);

      // get value
      strcpy(retVal, TmpStrBox.str.mystring); 
	  // printf("nilai : %s\n", retVal);
	  ret = 1; // for found
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 8;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

  return ret;
}

void del_str_array(VAL_LABEL valdat, long idx) {
  int ret = '\0';
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
  strcpy(TmpStrBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_s;
  // printf("\n get renban %d\n", renban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpStrBox.str.stackid = myrenban;
    TmpStrBox.str.idx = idx;

    // get current str value
    strarryPos = string_findData(TmpStrBox.str);
    if(strarryPos < 0) {
      // printf("nilai untaian tidak ditemukan\n");
    } else {
	  // remove at pos
	  // printf("del array str\n");
	  // string_printData();
      string_removeAt(strarryPos);
	  // string_printData();
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 8;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

}

void save_str_array(VAL_LABEL valdat, long idx, char entryVal[MAX_STRING_LEN]) {
  int ret = '\0';
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
  strcpy(TmpStrBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_s;
  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpStrBox.str.stackid = myrenban;
    TmpStrBox.str.idx = idx;

    // get current int value
    strarryPos = string_findData(TmpStrBox.str);
    if(strarryPos < 0) {
	  // printf(" %s idx %d , new value: %s\n", valdat.array_name, idx, entryVal);
      // set value
      strcpy(TmpStrBox.str.mystring , entryVal); 
      string_addFirst(TmpStrBox.str);
    } else {
      // printf(" %s idx %d , value ALREADY inside\n", valdat.array_name, idx);
      TmpStrBox.str = string_getElement(strarryPos);
      // set value
      strcpy(TmpStrBox.str.mystring , entryVal); 
      string_addFirst(TmpStrBox.str);
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 8;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

}



// ////////////////////////////////////////////////////////////////
#ifdef USE_GTK2
// ////////////////////////////////////////////////////////////////
GtkWidget *get_gui_array(VAL_LABEL valdat, long idx) {
  GtkWidget *ret = '\0';
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
  memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
  strcpy(TmpGuiBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_widget;
  // printf("\n get renban %d\n", renban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpGuiBox.val.stackid = myrenban;
    TmpGuiBox.val.idx = idx;

    // get current int value
    guiarryPos = gui_findData(TmpGuiBox.val);
    if(guiarryPos < 0) {
      // printf("nilai untaian tidak ditemukan\n");
	  ret = '\0'; // for NULL
    } else {
      TmpGuiBox.val = gui_getElement(guiarryPos);

      // get value
	  ret = TmpGuiBox.val.mywidget; 
      // int_push(TmpIntBox.val);
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 60;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

  return ret;
}

GtkWidget *get_eventbox_array(VAL_LABEL valdat, long idx) {
  GtkWidget *ret = '\0';
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
  memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
  strcpy(TmpGuiBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_widget;
  // printf("\n get renban %d\n", renban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpGuiBox.val.stackid = myrenban;
    TmpGuiBox.val.idx = idx;

    // get current int value
    guiarryPos = gui_findData(TmpGuiBox.val);
    if(guiarryPos < 0) {
      // printf("nilai untaian tidak ditemukan\n");
	  ret = '\0'; // for NULL
    } else {
      TmpGuiBox.val = gui_getElement(guiarryPos);

      // get value
	  ret = TmpGuiBox.val.eventbox; 
      // int_push(TmpIntBox.val);
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 60;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

  return ret;
}

int get_guitype_array(VAL_LABEL valdat, long idx) {
  int ret = '\0';
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
  memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
  strcpy(TmpGuiBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_widget;
  // printf("\nname %s get guitype, renban %d\n", valdat.array_name, myrenban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpGuiBox.val.stackid = myrenban;
    TmpGuiBox.val.idx = idx;

    // get current int value
    guiarryPos = gui_findData(TmpGuiBox.val);
    if(guiarryPos < 0) {
      // printf("nilai untaian tidak ditemukan\n");
	  ret = '\0'; // for NULL
    } else {
      TmpGuiBox.val = gui_getElement(guiarryPos);

      // get value
      ret = TmpGuiBox.val.GUItype;
      
      // printf("got GUItype %d \n", ret);
      // int_push(TmpIntBox.val);
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 60;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

  return ret;
}

void del_gui_array(VAL_LABEL valdat, long idx) {
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
  memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
  strcpy(TmpGuiBox.var.array_name, valdat.array_name);
  myrenban = valdat.array_widget;
  // printf("\n get renban %d\n", renban);

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpGuiBox.val.stackid = myrenban;
    TmpGuiBox.val.idx = idx;

    // get current int value
    guiarryPos = gui_findData(TmpGuiBox.val);
    if(guiarryPos < 0) {
      printf("nilai untaian tidak ditemukan\n");
    } else {
	  // remove at pos
	  // printf("===del array int\n");
	  // int_printData();
      gui_removeAt(guiarryPos);
	  // int_printData();
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 60;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

}

void save_gui_array(VAL_LABEL valdat, long idx, GtkWidget *widget, GtkWidget *eventbox, int GUItype) {
  int myrenban = 0;

  // get valdat current stackid
  memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
  memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
  strcpy(TmpGuiBox.var.array_name, valdat.array_name);

  myrenban = valdat.array_widget;

  if(myrenban < 0) {
    printf("variabel untaian tidak ditemukan\n");
  } else {
    TmpGuiBox.val.stackid = myrenban;
    TmpGuiBox.val.idx = idx;

    // get current int value
    guiarryPos = gui_findData(TmpGuiBox.val);
    if(guiarryPos < 0) {
      // printf(" found %s idx %d \n", valdat.array_name, idx);
      // set value
	  TmpGuiBox.val.mywidget = widget; 
	  TmpGuiBox.val.eventbox = eventbox; 
	  TmpGuiBox.val.GUItype  = GUItype; 

      gui_addFirst(TmpGuiBox.val);
    } else {
      // printf(" %s idx %d , value ALREADY inside\n", valdat.array_name, idx);
      TmpGuiBox.val = gui_getElement(guiarryPos);
      // set value
      TmpGuiBox.val.mywidget = widget; 
	  TmpGuiBox.val.eventbox = eventbox; 
	  TmpGuiBox.val.GUItype  = GUItype; 

      gui_addFirst(TmpGuiBox.val);
    }
  }
  // nothing changed with current datatype
  valdat.datatype = 60;

  // clear memory
  memset(&valdat, '\0', sizeof(valdat));

}

// ////////////////////////////////////////////////////////////////
#endif







// ////////////////////////////////////////////////////////////////
#ifdef USE_GTK3
// ////////////////////////////////////////////////////////////////
GtkWidget *get_gui_array(VAL_LABEL valdat, long idx) {
	GtkWidget *ret = '\0';
	int myrenban = 0;

	// get valdat current stackid
	memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
	memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
	strcpy(TmpGuiBox.var.array_name, valdat.array_name);
	myrenban = valdat.array_widget;
	// printf("\n get renban %d\n", renban);

	if (myrenban < 0) {
		printf("variabel untaian tidak ditemukan\n");
	}
	else {
		TmpGuiBox.val.stackid = myrenban;
		TmpGuiBox.val.idx = idx;

		// get current int value
		guiarryPos = gui_findData(TmpGuiBox.val);
		if (guiarryPos < 0) {
			// printf("nilai untaian tidak ditemukan\n");
			ret = '\0'; // for NULL
		}
		else {
			TmpGuiBox.val = gui_getElement(guiarryPos);

			// get value
			ret = TmpGuiBox.val.mywidget;
			// int_push(TmpIntBox.val);
		}
	}
	// nothing changed with current datatype
	valdat.datatype = 60;

	// clear memory
	memset(&valdat, '\0', sizeof(valdat));

	return ret;
}

GtkWidget *get_eventbox_array(VAL_LABEL valdat, long idx) {
	GtkWidget *ret = '\0';
	int myrenban = 0;

	// get valdat current stackid
	memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
	memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
	strcpy(TmpGuiBox.var.array_name, valdat.array_name);
	myrenban = valdat.array_widget;
	// printf("\n get renban %d\n", renban);

	if (myrenban < 0) {
		printf("variabel untaian tidak ditemukan\n");
	}
	else {
		TmpGuiBox.val.stackid = myrenban;
		TmpGuiBox.val.idx = idx;

		// get current int value
		guiarryPos = gui_findData(TmpGuiBox.val);
		if (guiarryPos < 0) {
			// printf("nilai untaian tidak ditemukan\n");
			ret = '\0'; // for NULL
		}
		else {
			TmpGuiBox.val = gui_getElement(guiarryPos);

			// get value
			ret = TmpGuiBox.val.eventbox;
			// int_push(TmpIntBox.val);
		}
	}
	// nothing changed with current datatype
	valdat.datatype = 60;

	// clear memory
	memset(&valdat, '\0', sizeof(valdat));

	return ret;
}

int get_guitype_array(VAL_LABEL valdat, long idx) {
	int ret = '\0';
	int myrenban = 0;

	// get valdat current stackid
	memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
	memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
	strcpy(TmpGuiBox.var.array_name, valdat.array_name);
	myrenban = valdat.array_widget;
	// printf("\nname %s get guitype, renban %d\n", valdat.array_name, myrenban);

	if (myrenban < 0) {
		printf("variabel untaian tidak ditemukan\n");
	}
	else {
		TmpGuiBox.val.stackid = myrenban;
		TmpGuiBox.val.idx = idx;

		// get current int value
		guiarryPos = gui_findData(TmpGuiBox.val);
		if (guiarryPos < 0) {
			// printf("nilai untaian tidak ditemukan\n");
			ret = '\0'; // for NULL
		}
		else {
			TmpGuiBox.val = gui_getElement(guiarryPos);

			// get value
			ret = TmpGuiBox.val.GUItype;

			// printf("got GUItype %d \n", ret);
			// int_push(TmpIntBox.val);
		}
	}
	// nothing changed with current datatype
	valdat.datatype = 60;

	// clear memory
	memset(&valdat, '\0', sizeof(valdat));

	return ret;
}

void del_gui_array(VAL_LABEL valdat, long idx) {
	int myrenban = 0;

	// get valdat current stackid
	memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
	memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
	strcpy(TmpGuiBox.var.array_name, valdat.array_name);
	myrenban = valdat.array_widget;
	// printf("\n get renban %d\n", renban);

	if (myrenban < 0) {
		printf("variabel untaian tidak ditemukan\n");
	}
	else {
		TmpGuiBox.val.stackid = myrenban;
		TmpGuiBox.val.idx = idx;

		// get current int value
		guiarryPos = gui_findData(TmpGuiBox.val);
		if (guiarryPos < 0) {
			printf("nilai untaian tidak ditemukan\n");
		}
		else {
			// remove at pos
			// printf("===del array int\n");
			// int_printData();
			gui_removeAt(guiarryPos);
			// int_printData();
		}
	}
	// nothing changed with current datatype
	valdat.datatype = 60;

	// clear memory
	memset(&valdat, '\0', sizeof(valdat));

}

void save_gui_array(VAL_LABEL valdat, long idx, GtkWidget *widget, GtkWidget *eventbox, int GUItype) {
	int myrenban = 0;

	// get valdat current stackid
	memset(&TmpGuiBox, '\0', sizeof(TmpGuiBox));
	memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
	strcpy(TmpGuiBox.var.array_name, valdat.array_name);

	myrenban = valdat.array_widget;

	if (myrenban < 0) {
		printf("variabel untaian tidak ditemukan\n");
	}
	else {
		TmpGuiBox.val.stackid = myrenban;
		TmpGuiBox.val.idx = idx;

		// get current int value
		guiarryPos = gui_findData(TmpGuiBox.val);
		if (guiarryPos < 0) {
			// printf(" found %s idx %d \n", valdat.array_name, idx);
			// set value
			TmpGuiBox.val.mywidget = widget;
			TmpGuiBox.val.eventbox = eventbox;
			TmpGuiBox.val.GUItype = GUItype;

			gui_addFirst(TmpGuiBox.val);
		}
		else {
			// printf(" %s idx %d , value ALREADY inside\n", valdat.array_name, idx);
			TmpGuiBox.val = gui_getElement(guiarryPos);
			// set value
			TmpGuiBox.val.mywidget = widget;
			TmpGuiBox.val.eventbox = eventbox;
			TmpGuiBox.val.GUItype = GUItype;

			gui_addFirst(TmpGuiBox.val);
		}
	}
	// nothing changed with current datatype
	valdat.datatype = 60;

	// clear memory
	memset(&valdat, '\0', sizeof(valdat));

}

// ////////////////////////////////////////////////////////////////
#endif