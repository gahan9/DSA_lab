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
#include <limits.h>

#define NOT_IN_HEAP 10000

struct heap_node {
    struct heap_node *parent;
    struct heap_node *next;
    struct heap_node *child;

    unsigned int degree;
    void *value;
    struct heap_node **ref;
};

struct heap {
    struct heap_node *head;
    /* We cache the minimum of the heap.
     * This speeds up repeated peek operations.
     */
    struct heap_node *min;
};

/* item comparison function:
 * return 1 if a has higher prio than b, 0 otherwise
 */
typedef int (*heap_prio_t)(struct heap_node *a, struct heap_node *b);

static inline void heap_init(struct heap *heap) {
    // Initialize Heap
    heap->head = NULL;
    heap->min = NULL;
}

static inline void heap_node_init_ref(struct heap_node **_h, void *value) {
    // Initialize reference to heap node
    struct heap_node *h = *_h;
    h->parent = NULL;
    h->next = NULL;
    h->child = NULL;
    h->degree = NOT_IN_HEAP;
    h->value = value;
    h->ref = _h;
}

static inline void heap_node_init(struct heap_node *h, void *value) {
    // Initialize heap node
    h->parent = NULL;
    h->next = NULL;
    h->child = NULL;
    h->degree = NOT_IN_HEAP;
    h->value = value;
    h->ref = NULL;
}

static inline void *heap_node_value(struct heap_node *h) {
    // set value to heap node
    return h->value;
}

static inline int is_empty(struct heap *heap) {
    return heap->head == NULL && heap->min == NULL;
}

static inline void __heap_link(struct heap_node *root, struct heap_node *child) {
    // create child node for root node
    child->parent = root;
    child->next = root->child;
    root->child = child;
    root->degree++;
}

static inline struct heap_node *__heap_merge(struct heap_node *a, struct heap_node *b) {
    // merge two heaps
    struct heap_node *head = NULL;
    struct heap_node **pos = &head;

    while (a && b) {
        if (a->degree < b->degree) {
            *pos = a;
            a = a->next;
        } else {
            *pos = b;
            b = b->next;
        }
        pos = &(*pos)->next;
    }
    if (a)
        *pos = a;
    else
        *pos = b;
    return head;
}

/* reverse a linked list of nodes. also clears parent pointer */
static inline struct heap_node *__heap_reverse(struct heap_node *h) {
    struct heap_node *tail = NULL;
    struct heap_node *next;

    if (!h)
        return h;

    h->parent = NULL;
    while (h->next) {
        next = h->next;
        h->next = tail;
        tail = h;
        h = next;
        h->parent = NULL;
    }
    h->next = tail;
    return h;
}

static inline void __heap_min(heap_prio_t higher_prio, struct heap *heap, struct heap_node **prev, struct heap_node **node) {
    struct heap_node *_prev, *cur;
    *prev = NULL;

    if (!heap->head) {
        *node = NULL;
        return;
    }

    *node = heap->head;
    _prev = heap->head;
    cur = heap->head->next;
    while (cur) {
        if (higher_prio(cur, *node)) {
            *node = cur;
            *prev = _prev;
        }
        _prev = cur;
        cur = cur->next;
    }
}

static inline void __heap_union(heap_prio_t higher_prio, struct heap *heap, struct heap_node *h2) {
    struct heap_node *h1;
    struct heap_node *prev, *x, *next;
    if (!h2)
        return;
    h1 = heap->head;
    if (!h1) {
        heap->head = h2;
        return;
    }
    h1 = __heap_merge(h1, h2);
    prev = NULL;
    x = h1;
    next = x->next;
    while (next) {
        if (x->degree != next->degree ||
            (next->next && next->next->degree == x->degree)) {
            /* nothing to do, advance */
            prev = x;
            x = next;
        } else if (higher_prio(x, next)) {
            /* x becomes the root of next */
            x->next = next->next;
            __heap_link(x, next);
        } else {
            /* next becomes the root of x */
            if (prev)
                prev->next = next;
            else
                h1 = next;
            __heap_link(next, x);
            x = next;
        }
        next = x->next;
    }
    heap->head = h1;
}

static inline struct heap_node *__heap_extract_min(heap_prio_t higher_prio,
                                                   struct heap *heap) {
    struct heap_node *prev, *node;
    __heap_min(higher_prio, heap, &prev, &node);
    if (!node)
        return NULL;
    if (prev)
        prev->next = node->next;
    else
        heap->head = node->next;
    __heap_union(higher_prio, heap, __heap_reverse(node->child));
    return node;
}

/* insert (and reinitialize) a node into the heap */
static inline void heap_insert(heap_prio_t higher_prio, struct heap *heap, struct heap_node *node) {
    struct heap_node *min;
    node->child = NULL;
    node->parent = NULL;
    node->next = NULL;
    node->degree = 0;
    if (heap->min && higher_prio(node, heap->min)) {
        /* swap min cache */
        min = heap->min;
        min->child = NULL;
        min->parent = NULL;
        min->next = NULL;
        min->degree = 0;
        __heap_union(higher_prio, heap, min);
        heap->min = node;
    } else
        __heap_union(higher_prio, heap, node);
}

