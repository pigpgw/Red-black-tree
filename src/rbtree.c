#include "rbtree.h"

#include <stdlib.h>
void left_rotate(rbtree* t, node_t* x);
void right_rotate(rbtree* t, node_t* y);
void rb_transplant(rbtree* t, node_t* u, node_t* v);
void rb_insert_fixup(rbtree* t, node_t* z);
void rb_delete_fixup(rbtree* t, node_t* x);
node_t* rb_min(rbtree* t, node_t* cur);
node_t* rb_max(rbtree* t, node_t* cur);
node_t inorder(rbtree *t,node_t *cur);

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t * nil = (node_t*)calloc(1,sizeof(node_t));

  nil->color = RBTREE_BLACK;
  nil->key = NULL;

  p->nil = nil;
  p->root = nil;
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  while(t->root != t->nil)
    rbtree_erase(t,t->root);
  free(t->nil);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t* z = (node_t*)malloc(sizeof(node_t));
  z->key = key;

  node_t* x,*y;
  x = t->root;
  y = t->nil; 
  while (x!=t->nil)
  {
    y=x;
    if(z->key < x->key)
      x = x->left;
    else 
      x = x->right;
    
  }
  z->parent = y;
  if( y == t->nil)
    t->root = z;
  else if(z->key < y->key)
    y->left = z;
  else
    y->right = z;
  
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  rb_insert_fixup(t,z);
  
  return z;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t* temp = t->root;
  while(temp != t->nil)
  {
    if(temp->key == key)
      return temp;
    else if (temp->key > key)
      temp = temp->left;
    else
      temp = temp->right; 
  }
  return NULL;
}

node_t* rb_min(rbtree* t, node_t* cur)
{
  while(cur->left != t->nil)
    cur = cur->left;
  return cur;
}
node_t* rb_max(rbtree* t, node_t* cur)
{
  while(cur->right != t->nil)
    cur = cur->right;
  return cur;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return rb_min(t,t->root);
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return rb_max(t,t->root);
}

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  node_t*y,*x;
  y=z;
  color_t y_original_color = y->color;

  if(z->left == t->nil){
    x = z->right;
    rb_transplant(t,z,z->right);
  }
  else if (z->right == t->nil){
    x = z->left;
    rb_transplant(t,z,z->left);
  }
  else
  {
    y = rb_min(t,z->right);
    y_original_color = y->color;
    x = y->right;
    
    if(y != z->right){
      rb_transplant(t,y,y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    else
      x->parent = y;
    rb_transplant(t,z,y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if(y_original_color == RBTREE_BLACK)
    rb_delete_fixup(t,x);
  free(z);
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  
  return 0;
}

node_t inorder(rbtree *t,node_t *cur){
  node_t *inorder_node = cur;
  if (inorder_node != NULL){
    inorder(t,cur->left);
    inorder_node = cur->key;
    inorder(t,cur->right);
  }
  return *inorder_node;
}

void left_rotate(rbtree* t, node_t* x)
{
  //Done
  node_t* y;
  y = x->right;
  x->right = y->left;
  if(y->left != t->nil)
    y->left->parent = x;
  

  y->parent = x->parent;
  if(x->parent == t->nil)
    t->root = y;
  else if ( x == x->parent->left)
    x->parent->left = y;
  else 
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}
void right_rotate(rbtree* t, node_t* y)
{
  //Done
  node_t* x;
  x = y->left;
  y->left = x->right;
  if(x->right != t->nil)
    x->right->parent = y;

  x->parent = y->parent;
  if(y->parent == t->nil)
    t->root = x;
  else if ( y == y->parent->left)
    y->parent->left = x;
  else 
    y->parent->right = x;
  
  x->right = y;
  y->parent = x;
}
void rb_transplant(rbtree* t, node_t* u, node_t* v)
{
  if(u->parent == t->nil)
    t->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
}
void rb_insert_fixup(rbtree* t, node_t* z)
{ 
  node_t* y;
  while(z->parent->color == RBTREE_RED){
    if(z->parent == z->parent->parent->left)
    {
      y = z->parent->parent->right;
      if(y->color == RBTREE_RED)
      {
         z->parent->color = RBTREE_BLACK;
         y->color = RBTREE_BLACK;
         z->parent->parent->color = RBTREE_RED;
         z = z->parent->parent;
      }
      else
      {
        if(z== z->parent->right)
        {
          z = z->parent;
          left_rotate(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t,z->parent->parent);
      }
    }
    else{
      y = z->parent->parent->left;
      if(y->color == RBTREE_RED)
      {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else
      {
        if(z == z->parent->left)
        {
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

void rb_delete_fixup(rbtree* t, node_t* x){
  node_t* w;
  while(x != t->root && x->color == RBTREE_BLACK)
  {
    if(x == x->parent->left)
    {
      w = x->parent->right;

      if(w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t,x->parent);
        w = x->parent->right;
      }
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else
      {
        if( w->right->color == RBTREE_BLACK)
        {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t,w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t,x->parent);
        x = t->root;
      }
    }
    else
    {
      w = x->parent->left;

      if( w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t,x->parent);
        w = x->parent->left;
      }
      if(w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK)
      {
        w->color =RBTREE_RED;
        x = x->parent;
      }
      else
      { 
        if(w->left->color == RBTREE_BLACK)
        {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t,w);
          w= x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t,x->parent);
        x= t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}