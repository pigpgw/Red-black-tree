#include "rbtree.h"

int main(int argc, char *argv[]) {
    rbtree *t = new_rbtree();
    rbtree_insert(t,10);
    rbtree_insert(t,40);
    rbtree_insert(t,15);
    rbtree_insert(t,11);
    return 0;
}