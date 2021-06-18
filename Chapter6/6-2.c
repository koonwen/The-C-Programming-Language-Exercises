// Exercise 6-2
/* Write a program that reads a C program and prints in alphabetical
   order each group of variable names that are identical in the
   first 6 characters, but different somewhere thereafter. Don't
   count words within strings and comments. Make 6 a parameter that
   can be set from the command line */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT 6
#define MAXWORD 100

struct llnode {
  char *word;
  struct llnode *next;
};

struct tnode {
  struct llnode ll;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *talloc(void);
struct tnode *addtree(struct tnode *, char *, int);
void addword(struct tnode *, char *);
void print_list(struct llnode *);
void print_tree(struct tnode *);
int getword(char*, int);

int main(int argc, char *argv[])
{
  int c, n = DEFAULT;
  char w[MAXWORD];
  struct tnode *root;
  root = NULL;

  while (*++argv) {
    if (strcmp(*argv, "-n") == 0)
      n = atoi(*++argv);
    else {
      printf("error: usage ./a.out [-n <int>]\n");
      return 0;
    }
  }

  while ((c = getword(w, MAXWORD)) != EOF)
    if (c > 0)
      root = addtree(root, w, n);

  print_tree(root);
  return 0;
}

/* ======================IO Functions======================== */
int getword(char *word, int lim)
{
  int c, tmp;
  char *w = word;

  while (isspace(c = getc(stdin)) || c == '\n')
    ;
  
  switch (c) {
  case EOF:			/* End of file reached */
    *w = '\0';
    return EOF;
  case '"':			/* handle string constants */
    while ((c = getc(stdin)) != '"')
      ;
    return 0;
  case '/':			/* handle comments */
    if ((c = getc(stdin)) == '/')
      while ((c = getc(stdin)) != '\n')
	;
    else if (c == '*')
      while (1) {
	c = getc(stdin);
	tmp = getc(stdin);
	if (c == '*' && tmp == '/')
	  break;
	else
	  ungetc(tmp, stdin);
      }
    else
      ungetc(c, stdin);
    return 0;
  case '#':			/* handle processor control lines */
    while ((c = getc(stdin)) != '\n')
      ;
    return 0;
  default:			/* collect word */
    if (isalpha(c)) {
      for (*w++ = c; isalnum(c = getc(stdin)); )
	*w++ = c;
      ungetc(c, stdin);
      *w = '\0';
      return 1;
    }
  }
  *w = '\0';
  return 0;
}

/* ======================Tree Functions======================== */
  
/* talloc: make a tnode */
struct tnode *talloc(void)
{
  return (struct tnode *) malloc(sizeof(struct tnode));
}

/* lalloc: make a llnode */
struct llnode *lalloc(void)
{
  return (struct llnode *) malloc(sizeof(struct llnode));
}

/* addword: chain word to tnode */
void addword(struct tnode *p, char *s)
{
  struct llnode *c = &(p->ll);
  
  while (c->next != NULL)
    c = c->next;
  c->next = lalloc();
  c->next->word = strdup(s);
  c->next->next = NULL;
} 

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int n)
{
  int c;
    
  if (p == NULL) {
    p = talloc();
    p->ll.word = strdup(w);
    p->ll.next = NULL;
    p->left = p->right = NULL;
    return p;
  } else if ((c = strncmp(w, p->ll.word, n)) == 0)
    addword(p, w);
  else if (c > 0)
    p->right = addtree(p->right, w, n);
  else
    p->left = addtree(p->left, w, n);
  return p;
}

void print_list(struct llnode *l)
{
  if (l != NULL) {
    printf("%s -> ", l->word);
    print_list(l->next);
  }
}

void print_tree(struct tnode *p)
{
  if (p != NULL) {
    print_tree(p->left);
    print_list(&(p->ll));
    printf("\n");
    print_tree(p->right);
  }
}
