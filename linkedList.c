#define _CRT_SECURE_NO_WARNINGS
#include "linkedList.h"

BOOL  L_init(List* pList)
{//create empty list to the pointer pList
	if (pList == NULL) return False;

	pList->head.next = NULL;
	
	return True;
}

Node* L_insert(Node* pNode, Object* ob)
{//pNode: pointer to node BEFORE the place for the new one
	Node* tmp;
	if (!pNode) return NULL;
	tmp = (Node*)malloc(sizeof(Node));
	if (tmp != NULL) {
		tmp->value = ob;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}

	BOOL L_delete(Node* pNode)
	{//pNode: pointer to node BEFORE the node to be deleted
		Node* tmp;
		if (!pNode || !(tmp = pNode->next)) return False;
		pNode->next = tmp->next;
		free(tmp);
		return True;
	}

	BOOL L_free(List* pList)
	{//free all memory of the list that pointered by list
		Node* tmp;

		if (!pList) return False;

		for (tmp = &(pList->head); L_delete(tmp); );

		free(pList);
		return True;
	}


