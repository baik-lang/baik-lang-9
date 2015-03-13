// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#ifndef S_SPLINT_S

#include <windows.h>
#include <string.h>
#include "regex.h"


/**************************************************************************
	Define
**************************************************************************/

#define ToLower(c)              ((c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c)

#define CHAR_SPACE_SIZE         256
#define EPSILON_TRANS           -1

#define CHAR_DOT                "\x01-\xff"

#ifdef UNICODE
#define tstrcpy                 strcpy
#else
#define tstrcpy                 lstrcpy
#endif

#ifdef UNICODE
#define tstrlen                 strlen
#else
#define tstrlen                 lstrlen
#endif


/**************************************************************************
	Global Variables
**************************************************************************/

//Tree
typedef enum {
 TOKEN_CHAR,
 TOKEN_GROUP_OPEN,
 TOKEN_GROUP_CLOSE,
 TOKEN_INTERVAL_ZERO_MORE_NG,
 TOKEN_INTERVAL_ONE_MORE_NG,
 TOKEN_INTERVAL_ZERO_ONE_NG,
 TOKEN_INTERVAL_CLOSE_NG,
 TOKEN_INTERVAL_ZERO_MORE,
 TOKEN_INTERVAL_ONE_MORE,
 TOKEN_INTERVAL_ZERO_ONE,
 TOKEN_INTERVAL_OPEN,
 TOKEN_INTERVAL_CLOSE,
 TOKEN_ANY_CHAR,
 TOKEN_LIST_OPEN,
 TOKEN_LIST_CLOSE,
 TOKEN_LINE_BEGIN,
 TOKEN_LINE_END,
 TOKEN_ALTERNATION,
 TOKEN_META_ESCAPE,
 TOKEN_END,
 TOKEN_LIST_NOT,
 TOKEN_LIST_RANGE,
 TOKEN_LIST_ESCAPE,
 TOKEN_INTERVAL_RANGE,
} TOKEN;

static char *token_chars[] = {
 "c",	"(",	")",	"*?",	"+?",	"??",	"}?",
 "*",	"+",	"?",	"{",	"}",	".",	"[",
 "]",	"^",	"$",	"|",	"\\",
 "",		"^",	"-",	"\\",	",",
};

typedef enum {
 OP_CHAR,
 OP_HEAD,
 OP_TAIL,
 OP_CHARCLASS,
 OP_CONCAT,
 OP_UNION,
 OP_CLOSURE,
 OP_CLOSURE_NG,
 OP_EMPTY,
 OP_OPEN,
 OP_CLOSE,
} OP;


typedef struct _TREE {
 OP op;
 union {
  char *chr_class;
  int i;
  struct {
    char c1;
    char c2;
  } c;
  struct {
    struct _TREE *left;
    struct _TREE *right;
  } x;
 } u;
} TREE;

typedef struct _REGE_PARSER {
 TREE *tree;
 TOKEN current_token;
 char token_char1;
 char token_char2;
 char *p;
 char user_char_set[CHAR_SPACE_SIZE];
 int intervals_open, intervals_close;
 int rfcnt;
} REGE_PARSER;


//match
typedef struct _REGE_MATCH {
 REGE_NFA *nfa;
 REGE_REFER *rf;
 BOOL icase;
} REGE_MATCH;


/**************************************************************************
	Local Function Prototypes
**************************************************************************/

//memory
static void *mem_alloc(int size);
static void mem_free(void **mem);
static char *alloc_copy(const char *buf);

//string
static char *str_cpy_n(char *ret, char *buf, int len);
static int str_cmp_n(const char *buf1, const char *buf2, int len);
static long x2d(const char *str);

//tree
static char *get_esc_string(char *c, char *ret, BOOL expand_flag);
static void get_token(REGE_PARSER *parser);
static TREE *make_tree_node(REGE_PARSER *parser, OP op, TREE *left, TREE *right);
static TREE *copy_tree(REGE_PARSER *parser, TREE *p);
static TREE *primary(REGE_PARSER *parser);
static TREE *factor(REGE_PARSER *parser);
static TREE *term(REGE_PARSER *parser);
static TREE *regexp(REGE_PARSER *parser);
static REGE_PARSER *parse(char *pattern);
static void free_tree(TREE *p);