static inline void __uncache_min(heap_prio_t higher_prio, struct heap *heap) {
    struct heap_node *min;
    if (heap->min) {
        min = heap->min;
        heap->min = NULL;
        heap_insert(higher_prio, heap, min);
    }
}

/* merge addition into target */
static inline void heap_union(heap_prio_t higher_prio,
                              struct heap *target, struct heap *addition) {
    /* first insert any cached minima, if necessary */
    __uncache_min(higher_prio, target);
    __uncache_min(higher_prio, addition);
    __heap_union(higher_prio, target, addition->head);
    /* this is a destructive merge */
    addition->head = NULL;
}

static inline struct heap_node *heap_peek(heap_prio_t higher_prio,
                                          struct heap *heap) {
    if (!heap->min)
        heap->min = __heap_extract_min(higher_prio, heap);
    return heap->min;
}

static inline struct heap_node *heap_take(heap_prio_t higher_prio,
                                          struct heap *heap) {
    struct heap_node *node;
    if (!heap->min)
        heap->min = __heap_extract_min(higher_prio, heap);
    node = heap->min;
    heap->min = NULL;
    if (node)
        node->degree = NOT_IN_HEAP;
    return node;
}

static inline void heap_decrease(heap_prio_t higher_prio, struct heap *heap,
                                 struct heap_node *node) {
    struct heap_node *parent;
    struct heap_node **tmp_ref;
    void *tmp;

    /* node's priority was decreased, we need to update its position */
    if (!node->ref)
        return;
    if (heap->min != node) {
        if (heap->min && higher_prio(node, heap->min))
            __uncache_min(higher_prio, heap);
        /* bubble up */
        parent = node->parent;
        while (parent && higher_prio(node, parent)) {
            /* swap parent and node */
            tmp = parent->value;
            parent->value = node->value;
            node->value = tmp;
            /* swap references */
            if (parent->ref)
                *(parent->ref) = node;
            *(node->ref) = parent;
            tmp_ref = parent->ref;
            parent->ref = node->ref;
            node->ref = tmp_ref;
            /* step up */
            node = parent;
            parent = node->parent;
        }
    }
}


struct token {
    int prio;
    const char *str;
};

#define LENGTH(a) (sizeof(a) / sizeof(a[0]))

struct token tokens1[] = {
        {200,  "!"}
};

struct token tokens2[] = {
    {103, "the Force"},
    {104, "be"},
    {112, "with"},
    {120, "you!"},
    {100, "\nMay"}
};

#define line "\n==================================="

struct token layout[] = {
        {90,  line},
        {-2,  line},
        {200, line},
        {201, "\n\n"}
};


struct token title[] = {
        {1000, "\nStar Trek"},
        {120,  "\nStar Wars"}
};


static int token_cmp(struct heap_node *_a, struct heap_node *_b) {
    struct token *a, *b;
    a = (struct token *) heap_node_value(_a);
    b = (struct token *) heap_node_value(_b);
    return a->prio < b->prio;
}

static void add_token(struct heap *heap, struct token *tok) {
    struct heap_node *hn = malloc(sizeof(struct heap_node));
    heap_node_init(hn, tok);
    heap_insert(token_cmp, heap, hn);
}

static void add_token_ref(struct heap *heap, struct token *tok,
                          struct heap_node **hn) {
    *hn = malloc(sizeof(struct heap_node));
    heap_node_init_ref(hn, tok);
    heap_insert(token_cmp, heap, *hn);
}

static void add_tokens(struct heap *heap, struct token *tok, int len) {
    int i;
    for (i = 0; i < len; i++)
        add_token(heap, tok + i);
}

int main(int argc __attribute__((unused)), char **argv __attribute__((unused))) {
    struct heap h1, h2, h3;
    struct heap_node *hn;
    struct heap_node *t1, *t2, *b1, *b2;
    struct token *tok;

    heap_init(&h1);
    heap_init(&h2);
    heap_init(&h3);

    int i;
    for (i = 0; i < LENGTH(tokens2); i++)
        struct heap_node *hn = malloc(sizeof(struct heap_node));
        heap_node_init(hn, tok);
        heap_insert(token_cmp, h2, hn);

    add_tokens(&h2, tokens2, LENGTH(tokens2));

    add_token_ref(&h3, title, &t1);
    add_token_ref(&h2, title + 1, &t2);

    heap_union(token_cmp, &h2, &h3);
    heap_union(token_cmp, &h1, &h2);

    heap_union(token_cmp, &h1, &h3);

    title[0].prio = -1;
    title[1].prio = 99;

    heap_decrease(token_cmp, &h1, t1);
    heap_decrease(token_cmp, &h1, t2);

    printf("htest:\n");
    while (!is_empty(&h1)) {
        hn = heap_take(token_cmp, &h1);
        tok = heap_node_value(hn);
        printf("%s ", tok->str);
        free(hn);
    }
    return 0;
}