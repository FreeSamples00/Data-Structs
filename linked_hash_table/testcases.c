#include "linked_hash_table.h"

int main(int args, char* argv[]) {
	int c;

	if (args == 2) {

		c = (int)argv[1][0];

	} else {
	
		printf("Test cases:\n");
		printf("\t0. Linked list\n");
		printf("\t1. Hash table set + contains\n");
		printf("\t2. Hash table set + retrieve\n");
		printf("\t3. Hash table set + remove + retrieve\n");
		printf("\t4. Hash collision\n");
		printf("\t5. Print Hash Table\n");
		printf("\nEnter choice: ");
		c = getchar();
		printf("\n");

	}

	printf("\n \033[90m====== TEST BEGIN ======\033[0m\n\n");
	switch(c) {
		case '0': { // linked list

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

		case '1': {
			char* keys[] = {"key1", "key2"};

			// initialize hashtable
			dict* ht = HT_init();
			printf("Hashtable created\n");

			// set keyvalue pairs
			printf("\nSetting Records\n");
			for (int i=0; i<2; i++) {
				HT_set(ht, keys[i], i);
				printf("\tSet '%s' to %d\n", keys[i], i);
			}

			printf("\nChecking Records\n");
			// check if hash table contains valid key
			if (HT_contains(ht, "key1")) {
				printf("\tKey 'key1' is present\n");
			} else {
				printf("\tKey 'key1' not present\n");
			}

			// check if hashtable contains invalid key
			if (HT_contains(ht, "key3")) {
				printf("\tKey 'key3' is present\n");
			} else {
				printf("\tKey 'key3' not present\n");
			}

			printf("\nFreeing Hashtable\n");
			HT_free(ht);

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

			printf("\nFreeing Hastable\n");
			HT_free(ht);

			break;
		}

		case '3': { // set + remove + retrieve
			char* keys[] = {"key1", "key2", "key3"};
			int values[] = {1, 2, 3};

			dict* ht = HT_init();
			printf("Hashtable created\n");

			printf("\nSetting key-value pairs\n");
			for (int i=0; i<3; i++) {
				HT_set(ht, keys[i], values[i]);
				printf("\tSet %d to '%s'\n", values[i], keys[i]);
			}
			

			printf("\nRemoving key-value pair\n");
			HT_remove(ht, keys[2]);
			printf("\tRemoved '%s':%d pair.\n", keys[2], values[2]);

			printf("\nRetrieving key-values pairs\n");
			for (int i=0; i<3; i++) {
				printf("\tRetrieved %d from '%s'\n", HT_get(ht, keys[i]), keys[i]);
			}

			printf("\nFreeing Hastable\n");
			HT_free(ht);


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
				printf("\tSet '%s' to %d\n", keys[i], values[i]);
			}

			// retrieve set key-value pairs
			printf("\nRetrieving keys\n");
			for (int i=0; i<2; i++) {
				printf("\tRetrieved %d from '%s'\n", HT_get(ht, keys[i]), keys[i]);
			}

			printf("\nFreeing Hastable\n");
			HT_free(ht);

			break;
		}

		case '5': { // print all pairs
			char* keys[] = {"d", "dddddddddd>>", "abcd", "aoiwbcaw"};
			int values[] = {1, 2, 3, 4};

			// initialize hashtable
			dict* ht = HT_init();
			printf("Hashtable created\n");

			// set key-value pairs
			printf("\nSetting key-value pairs\n");
			for (int i=0; i<4; i++) {
				HT_set(ht, keys[i], values[i]);
				printf("\tSet '%s' to %d\n", keys[i], values[i]);
			}
			
			printf("\n%d records in %d buckets\n", ht->records, ht->max_buckets);
			node** all_records = HT_getpairs(ht);

			printf("\n---------\n'key': value\n---------\n");

			for (int i=0; all_records[i] != NULL; i++) {
				printf("'%s': %d\n", all_records[i]->key, all_records[i]->value);
			}
			printf("---------\n");

			// ensure all nodes are still present
			printf("\nChecking nodes\n");
			for (int i=0; i<4; i++) {
				if (HT_contains(ht, keys[i])) {
					printf("\tkey '%s' present\n", keys[i]);
				} else {
					printf("\t\033[92mkey '%s' not present\n", keys[i]);
				}
			}

			printf("\nFreeing Hashtable\n");
			HT_free(ht);

			break;
		}


		default: {
			printf("\033[91mInvalid test case: '%c'\033[0m\n", c);
			printf("\n \033[90m====== TEST END ======\033[0m\n\n");
			return 1;
		}
	}
	printf("\n \033[90m====== TEST END ======\033[0m\n\n");

	return 0;

}