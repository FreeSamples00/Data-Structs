#include "linked_hash_table.h"

int main(int args, char* argv[]) {
	int c;

	if (args == 2) {

		c = (int)argv[1][0];

	} else {
	
		printf("Test cases:\n");
		printf("\t1. Linked list\n");
		printf("\t2. Hash table set + retrieve\n");
		printf("\t3. Hash table set + remove + retrieve\n");
		printf("\t4. Hash collision\n");
		printf("\nEnter choice: ");
		c = getchar();
		printf("\n");

	}

	printf("\n ====== TEST BEGIN ======\n\n");
	switch(c) {
		case '1': { // linked list

			node* head = NULL;
			char* keys[] = {"key0", "key1", "key2", "key3"};
			int values[] = {0, 1, 2, 3};
			
			// appends
			for (int i=0; i<4; i++) {
				head = NODE_append(head, NODE_init(keys[i], values[i]));
			}

			// print list
			printf("Appends Completed:\n\n");
			NODE_printlist(head);

			// removes
			for (int i=0; i<4; i+=2) {
				head = NODE_remove(head, keys[i]);
			}

			// print list
			printf("\nRemoves Completed:\n\n");
			NODE_printlist(head);

			// free list
			printf("\nFreeing List\n");
			NODE_freelist(head);

			break;
		}

		case '2': { // set + retrieve
			char* key = "Hello World!";
			int value = 42;


			// initialize hash table
			dict* ht = HT_init();
			printf("Hashtable created\n");

			// set some keyvalue pairs
			HT_set(ht, key, value);
			printf("Set '%s' to %d\n", key, value);

			// retrieve and print a value
			printf("Retrieved %d from '%s'\n", HT_get(ht, key), key);

			// TODO: free table + lists

			break;
		}

		case '3': { // set + remove + retrieve

			break;
		}

		case '4': { // hash collision
			char* keys[] = {"d", "dddddddddd>>"};
			int values[] = {1, 2};

			// initialize hashtable
			dict* ht = HT_init();
			printf("Hashtable created\n");

			// set key-value pairs
			printf("\nSetting key-value pairs\n");
			for (int i=0; i<2; i++) {
				HT_set(ht, keys[i], values[i]);
				printf("Set '%s' to %d\n", keys[i], values[i]);
			}

			// retrieve set key-value pairs
			printf("\nRetrieving keys\n");
			for (int i=0; i<2; i++) {
				printf("Retrieved %d from '%s'\n", HT_get(ht, keys[i]), keys[i]);
			}

			// TODO: free tables

			break;
		}

		default: {
			printf("Invalid test case: '%c'\n", c);
			printf("\n ====== TEST END ======\n\n");
			return 1;
		}
	}
	printf("\n ====== TEST END ======\n\n");

	return 0;

}