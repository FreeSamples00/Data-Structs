#include "linked_hash_table.h"

// =========== INTERNAL DECLARATIONS ===========

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

/**
 * @brief prints error message and exits
 * @param message formatted er message
 */
void error(const char* message, ...) {

	fprintf(stderr, "\033[31mERROR: ");
	va_list args;
	va_start(args, message);
	vfprintf(stderr, message, args);
	va_end(args);
	fprintf(stderr, "\033[0m\n\n");

	exit(1);
}

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

	loc = loc * loc * loc;

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

node* NODE_init(char* key, int value) {

	// create memory space for node
	node* n = (node*)malloc(sizeof(node));
	if (n == NULL) {error("Malloc denied in node initilization");}

	// store data in node
	if (strlen(key) < MAX_KEY_LEN) {
		strncpy(n->key, key, strlen(key));
	} else {
		strncpy(n->key, key, MAX_KEY_LEN);
	}
	
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

