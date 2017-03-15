/*
 *	Code adapted from:
 *		The practice of programming/Brian W. Kernighan and Rob Pike,
 *			Addison-Wesley professional computing series, 1999.
 *			ISBN 0-201-61586-X
 *
 */

#ifndef	__NAMEVAL_LIST_HEADER__
#define	__NAMEVAL_LIST_HEADER__

#include "MyData.h"

/*
 * define our types
 */
typedef struct LLNode LLNode;

struct LLNode {
	MyData data;
	int index;
	struct LLNode *next;
};



/* llNewNode: create and initialize data */
LLNode *llNewNode(MyData *value);

/* llPrepend: add newp to front of list */
LLNode *llPrepend(LLNode *listp, LLNode *newp);

/* llAppend: add newp to end of listp */
LLNode *llAppend(LLNode *listp, LLNode *newp);

/* llInsertSort: place the value in the list according to index ordering */
LLNode *llInsertByIndexOrder(LLNode *listp, LLNode *newp);

/* llLookupKey: sequential search for name in listp */
LLNode *llLookupKey(LLNode *listp, char *key, int (*cmp)(char *, LLNode *));

/* llApplyFn: execute fn for each element of listp */
void llApplyFn(LLNode *listp, void (*fn)(LLNode*, void*), void *arg);

/* llFree : free all elements of listp */
void llFree(LLNode *listp);

#endif /*	__NAMEVAL_LIST_HEADER__ */
