#include "skip_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


// =========== INTERNAL DECLARATIONS ===========

/**
 * @brief prints error message and exits
 * @param message formatted er message
 */
void error(const char* message, ...);

/**
 * @brief determines whether or not to create a higher level node 
 * 		(this function may be changed based on use case)
 * @param sk skip list, in case any status info needs to be checked
 * @return integer boolean representing decision
 */
int levelup(sk_lst* sk);

/**
 * @brief initializes node with key and value
 * @param key char* key of record
 * @param value int value of record
 * @return pointer to new node
 */
node* init_node(char* key);

/**
 * @brief compares two keys
 * @param key1 key that will be compared against key2
 * @param key2 key to be compared against
 * @return integer -1, 0, or 1
 * 		   -1: key1 < key2,
 * 		    0: key1 == key2,
 * 		    1: key1 > key2
 */
int key_compare(const char* key1, const char* key2);


// ============ FUNCTIONS ============ 

void error(const char* message, ...) {

	fprintf(stderr, "\033[31mERROR: ");
	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);
	fprintf(stderr, "\033[0m\n\n");

	exit(1);
}

sk_lst* SK_init(int num_levels) {

 	// init struct
	sk_lst* sk = (sk_lst*) malloc(sizeof(sk_lst) + (num_levels * sizeof(node*)));
	if (sk == NULL) {error("Malloc failed in SK_init");}

	// set values
	sk->records = 0;
	sk->NUM_LEVELS = num_levels;

	// set links
	for (int i=0; i<num_levels; i++) {
		sk->levels[i] = NULL;
	}

	return sk;
}

sk_lst* SK_set(sk_lst* sk, char* key, int value) {

	// TODO: finish

	// insert in front
	if (sk->levels[0] == NULL || (key_compare(key, sk->levels[0]->key) == -1)) {

		node* new_node;
		for (int i=0; i<sk->NUM_LEVELS; i++) {

			new_node = init_node(key);

			if (i == 0) {
				new_node->value = value;
			} else {
				new_node->down = sk->levels[i-1];
			}

			new_node->next = sk->levels[i];

			sk->levels[i] = new_node;
		}
		return sk;
	}

	// get highest level beginning node
	node* head = sk->levels[sk->NUM_LEVELS-1];

	// traverse levels, descending when necessary
	while (head->down != NULL) {

		while (key > head->key) {
			head = head->next;
		}

		head = head->down;

	}


	// TODO: node needs to go in first space

	// TODO: find desired location

	// TODO: chance node gets express lane

	error("SK_set() not implemented");
	return NULL;
}

sk_lst* SK_remove(sk_lst* sk ,char* key) {

	// TODO: node is first in list

	// TODO: find node

	// TODO: node is linked to express nodes

	// TODO: 

	error("SK_remove not implemented");
	return NULL;
}

int SK_get(sk_lst* sk, char* key) {
	// TODO:
	error("SK_get() not implemented");
	return -1;
}

int SK_contains(sk_lst* sk, char* key) {
	// TODO:
	error("SK_contains() not implemented");
	return -1;
}

node** SK_getrecords(sk_lst* sk) {
	// TODO:
	error("SK_getrecords() not implemented");
	return NULL;
}

void SK_free(sk_lst* sk) {
	// TODO:
	error("SK_free() not implemented");
}

void SK_print(sk_lst* sk) {

	// TODO: finish

	// create heads list
	node* heads[sk->NUM_LEVELS];
	for (int i=0; i<sk->NUM_LEVELS; i++) {
		heads[i] = sk->levels[i];
	}

	char key[MAX_KEY_LEN];

	// traverse skip list
	while (heads[0] != NULL) {

		// retrieve curr key for matching
		strncpy(key, heads[0]->key, strlen(heads[0]->key));
		printf("'key': %s\n", key);
		printf("'heads[0]->key': %s\n", heads[0]->key);
		printf("'strlen(heads[0]->key]': %ld\n", strlen(heads[0]->key));
		printf("'strlen(key)': %ld\n", strlen(key));

		// print all applicable levels
		for (int i=0; i<sk->NUM_LEVELS; i++) {

			if (i == 0) {
				printf("[%s, %d] ", heads[0]->key, heads[0]->value);
				heads[0] = heads[0]->next;
			} else {
				if (! key_compare(key, heads[i]->key)) {
					printf("[%s] ", heads[i]->key);
					heads[i] = heads[i]->next;
				}
				printf("[%s] ", heads[i]->key);
				heads[i] = heads[i]->next;
			}

		}

		printf("\n");
	}

}

node* init_node(char* key) {

	// init node
	node* n = (node*) malloc(sizeof(node));
	if (n == NULL) {error("Malloc failed in NODE_init");}

	// set key
	if (strlen(key) < MAX_KEY_LEN) {
		strncpy(n->key, key, strlen(key));
	} else {
		strncpy(n->key, key, MAX_KEY_LEN);
	}

	// set links
	n->next = NULL;
	n->down = NULL;
	n->prev = NULL;

	return n;
}

int levelup(sk_lst* sk) {
	return (EXPR_CHANCE*100) <= (rand() % 100);
}

int key_compare(const char* key1, const char* key2) {

	for (int i=0; (key1[i] != '\0') && (key2[i] != '\0'); i++) {

		if ((int)key1[i] > (int)key2[i]) {
			return 1;
		} else if ((int)key1[i] < (int)key2[i]) {
			return -1;
		}
	}

	if (strlen(key1) > strlen(key2)) {
		return 1;
	} else if (strlen(key1) < strlen(key2)) {
		return -1;
	}

	return 0;
}


