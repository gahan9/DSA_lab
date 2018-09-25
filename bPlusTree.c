#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifdef _WIN32
#define bool char
#define false 0
#define true 1
#endif

// Default order is 4.
#define DEFAULT_ORDER 4
#define BUFFER_SIZE 256

typedef struct record {
	int value;
} record;

typedef struct node {
	void ** pointers;
	int * keys;
	struct node * parent;
	bool is_leaf;
	int num_keys;
	struct node * next; // Used for queue.
} node;


int order = DEFAULT_ORDER;

node * queue = NULL;

bool verbose_output = false;


void license_notice(void);
void usage_1(void);
void usage_2(void);
void usage_3(void);
void enqueue(node * new_node);
node * dequeue(void);
int height(node * const root);
int path_to_root(node * const root, node * child);
void print_leaves(node * const root);
void print_tree(node * const root);
void find_and_print(node * const root, int key, bool verbose);
void find_and_print_range(node * const root, int range1, int range2, bool verbose);
int find_range(node * const root, int key_start, int key_end, bool verbose,
		int returned_keys[], void * returned_pointers[]);
node * find_leaf(node * const root, int key, bool verbose);
record * find(node * root, int key, bool verbose, node ** leaf_out);
int cut(int length);

// Insertion.

record * make_record(int value);
node * make_node(void);
node * make_leaf(void);
int get_left_index(node * parent, node * left);
node * insert_into_leaf(node * leaf, int key, record * pointer);
node * insert_into_leaf_after_splitting(node * root, node * leaf, int key,
                                        record * pointer);
node * insert_into_node(node * root, node * parent,
		int left_index, int key, node * right);
node * insert_into_node_after_splitting(node * root, node * parent,
                                        int left_index,
		int key, node * right);
node * insert_into_parent(node * root, node * left, int key, node * right);
node * insert_into_new_root(node * left, int key, node * right);
node * start_new_tree(int key, record * pointer);
node * insert(node * root, int key, int value);

void enqueue(node * new_node) {
	node * c;
	if (queue == NULL) {
		queue = new_node;
		queue->next = NULL;
	}
	else {
		c = queue;
		while(c->next != NULL) {
			c = c->next;
		}
		c->next = new_node;
		new_node->next = NULL;
	}
}


node * dequeue(void) {
	node * n = queue;
	queue = queue->next;
	n->next = NULL;
	return n;
}


void print_leaves(node * const root) {
	if (root == NULL) {
		printf("Empty tree.\n");
		return;
	}
	int i;
	node * c = root;
	while (!c->is_leaf)
		c = c->pointers[0];
	while (true) {
		for (i = 0; i < c->num_keys; i++) {
			if (verbose_output)
				printf("%p ", c->pointers[i]);
			printf("%d ", c->keys[i]);
		}
		if (verbose_output)
			printf("%p ", c->pointers[order - 1]);
		if (c->pointers[order - 1] != NULL) {
			printf(" | ");
			c = c->pointers[order - 1];
		}
		else
			break;
	}
	printf("\n");
}

int height(node * const root) {
	int h = 0;
	node * c = root;
	while (!c->is_leaf) {
		c = c->pointers[0];
		h++;
	}
	return h;
}

int path_to_root(node * const root, node * child) {
	int length = 0;
	node * c = child;
	while (c != root) {
		c = c->parent;
		length++;
	}
	return length;
}

void print_tree(node * const root) {

	node * n = NULL;
	int i = 0;
	int rank = 0;
	int new_rank = 0;

	if (root == NULL) {
		printf("Empty tree.\n");
		return;
	}
	queue = NULL;
	enqueue(root);
	while(queue != NULL) {
		n = dequeue();
		if (n->parent != NULL && n == n->parent->pointers[0]) {
			new_rank = path_to_root(root, n);
			if (new_rank != rank) {
				rank = new_rank;
				printf("\n");
			}
		}
		if (verbose_output)
			printf("(%p)", n);
		for (i = 0; i < n->num_keys; i++) {
			if (verbose_output)
				printf("%p ", n->pointers[i]);
			printf("%d ", n->keys[i]);
		}
		if (!n->is_leaf)
			for (i = 0; i <= n->num_keys; i++)
				enqueue(n->pointers[i]);
		if (verbose_output) {
			if (n->is_leaf)
				printf("%p ", n->pointers[order - 1]);
			else
				printf("%p ", n->pointers[n->num_keys]);
		}
		printf("| ");
	}
	printf("\n");
}