//NFA
static NFA_LIST *add_transition(REGE_NFA *nfa, int from, int to, int eps, OP op);
static void generate_nfa(REGE_NFA *nfa, TREE *tree, int entry, int way_out);
static int generate_nfa_count(TREE *tree);
static REGE_NFA *build_nfa(REGE_PARSER *parser);

//match
static BOOL charclass_match(char *p, char *c);
static char *rege_match(REGE_MATCH *rm, int i, char *c);


static void *mem_alloc(int size)
{
 return LocalAlloc(LMEM_FIXED, size);
}



static void mem_free(void **mem)
{
  if(*mem != NULL){
     LocalFree(*mem);
     *mem = NULL;
  }
}



static char *alloc_copy(const char *buf)
{
  char *ret;

  ret = NULL;
  if(buf == NULL){
    return NULL;
  }
  ret = (char *)mem_alloc(sizeof(char) * (tstrlen(buf) + 1));
  if(ret != NULL){
    tstrcpy(ret, buf);
  }
  return ret;
}



static char *str_cpy_n(char *ret, char *buf, int len)
{
  if(buf == NULL || len <= 0){
    *ret = '\0';
    return ret;
  }
  while(--len && (*(ret++) = *(buf++)));
  *ret = '\0';
  if(len != 0) ret--;
  return ret;
}



static int str_cmp_n(const char *buf1, const char *buf2, int len)
{
  int i = 0;

  for(; *buf1 == *buf2 && *buf1 != '\0' && i < len; i++, buf1++, buf2++);
  return ((i == len) ? 0 : *buf1 - *buf2);
}


static long x2d(const char *str)
{
  int num = 0;
  int m;

  for(; *str != '\0'; str++){
    if(*str >= '0' && *str <= '9'){
      m = *str - '0';
    }else if(*str >= 'A' && *str <= 'F'){
      m = *str - 'A' + 10;
    }else if(*str >= 'a' && *str <= 'f'){
      m = *str - 'a' + 10;
    }else{
      break;
    }
    num = 16 * num + m;
  }

  return num;
}


static char *get_esc_string(char *c, char *ret, BOOL expand_flag)
{
	if(expand_flag == FALSE){
		switch(*(c + 1))
		{
		case '\\':
		case 'w':
		case 'W':
		case 'd':
		case 'D':
		case 's':
		case 'S':
			*ret = *(c++);
			*(ret + 1) = *(c++);
			*(ret + 2) = '\0';
			return c;
		}
	}

	*(ret + 1) = '\0';
	c++;

	switch(*c)
	{
	case 'r':
	case 'R':
		*ret = '\r';
		break;

	case 'n':
	case 'N':
		*ret = '\n';
		break;

	case 't':
	case 'T':
		*ret = '\t';
		break;

	case 'w':
		tstrcpy(ret, "0-9a-zA-Z_");
		break;

	case 'W':
		tstrcpy(ret, "^0-9a-zA-Z_");
		break;

	case 'd':
		tstrcpy(ret, "0-9");
		break;

	case 'D':
		tstrcpy(ret, "^0-9");
		break;

	case 's':
		tstrcpy(ret, "\t\r\n ");
		break;

	case 'S':
		tstrcpy(ret, "^\t\r\n ");
		break;

	case 'x':
	case 'X':
		//Char (Hex)
		c++;
		if(*c != '\0'){
			char tmp[10], *r;

			for(r = c; (r - c) < 2 && ((*r >= '0' && *r <= '9')
				|| (*r >= 'A' && *r <= 'F')
				|| (*r >= 'a' && *r <= 'f')); r++);
			str_cpy_n(tmp, c, r - c + 1);
			*ret = (unsigned char)x2d(tmp);
			c += r - c - 1;
		}
		break;

	default:
		*ret = *c;
		break;
	}
	return (c + 1);
}


