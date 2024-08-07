#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void *left_rotate(rbtree *t, node_t *z);
void *right_rotate(rbtree *t, node_t *z);

rbtree *new_rbtree(void)
{
  // TODO: initialize struct if needed
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  if (p == NULL){
    return NULL;
  }
  p->nil = (node_t *)calloc(1,sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  p->root= p->nil;
  if (p->root == NULL){
    return NULL;
  }

  if (p->nil == NULL){
    free(p);
    return NULL;
  }

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
  if (t == NULL || t->root == NULL) return NULL;
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  if (newNode == NULL) return NULL;

  newNode->key = key;

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
  
  newNode->left = t->nil;
  newNode->right = t->nil;
  newNode->color = RBTREE_RED;
  rb_insert_fixup(t,newNode);
  return newNode;
}

void *left_rotate(rbtree *t, node_t *z)
{
  // TODO: implement find
  node_t *y = z->right;
  z->right = y->left;
  if (y->left != t->nil){
    y->left->parent = z;
  }
  y->parent = z->parent;
  if (z->parent == t->nil){
    t->root = y;
  }
  else if (z == z->parent->left){
    z->parent->left = y;
  }
  else {
    z->parent->right = y;
  }
  y->left = z;
  z->parent = y;
  return;
}


void *right_rotate(rbtree *t, node_t *z)
{
  node_t *y = z->left;
  z->left = y->right;
  if (y->right != t->nil){
    y->right->parent = z;
  }
  y->parent = z->parent;
  if (z->parent == t->nil){
    t->root = y;
  }
  else if (z == z->parent->right){
    z->parent->right = y;
  }
  else {
    z->parent->left = y;
  }
  y->right = z;
  z->parent = y;
}

void rb_insert_fixup(rbtree *t, node_t *z){
  node_t *y;  
  while (z->parent->color == RBTREE_RED)
  {
    if (z->parent == z->parent->parent->left){
      y = z->parent->parent->right;
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } 
      else {
        if (z == z->parent->right){
          z = z->parent;
          left_rotate(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED; 
        right_rotate(t,z->parent->parent);
      }
    }
    else {
      y = z->parent->parent->left;
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED; 
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->left){
          z = z->parent;
          right_rotate(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t,z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
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