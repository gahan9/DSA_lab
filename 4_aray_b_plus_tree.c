//
// Created by gahan on 20/8/18.
// Implement B tree then B+ tree
// Implement B+ tree of 4-aray
// Insertion and deletion
//
#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sort/utility.h"
#define TREE_ORDER 4

struct Btree{
    int total_keys;  // less than TREE_ORDER
    int key_array[TREE_ORDER];
    struct Btree *p[TREE_ORDER];  // pointer array to hold child nodes
    bool leaf_node;
}*root_node=NULL;

typedef struct root_node create_btree

int Btree_Search(int *root_subtree, int search_key){
    int i=0;
    while(i < root_subtree.current_keys_count && search_key > root_subtree.key_array[i])
        i++;
    if (root_subtree.key_array[i] == search_key)
        return s
    return 0;
}

int main(){
    return 0;
}
