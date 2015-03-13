// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


#include <windows.h>

#ifndef _INC_REGEX_H
#define _INC_REGEX_H

typedef struct _NFA_LIST {
  int op;
  union {
    char *chr_class;
    int i;
    struct {
      char c1;
      char c2;
    } c;
  } u;
  int eps;
  int to;
  struct _NFA_LIST *next;
} NFA_LIST;


typedef struct _REGE_NFA {
  struct _NFA_LIST **states;
  int entry;
  int exit;
  int nstate;
  int rfcnt;
  #ifndef S_SPLINT_S
  BOOL head_flag;
  BOOL tail_flag;
  #else
  bool head_flag;
  bool tail_flag;
  #endif

} REGE_NFA;


typedef struct _REGE_REFER {
  char *st;
  char *en;
} REGE_REFER;

void free_nfa(REGE_NFA *nfa);
REGE_NFA *rege_compile(char *ptn);

#ifndef S_SPLINT_S
int reg_match(REGE_NFA *nfa, char *str, REGE_REFER **rf, BOOL icase);
#else
int reg_match(REGE_NFA *nfa, char *str, REGE_REFER **rf, bool icase);
#endif
void free_refer(REGE_REFER *rf);

#endif
