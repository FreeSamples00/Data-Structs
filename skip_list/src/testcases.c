#include "skip_list.h"

int main(int args, char* argv[]) {
	int c;

	if (args == 2) {

		c = (int)argv[1][0];

	} else {
	
		printf("Test cases:\n");
		
		c = getchar();
		printf("\n");

	}

	printf("\n \033[90m====== TEST BEGIN ======\033[0m\n\n");
	switch(c) {
		case '0': {

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