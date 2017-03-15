#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "LLNode.h"



/* forward declarations */
static void printHelp();

int loadData(LLNode **list, char *filename, int verbose, int reverse)
{
}

int main(int argc, char **argv)
{
	FILE *ofp = stdout;
	LLNode *aList = NULL;
	int reverse = 0;
	int verbose = 0;
	int optionChar;
	int i;


	while ((optionChar = getopt(argc, argv, "hvro:")) != -1) {
		switch (optionChar) {

		case 'r':
			reverse = 1 - reverse;
			break;

		case 'v':
			verbose++;
			break;

		case 'o':
			/* override the standard output destination */
			ofp = fopen(optarg, "w");
			if (ofp == NULL)
			{
				/*
				 * if we couldn't open the file, use strerror(3)
				 * to let the user know why
				 */
				(void) fprintf(stderr,
						"Cannot open '%s': %s\n",
						optarg, strerror(errno));
				exit(1);
			}
			break;

		case 'h':
		case '?':
		default:
			printHelp();
			exit (1);
		}
	}

	/* skip past the arguments processed by getopt(3) */
	argc -= optind;
	argv += optind;



	/* sort any files seen, collecting (logical) exit status */
	for (i = 0; i < argc; i++)
	{
		if (loadData(&aList, argv[i], verbose, reverse) < 0)
		{
			fprintf(stderr, "Failed processing file '%s'\n", argv[i]);
		}
	}

	if (aList != NULL)
	{
		printList(ofp, aList);

		/** delete our data */
		llFree(aList);
	}

	return 0;
}

void printHelp()
{
	printf("Print out lines from a file\n");
	printf("\n");
	printf("Options: -r reverses, -v is more verbose, -o set output file\n");
}
