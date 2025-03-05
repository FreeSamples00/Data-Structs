#include "linked_hash_table.h"

// Test functions here

int main(int args, char* argv[]) {
	int c;

	if (args == 2) {

		c = (int)argv[1][0];

	} else {
	
		printf("Test cases:\n");
		printf("\t1. Linked list\n");
		printf("\t2. Hash table set\n");
		printf("\t3. Hash table set + remove\n");
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

		case '2': { // set
			dict* ht = HT_init();

			HT_set(ht, "Hello World!", 42);

			break;
		}

		case '3': { // set + remove

			break;
		}

		case '4': { // hash collision

			break;
		}

		default: {
			printf("Invalid test case: %c\n", c);
			return 1;
		}
	}
	printf("\n ====== TEST END ======\n\n");

	return 0;

}