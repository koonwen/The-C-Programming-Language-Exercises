// Exercise 6-6
/* Implement a simple version of the #define processor (i.e., no
   arguments) suitable for use with C programs, based on the routes
   of this section. You may also find getch and ungetch helpful */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100

int getword(void);
int process_word(void);
int process_macro(void);

struct nlist {			/* table entry */
  struct nlist *next;		/* pointer to next entry */
  char *name;			/* defined name */
  char *defn;			/* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int undef(char *);
void print_tab(void);

int main()
{
  int c;
  while ((c = getword()) != EOF) {
    if (c == '#') {
      putchar(c);
      process_macro();
    }
    else
      process_word();
  }
  print_tab();
  return 0;
}

/* =====================IO FUNCTIONS========================= */
static char s[MAXWORD];
/* getword: reads in words and prints out whatever was read in */
int getword()
{
  int lim = MAXWORD-1;
  int c;
  char *w = s;

  while (isspace(c = getchar()))
    putchar(c);
  if (c == '\n')
    return c;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++)
    if (!isalnum(*w = getchar())) {
      ungetc(*w, stdin);
      break;
    }
  *w = '\0';
  return w[0];
}

/* process_macro: get macro */
int process_macro(void)
{
  int c;
  static char name[MAXWORD];
  static char defn[MAXWORD];
  c = getword();
  if (strcmp(s, "define") != 0) {
    fputs(s, stdout);
    return c;
  }
  fputs(s, stdout);
  
  c = getword();
  fputs(s, stdout);
  strcpy(name, s);
  
  c = getword();
  fputs(s, stdout);
  strcpy(defn, s);
  
  install(name, defn);

  return c;
} 

/* process_line: print line while replacing macros */
int process_word(void)
{
  int c;
  struct nlist *p;
  if ((p = lookup(s)) != NULL)
      fputs(p->defn, stdout);
    else
      fputs(s, stdout);
  return c;
}

/* =====================HASH FUNCTIONS========================= */
/* hash: form hash value for string */
unsigned hash(char *s)
{
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(np->name, s) == 0)
      return np;		/* found */
  return NULL;			/* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) { /* not found */
    np = (struct nlist *) malloc(sizeof(struct nlist));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else			/* found */
    free((void *) np->defn);
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

/* undef: drop (name, defn) in hashtab */
int undef(char *name)
{
  struct nlist *np, *pp;
  pp = NULL;

  unsigned hashval = hash(name);
  for (np = hashtab[hashval]; np != NULL; pp = np, np = np->next)
    if (strcmp(name, np->name) == 0) {
      if (pp == NULL)		/* name and defn is first entry */
	hashtab[hashval] = np->next;
      else			/* name and defn is middle */
	pp->next = np->next;
      free((void *) np);
      return 1;
    }
  return -1;
}

/* print_nlist: print out nlist representation */
void print_nlist(struct nlist *p)
{
  for ( ; p != NULL; p = p->next)
    printf("(%s, %s) -> ", p->name, p->defn);
}

/* print_tab: print out current hashtable representation */
void print_tab(void)
{
  printf("\n_______TABLE________\n");
  for (int i = HASHSIZE; i > 0; i--) {
    printf("[] -> ");
    print_nlist(hashtab[i-1]);
    printf("\n");
  }
}
