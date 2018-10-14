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
#include <stdbool.h>

struct node{
    int total_nodes;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
};

struct node* CreateBlankHeap();
struct node* create_node(int);
struct node* heap_union(struct node*, struct node*);
struct node* heap_insert(struct node*, struct node*);
struct node* merge_heap(struct node*, struct node*);
struct node* pop_min(struct node*);
int revert_lis(struct node*);
int display_heap(struct node*);
struct node* search_node(struct node*, int);


int count = 1;


struct node* CreateBlankHeap() {
    struct node* np;
    np = NULL;
    return np;
}


struct node * H = NULL;
struct node *Hr = NULL;


int link(struct node* y, struct node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}


struct node* create_node(int k) {
    struct node* p;  //new node;
    p = (struct node*) malloc(sizeof(struct node));
    p->total_nodes = k;
    return p;
}


struct node* merge_heap(struct node* H1, struct node* H2) {
    struct node* H = CreateBlankHeap();
    struct node* y;
    struct node* z;
    struct node* a;
    struct node* b;
    y = H1;
    z = H2;
    if (y != NULL) {
        if (z != NULL && y->degree <= z->degree)
            H = y;
        else if (z != NULL && y->degree > z->degree)
            // need some modifications here;the first and the else conditions can be merged together!!!!
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


struct node* heap_union(struct node* H1, struct node* H2) {
    struct node* prev_x;
    struct node* next_x;
    struct node* x;
    struct node* H = CreateBlankHeap();
    H = merge_heap(H1, H2);
    if (H == NULL)
        return H;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL) {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        } else {
            if (x->total_nodes <= next_x->total_nodes) {
                x->sibling = next_x->sibling;
                link(next_x, x);
            } else {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                link(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}


struct node* heap_insert(struct node* H, struct node* x) {
    struct node* H1 = CreateBlankHeap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = heap_union(H, H1);
    return H;
}


int display_heap(struct node* H) {
    struct node* p;
    if (H == NULL) {
        printf("\nHEAP EMPTY");
        return 0;
    }
    printf("\nTHE ROOT NODES ARE:-\n");
    p = H;
    while (p != NULL) {
        printf("%d", p->total_nodes);
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");
}



struct node* pop_min(struct node* H1) {
    int min;
    struct node* t = NULL;
    struct node* x = H1;
    struct node *Hr;
    struct node* p;
    Hr = NULL;
    if (x == NULL) {
        printf("\nNOTHING TO EXTRACT");
        return x;
    }
    //    int min=x->n;
    p = x;
    while (p->sibling != NULL) {
        if ((p->sibling)->total_nodes < min) {
            min = (p->sibling)->total_nodes;
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
        revert_lis(x->child);
        (x->child)->sibling = NULL;
    }
    H = heap_union(H1, Hr);
    return x;
}



int revert_lis(struct node* y) {
    if (y->sibling != NULL) {
        revert_lis(y->sibling);
        (y->sibling)->sibling = y;
    } else {
        Hr = y;
    }
}



struct node* search_node(struct node* H, int k) {
    struct node* x = H;
    struct node* p = NULL;
    if (x->total_nodes == k) {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL) {
        p = search_node(x->child, k);
    }

    if (x->sibling != NULL && p == NULL) {
        p = search_node(x->sibling, k);
    }
    return p;
}


int main(int argc, char *argv[]) {
    int i, n, m, l;
    struct node* p;
    struct node* np;
    char ch;
    printf("\nENTER THE NUMBER OF ELEMENTS:");
    scanf("%d", &n);
    printf("\nENTER THE ELEMENTS:\n");

    for (i = 1; i <= n; i++) {
        scanf("%d", &m);
        np = create_node(m);
        H = heap_insert(H, np);
    }

    display_heap(H);
    int choice;
    printf("\n######################################################"
           "\n1. Insert"
           "\n2. Display tree"
           "\n3. Exit"
           "\n######################################################\n");
    while (choice != 3) {
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nENTER THE ELEMENT TO BE INSERTED:");
                scanf("%d", &m);
                p = create_node(m);
                H = heap_insert(H, p);
                printf("\nNOW THE HEAP IS:\n");
                break;
            case 2:
                display_heap(H);
                break;
            case 3:
                printf("\nBye!\n");
                break;
            default:
                printf("\nINVALID ENTRY...TRY AGAIN....\n");
        }
    }

}