static void get_token(REGE_PARSER *parser)
{
	TOKEN i;
	int l;
	char *c;

	parser->token_char1 = '\0';
	parser->token_char2 = '\0';
	parser->current_token = TOKEN_CHAR;

	for(i = TOKEN_CHAR + 1; i < TOKEN_END; i++){
		if(*parser->p == '\0'){
			parser->current_token = TOKEN_END;
			return;
		}
		if((l = tstrlen(*(token_chars + i))) &&
			str_cmp_n(parser->p, *(token_chars + i), l) == 0){
			parser->current_token = i;
			break;
		}
	}

	c = parser->p;
	parser->p += tstrlen(*(token_chars + parser->current_token));

	switch(parser->current_token)
	{
	case TOKEN_CHAR:
		parser->token_char1 = *c;
		if(IsDBCSLeadByte((BYTE)*c)){
			parser->token_char2 = *parser->p++;
		}
		break;

	case TOKEN_ANY_CHAR:
		parser->current_token = TOKEN_LIST_CLOSE;
		tstrcpy(parser->user_char_set, CHAR_DOT);
		break;

	case TOKEN_LINE_BEGIN:
		parser->token_char1 = *c;
		break;

	case TOKEN_LINE_END:
		parser->token_char1 = *c;
		break;

	case TOKEN_INTERVAL_OPEN:
		if(*parser->p != '\0'){
			int *i = &parser->intervals_open;

			parser->intervals_open = 0;
			parser->intervals_close = 0;
			c = parser->p++;
			while(*c != '\0'){
				if(*c == **(token_chars + TOKEN_INTERVAL_CLOSE)){
					if(i == &parser->intervals_open){
						parser->intervals_close = parser->intervals_open;
					}
					parser->current_token = TOKEN_INTERVAL_CLOSE;
					break;

				}else if(*c == **(token_chars + TOKEN_INTERVAL_RANGE)){
					i = &parser->intervals_close;
					c = parser->p;
					parser->p++;

				}else if(*c >= '0' && *c <= '9'){
					*i = *i * 10 + (*c - '0');
					c = parser->p++;

				}else{
					c = parser->p++;
				}
			}
		}
		if(parser->current_token != TOKEN_INTERVAL_CLOSE){
			parser->current_token = TOKEN_END;
		}else{
			if(*parser->p == '?'){
				parser->current_token = TOKEN_INTERVAL_CLOSE_NG;
				parser->p++;
			}
		}
		break;

	case TOKEN_LIST_OPEN:
		if(*parser->p != '\0'){
			int i = 0;

			c = parser->p++;
			if(*c == **(token_chars + TOKEN_LIST_CLOSE)){
				*(parser->user_char_set + i++) = **(token_chars + TOKEN_LIST_CLOSE);
				c = parser->p;
				parser->p++;
			}

			if(*c == **(token_chars + TOKEN_LIST_NOT) &&
				*parser->p == **(token_chars + TOKEN_LIST_CLOSE)){
				*(parser->user_char_set + i++) = **(token_chars + TOKEN_LIST_NOT);
				c = parser->p++;
				*(parser->user_char_set + i++) = **(token_chars + TOKEN_LIST_CLOSE);
				c = parser->p++;
			}

			while(*c != '\0'){
				if(*c == **(token_chars + TOKEN_LIST_CLOSE)){
					*(parser->user_char_set + i) = '\0';
					parser->current_token = TOKEN_LIST_CLOSE;
					break;
				}else if(*c == **(token_chars + TOKEN_LIST_ESCAPE)){
					char tmp[CHAR_SPACE_SIZE];
					parser->p = get_esc_string(c, tmp, FALSE);
					tstrcpy(parser->user_char_set + i, tmp);
					i += tstrlen(tmp);
				}else{
					if(IsDBCSLeadByte((BYTE)*c) == TRUE){
						*(parser->user_char_set + i++) = *c;
						c = parser->p++;
					}
					*(parser->user_char_set + i++) = *c;
				}
				c = parser->p++;
			}
		}
		if(parser->current_token != TOKEN_LIST_CLOSE) {
			parser->current_token = TOKEN_END;
		}
		break;

	case TOKEN_META_ESCAPE:
		if(*parser->p != '\0'){
			parser->p = get_esc_string(c, parser->user_char_set, TRUE);
			parser->current_token = TOKEN_LIST_CLOSE;

			if(tstrlen(parser->user_char_set) == 1){
				parser->current_token = TOKEN_CHAR;
				parser->token_char1 = *parser->user_char_set;
			}
		}
		break;
	}
}



