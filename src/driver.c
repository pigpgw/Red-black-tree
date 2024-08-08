#include "rbtree.h"

int main(int argc, char *argv[]) {
    rbtree *t = new_rbtree();
    rbtree_insert(t,11);
    rbtree_insert(t,2);
    rbtree_insert(t,14);
    rbtree_insert(t,1);
    rbtree_insert(t,7);
    rbtree_insert(t,5);
    rbtree_insert(t,8);
    rbtree_insert(t,15);
    rbtree_insert(t,4);
    node_t *test_node = t->root->left->right;
    rbtree_erase(t,test_node);
    return 0;
} 