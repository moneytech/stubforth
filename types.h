#ifndef TYPES_H
#define TYPES_H

union cell {
  void *a;
  void **aa;
  long i;
  char *s;
};
typedef union cell cell;

struct word {
  const char *name;
  int compile_only : 1;
  int immediate : 1;
  int smudge : 1;
  struct word *link;
  void *code;
  cell data[];
};

struct vmstate {
  cell *dp;
  struct word *dictionary;
  char *errstr;
  char base;
  int compiling : 1;
  int raw : 1;
  int quiet : 1;
  int errno : 14;
  cell *return_stack;
  cell *param_stack;
  cell *dictionary_stack;
};

#define IS_WORD(c) (c > ' ')

#define offsetof(TYPE, MEMBER)  __builtin_offsetof (TYPE, MEMBER)

#define CFA2WORD(cfa)  cfa - offsetof(word, code)

extern struct vmstate vmstate;

typedef struct word word;

int vm(struct vmstate *vmstate, const char *startword);

#endif