static TREE *make_tree_node(REGE_PARSER *parser, OP op, TREE *left, TREE *right)
{
  TREE *p;

  p = NULL;
  if((p = mem_alloc(sizeof(TREE))) == NULL){
    return NULL;
  }
  ZeroMemory(p, sizeof(TREE));
  p->op = op;
  p->u.x.left = left;
  p->u.x.right = right;
  return p;
}


static TREE *copy_tree(REGE_PARSER *parser, TREE *p)
{
	TREE *x;

	x = NULL;
	if(p == NULL){
		return NULL;
	}
	switch(p->op)
	{
	case OP_CONCAT:
	case OP_UNION:
		x = make_tree_node(parser, p->op,
			copy_tree(parser, p->u.x.left), copy_tree(parser, p->u.x.right));
		break;

	case OP_CLOSURE:
		x = make_tree_node(parser, p->op,
			copy_tree(parser, p->u.x.left), NULL);
		break;

	case OP_CHAR:
		x = make_tree_node(parser, p->op, NULL, NULL);
		x->u.c.c1 = p->u.c.c1;
		x->u.c.c2 = p->u.c.c2;
		break;

	case OP_CHARCLASS:
		x = make_tree_node(parser, p->op, NULL, NULL);
		x->u.chr_class = alloc_copy(p->u.chr_class);
		break;

	default:
		x = make_tree_node(parser, p->op, NULL, NULL);
		break;
	}
	return x;
}

static TREE *primary(REGE_PARSER *parser)
{
	TREE *x = NULL;
	TREE *o, *c;

	o = NULL;
	c = NULL;
	switch(parser->current_token)
	{
	case TOKEN_CHAR:
		// X
		x = make_tree_node(parser, OP_CHAR, NULL, NULL);
		x->u.c.c1 = parser->token_char1;
		x->u.c.c2 = parser->token_char2;
		get_token(parser);
		break;

	case TOKEN_LINE_BEGIN:
		// ^
		x = make_tree_node(parser, OP_HEAD, NULL, NULL);
		x->u.c.c1 = parser->token_char1;
		get_token(parser);
		break;

	case TOKEN_LINE_END:
		// $
		x = make_tree_node(parser, OP_TAIL, NULL, NULL);
		x->u.c.c1 = parser->token_char1;
		get_token(parser);
		break;

	case TOKEN_LIST_CLOSE:
		// [...]
		x = make_tree_node(parser, OP_CHARCLASS, NULL, NULL);
		x->u.chr_class = alloc_copy(parser->user_char_set);
		get_token(parser);
		break;

	case TOKEN_GROUP_OPEN:
		// (...)
		parser->rfcnt++;
		o = make_tree_node(parser, OP_OPEN, NULL, NULL);
		o->u.i = parser->rfcnt;
		c = make_tree_node(parser, OP_CLOSE, NULL, NULL);
		c->u.i = parser->rfcnt;

		get_token(parser);
		x = make_tree_node(parser, OP_CONCAT, o,
			make_tree_node(parser, OP_CONCAT, regexp(parser), c));
		get_token(parser);
		break;
	}
	return x;
}