void find_and_print(node * const root, int key, bool verbose) {
    node * leaf = NULL;
	record * r = find(root, key, verbose, NULL);
	if (r == NULL)
		printf("Record not found under key %d.\n", key);
	else
		printf("Record at %p -- key %d, value %d.\n",
				r, key, r->value);
}

void find_and_print_range(node * const root, int key_start, int key_end,
		bool verbose) {
	int i;
	int array_size = key_end - key_start + 1;
	int returned_keys[array_size];
	void * returned_pointers[array_size];
	int num_found = find_range(root, key_start, key_end, verbose,
			returned_keys, returned_pointers);
	if (!num_found)
		printf("None found.\n");
	else {
		for (i = 0; i < num_found; i++)
			printf("Key: %d   Location: %p  Value: %d\n",
					returned_keys[i],
					returned_pointers[i],
					((record *)
					 returned_pointers[i])->value);
	}
}

int find_range(node * const root, int key_start, int key_end, bool verbose,
		int returned_keys[], void * returned_pointers[]) {
	int i, num_found;
	num_found = 0;
	node * n = find_leaf(root, key_start, verbose);
	if (n == NULL) return 0;
	for (i = 0; i < n->num_keys && n->keys[i] < key_start; i++) ;
	if (i == n->num_keys) return 0;
	while (n != NULL) {
		for (; i < n->num_keys && n->keys[i] <= key_end; i++) {
			returned_keys[num_found] = n->keys[i];
			returned_pointers[num_found] = n->pointers[i];
			num_found++;
		}
		n = n->pointers[order - 1];
		i = 0;
	}
	return num_found;
}

node * find_leaf(node * const root, int key, bool verbose) {
	if (root == NULL) {
		if (verbose)
			printf("Empty tree.\n");
		return root;
	}
	int i = 0;
	node * c = root;
	while (!c->is_leaf) {
		if (verbose) {
			printf("[");
			for (i = 0; i < c->num_keys - 1; i++)
				printf("%d ", c->keys[i]);
			printf("%d] ", c->keys[i]);
		}
		i = 0;
		while (i < c->num_keys) {
			if (key >= c->keys[i]) i++;
			else break;
		}
		if (verbose)
			printf("%d ->\n", i);
		c = (node *)c->pointers[i];
	}
	if (verbose) {
		printf("Leaf [");
		for (i = 0; i < c->num_keys - 1; i++)
			printf("%d ", c->keys[i]);
		printf("%d] ->\n", c->keys[i]);
	}
	return c;
}

record * find(node * root, int key, bool verbose, node ** leaf_out) {
    if (root == NULL) {
        if (leaf_out != NULL) {
            *leaf_out = NULL;
        }
        return NULL;
    }

	int i = 0;
    node * leaf = NULL;

	leaf = find_leaf(root, key, verbose);

    /* If root != NULL, leaf must have a value, even
     * if it does not contain the desired key.
     * (The leaf holds the range of keys that would
     * include the desired key.)
     */

	for (i = 0; i < leaf->num_keys; i++)
		if (leaf->keys[i] == key) break;
    if (leaf_out != NULL) {
        *leaf_out = leaf;
    }
	if (i == leaf->num_keys)
		return NULL;
	else
		return (record *)leaf->pointers[i];
}

int cut(int length) {
	if (length % 2 == 0)
		return length/2;
	else
		return length/2 + 1;
}

record * make_record(int value) {
	record * new_record = (record *)malloc(sizeof(record));
	if (new_record == NULL) {
		perror("Record creation.");
		exit(EXIT_FAILURE);
	}
	else {
		new_record->value = value;
	}
	return new_record;
}

