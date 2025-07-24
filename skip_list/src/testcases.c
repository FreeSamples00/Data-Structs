#include "skip_list.h"
#include <stdio.h>

int main(int args, char* argv[]) {
	int c;

	if (args == 2) {

		c = (int)argv[1][0];

	} else {
	
		printf("Test cases:\n");
		printf("0: Test initial insertion");
		
		c = getchar();
		printf("\n");

	}

	printf("\n \033[90m====== TEST BEGIN ======\033[0m\n\n");
	switch(c) {
		case '0': {
			sk_lst* sk = SK_init(3);

			SK_set(sk, "test", 0);

			SK_print(sk);

			break;
		}

		default: {
				printf("\033[91mERROR: Invalid test case: '%c'\n", c);
				return 1;
			}
		}

	printf("\n \033[90m====== TEST END ======\033[0m\n\n");

	return 0;

}