#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  if (p == NULL){
    return NULL;
  }
  p->nil = (node_t *)malloc(sizeof(node_t));
  if (p->nil == NULL){
    free(p);
    return NULL;
  }

  p->nil->color = RBTREE_BLACK;
  p->nil->parent = p->nil->left = p->nil->right = NULL;

  p->root = p->nil;
  p->nil = p->nil;
  printf("트리 생성");
  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  if (newNode == NULL) return NULL;

  newNode->color = RBTREE_RED;
  newNode->key = key;
  newNode->left = t->nil;
  newNode->right = t->nil;

  node_t *x = t->root;
  node_t *y = t->nil;

  while (x != t->nil)
  {
    y = x;
    if (newNode->key < x->key){
      x = x->left;
    }
    else x = x->right;
  }

  newNode->parent = y;
  if (y == t->nil) t->root = newNode;
  else if (newNode->key < y->key) y->left = newNode;
  else y->right = newNode;

  rb_insert_fixup(t,newNode);
  return 0;
}

int rb_insert_fixup(rbtree *t,const node_t *z){
  
  return 0;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
