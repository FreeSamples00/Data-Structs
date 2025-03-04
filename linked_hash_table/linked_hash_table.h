#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ====== MACROS ======

#define TABLE_SIZE 1024
#define BUCKET_DEPTH 3
#define MAX_KEY_LEN 50


// ====== DATA STRUCTS ======

typedef struct keypair_node {

	char key[MAX_KEY_LEN];
	int value;
	struct keypair_node* link;

} node;

typedef struct hash_table {

	int capacity;
	int occupancy;

	node* table[TABLE_SIZE];

} dict;


// ====== DECLARATIONS ======

int HT_set(dict HT, char* key, int value);
int HT_clear(dict HT, char* key);
int HT_retrieve(dict HT, char* key);
dict* HT_init(void);
int HT_hash(char* key);

node* NODE_init(char* key, int value);
node* NODE_append(node* head, node* end);
node* NODE_remove(node* head, char* key);


// ============ FUNCTIONS ============


// ====== hashtable methods ======

dict* HT_init(void) {

	dict* ht = malloc(sizeof(dict));
	if (ht == NULL) {exit(1);}

	for (int i=0; i<TABLE_SIZE; i++) {
		ht->table[i] = NULL;
	}

	ht->capacity = TABLE_SIZE;
	ht->occupancy = 0;


	// TODO: finish init

	return ht;
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

int HT_hash(char* key) {

	unsigned long loc = 0;
	
	for (int i=0; key[i] != '\0'; i++) {
		loc += (unsigned int) key[i];
	}

	return loc % TABLE_SIZE;
}


// ====== node methods ======

node* NODE_init(char* key, int value) {

	node* n = malloc(sizeof(node));
	if (n == NULL) {exit(1);}

	strncpy(n->key, key, strlen(key));
	n->value = value;
	n->link = NULL;

	return n;
}

node* NODE_append(node* head, node* n) {

	if (head == NULL) {
		return n;
	}
	node* temp = head;
	while (temp->link != NULL) {
		temp = temp->link;
	}
	temp->link = n;
	return head;
}

// TODO: does not work
node* NODE_remove(node* head, char* key) {

	if (head == NULL) {return head;}

	node* temp = head;

	// key is head
	if (temp->key == key) {
		head = temp->link;
		free(temp);
		return head;
	}

	// advance through list, exit on end
	while (temp->link->key != key) {
		if (temp->link == NULL) {return head;}
		temp = temp->link;
	}

	// remove node
	node* next;
	if (temp->link->link != NULL) {
		next = temp->link->link;
	} else {
		next = NULL;
	}
	free(temp->link);
	temp->link = next;

	return head;

}