static TREE *factor(REGE_PARSER *parser)
{
	TREE *p, *r, *x;
	int i;


	p = NULL;
	r = NULL;
	x = NULL;

	x = primary(parser);
	switch(parser->current_token)
	{
	case TOKEN_INTERVAL_ZERO_MORE:
		// X*
		x = make_tree_node(parser, OP_CLOSURE, x, NULL);
		get_token(parser);
		break;

	case TOKEN_INTERVAL_ZERO_MORE_NG:
		// X*?
		x = make_tree_node(parser, OP_CLOSURE_NG, x, NULL);
		get_token(parser);
		break;

	case TOKEN_INTERVAL_ONE_MORE:
		// X+
		p = copy_tree(parser, x);
		x = make_tree_node(parser, OP_CONCAT, x,
			make_tree_node(parser, OP_CLOSURE, p, NULL));
		get_token(parser);
		break;

	case TOKEN_INTERVAL_ONE_MORE_NG:
		// X+?
		p = copy_tree(parser, x);
		x = make_tree_node(parser, OP_CONCAT, x,
			make_tree_node(parser, OP_CLOSURE_NG, p, NULL));
		get_token(parser);
		break;

	case TOKEN_INTERVAL_ZERO_ONE:
		// X?
		x = make_tree_node(parser, OP_UNION,
			make_tree_node(parser, OP_EMPTY, NULL, NULL), x);
		get_token(parser);
		break;

	case TOKEN_INTERVAL_ZERO_ONE_NG:
		// X??
		x = make_tree_node(parser, OP_UNION, x,
			make_tree_node(parser, OP_EMPTY, NULL, NULL));
		get_token(parser);
		break;

	case TOKEN_INTERVAL_CLOSE:
		// X{n,m}
		if(parser->intervals_close == 0){
			r = copy_tree(parser, x);
			p = make_tree_node(parser, OP_CLOSURE, r, NULL);
		}else{
			p = make_tree_node(parser, OP_EMPTY, NULL, NULL);
		}
		for(i = parser->intervals_close; i > parser->intervals_open; i--){
			r = copy_tree(parser, x);
			p = make_tree_node(parser, OP_CONCAT, p,
				make_tree_node(parser, OP_UNION,
				make_tree_node(parser, OP_EMPTY, NULL, NULL), r));
		}
		for(i = parser->intervals_open; i > 0; i--){
			r = copy_tree(parser, x);
			p = make_tree_node(parser, OP_CONCAT, r, p);
		}
		if(parser->intervals_open == 0){
			p = make_tree_node(parser, OP_UNION,
				make_tree_node(parser, OP_EMPTY, NULL, NULL), p);
		}
		free_tree(x);
		x = p;
		get_token(parser);
		break;

	case TOKEN_INTERVAL_CLOSE_NG:
		// X{n,m}?
		if(parser->intervals_close == 0){
			r = copy_tree(parser, x);
			p = make_tree_node(parser, OP_CLOSURE_NG, r, NULL);
		}else{
			p = make_tree_node(parser, OP_EMPTY, NULL, NULL);
		}
		for(i = parser->intervals_close; i > parser->intervals_open; i--){
			r = copy_tree(parser, x);
			p = make_tree_node(parser, OP_CONCAT, p,
				make_tree_node(parser, OP_UNION, r,
				make_tree_node(parser, OP_EMPTY, NULL, NULL)));
		}
		for(i = parser->intervals_open; i > 0; i--){
			r = copy_tree(parser, x);
			p = make_tree_node(parser, OP_CONCAT, r, p);
		}
		if(parser->intervals_open == 0){
			p = make_tree_node(parser, OP_UNION, p,
				make_tree_node(parser, OP_EMPTY, NULL, NULL));
		}
		free_tree(x);
		x = p;
		get_token(parser);
		break;
	}
	return x;
}


static TREE *term(REGE_PARSER *parser)
{
  TREE *x;

  x = NULL;
  if(parser->current_token == TOKEN_ALTERNATION
		|| parser->current_token == TOKEN_GROUP_CLOSE
		|| parser->current_token == TOKEN_END){
		x = make_tree_node(parser, OP_EMPTY, NULL, NULL);

  }else{
		x =  factor(parser);
		while(parser->current_token != TOKEN_ALTERNATION
			&& parser->current_token != TOKEN_GROUP_CLOSE
			&& parser->current_token != TOKEN_END){
			x = make_tree_node(parser, OP_CONCAT, x, factor(parser));
		}
  }
  return x;

}


