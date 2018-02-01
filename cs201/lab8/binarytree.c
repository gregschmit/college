#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

typedef struct NODE *TREE;
struct NODE {
	int element;
	TREE leftChild, rightChild;
};

/*
Dealing with Binary Search Trees
every element in the leftChild subtree is < root
every element in the rightChild subtree is > root
*/

/* lookup returns 1 if x is found, 0 if x is not found */

int lookup (int x, TREE T){
int temp =0;
	if (T == NULL) {
		temp =0;
		}
	else {
		if (x == T->element){ temp = 1;}
		else {
			if (x < T->element ) {temp = lookup(x,T->leftChild);}
			else {temp =lookup(x,T->rightChild);}
			}
		}
	return temp;


}


/*
 insert uses recursion to determine  where the value x should reside in T
 When location is found, new node is created and reference to node
 is returned. want to make sure to only have 1 return statement in code
*/
TREE insert(int x, TREE T){

	if (T == NULL) {
		T=malloc(sizeof(*T));
		T->element=x;
		T->leftChild=NULL;
		T->rightChild=NULL;
	}
	else {
	if (x < T->element ) {T->leftChild=insert(x,T->leftChild);}
	else {T->rightChild=insert(x,T->rightChild);}
	}
	return T;

}

void delete(int x, TREE *pT) {
	if (pT == 0 || *pT) { return; }
	int exists;
	exists = lookup(x, *pT);
	if (!exists) { return; }
  struct NODE *cur;
	struct NODE *last;
	int lastleft;
	cur = *pT;
	last = 0;
	lastleft = 0;
	while (cur->element != x) {
		if (x < cur->element) {
			last = cur;
			lastleft = 1;
			cur = cur->leftChild;
		} else {
			last = cur;
			lastleft = 0;
			cur = cur->rightChild;
		}
	}
	if (cur->leftChild == 0 && cur->rightChild == 0) { // has no children
		free(cur);
		if (lastleft) {
			last->leftChild = 0;
		} else {
			last->rightChild = 0;
		}
	} else if (cur->leftChild == 0) {				// has left child, no left
		if (lastleft) {
			last->leftChild = cur->leftChild;
		} else {
			last->rightChild = cur->leftChild;
		}
	} else if (cur->rightChild == 0) {			// has right child, no left
		if (lastleft) {
			last->leftChild = cur->rightChild;
		} else {
			last->rightChild = cur->rightChild;
		}
	} else {
		/*
		 * has two children, need to go right, then left as far as I can, push
		 * the leaf to cur, delete the leaf. I could go left than right; it
		 * doesn't matter.
		 */
		struct NODE *leaf;
		struct NODE *lastleaf;
		leaf = cur->rightChild;
		lastleaf = cur;
		while (leaf->leftChild != 0) {
			lastleaf = leaf;
			leaf = leaf->leftChild;
		}
		// swap
		cur->element = leaf->element;
		// delete leaf
		free(leaf);
		lastleaf->leftChild = 0;
	}
	return;
}

int main() {

	TREE T=NULL;
	T=insert(50,T);
	T=insert(30,T);
	printf("30 %d \n",lookup(30,T));
	printf("130 %d \n",lookup(130,T));
	delete(3, T);

return 0;
}
