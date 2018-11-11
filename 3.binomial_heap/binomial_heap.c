//
// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Implementing Binomial Heap

#include<stdio.h>
#include<malloc.h>
#define DEBUG  1
#include "../utils/utility.h"

struct node {
    int n;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *sibling;
};


struct node *CreateBinomialHeap() {
    struct node *np;
    np = NULL;
    return np;
}

int b_link(struct node *a, struct node *b) {
    a->parent = b;
    a->sibling = b->child;
    b->child = a;
    b->degree = b->degree + 1;
}

struct node *CreateNode(int k) {
    struct node *p; //new node;
    p = (struct node *) malloc(sizeof(struct node));
    p->n = k;
    write_log("Node created with element: %d", k);
    return p;
}
int count = 1;

struct node *H = NULL;
struct node *Hr = NULL;

int rlist(struct node *a) {
    if (a->sibling != NULL) {
        rlist(a->sibling);
        (a->sibling)->sibling = a;
    } else {
        Hr = a;
    }
}

int DisplayBinomialHeap(struct node *H) {
    struct node *p;
    if (H == NULL) {
        printf("\nheap empty!!!");
        return 0;
    }
    printf("\n-:[ROOT NODES]:-\n");
    p = H;
    while (p != NULL) {
        printf("%d", p->n);
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");

}


struct node *MergeBinomialHeap(struct node *heap1, struct node *heap2) {
    write_log("Merging Binomial Heaps");
//    struct node *H = CreateBinomialHeap();
    if (heap1 != NULL) {
        // elect heap accordingly Min Heap Condition
        if (heap2 != NULL && heap1->degree > heap2->degree)
            H = heap2;
        else
            H = heap1;
    }
    else
        H = heap2;

    while (heap1 != NULL && heap2 != NULL) {
        if (heap1->degree < heap2->degree) {
            heap1 = heap1->sibling;
        }
        else if (heap1->degree == heap2->degree) {
            heap1 = heap2->sibling;
            heap1->sibling = heap2;
        } else {
            heap2 = heap2->sibling;
            heap2->sibling = heap1;
        }
    }
    write_log("binomial heap Merged successfully");
    return H;
}

struct node *UnionBinomialHeap(struct node *H1, struct node *H2) {
    struct node *x_prev;
    struct node *x_next;
    struct node *x;
//    struct node *H = CreateBinomialHeap();
    H = MergeBinomialHeap(H1, H2);
    if (H == NULL)
        return H;
    x_prev = NULL;
    x = H;
    x_next = x->sibling;
    while (x_next != NULL) {
        if ((x->degree != x_next->degree) || ((x_next->sibling != NULL) && (x_next->sibling)->degree == x->degree)) {
            x_prev = x;
            x = x_next;
        }
        else {
            if (x->n <= x_next->n) {
                x->sibling = x_next->sibling;
                b_link(x_next, x);
            }
            else {
                if (x_prev == NULL)
                    H = x_next;
                else
                    x_prev->sibling = x_next;
                b_link(x, x_next);
                x = x_next;
            }
        }
        x_next = x->sibling;
    }
    return H;
}

struct node *InsertBinomialHeap(struct node *H, struct node *x) {
    struct node *H1 = CreateBinomialHeap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = UnionBinomialHeap(H, H1);
    write_log("Node successfully inserted in to Binomial Heap");
    return H;
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
// int min=x->n;
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
        rlist(x->child);
        (x->child)->sibling = NULL;
    }
    H = UnionBinomialHeap(H1, Hr);
    return x;
}

struct node *Search(struct node *H, int k) {
    struct node *x = H;
    struct node *p = NULL;
    if (x->n == k) {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL) {
        p = Search(x->child, k);
    }
    if (x->sibling != NULL && p == NULL) {
        p = Search(x->sibling, k);
    }
    return p;
}