static TREE *regexp(REGE_PARSER *parser)
{
  TREE *x;

  x = NULL;
  x = term(parser);
  while(parser->current_token == TOKEN_ALTERNATION){
    get_token(parser);
    x = make_tree_node(parser, OP_UNION, term(parser), x);
  }
  return x;
}



static REGE_PARSER *parse(char *pattern)
{
  REGE_PARSER *parser;

  if((parser = mem_alloc(sizeof(REGE_PARSER))) == NULL){
    return NULL;
  }
  ZeroMemory(parser, sizeof(REGE_PARSER));

  parser->p = pattern;
  get_token(parser);

  parser->tree = regexp(parser);
  return parser;
}

static void free_tree(TREE *p)
{
	if(p == NULL){
		return;
	}
	switch (p->op)
	{
	case OP_CONCAT:
	case OP_UNION:
		free_tree(p->u.x.right);
		p->u.x.right = NULL;
	case OP_CLOSURE:
	case OP_CLOSURE_NG:
		free_tree(p->u.x.left);
		p->u.x.left = NULL;
		break;

	case OP_CHARCLASS:
		mem_free((void **)&p->u.chr_class);
		break;

	default:
		break;
	}
	mem_free((void **)&p);
}



static NFA_LIST *add_transition(REGE_NFA *nfa, int from, int to, int eps, OP op)
{
  NFA_LIST *p;

  if((p = mem_alloc(sizeof(NFA_LIST))) == NULL){
    return NULL;
  }
  ZeroMemory(p, sizeof(NFA_LIST));

  p->eps = eps;
  p->op = op;
  p->to = to;
  p->next = *(nfa->states + from);
  *(nfa->states + from) = p;
  return p;
}


static void generate_nfa(REGE_NFA *nfa, TREE *tree, int entry, int way_out)
{
	NFA_LIST *p;
	int a1, a2;

	if(tree == NULL){
		return;
	}
	switch(tree->op)
	{
	case OP_CHAR:
		p = add_transition(nfa, entry, way_out, 0, tree->op);
		if(p != NULL){
			p->u.c.c1 = tree->u.c.c1;
			p->u.c.c2 = tree->u.c.c2;
		}
		break;

	case OP_HEAD:
		if(entry == nfa->entry) {
			nfa->head_flag = TRUE;
			add_transition(nfa, entry, way_out, EPSILON_TRANS, tree->op);
		}
		break;

	case OP_TAIL:
		if(way_out == nfa->exit){
			nfa->tail_flag = TRUE;
			add_transition(nfa, entry, way_out, EPSILON_TRANS, tree->op);
		}
		break;

	case OP_CHARCLASS:
		p = add_transition(nfa, entry, way_out, 0, tree->op);
		if(p != NULL){
			p->u.chr_class = alloc_copy(tree->u.chr_class);
		}
		break;

	case OP_OPEN:
	case OP_CLOSE:
		p = add_transition(nfa, entry, way_out, EPSILON_TRANS, tree->op);
		if(p != NULL){
			p->u.i = tree->u.i;
		}
		break;

	case OP_EMPTY:
		add_transition(nfa, entry, way_out, EPSILON_TRANS, tree->op);
		break;

	case OP_UNION:
		generate_nfa(nfa, tree->u.x.left, entry, way_out);
		generate_nfa(nfa, tree->u.x.right, entry, way_out);
		break;

	case OP_CLOSURE:
		a1 = nfa->nstate++;
		a2 = nfa->nstate++;
		add_transition(nfa, entry, a1, EPSILON_TRANS, tree->op);
		add_transition(nfa, a2, a1, EPSILON_TRANS, tree->op);
		add_transition(nfa, a1, way_out, EPSILON_TRANS, tree->op);
		generate_nfa(nfa, tree->u.x.left, a1, a2);
		break;

	case OP_CLOSURE_NG:
		a1 = nfa->nstate++;
		a2 = nfa->nstate++;
		add_transition(nfa, entry, a1, EPSILON_TRANS, tree->op);
		generate_nfa(nfa, tree->u.x.left, a1, a2);
		add_transition(nfa, a2, a1, EPSILON_TRANS, tree->op);
		add_transition(nfa, a1, way_out, EPSILON_TRANS, tree->op);
		break;

	case OP_CONCAT:
		a1 = nfa->nstate++;
		generate_nfa(nfa, tree->u.x.left, entry, a1);
		generate_nfa(nfa, tree->u.x.right, a1, way_out);
		break;

	default:
		break;
	}
}


