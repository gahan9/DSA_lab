//
// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Implementing Binomial Heap

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define DEBUG  1

#include "../utils/utility.h"

struct node {
    // Node for binomial heap
    int n;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *sibling;
};

int count = 1;

struct node *MAKE_bin_HEAP() {
    struct node *np;
    np = NULL;
    return np;
}

struct node *H = NULL;
struct node *Hr = NULL;

int linkBinomialHeap(struct node *y, struct node *z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

struct node *CreateNode(int k) {
    struct node *p;//new node;
    p = (struct node *) malloc(sizeof(struct node));
    p->n = k;
    return p;
}

struct node *BinomialHeapMerge(struct node *H1, struct node *H2) {
    struct node *H = MAKE_bin_HEAP();
    struct node *y;
    struct node *z;
    struct node *a;
    struct node *b;
    y = H1;
    z = H2;
    if (y != NULL) {
        if (z != NULL && y->degree <= z->degree)
            H = y;
        else if (z != NULL && y->degree > z->degree)
            /* need some modifications here;the first and the else conditions can be merged together!!!! */
            H = z;
        else
            H = y;
    } else
        H = z;
    while (y != NULL && z != NULL) {
        if (y->degree < z->degree) {
            y = y->sibling;
        } else if (y->degree == z->degree) {
            a = y->sibling;
            y->sibling = z;
            y = a;
        } else {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

struct node *BinomialHeapUnion(struct node *H1, struct node *H2) {
    struct node *prev_x;
    struct node *next_x;
    struct node *x;
    struct node *H = MAKE_bin_HEAP();
    H = BinomialHeapMerge(H1, H2);
    if (H == NULL)
        return H;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL) {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
                                              && (next_x->sibling)->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        } else {
            if (x->n <= next_x->n) {
                x->sibling = next_x->sibling;
                linkBinomialHeap(next_x, x);
            } else {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                linkBinomialHeap(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}

struct node *BinomialHeapInsert(struct node *H, struct node *x) {
    struct node *H1 = MAKE_bin_HEAP();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = BinomialHeapUnion(H, H1);
    return H;
}

//int NodeExplorer(struct node *n){
//    write_log("Exploring node: %d\n", n->n);
//    if (n == NULL){
//        printf("Empty Node!!!\n");
//        return 0;
//    }
//    else{
//        printf("%d, ", n->n);
//        if (p->sibling != NULL)
//            printf("\n-->");
//    }
//    printf("\n");
//}

int DisplayBinomialHeap(struct node *H) {
    // TODO: Remove redundant print... do pretty print of heap
//    printf("\n");
    struct node *p;
    if (H == NULL) {
        printf("\nHEAP EMPTY");
        return 0;
    }
//    printf("\nTHE HEAP:-\n");
    p = H;
    while (p != NULL) {
        printf("[%d]", p->n);
        if (p->sibling != NULL) {
//            printf("Parent: %d", p->parent->n);
            printf("------------>");
            DisplayBinomialHeap(p->sibling);
        }

        if (p->child != NULL){
            printf("\nParent: of %d is %d\n",p->child->n, p->n);
            DisplayBinomialHeap(p->child);
        }
        else if (p->child == NULL){
            printf("---[leaf node] Nothing to explore for this node.");
        }
        p = p->sibling;
    }
    printf("\n");
    return 1;
}

int RevertList(struct node *y) {
    if (y->sibling != NULL) {
        RevertList(y->sibling);
        (y->sibling)->sibling = y;
    } else {
        Hr = y;
    }
}

struct node *ExtractMinBinomialHeap(struct node *H1) {
    int min;
    struct node *t = NULL;
    struct node *x = H1;
    struct node *Hr;
    struct node *p;
    Hr = NULL;
    if (x == NULL) {
        printf("\nNOTHING TO EXTRACT");
        return x;
    }
    //    int min=x->n;
    p = x;
    while (p->sibling != NULL) {
        if ((p->sibling)->n < min) {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if (t == NULL && x->sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;
    if (x->child != NULL) {
        RevertList(x->child);
        (x->child)->sibling = NULL;
    }
    H = BinomialHeapUnion(H1, Hr);
    return x;
}

struct node *FIND_NODE(struct node *H, int k) {
    struct node *x = H;
    struct node *p = NULL;
    if (x->n == k) {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL) {
        p = FIND_NODE(x->child, k);
    }

    if (x->sibling != NULL && p == NULL) {
        p = FIND_NODE(x->sibling, k);
    }
    return p;
}

int bin_HEAP_DECREASE_KEY(struct node *H, int i, int k) {
    int temp;
    struct node *p;
    struct node *y;
    struct node *z;
    p = FIND_NODE(H, i);
    if (p == NULL) {
        printf("\nINVALID CHOICE OF KEY TO BE REDUCED");
        return 0;
    }
    if (k > p->n) {
        printf("\nSORY!THE NEW KEY IS GREATER THAN CURRENT ONE");
        return 0;
    }
    p->n = k;
    y = p;
    z = p->parent;
    while (z != NULL && y->n < z->n) {
        temp = y->n;
        y->n = z->n;
        z->n = temp;
        y = z;
        z = z->parent;
    }
    printf("\nKEY REDUCED SUCCESSFULLY!");
}

int bin_HEAP_DELETE(struct node *H, int k) {
    struct node *np;
    if (H == NULL) {
        printf("\nHEAP EMPTY");
        return 0;
    }

    bin_HEAP_DECREASE_KEY(H, k, -1000);
    np = ExtractMinBinomialHeap(H);
    if (np != NULL)
        printf("\nNODE DELETED SUCCESSFULLY");
}

int main(int argc, char *argv[]) {
    int i, n, m, l;
    struct node *p;
    struct node *np;
    char ch;
    int number_of_elements;
    if (atoi(argv[1]))
        number_of_elements = atoi(argv[1]);
    else
        number_of_elements = 5;  // elements to be pre filled
    for (i = 1; i <= number_of_elements; i++) {
        m = rand() % 10;
        printf("Inserting: %d\n", m);
        np = CreateNode(m);
        H = BinomialHeapInsert(H, np);
    }
//    DisplayBinomialHeap(H);
    do {
        printf("\n###################***MENU***#########################"
               "\n1. Insert"
               "\n2. Extract Minimum key Node"
               "\n3. Display Binomial Heap"
               "\n4. Exit"
               "\n######################################################\n");
        scanf("%d", &l);
        switch (l) {
            case 1:
                printf("\n[INSERT]:");
                scanf("%d", &m);
                write_log("Inserting: %d", m);
                p = CreateNode(m);
                H = BinomialHeapInsert(H, p);
                printf("\n<<<HEAP>>>");
                DisplayBinomialHeap(H);
                scanf("%c", &ch);
                break;
            case 2:
                printf("\nExtracting min key node");
                p = ExtractMinBinomialHeap(H);
                if (p != NULL)
                    printf("\nExtracted node is %d", p->n);
                printf("\n<<<HEAP>>>");
                DisplayBinomialHeap(H);
                scanf("%c", &ch);
                break;
            case 3:
                printf("\n<<<HEAP>>>");
                DisplayBinomialHeap(H);
                break;
            case 4:
                printf("\nGratitude! for interacting with program\n");
                break;
            default:
                printf("\nOoops.... that's invalid choice\n");
                break;
        }
    } while (l != 4);
}
