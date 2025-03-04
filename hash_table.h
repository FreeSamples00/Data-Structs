#include <stdio.h>
#include <stdlib.h>


// macros
#define TABLE_SIZE 1024;
#define BUCKET_DEPTH 3;
#define MAX_KEY_LEN 50


// data structs
typedef struct keypair_node {
	char key[MAX_KEY_LEN];
	int data;
	keypair_node* link;
} node; 

typedef struct hash_table {
	int capacity;
	int occupancy;

	node table[TABLE_SIZE];
} dict;



// declarations
int HT_set(dict HT, char* key, int value);
int HT_clear(dict HT, char* key);
int HT_retrieve(dict HT, char* key);
dict* HT_init(void);

int hash_key(char* key);

/*  
	TODO: init node
	TODO: add node
	TODO: remove node
*/

// functions
dict* HT_init(void) {
	dict* new_dict = malloc(sizeof(dict));
	if (new_dict == NULL) {
		exit(1);
	}
	new_dict->capacity = TABLE_SIZE;

	// TODO: finish init

	return new_dict;
}

int HT_set(dict HT, char* key, int value) {

	// TODO: if key absent create key/value pair, else change existing value

	return 0;
}

int HT_clear(dict HT, char* key) {

	// TODO: remove key/value pair

	return 0;
}

int HT_retrieve(dict HT, char* key) {

	// TODO

	return 0;
}


// TODO: second hash function?
// TODO: verify distribution is even-ish
int hash_key(char* key) {

	unsigned long b = 0x0;
	printf("%lu\n\n", bucket);
	

	for (int i=0; key[i] != '\0'; i++) {
		printf("'%c' -> %d\n", key[i], key[i]);
		printf("b + '%c' = %lu + %d", key[i], b, key[i]);
		b += (unsigned int) key[i];
		printf(" = %lu\n\n", bucket);
	}

	return bucket % TABLE_SIZE;
}