static int generate_nfa_count(TREE *tree)
{
	int ret = 0;

	if(tree == NULL){
		return 0;
	}
	switch (tree->op)
	{
	case OP_UNION:
		ret = 0;
		ret += generate_nfa_count(tree->u.x.left);
		ret += generate_nfa_count(tree->u.x.right);
		break;

	case OP_CLOSURE:
		ret = 2;
		ret += generate_nfa_count(tree->u.x.left);
		break;

	case OP_CLOSURE_NG:
		ret = 2;
		ret += generate_nfa_count(tree->u.x.left);
		break;

	case OP_CONCAT:
		ret = 1;
		ret += generate_nfa_count(tree->u.x.left);
		ret += generate_nfa_count(tree->u.x.right);
		break;

	default:
		break;
	}
	return ret;
}


static REGE_NFA *build_nfa(REGE_PARSER *parser)
{
	REGE_NFA *nfa;
	int i;

	if((nfa = mem_alloc(sizeof(REGE_NFA))) == NULL){
		return NULL;
	}
	ZeroMemory(nfa, sizeof(REGE_NFA));

	i = generate_nfa_count(parser->tree);
	nfa->states = mem_alloc(sizeof(NFA_LIST *) * (i + 2));
	ZeroMemory(nfa->states, sizeof(NFA_LIST *) * (i + 2));

	nfa->nstate = 0;
	nfa->entry = nfa->nstate++;
	nfa->exit = nfa->nstate++;
	nfa->head_flag = FALSE;
	nfa->tail_flag = FALSE;
	nfa->rfcnt = parser->rfcnt + 1;
	generate_nfa(nfa, parser->tree, nfa->entry, nfa->exit);
	return nfa;
}


void free_nfa(REGE_NFA *nfa)
{
	int i;
	NFA_LIST *p, *q;

	if(nfa == NULL) return;

	for(i = 0; i < nfa->nstate; i++){
		if(*(nfa->states + i) != NULL){
			p = *(nfa->states + i);
			while(p != NULL){
				q = p;
				p = p->next;
				if(q->op == OP_CHARCLASS){
					mem_free((void **)&q->u.chr_class);
				}
				mem_free((void **)&q);
			}
		}
	}
	mem_free((void **)&nfa->states);
	mem_free((void **)&nfa);
}



static BOOL charclass_match(char *p, char *c)
{
	char tmp[CHAR_SPACE_SIZE];
	BOOL ret = FALSE;
	BOOL neg_flag = FALSE;

	if(*p == **(token_chars + TOKEN_LIST_NOT)){
		neg_flag = TRUE;
		p++;
	}

	while(*p != '\0' && ret == FALSE){
		if(IsDBCSLeadByte((BYTE)*p) == TRUE){
			if(*(p + 2) == **(token_chars + TOKEN_LIST_RANGE) && IsDBCSLeadByte((BYTE)*(p + 3)) == TRUE){
				ret = ((unsigned)*c >= (unsigned)*p &&
					(unsigned)*(c + 1) >= (unsigned)*(p + 1) &&
					(unsigned)*c <= (unsigned)*(p + 3) &&
					(unsigned)*(c + 1) <= (unsigned)*(p + 4)) ? TRUE : FALSE;
				p += 4;
			}else{
				ret = (*p == *c && *(p + 1) == *(c + 1)) ? TRUE : FALSE;
				p++;
			}
			p++;
			continue;
		}
		if(*(p + 1) == **(token_chars + TOKEN_LIST_RANGE) && *(p + 2) != '\0'){
			ret = ((unsigned)*c >= (unsigned)*p &&
				(unsigned)*c <= (unsigned)*(p + 2)) ? TRUE : FALSE;
			p += 2;
		}else{
			if(*p == **(token_chars + TOKEN_LIST_ESCAPE) && *(p + 1) != '\0'){
				p = get_esc_string(p, tmp, TRUE);
				ret = charclass_match(tmp, c);
				continue;
			}else{
				ret = (*p == *c) ? TRUE : FALSE;
			}
		}
		p++;
	}
	return ((neg_flag == FALSE) ? ret : !ret);
}


