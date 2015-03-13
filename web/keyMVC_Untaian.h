// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

MVCPARSING keyMVC_Untaian (char ident[MAX_IDENT_LEN], MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  VAL_LABEL valdat, valdat2, tmpdat;

  MVCPARSING par;
  
  memset(&par, '\0', sizeof(par));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  //printf("inside keyUntaian\n");

  //getlex();
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  = par.mvc_pg;

  //printf("type after getlex %d\n", mvc_lex.type);

  switch( mvc_lex.type )
	    {
	    case TYPE_MVC_STR:
	    case TYPE_MVC_IDENT:
	    case TYPE_MVC_NUM:
	    case TYPE_MVC_ARRAY:

             valdat.val = -1;

             valdat.array_i = '\0';
             valdat.array_d = '\0';

             valdat.datatype = -1;

             memset(&valdat.str[0], '\0', sizeof(valdat.str));
             memset(&valdat.array_str[0], '\0', sizeof(valdat.array_str));
             memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));

             if(strlen(mvc_lex.detail.array_str) > 0) {
                // get array components
                strcpy(valdat.array_str, mvc_lex.detail.array_str);
                getArrayName(mvc_lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(mvc_lex.detail.array_str, (char *)&valdat.array_idx);

                //printf("untaian arry name: %s\n", valdat.array_name);

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
		
                //printf("keyUntaian renban %d \n", renban);

		// /////////////////////
                // create INTEGER array
		// /////////////////////
                memset(&TmpIntBox, '\0', sizeof(TmpIntBox));
                memset(&TmpIntBox.var.array_name, '\0', sizeof(TmpIntBox.var.array_name));
		strcpy(TmpIntBox.var.array_name, valdat.array_name);
		// printf("start createRenban \n");
                TmpIntBox.var.stackid = createRenban(renban);
                valdat.array_i = TmpIntBox.var.stackid;             // keep stackid
                //printf("STACKID array_i %d\n", TmpIntBox.var.stackid);

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

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);


  par.mvc_lex = mvc_lex;
  par.mvc_pg  = mvc_pg;

  return par;
}

