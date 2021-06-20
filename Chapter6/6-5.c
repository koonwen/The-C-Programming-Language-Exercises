// Exercise 6-5
/* Write a function undef that will remove a name and definition from
   the table maintained by lookup and install. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

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
  install("hello", "world");
  install("this", "is");
  install("a", "test");
  install("hello", "replace");
  print_tab();
  undef("hello");
  print_tab();
  return 0;
}

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
