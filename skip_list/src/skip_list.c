#include "skip_list.h"

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
node* NODE_init(char* key, int value);


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

sk_lst* SK_init() {

 	// init struct
	sk_lst* sk = (sk_lst*) malloc(sizeof(sk_lst));
	if (sk == NULL) {error("Malloc failed in SK_init");}

	// set values
	sk->records = 0;

	// set links
	for (int i=0; i<NUM_LEVELS; i++) {
		sk->levels[i] = NULL;
	}

	return sk;
}

sk_lst* SK_set(sk_lst* sk, char* key, int value) {

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
	// TODO:
	error("SK_print() not implemented");
}

node* NODE_init(char* key, int value) {

	// init node
	node* n = (node*) malloc(sizeof(node));
	if (n == NULL) {error("Malloc failed in NODE_init");}

	// set values
	if (strlen(key) < MAX_KEY_LEN) {
		strncpy(n->key, key, strlen(key));
	} else {
		strncpy(n->key, key, MAX_KEY_LEN);
	}
	n->value = value;

	// set links
	n->next = NULL;
	n->down = NULL;
	n->prev = NULL;

	return n;
}