node * make_node(void) {
	node * new_node;
	new_node = malloc(sizeof(node));
	if (new_node == NULL) {
		perror("Node creation.");
		exit(EXIT_FAILURE);
	}
	new_node->keys = malloc((order - 1) * sizeof(int));
	if (new_node->keys == NULL) {
		perror("New node keys array.");
		exit(EXIT_FAILURE);
	}
	new_node->pointers = malloc(order * sizeof(void *));
	if (new_node->pointers == NULL) {
		perror("New node pointers array.");
		exit(EXIT_FAILURE);
	}
	new_node->is_leaf = false;
	new_node->num_keys = 0;
	new_node->parent = NULL;
	new_node->next = NULL;
	return new_node;
}

node * make_leaf(void) {
	node * leaf = make_node();
	leaf->is_leaf = true;
	return leaf;
}

int get_left_index(node * parent, node * left) {

	int left_index = 0;
	while (left_index <= parent->num_keys &&
			parent->pointers[left_index] != left)
		left_index++;
	return left_index;
}

node * insert_into_leaf(node * leaf, int key, record * pointer) {

	int i, insertion_point;

	insertion_point = 0;
	while (insertion_point < leaf->num_keys && leaf->keys[insertion_point] < key)
		insertion_point++;

	for (i = leaf->num_keys; i > insertion_point; i--) {
		leaf->keys[i] = leaf->keys[i - 1];
		leaf->pointers[i] = leaf->pointers[i - 1];
	}
	leaf->keys[insertion_point] = key;
	leaf->pointers[insertion_point] = pointer;
	leaf->num_keys++;
	return leaf;
}

node * insert_into_leaf_after_splitting(node * root, node * leaf, int key, record * pointer) {

	node * new_leaf;
	int * temp_keys;
	void ** temp_pointers;
	int insertion_index, split, new_key, i, j;

	new_leaf = make_leaf();

	temp_keys = malloc(order * sizeof(int));
	if (temp_keys == NULL) {
		perror("Temporary keys array.");
		exit(EXIT_FAILURE);
	}

	temp_pointers = malloc(order * sizeof(void *));
	if (temp_pointers == NULL) {
		perror("Temporary pointers array.");
		exit(EXIT_FAILURE);
	}

	insertion_index = 0;
	while (insertion_index < order - 1 && leaf->keys[insertion_index] < key)
		insertion_index++;

	for (i = 0, j = 0; i < leaf->num_keys; i++, j++) {
		if (j == insertion_index) j++;
		temp_keys[j] = leaf->keys[i];
		temp_pointers[j] = leaf->pointers[i];
	}

	temp_keys[insertion_index] = key;
	temp_pointers[insertion_index] = pointer;

	leaf->num_keys = 0;

	split = cut(order - 1);

	for (i = 0; i < split; i++) {
		leaf->pointers[i] = temp_pointers[i];
		leaf->keys[i] = temp_keys[i];
		leaf->num_keys++;
	}

	for (i = split, j = 0; i < order; i++, j++) {
		new_leaf->pointers[j] = temp_pointers[i];
		new_leaf->keys[j] = temp_keys[i];
		new_leaf->num_keys++;
	}

	free(temp_pointers);
	free(temp_keys);

	new_leaf->pointers[order - 1] = leaf->pointers[order - 1];
	leaf->pointers[order - 1] = new_leaf;

	for (i = leaf->num_keys; i < order - 1; i++)
		leaf->pointers[i] = NULL;
	for (i = new_leaf->num_keys; i < order - 1; i++)
		new_leaf->pointers[i] = NULL;

	new_leaf->parent = leaf->parent;
	new_key = new_leaf->keys[0];

	return insert_into_parent(root, leaf, new_key, new_leaf);
}

node * insert_into_node(node * root, node * n,
		int left_index, int key, node * right) {
	int i;

	for (i = n->num_keys; i > left_index; i--) {
		n->pointers[i + 1] = n->pointers[i];
		n->keys[i] = n->keys[i - 1];
	}
	n->pointers[left_index + 1] = right;
	n->keys[left_index] = key;
	n->num_keys++;
	return root;
}

