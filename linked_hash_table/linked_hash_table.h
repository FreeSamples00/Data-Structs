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
int HT_clear(dict* ht, char* key);
int HT_retrieve(dict* ht, char* key);
ndode* HT_getdata(dict* ht);
dict* HT_init(void);
int HT_hash(char* key);

node* NODE_init(char* key, int value);
node* NODE_append(node* head, node* end);
node* NODE_remove(node* head, char* key);
int NODE_printlist(node* head);


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

	return ht;
}

int HT_set(dict* ht, char* key, int value) {

	// TODO: if key absent create key/value pair, else change existing value

	return 0;
}

int HT_clear(dict* ht, char* key) {

	// TODO: remove key/value pair

	return 0;
}

int HT_retrieve(dict* ht, char* key) {

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

node* HT_getdata(dict* ht) {

	/* TODO: 
		- finds all stored keyvalue pairs
		- strings themm together
		- returns them as a linkedlist
	*/

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

node* NODE_remove(node* head, char* key) {

	if (head == NULL) {return head;}

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

