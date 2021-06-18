// Exercise 6-3
/* Write a cross-referencer that prints a list of all words in a
   document, and, for each word, a list of the line numbers on which
   it occurs. Remove noise words like "the", "and," and so on.  */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct linked_list {
  int linenum;
  struct linked_list *next;
};

struct tree_node {
  char *word;
  struct linked_list *lp;
  struct tree_node *left;
  struct tree_node *right;
};

int getword(char *character_array, int limit, int *current_linenum);
struct tree_node *add_to_tree(struct tree_node *root, char *word, int linum);
void print_tree(struct tree_node *);

int main()
{
  int linenum = 1;
  char word[MAXWORD];
  struct tree_node *root;
  root = NULL;

  while (getword(word, MAXWORD, &linenum) != EOF)
    if (isalpha(word[0]))
      root = add_to_tree(root, word, linenum);

  print_tree(root);
  return 0;
}

/* ======================IO Functions======================== */
int getword(char *word, int lim, int *ln)
{
  int c;
  char *w = word;

  while (isspace(c = getchar()))
    if (c == '\n')
      *ln+=1;
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
  return word[0];
}

/* ======================Tree Functions======================== */

struct tree_node *talloc(void)
{
  return (struct tree_node *) malloc(sizeof(struct tree_node));
}

struct linked_list *lalloc(void)
{
  return (struct linked_list *) malloc(sizeof(struct linked_list));
}

void add_to_list(struct tree_node *p, int n)
{
  struct linked_list *hold = p->lp;
  p->lp = lalloc();
  p->lp->linenum = n;
  p->lp->next = hold;
}    

struct tree_node *add_to_tree(struct tree_node *p, char *w, int n)
{
  int c;
  
  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->lp = lalloc();
    p->lp->linenum = n;
    p->lp->next = NULL;
    p->left = p->right = NULL;
  } else if ((c = strcmp(p->word, w)) == 0)
    add_to_list(p, n);
  else if (c > 0)
    p->right = add_to_tree(p->right, w, n);
  else
    p->left = add_to_tree(p->left, w, n);

  return p;
}

void print_list(struct linked_list *p)
{
  if (p != NULL) {
    print_list(p->next);
    printf("%d, ", p->linenum);
  }
}

void print_tree(struct tree_node *p)
{
  if (p != NULL) {
    print_tree(p->left);
    printf("\"%s\" appears on line(s): ", p->word);
    print_list(p->lp);
    printf("\n");
    print_tree(p->right);
  }
}
      
