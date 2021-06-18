// Exercise 6-4
/* Write a program that prints distinct words in its input sorted
   into decreasing order of frequency of occurence. Precede each word
   by its count */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct tree_node {
  char *word;
  int count;
  struct tree_node *left;
  struct tree_node *right;
};

struct heap_node {
  char *word;
  int *count;
};

int getword(char *character_array, int limit, int *current_linenum);
struct tree_node *add_to_tree(struct tree_node *root, char *word, int linum, int *nodecount);
void print_tree(struct tree_node *);
void flatten_tree(struct tree_node *, struct heap_node *);
void myheapsort(struct heap_node *);

int main()
{
  int linenum = 1, nodecount = 0;
  char word[MAXWORD];
  struct tree_node *root;
  root = NULL;

  while (getword(word, MAXWORD, &linenum) != EOF)
    if (isalpha(word[0]))
      root = add_to_tree(root, word, linenum, &nodecount);

  struct heap_node *heap = (struct heap_node *) malloc((nodecount+1) * sizeof(struct heap_node));
  flatten_tree(root, heap);
  heap[0].count = &nodecount;
  int i = nodecount;
  myheapsort(heap);
  for ( ; i > 0; i--)
    printf("(%d), %s\n", *(heap[i].count), heap[i].word);
  return 0;
}

/* ======================IO Functions======================== */
int getword(char *word, int lim, int *ln)
{
  int c;
  char *w = word;

  while (isspace(c = getchar()))
    if (c == '\n')
      (*ln)++;
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

struct tree_node *add_to_tree(struct tree_node *p, char *w, int n, int *nc)
{
  int c;
  
  if (p == NULL) {
    (*nc)++;
    p = talloc();
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((c = strcmp(p->word, w)) == 0)
    p->count++;
  else if (c > 0)
    p->right = add_to_tree(p->right, w, n, nc);
  else
    p->left = add_to_tree(p->left, w, n, nc);

  return p;
}

void flatten_tree(struct tree_node *p, struct heap_node *A)
{
  static char n = 1;
  
  if (p != NULL) {
    flatten_tree(p->left, A);
    A[n].word = p->word;
    A[n].count = &(p->count);
    n++;
    flatten_tree(p->right, A);
  }
}

/* ======================Heap Functions======================== */
int left(int i)
{
  return 2*i;
}

int right(int i)
{
  return 2*i + 1;
}

int heapsize(struct heap_node *A)
{
  return *(A[0].count);
}
void swap(struct heap_node *A, int x, int y)
{
  char *s = A[x].word; int *i = A[x].count;
  A[x].word = A[y].word; A[x].count = A[y].count;
  A[y].word = s; A[y].count = i;
}

void max_heapify(struct heap_node *A, int i)
{
  int l = left(i);
  int r = right(i);
  int largest;
  if (l <= heapsize(A) && *(A[l].count) > *(A[i].count))
    largest = l;
  else
    largest = i;
  if (r <= heapsize(A) && *(A[r].count) > *(A[largest].count))
    largest = r;
  if (largest != i) {
    swap(A, largest, i);
    max_heapify(A, largest);
  }
}

void build_max_heap(struct heap_node *A)
{
  for (int i = heapsize(A)/2; i > 0; i--)
    max_heapify(A, i);
}

void myheapsort(struct heap_node *A)
{
  build_max_heap(A);
  for (int i = heapsize(A); i > 1; i--) {
    swap(A, 1, i);
    *(A[0].count)-=1;
    max_heapify(A, 1);
  }
}
  
    
