//
// Created by gahan on 20/8/18.
// Implement B tree then B+ tree
// Implement B+ tree of 4-aray
// Insertion and deletion
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "sort/constant.h"
#include "sort/utility.h"
#define TREE_ORDER 4
#define MAX_KEYS 4


typedef struct BTree_node {
    int total_keys;    /* how many keys does this node contain? */
    bool is_leaf;     /* is this a leaf node? */
    int keys[MAX_KEYS];
    struct BTree_node *kids[MAX_KEYS];  /* kids[i] holds nodes < keys[i] */
}*Btree;


/* create a new empty tree */
Btree create(void) {
    Btree b;
    b = malloc(sizeof(*b));
    assert(b);

    b->is_leaf = true;
    b->total_keys = 0;
    return b;
}

/* return smallest index i in sorted array such that search_key <= key_array[i] */
/* (or max_keys if there is no such index) */
static int searchKey(int max_keys, const int *key_array, int search_key){
    int low = -1, high = max_keys, mid;

    // bisaction for key lookup
    while(low + 1 < high) {
        mid = (low + high)/2;
        if(key_array[mid] == search_key) {
            return mid;
        } else if(key_array[mid] < search_key) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return high;
}

int Btree_Search(Btree b, int search_key){
    int position;
    // check for empty tree
    if(b->total_keys == 0) {
        return 0;
    }

    // seek for smallest position that key fits before
    position = searchKey(b->total_keys, b->keys, search_key);

    if(position < b->total_keys && b->keys[position] == search_key) {
        return 1;
    } else {
        return(!b->is_leaf && Btree_Search(b->kids[position], search_key));
    }
}


/* insert a new key into a tree */
/* returns new right sibling if the node splits */
/* and puts the median in *median */
/* else returns 0 */
static Btree _insert(Btree b, int key, int *median) {
    int position;
    int mid;
    Btree b2;

    position = searchKey(b->total_keys, b->keys, key);

    if(position < b->total_keys && b->keys[position] == key) {
        // no balancing require
        return 0;
    }

    if(b->is_leaf) {
        // everybody above position shifts up one space
        memmove(&b->keys[position+1], &b->keys[position], sizeof(*(b->keys)) * (b->total_keys - position));
        b->keys[position] = key;
        b->total_keys++;

    }
    else {

        // insert in child node
        b2 = _insert(b->kids[position], key, &mid);

        // maybe insert a new key in b (if require)
        if(b2) {

            // every key above position shifts up one space
            memmove(&b->keys[position+1], &b->keys[position], sizeof(*(b->keys)) * (b->total_keys - position));
            // new kid goes in position + 1
            memmove(&b->kids[position+2], &b->kids[position+1], sizeof(*(b->keys)) * (b->total_keys - position));

            b->keys[position] = mid;
            b->kids[position+1] = b2;
            b->total_keys++;
        }
    }

    /* we waste a tiny bit of space by splitting now
     * instead of on next insert */
    if(b->total_keys >= MAX_KEYS) {
        mid = b->total_keys/2;

        *median = b->keys[mid];

        /* make a new node for keys > median */
        /* picture is:
         *
         *      3 5 7
         *      A B C D
         *
         * becomes
         *          (5)
         *      3        7
         *      A B      C D
         */
        b2 = malloc(sizeof(*b2));

        b2->total_keys = b->total_keys - mid - 1;
        b2->is_leaf = b->is_leaf;

        memmove(b2->keys, &b->keys[mid+1], sizeof(*(b->keys)) * b2->total_keys);
        if(!b->is_leaf) {
            memmove(b2->kids, &b->kids[mid+1], sizeof(*(b->kids)) * (b2->total_keys + 1));
        }

        b->total_keys = mid;

        return b2;
    } else {
        return 0;
    }
}


void Btree_insert(Btree b, int key) {
    Btree b1;   /* new left child */
    Btree b2;   /* new right child */
    int median;

    b2 = _insert(b, key, &median);

    if(b2) {
        /* basic issue here is that we are at the root */
        /* so if we split, we have to make a new root */

        b1 = malloc(sizeof(*b1));
        assert(b1);

        /* copy root to b1 */
        memmove(b1, b, sizeof(*b));

        /* make root point to b1 and b2 */
        b->total_keys = 1;
        b->is_leaf = 0;
        b->keys[0] = median;
        b->kids[0] = b1;
        b->kids[1] = b2;
    }
}


int main(int argc, char *argv[]){
    // TODO: Sequential Search
    // TODO: pretty print
    int no_of_elements;
    if (atoi(argv[1]))
        no_of_elements = atoi(argv[1]);
    else
        no_of_elements = 100;
    Btree b;
    int i;
    b = create();
    assert(b);

    for(i = 1; i <= no_of_elements; i++) {
        assert(Btree_Search(b, i) == 0);
        Btree_insert(b, i);
        assert(Btree_Search(b, i) == 1);
    }
    for(i=0; i < MAX_KEYS-1; i++) {
        if (b->is_leaf && b->keys[i]) {
            printf("| %d ", b->keys[i]);
        }
        else {
            for(int j=0; j < MAX_KEYS-1; j++) {
                printf("| %d ", b->kids[i]->keys[j]);
            }
        }
    }
    printf("| \n");
    return 0;
}
