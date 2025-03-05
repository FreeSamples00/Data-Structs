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

int HT_set(dict* ht, char* key, int value);
int HT_remove(dict* ht, char* key);
int HT_get(dict* ht, char* key);
node* HT_getpairs(dict* ht);
dict* HT_init(void);
int HT_hash(char* key);
int HT_free(dict* ht);

node* NODE_init(char* key, int value);
node* NODE_append(node* head, node* end);
node* NODE_remove(node* head, char* key);
int NODE_printlist(node* head);


// ============ FUNCTIONS ============


// ====== hashtable methods ======

// initialize hash table
dict* HT_init(void) {

	dict* ht = malloc(sizeof(dict));
	if (ht == NULL) {exit(1);}

	for (int i=0; i<TABLE_SIZE; i++) {
		ht->table[i] = NULL;
	}

	ht->capacity = TABLE_SIZE;
	ht->occupancy = 0;

	return ht;
}

// set a key to a value in the hashtable
int HT_set(dict* ht, char* key, int value) {
	node* head;
	node* temp;

	// handle key that's too long
	if (strlen(key) > MAX_KEY_LEN) {
		printf("\033[33mERROR: key too long.\n\tkey:  '%s'\n\tmax length: %d\033[0m\n", key, MAX_KEY_LEN);
		exit(1);
	}

	// hash the key
	int index = HT_hash(key);

	// check for key existence (if it does, change it on the spot)
	head = ht->table[index];
	if (head != NULL) {
		temp = head;
		while (temp != NULL) {
			
			if (!strcmp(temp->key, key)) {
				temp->value = value;
				return 0;
			}

			temp = temp->link;
		}
	}

	// append key-value pair to hashtable
	temp = NODE_init(key, value);
	ht->table[index] = NODE_append(head, temp);

	return 0;
}

// remove a key-value pair from hashtable
int HT_remove(dict* ht, char* key) {

	// TODO: remove key/value pair

	return 0;
}

// retrieve a value from hashtable using key
int HT_get(dict* ht, char* key) {

	// hash key
	int index = HT_hash(key);

	// find key in table to return
	node* head = ht->table[index];
	while (head != NULL) {
		if (!strcmp(head->key, key)) {
			return head->value;
		}
		head = head->link;
	}

	// if not present, keyerror
	printf("ERROR: key %s not found\n", key);
	exit(1);
	return -1;
}

// hash key into an index in the hashtable
int HT_hash(char* key) {

	unsigned long loc = 0;
	
	for (int i=0; key[i] != '\0'; i++) {
		loc += (unsigned int) key[i];
	}

	return loc % TABLE_SIZE;
}

// gets a linked list of all data stored in hash table
node* HT_getpairs(dict* ht) {

	/* TODO: 
		- finds all stored key-value pairs
		- strings themm together
		- returns them as a linkedlist
	*/

	return NULL;

}

// free hashtable and its internal structs
int HT_free(dict* ht) {

	// TODO: free all linked lists, then free ht itself

	return 1;
}


// ====== node methods ======

// initalize linked node w/ key-value data
node* NODE_init(char* key, int value) {

	// create memory space for node
	node* n = malloc(sizeof(node));
	if (n == NULL) {exit(1);}

	// store data in node
	strncpy(n->key, key, strlen(key));
	n->value = value;
	n->link = NULL;

	return n;
}

// append node to a linked list
node* NODE_append(node* head, node* n) {

	// if list is empty
	if (head == NULL) {
		return n;
	}

	// iterate through list
	node* temp = head;
	while (temp->link != NULL) {
		temp = temp->link;
	}

	// add node to end
	temp->link = n;

	return head;
}

// remove node from a linked list
node* NODE_remove(node* head, char* key) {

	if (head == NULL) {return head;} // TODO: throw error?

	node* temp = head;

	// key is head
	if (!strcmp(temp->key, key)) {
		head = temp->link;
		free(temp);
		return head;
	}

	// advance through list, exit on end
	while (strcmp(temp->link->key, key)) {
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

// print this and all following nodes in a linked list
int NODE_printlist(node* head) {
	if (head == NULL) {return 1;}

	printf("  key | value\n");
	printf("------+--------\n");

	while (head != NULL) {
		printf(" %s | %d\n", head->key, head->value);
		head = head->link;
	}

	return 0;
}

// free this node and all follwing it in linked list
int NODE_freelist(node* head) {
	node* temp;

	while (head != NULL) {
		temp = head;
		head = head->link;
		free(temp);
	}
	free(head);

	return 1;
}