static char *rege_match(REGE_MATCH *rm, int i, char *c)
{
	NFA_LIST *p;
	char *ret;

	if(rm->nfa->exit == i){
		if(rm->nfa->tail_flag == TRUE &&
			*c != '\0' && *c != '\r' && *c != '\n'){
			return NULL;
		}

		return c;
	}
	for(p = *(rm->nfa->states + i); p != NULL; p = p->next){
		if(p->eps == EPSILON_TRANS){

			switch(p->op)
			{
			case OP_OPEN:
				if(rm->rf == NULL){
					break;
				}
				(rm->rf + p->u.i)->st = c;
				break;

			case OP_CLOSE:
				if(rm->rf == NULL){
					break;
				}
				(rm->rf + p->u.i)->en = c;
				break;
			}
			if((ret = rege_match(rm, p->to, c)) != NULL){
				return ret;
			}
			continue;
		}


		if(*c == '\0'){
			continue;
		}
		if(rm->nfa->tail_flag == TRUE && (*c == '\r' || *c == '\n')){
			continue;
		}
		if(IsDBCSLeadByte((BYTE)*c) == TRUE){

			if(p->op == OP_CHARCLASS){

				if(charclass_match(p->u.chr_class, c) == TRUE &&
					(ret = rege_match(rm, p->to, c + 2)) != NULL){
					return ret;
				}
			}else if(p->u.c.c1 == *c && p->u.c.c2 == *(c + 1) &&
				(ret = rege_match(rm, p->to, c + 2)) != NULL){
				return ret;
			}
			continue;
		}
		if(p->op == OP_CHARCLASS){

			if(charclass_match(p->u.chr_class, c) == TRUE &&
				(ret = rege_match(rm, p->to, c + 1)) != NULL){
				return ret;
			}
		}else if(rm->icase == TRUE){

			if(ToLower(p->u.c.c1) == ToLower(*c) &&
				(ret = rege_match(rm, p->to, c + 1)) != NULL){
				return ret;
			}
		}else if(p->u.c.c1 == *c &&
			(ret = rege_match(rm, p->to, c + 1)) != NULL){
			return ret;
		}
	}
	return NULL;
}



REGE_NFA *rege_compile(char *ptn)
{
  REGE_PARSER *parser;
  REGE_NFA *nfa;

  parser = parse(ptn);

  nfa = build_nfa(parser);
  free_tree(parser->tree);
  mem_free((void **)&parser);
  return nfa;
}



int reg_match(REGE_NFA *nfa, char *str, REGE_REFER **rf, BOOL icase)
{
	REGE_MATCH rm;
	char *to;
	char *p;

	to = NULL;

	if(nfa == NULL){
		return 0;
	}

	ZeroMemory(&rm, sizeof(REGE_MATCH));
	rm.nfa = nfa;
	rm.icase = icase;
	rm.rf = mem_alloc(sizeof(REGE_REFER) * nfa->rfcnt);

	p = str;
	while(*p != '\0'){
		ZeroMemory(rm.rf, sizeof(REGE_REFER) * nfa->rfcnt);
		to = rege_match(&rm, 0, p);
		if(to != NULL){
			break;
		}
		if(nfa->head_flag == TRUE){
			for(; *p != '\0' && *p != '\r' && *p != '\n'; p++);
			for(; *p == '\r' || *p == '\n'; p++);
		}else{
			p++;
		}
	}
	if(to == NULL){
		mem_free((void **)&rm.rf);
		return 0;
	}
	rm.rf->st = p;
	rm.rf->en = to;
	*rf = rm.rf;
	return nfa->rfcnt;
}



void free_refer(REGE_REFER *rf)
{
  if(rf == NULL) return;
  mem_free((void **)&rf);
}

#endif