node * insert_into_node_after_splitting(node * root, node * old_node, int left_index,
		int key, node * right) {

	int i, j, split, k_prime;
	node * new_node, * child;
	int * temp_keys;
	node ** temp_pointers;

	temp_pointers = malloc((order + 1) * sizeof(node *));
	if (temp_pointers == NULL) {
		perror("Temporary pointers array for splitting nodes.");
		exit(EXIT_FAILURE);
	}
	temp_keys = malloc(order * sizeof(int));
	if (temp_keys == NULL) {
		perror("Temporary keys array for splitting nodes.");
		exit(EXIT_FAILURE);
	}

	for (i = 0, j = 0; i < old_node->num_keys + 1; i++, j++) {
		if (j == left_index + 1) j++;
		temp_pointers[j] = old_node->pointers[i];
	}

	for (i = 0, j = 0; i < old_node->num_keys; i++, j++) {
		if (j == left_index) j++;
		temp_keys[j] = old_node->keys[i];
	}

	temp_pointers[left_index + 1] = right;
	temp_keys[left_index] = key;

	split = cut(order);
	new_node = make_node();
	old_node->num_keys = 0;
	for (i = 0; i < split - 1; i++) {
		old_node->pointers[i] = temp_pointers[i];
		old_node->keys[i] = temp_keys[i];
		old_node->num_keys++;
	}
	old_node->pointers[i] = temp_pointers[i];
	k_prime = temp_keys[split - 1];
	for (++i, j = 0; i < order; i++, j++) {
		new_node->pointers[j] = temp_pointers[i];
		new_node->keys[j] = temp_keys[i];
		new_node->num_keys++;
	}
	new_node->pointers[j] = temp_pointers[i];
	free(temp_pointers);
	free(temp_keys);
	new_node->parent = old_node->parent;
	for (i = 0; i <= new_node->num_keys; i++) {
		child = new_node->pointers[i];
		child->parent = new_node;
	}


	return insert_into_parent(root, old_node, k_prime, new_node);
}

node * insert_into_parent(node * root, node * left, int key, node * right) {

	int left_index;
	node * parent;
	parent = left->parent;
	if (parent == NULL)
		return insert_into_new_root(left, key, right);

	left_index = get_left_index(parent, left);
	if (parent->num_keys < order - 1)
		return insert_into_node(root, parent, left_index, key, right);
	return insert_into_node_after_splitting(root, parent, left_index, key, right);
}

node * insert_into_new_root(node * left, int key, node * right) {

	node * root = make_node();
	root->keys[0] = key;
	root->pointers[0] = left;
	root->pointers[1] = right;
	root->num_keys++;
	root->parent = NULL;
	left->parent = root;
	right->parent = root;
	return root;
}

node * start_new_tree(int key, record * pointer) {

	node * root = make_leaf();
	root->keys[0] = key;
	root->pointers[0] = pointer;
	root->pointers[order - 1] = NULL;
	root->parent = NULL;
	root->num_keys++;
	return root;
}

node * insert(node * root, int key, int value) {

	record * record_pointer = NULL;
	node * leaf = NULL;

	record_pointer = find(root, key, false, NULL);
    if (record_pointer != NULL) {
        record_pointer->value = value;
        return root;
    }

	record_pointer = make_record(value);

	if (root == NULL)
		return start_new_tree(key, record_pointer);

	leaf = find_leaf(root, key, false);
	if (leaf->num_keys < order - 1) {
		leaf = insert_into_leaf(leaf, key, record_pointer);
		return root;
	}
	return insert_into_leaf_after_splitting(root, leaf, key, record_pointer);
}

int get_neighbor_index(node * n) {

	int i;

	for (i = 0; i <= n->parent->num_keys; i++)
		if (n->parent->pointers[i] == n)
			return i - 1;

	// Error state.
	printf("Search for nonexistent pointer to node in parent.\n");
	printf("Node:  %#lx\n", (unsigned long)n);
	exit(EXIT_FAILURE);
}


node * adjust_root(node * root) {

	node * new_root;

	if (root->num_keys > 0)
		return root;

	if (!root->is_leaf) {
		new_root = root->pointers[0];
		new_root->parent = NULL;
	}

	else
		new_root = NULL;

	free(root->keys);
	free(root->pointers);
	free(root);

	return new_root;
}


