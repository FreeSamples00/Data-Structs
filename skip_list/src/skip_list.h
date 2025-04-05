#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// ============ MACROS ============

#define NUM_LEVELS 3
#define MAX_KEY_LEN 50
#define EXPR_CHANCE 0.2

// ============ DATA STRUCTS ============

/**
 * @brief struct for linked node 
 * @param down link to node in list below (if NULL, is base node)
 * @param next link to next node in list (if NULL, is end of list)
 * @param key key of record (char*)
 * @param value value of record (int) (only base node has non NULL value)
 */ 
typedef struct linked_node {

	struct linked_node* next;
	struct linked_node* down;
	struct linked_node* prev;

	char key[MAX_KEY_LEN];
	int value;

} node;

/**
 * @brief struct for skip list usage
 * @param levels array of linked lists (0 is base, rest are express lists)
 * @param records number of records stored in skip list 
 */
typedef struct skip_list {

	node* levels[NUM_LEVELS];
	int records;

} sk_lst;

// ============ DECLARATIONS ============

/**
 * @brief initializes new skip list
 * @return point to new skip list
 */
sk_lst* SK_init(void);

/**
 * @brief changes or creates a record with key-value pair
 * @param sk pointer to skip list to edit
 * @param key string key value of record
 * @param value int value of record
 * @return pointer to affected skip list
 */
sk_lst* SK_set(sk_lst* sk, char* key, int value);

/**
 * @brief removes a record in skip list
 * @param sk pointer to skip list to edit
 * @param key string value of record to be removed
 * @return pointer to affected skip list
 */
sk_lst* SK_remove(sk_lst* sk, char* key);

/**
 * @brief retrieve value of a key from skip list
 * @param sk pointer to skip list to search
 * @param key string value to search for
 * @return int value from record w/ key
 */
int SK_get(sk_lst* sk, char* key);

/**
 * @brief retrieve all records in skip list
 * @param sk skip list to pull from
 * @return an array of node pointers (length found in sk->records)
 */
node** SK_getrecords(sk_lst* sk);

/**
 * @brief boolean check if record is within skip list
 * @param sk pointer to skip list to search
 * @param key value to search for
 * @return boolean if record present
 */
int SK_contains(sk_lst* sk, char* key);

/**
 * @brief frees all nodes and structs of skip list
 * @param sk skip list to free
 */
void SK_free(sk_lst* sk);

/**
 * @brief print all records in skip list, formatted by level
 * @param sk skip list pointer to print
 * @return none, but prints to stdout
 */
void SK_print(sk_lst* sk);

#endif