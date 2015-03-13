// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyUntaian (char ident[MAX_IDENT_LEN])
{
  VAL_LABEL valdat, valdat2, tmpdat;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  // printf("inside keyUntaian\n");
  // get variabel for array init
  getlex();

  switch( lex.type )
	    {
	    case TYPE_STR:
	    case TYPE_IDENT:
	    case TYPE_NUM:
	    case TYPE_ARRAY:

             valdat.val = -1;

             valdat.array_i = '\0';
             valdat.array_d = '\0';

             valdat.datatype = -1;

             memset(&valdat.str[0], '\0', sizeof(valdat.str));
             memset(&valdat.array_str[0], '\0', sizeof(valdat.array_str));
             memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));

             if(strlen(lex.detail.array_str) > 0) {
                // get array components
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(currentClass != NULL && strlen(currentClass) > 0) {
                  sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
                  //printf("construct class var: %s\n", class_tmpvar);
                  memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));
                  strcpy(valdat.array_name, class_tmpvar);
                }

                // printf("untaian arry name: %s\n", valdat.array_name);

                /* Read and check variable inside tree */
                valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
				if(valdat2.datatype >=0 && valdat2.scope != 2) // not global
                  Error("variabel sudah terpakai");

				// keep scope
				valdat.scope = valdat2.scope;

                if(isdigit(valdat.array_idx[0]) || valdat.array_idx[0] == '-') {
                  valdat.array_max = atoi (valdat.array_idx);
                } else {
                  /* printf("untai idx not digit : %s\n", valdat.array_idx); */

                  /* Get variable idx from tree */
                  tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                  /* printf("get type %d\n", tmpdat.datatype); */
                  
                  if(tmpdat.datatype==0) {
                    valdat.array_max = tmpdat.val;
                    /* printf("i %d\n", tmpdat.val); */
                    }
                  else
                    Error("Untaian salah masukan");
                }

                if(valdat.array_max < 0 || valdat.array_max > MAX_ARRAY)
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(renban != '\0')
                  renban++;
                else
                  renban = 0;

		if(renban > 999) {
                  renban = 0;
		}
                // printf("keyUntaian renban %d \n", renban);

		// /////////////////////
                // create INTEGER array
		// /////////////////////
                memset(&TmpIntBox, '\0', sizeof(TmpIntBox));
                memset(&TmpIntBox.var.array_name, '\0', sizeof(TmpIntBox.var.array_name));
		strcpy(TmpIntBox.var.array_name, valdat.array_name);
		// printf("start createRenban \n");
                TmpIntBox.var.stackid = createRenban(renban);
                valdat.array_i = TmpIntBox.var.stackid;             // keep stackid
                // printf("STACKID %d\n", TmpIntBox.var.stackid);
                if(stackInt_getID(TmpIntBox.var) >= 0.0) {
                  printf("nama variabel sudah terpakai! \n");
                } else {
                  stackInt_addFirst(TmpIntBox.var);
                }

		// /////////////////////
                // create DOUBLE array
		// /////////////////////
                memset(&TmpDblBox, '\0', sizeof(TmpDblBox));
                memset(&TmpDblBox.var.array_name, '\0', sizeof(TmpDblBox.var.array_name));
		strcpy(TmpDblBox.var.array_name, valdat.array_name);
		// printf("start createRenban \n");
                TmpDblBox.var.stackid = createRenban(renban);
                valdat.array_d = TmpDblBox.var.stackid;             // keep stackid
                // printf("STACKID %d\n", TmpIntBox.var.stackid);
                if(stackDbl_getID(TmpDblBox.var) >= 0.0) {
                  printf("nama variabel sudah terpakai! \n");
                } else {
                  stackDbl_addFirst(TmpDblBox.var);
                }

				// /////////////////////
                // create STRING array
				// /////////////////////
                memset(&TmpStrBox, '\0', sizeof(TmpStrBox));
                memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				strcpy(TmpStrBox.var.array_name, valdat.array_name);
				// printf("start createRenban \n");
                TmpStrBox.var.stackid = createRenban(renban);       // create stackid here
                valdat.array_s = TmpStrBox.var.stackid;             // keep stackid
                // printf("STACKID %d\n", TmpStrBox.var.stackid);
                if(stackStr_getID(TmpStrBox.var) >= 0.0) {
                  printf("nama variabel sudah terpakai! \n");
                } else {
                  stackStr_addFirst(TmpStrBox.var);
                }


		// ///////////////////////
                // create GUI Widget array
		// ///////////////////////
                #ifdef USE_GTK2
                memset(&TmpGuiBox, '\0', sizeof(TmpIntBox));
                memset(&TmpGuiBox.var.array_name, '\0', sizeof(TmpGuiBox.var.array_name));
		strcpy(TmpGuiBox.var.array_name, valdat.array_name);
		// printf("start createRenban \n");
                TmpGuiBox.var.stackid = createRenban(renban);
                valdat.array_widget = TmpGuiBox.var.stackid;             // keep stackid
                // printf("STACKID %d\n", TmpGuiBox.var.stackid);
                if(stackGui_getID(TmpGuiBox.var) >= 0.0) {
                  printf("nama variabel sudah terpakai! \n");
                } else {
                  stackGui_addFirst(TmpGuiBox.var);
                }

                //printf("arr ALL : %s\n", valdat.array_str);
                //printf("arr name : %s\n", valdat.array_name);
                //printf("arr idx : %s\n", valdat.array_idx);
                #endif

             } else {
                  Error("Salah dalam pendefinisian Untaian");
             }

             //printf("define arr datatype : %d\n", valdat.datatype);
             //printf("define arr name : %s\n", valdat.array_name);
             //printf("define arr idx : %s\n", valdat.array_idx);
             //printf("define arr max : %d\n", valdat.array_max);

             /* Store Array Initialization to Node memory tree */
             ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_W );

             memset(&valdat, '\0', sizeof(valdat));
             memset(&valdat2, '\0', sizeof(valdat2));
             memset(&tmpdat, '\0', sizeof(tmpdat));                          

	      break;

	    default:
	      Error("kode perintah UNTAIAN salah");
	    }

  if(valdat.filename != NULL)
    free(valdat.filename);
  if(valdat.folder != NULL)
    free(valdat.folder);
  if(valdat.filedata != NULL)
    free(valdat.filedata);
  if(valdat.long_str != NULL)
    free(valdat.long_str);

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(tmpdat.filename != NULL)
    free(tmpdat.filename);
  if(tmpdat.folder != NULL)
    free(tmpdat.folder);
  if(tmpdat.filedata != NULL)
    free(tmpdat.filedata);
  if(tmpdat.long_str != NULL)
    free(tmpdat.long_str);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

}

