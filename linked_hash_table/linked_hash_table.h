#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


// ====== MACROS ======

#define TABLE_SIZE 1024
#define BUCKET_DEPTH 3
#define MAX_KEY_LEN 50


// ====== DATA STRUCTS ======

/**
 * @brief linked_node that golds record
 * @param key key of record
 * @param value value of record
 * @param link the next node in linked list
 */
typedef struct keypair_node {

	char key[MAX_KEY_LEN];
	int value;
	struct keypair_node* link;

} node;

/**
 * @brief structure that holds buckets and hashtable info
 * @param max_buckes maximum number of buckets allowed (also the size of table array)
 * @param used_buckets number of buckets with records stored in them
 * @param records number of records stored in the whole struct
 * @param table array of node pointers representing bucket data
 */
typedef struct hash_table {

	int max_buckets;
	int used_buckets;
	int records;

	node* table[TABLE_SIZE];

} dict;


// ============ DECLARATIONS ============

// ====== general ======

/**
 * @brief prints error message and exits
 * @param message formatted er message
 */
void error(const char* message, ...);


// ====== hash table ======

/**
 * @brief set a key-value record
 * @param ht hashtable to manipulate
 * @param key key to insert
 * @param value value to insert
 * @return editied hashtable  
 */
void HT_set(dict* ht, char* key, int value);

/**
 * @brief removes a record from hashtable
 * @param ht hashtable to edit
 * @param key key of record to remove
 * @return editied hashtable
 */
void HT_remove(dict* ht, char* key);

/**
 * @brief retrieves a stored value from a record
 * @param ht hashtable to search
 * @param key key to search for
 * @return value from found record
 */
int HT_get(dict* ht, char* key);

/**
 * @brief gets an array of all records in hashtable, length found in ht struct
 * @param ht hashtable to retrieve from
 * @return array of node* for each record (length in ht.records)
 */
node** HT_getrecords(dict* ht);

/**
 * @brief initializes a new hashtable
 * @return new hashtable 
*/
dict* HT_init(void);

/**
 * @brief hashes a key for internal use
 * @param key key to hash
 * @return hashed key
 */
int HT_hash(char* key);

/**
 * @brief frees hashtable and all nodes within
 * @param ht hashtable to free
 */
void HT_free(dict* ht);

/**
 * @brief checks if a record is present in hashtable
 * @param ht hashtable to serch
 * @param key key to search for
 * @return is record present (bool)
 */
int HT_contains(dict* ht, char* key);


// ====== nodes ======

/**
 * @brief initializes a record node
 * @param key key to store in record
 * @param value value to store in record
 * @return initialized record
 */
node* NODE_init(char* key, int value);

/**
 * @brief appends a record to a linked list of records
 * @param head first record in linked list
 * @param n node to append to end of list
 * @return head of edited list
 */
node* NODE_append(node* head, node* end);

/**
 * @brief remove a record w/ passed key from record list
 * @param head first record in linked list
 * @param key key of record ot be removed
 * @return head of edited list
 */
node* NODE_remove(node* head, char* key);

/**
 * @brief prints all records in a linked list
 * @param head first record in list
 */
void NODE_printlist(node* head);

/**
 * @brief frees all records in linked list
 * @param head first record in linked list
 */
void NODE_freelist(node* head);


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


// ====== hashtable methods ======

dict* HT_init(void) {

	dict* ht = (dict*)malloc(sizeof(dict));
	if (ht == NULL) {error("Malloc denied in hashtable initialization");}

	for (int i=0; i<TABLE_SIZE; i++) {
		ht->table[i] = NULL;
	}

	ht->max_buckets = TABLE_SIZE;
	ht->records = 0;

	return ht;
}

void HT_set(dict* ht, char* key, int value) {
	node* head;
	node* temp;

	// handle key that's too long
	if (strlen(key) > MAX_KEY_LEN) {
		error("key too long.\n\tkey: '%s'\n\tmax key length: %d", key, MAX_KEY_LEN);
	}

	// hash the key
	int index = HT_hash(key);

	// check for key existence (if it does, change it on the spot)
	head = ht->table[index];
	if (head != NULL) {
		temp = head;
		while (temp != NULL) {
			
			if (!strncmp(temp->key, key, MAX_KEY_LEN)) {
				temp->value = value;
				return;
			}

			temp = temp->link;
		}
	}

	// append key-value pair to hashtable
	temp = NODE_init(key, value);
	ht->table[index] = NODE_append(head, temp);
	ht->records++;

	return;
}

void HT_remove(dict* ht, char* key) {

	int index = HT_hash(key);

	NODE_remove(ht->table[index], key);

	ht->records--;
}

int HT_get(dict* ht, char* key) {

	// hash key
	int index = HT_hash(key);

	// find key in table to return
	node* head = ht->table[index];
	while (head != NULL) {
		if (!strncmp(head->key, key, MAX_KEY_LEN)) {
			return head->value;
		}
		head = head->link;
	}

	// if not present, keyerror
	error("key '%s' not found.", key);
	return -1;
}

int HT_hash(char* key) {

	unsigned long loc = 0;
	
	for (int i=0; key[i] != '\0'; i++) {
		loc += (unsigned int) key[i];
	}

	return loc % TABLE_SIZE;
}

node** HT_getrecords(dict* ht) {

	node** arr_out = (node**)malloc((ht->records) * sizeof(node*));
	if (arr_out == NULL) {error("Malloc denied while getting pairs");}

	int arr_head = 0;
	node* head;
	for (int i=0; i<ht->max_buckets; i++) {
		head = ht->table[i];
		while (head != NULL) {
			arr_out[arr_head++] = head;
			head = head->link;
		}
	}
	return arr_out;

}

int HT_contains(dict* ht, char* key) {

	// hash key
	int index = HT_hash(key);

	// find key in table to return
	node* head = ht->table[index];
	while (head != NULL) {
		if (!strncmp(head->key, key, MAX_KEY_LEN)) {
			return 1;
		}
		head = head->link;
	}

	return 0;

}

void HT_free(dict* ht) {


	for (int i=0; i<ht->max_buckets; i++) {
		if (ht->table[i] != NULL) {
			NODE_freelist(ht->table[i]);
		}
	}

	free(ht);

}


// ====== node methods ======

node* NODE_init(char* key, int value) {

	// create memory space for node
	node* n = (node*)malloc(sizeof(node));
	if (n == NULL) {error("Malloc denied in node initilization");}

	// store data in node
	strncpy(n->key, key, strlen(key));
	n->value = value;
	n->link = NULL;

	return n;
}

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

node* NODE_remove(node* head, char* key) {

	if (head == NULL) {error("node remove passed a NULL.");}

	node* temp = head;

	// key is head
	if (!strncmp(temp->key, key, MAX_KEY_LEN)) {
		head = temp->link;
		free(temp);
		return head;
	}

	// advance through list, exit on end
	while (strncmp(temp->link->key, key, MAX_KEY_LEN)) {
		if (temp->link == NULL) {error("key '%s' not found in nodelist.", key);}
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

void NODE_printlist(node* head) {
	if (head == NULL) {return;}

	printf("\n--------------\n");
	printf("key: value\n");
	printf("--------------\n");

	while (head != NULL) {
		printf("'%s': %d\n", head->key, head->value);
		head = head->link;
	}
}


void NODE_freelist(node* head) {
	node* temp;

	while (head != NULL) {
		temp = head;
		head = head->link;
		free(temp);
	}
	if (head != NULL) {free(head);}
}