int dec_key(struct node *H, int i, int k) {
    int temp;
    struct node *p;
    struct node *a;
    struct node *b;
    p = Search(H, i);
    if (p == NULL) {
        printf("\nINVALID CHOICE OF key TO BE REDUCED");
        return 0;
    }
    if (k > p->n) {
        printf("\nSORa!THE NEW key IS GREATER THAN CURRENT ONE");
        return 0;
    }
    p->n = k;
    a = p;
    b = p->parent;
    while (b != NULL && a->n < b->n) {
        temp = a->n;
        a->n = b->n;
        b->n = temp;
        a = b;
        b = b->parent;
    }
    printf("\nkey REDUCED SUCCESSFULLa!");
}

int BinomialHeapDelete(struct node *H, int k) {
    struct node *np;
    if (H == NULL) {
        printf("\nHEAP EMPTa");

        return 0;
    }
    dec_key(H, k, -1000);
    np = ExtractMinBinomialHeap(H);
    if (np != NULL)
        printf("\nNODE DELETED SUCCESSFULLa");
}

int main() {
    int i, n, m, l, choice;
    struct node *p;
    struct node *np;
    char sub_choice;
//    printf("\nENTER THE NUMBER OF ELEMENTS:");
//    scanf("%d", &n);
//    printf("\nENTER THE ELEMENTS:\n");
//    for (i = 1; i <= n; i++) {
//        printf("[INSERT]: ");
//        scanf("%d\n", &m);
//        write_log("inserting : %d\n", m);
//        np = CreateNode(m);
//        H = InsertBinomialHeap(H, np);
//    }
//    write_log("Displaying initial heap:");
//    DisplayBinomialHeap(H);
    do {
        printf("\n###################***MENU***#########################"
               "\n1. Insert"
               "\n2. Extract Minimum key Node"
               "\n3. Decrease Node key"
               "\n4. Delete Node"
               "\n5. Display Binomial Heap"
               "\n6. Exit"
               "\n######################################################\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                do {
                    printf("\n[INSERT]:");
                    scanf("%d", &m);
                    write_log("Inserting: %d", m);
                    p = CreateNode(m);
                    H = InsertBinomialHeap(H, p);
                    printf("\n<<<HEAP>>>");
                    DisplayBinomialHeap(H);
                    printf("\nInsert More? (y/n): ");
                    fflush(stdin);
                    scanf("%c", &sub_choice);
                } while (sub_choice == 'Y' || sub_choice == 'y');
                break;
            case 2:
                do {
                    printf("\nEXTRACTING THE MINIMUM key NODE");
                    p = ExtractMinBinomialHeap(H);
                    if (p != NULL)
                        printf("\nTHE EXTRACTED NODE IS %d", p->n);
                    printf("\n<<<HEAP>>>\n");
                    DisplayBinomialHeap(H);
                    printf("\nExtract More?(y/n): ");
                    fflush(stdin);
                    scanf("%c", &sub_choice);
                } while (sub_choice == 'Y' || sub_choice == 'y');
                break;
            case 3:
                do {
                    printf("\n[NODE KEY TO DECREASE]");
                    scanf("%d", &m);
                    printf("\n[NEW KEY]: ");
                    scanf("%d", &l);
                    dec_key(H, m, l);
                    printf("\n<<<HEAP>>>");
                    DisplayBinomialHeap(H);
                    printf("\nDecrease More?(ay/n): ");
                    fflush(stdin);
                    scanf("%c", &sub_choice);
                } while (sub_choice == 'Y' || sub_choice == 'y');
                break;
            case 4:
                do {
                    printf("\n[DELETE]: ");
                    scanf("%d", &m);
                    BinomialHeapDelete(H, m);
                    printf("\nDelete More?(y/n): ");
                    fflush(stdin);
                    scanf("%c", &sub_choice);
                } while (sub_choice == 'Y' || sub_choice == 'y');
                break;
            case 5:
                DisplayBinomialHeap(H);
                break;
            case 6:
                printf("\nGratitude! for interacting with program\n");
                break;
            default:
                printf("\nOoops.... that's invalid choice\n");
        }
    } while (choice != 6);
    return 0;
}