node * redistribute_nodes(node * root, node * n, node * neighbor, int neighbor_index,
		int k_prime_index, int k_prime) {

	int i;
	node * tmp;

	if (neighbor_index != -1) {
		if (!n->is_leaf)
			n->pointers[n->num_keys + 1] = n->pointers[n->num_keys];
		for (i = n->num_keys; i > 0; i--) {
			n->keys[i] = n->keys[i - 1];
			n->pointers[i] = n->pointers[i - 1];
		}
		if (!n->is_leaf) {
			n->pointers[0] = neighbor->pointers[neighbor->num_keys];
			tmp = (node *)n->pointers[0];
			tmp->parent = n;
			neighbor->pointers[neighbor->num_keys] = NULL;
			n->keys[0] = k_prime;
			n->parent->keys[k_prime_index] = neighbor->keys[neighbor->num_keys - 1];
		}
		else {
			n->pointers[0] = neighbor->pointers[neighbor->num_keys - 1];
			neighbor->pointers[neighbor->num_keys - 1] = NULL;
			n->keys[0] = neighbor->keys[neighbor->num_keys - 1];
			n->parent->keys[k_prime_index] = n->keys[0];
		}
	}

	else {
		if (n->is_leaf) {
			n->keys[n->num_keys] = neighbor->keys[0];
			n->pointers[n->num_keys] = neighbor->pointers[0];
			n->parent->keys[k_prime_index] = neighbor->keys[1];
		}
		else {
			n->keys[n->num_keys] = k_prime;
			n->pointers[n->num_keys + 1] = neighbor->pointers[0];
			tmp = (node *)n->pointers[n->num_keys + 1];
			tmp->parent = n;
			n->parent->keys[k_prime_index] = neighbor->keys[0];
		}
		for (i = 0; i < neighbor->num_keys - 1; i++) {
			neighbor->keys[i] = neighbor->keys[i + 1];
			neighbor->pointers[i] = neighbor->pointers[i + 1];
		}
		if (!n->is_leaf)
			neighbor->pointers[i] = neighbor->pointers[i + 1];
	}

	n->num_keys++;
	neighbor->num_keys--;

	return root;
}

int main(int argc, char ** argv) {

	char * input_file;
	FILE * fp;
	node * root;
	int input_key, input_key_2;
	char instruction;

	root = NULL;
	verbose_output = false;

	if (argc > 1) {
		order = atoi(argv[1]);
		if (order < 3) {  // less than minimum order 3
			fprintf(stderr, "Invalid order: %d .\n\n", order);
			exit(EXIT_FAILURE);
		}
	}

	if (argc > 2) {
		input_file = argv[2];
		fp = fopen(input_file, "r");
		if (fp == NULL) {
			perror("Failure to open input file.");
			exit(EXIT_FAILURE);
		}
		while (!feof(fp)) {
			fscanf(fp, "%d\n", &input_key);
			root = insert(root, input_key, input_key);
		}
		fclose(fp);
		print_tree(root);
        return EXIT_SUCCESS;
	}

	printf("> ");
    char buffer[BUFFER_SIZE];
    int count = 0;
    bool line_consumed = false;
	while (scanf("%c", &instruction) != EOF) {
        line_consumed = false;
		switch (instruction) {
			case 'i':
				fgets(buffer, BUFFER_SIZE, stdin);
				line_consumed = true;
				count = sscanf(buffer, "%d %d", &input_key, &input_key_2);
				if (count == 1)
					input_key_2 = input_key;
				root = insert(root, input_key, input_key_2);
				print_tree(root);
				break;
			case 'f':
			case 'p':
				scanf("%d", &input_key);
				find_and_print(root, input_key, instruction == 'p');
				break;
			case 'r':
				scanf("%d %d", &input_key, &input_key_2);
				if (input_key > input_key_2) {
					int tmp = input_key_2;
					input_key_2 = input_key;
					input_key = tmp;
				}
				find_and_print_range(root, input_key, input_key_2, instruction == 'p');
				break;
			case 'l':
				print_leaves(root);
				break;
			case 'q':
				while (getchar() != (int) '\n');
				return EXIT_SUCCESS;
				break;
			case 't':
				print_tree(root);
				break;
			case 'v':
				verbose_output = !verbose_output;
				break;
		}
        if (!line_consumed)
           while (getchar() != (int)'\n');
		printf("> ");
	}
	printf("\n");

	return EXIT_SUCCESS;
}