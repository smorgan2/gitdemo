/*
 *	Code adapted from:
 *		The practice of programming/Brian W. Kernighan and Rob Pike,
 *			Addison-Wesley professional computing series, 1999.
 *			ISBN 0-201-61586-X
 */

#include <stdlib.h>
#include <string.h>

#include "LLNode.h"


/*
 * llNewNode: create and initialize data
 */
LLNode *
llNewNode(MyData *data)
{
	LLNode *newp;

	newp = (LLNode *) malloc(sizeof(LLNode));

	/* assign data within new node */
	newp->data = *data;

	/* make sure we point at nothing */
	newp->next = NULL;

	return newp;
}


/*
 * llAppend: add newp to end of listp
 *
 * as above, we always return the value that
 * should be the new head of the list 
 */
LLNode *
llAppend(LLNode *listp, LLNode *newp)
{
	LLNode *p;

	if (listp == NULL)
		return newp;

	for (p = listp; p->next; p = p->next)
		;

	p->next = newp;
	return listp;
}


/*
 * llPrepend: add newp to front of list
 *
 * by returning ourselves, we give back the
 * value that should be the new head of the list
 */
LLNode *
llPrepend(LLNode *listp, LLNode *newp)
{
	newp->next = listp;
	return newp;
}


/* llInsertSort: place the value in the list according to index ordering */
LLNode *
llInsertByIndexOrder(LLNode *listp, LLNode *newp)
{
	LLNode *p, *prevp = NULL;

	if (listp == NULL)
		return newp;
	
	/** find either the end, or the point where we should go */
	p = listp;
	while (p->index < newp->index && p->next != NULL) {
		prevp = p;
		p = p->next;
	}

	/*
	 * if we have found a larger index, then we go before it
	 */
	if ( p->index >= newp->index) {
		newp->next = p;

		/*
		 * if there is only one node, there won't be a prevp,
		 * and we are the new head
		 */
		if (prevp == NULL) return newp;

		prevp->next = newp;
		return listp;
	}

	/* otherwise, we go at the end */
	p->next = newp;
	return listp;
}


/* llLookupKey: sequential search for key in listp */
LLNode *
llLookupKey(LLNode *listp, char *key, int (*comparator)(char *, LLNode *))
{
	for ( ; listp != NULL; listp = listp->next)
		if ((*comparator)(key, listp) == 0)
			return listp;

	return NULL; /* no match */
}


/* llApplyFn: execute fn for each element of listp */
void
llApplyFn(LLNode *listp, void (*fn)(LLNode*, void*), void *arg)
{
	for ( ; listp != NULL; listp = listp->next)
		(*fn)(listp, arg); /* call the function */
}


/* llFree : free all elements of listp */
void
llFree(LLNode *listp)
{
	LLNode *next;

	for ( ; listp != NULL; listp = next) {

		/** hang on to the next pointer */
		next = listp->next;

		/** free the list node itself */
		free(listp);
	}
}

