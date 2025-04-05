#ifndef LINKED_HASH_TABLE_H
#define LINKED_HASH_TABLE_H

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

#endif

