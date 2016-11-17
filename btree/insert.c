/*
 * insert.c
 *
 *  Created on: Nov 11, 2016
 *      Author: Matthias Nickel
 */

#include "btree.h"

short insert(stdelement e){
	if(!(root == NULL)){
		//look if element is already in tree
		struct node_element* selected = findElement(e);
		/*
		 * if not insert element into tree,
		 * correct node already selected by findElement function
		 */
		if(selected->index == -1){
			insert_into_node(selected->node, e);
		}
	//if node is empty create new root with e as first element
	}else{
		root = calloc(1, sizeof(struct node));
		root->elements[0] = e;
		root->number_of_elements = 1;
	}
	//return current selected/new created node
	return 0;
}

struct node* insert_into_node(struct node* node, stdelement e){
	//get index where element shall be added
	short i, index;
	for(i = 0; i < node->number_of_elements; i++){
		if(node->elements[i] > e) break;
	}
	index = i;
	struct node* newNode = NULL;
	//case: node already has maximum number of elements
	if(node->number_of_elements >= MAXNODE){
		//element to 'expand' the array of elements
		stdelement extra;
		/*
		 * insert new element to correct position in array
		 * or if e is largest element, set to extra
		 */
		if(index == MAXNODE){
			extra = e;
		} else{
			extra = node->elements[MAXNODE - 1];
			for(i = MAXNODE - 1; i > index; i--){
				node->elements[i] = node->elements[i-1];
			}
			node->elements[index] = e;
		}

		//get middle element
		stdelement middle = node->elements[ORDER];
		newNode = calloc(1, sizeof(struct node));
		//position of first element of right half
		short right = ORDER + 1;
		//set position of first child node of right half
		short ci = (index >= ORDER) ? right : ORDER;

		for(i = 0; i < ORDER; i++){
			newNode->elements[i] = node->elements[right + i];
			newNode->children[i] = node->children[ci + i];
			//remove values of right half
			node->elements[right + i] = 0;
			node->children[ci + i] = NULL;
			//change parent of children of newNode
			if(newNode->children[i] != NULL){
				newNode->children[i]->parent = newNode;
			}
		}

		//do also the same to the last child node
		newNode->children[i] = node->children[MAXNODE];
		node->children[MAXNODE] = NULL;
		if(newNode->children[i] != NULL){
			newNode->children[i]->parent = newNode;
		}
		//set value of largest element to newNode
		newNode->elements[ORDER - 1] = extra;
		//set new size of split node
		node->number_of_elements = ORDER;
		newNode->number_of_elements = ORDER;
		//if split node is root node create new root with middle element
		if(node == root){
			root = NULL;
			insert(middle);
			root->children[0] = node;
			root->children[1] = newNode;
			node->parent = root;
			newNode->parent = root;
		}else{
			//give middle value to node above
			struct node* newParent = insert_into_node(node->parent, middle);
			i = getIndex(node->parent, middle);
			//check if node above was also split
			if(newParent == NULL){
				/*
				 * if not, set parent of newNode to parent of node
				 * and add newNode as child
				 */
				newNode->parent = node->parent;
				moveChildren(node->parent, i);
				node->parent->children[i+1] = newNode;
 			} else{
 				/*
 				 * case:
 				 * node above was also split and middle element is not
 				 * in parent of node
 				 */
 				if(i == -1){
 					//check if middle element is in NewParent
 					i = getIndex(newParent, middle);
 					newNode->parent = newParent;
 					if(i == -1){
 						/**
 						 * case:
 						 * middle was also middle element of node above
 						 */
 						moveChildren(newParent, 0);
 						newParent->children[0] = newNode;
 					} else{
 						/*
 						 * case:
 						 * middle node is in newParent
 						 */
 						node->parent = newParent;

 						moveChildren(newParent, i);
 						newParent->children[i+1] = newNode;
 					}
 				}else{
 					/**
 					 * case:
 					 * node above got split and middle element got inserted
 					 * in left side
 					 */
 					newNode->parent = node->parent;

 					moveChildren(node->parent, i);
 					node->parent->children[i+1] = newNode;
 				}
 			}
		}
	} else{
		//case: new element is first or between other elements
		if((index + 1) <= node->number_of_elements){
			for(i = node->number_of_elements; i > index; i--){
				node->elements[i] = node->elements[i-1];
			}
		}
		node->elements[index] = e;
		node->number_of_elements++;
	}
	return newNode;
}


short getIndex(struct node* node, stdelement e){
	short i, result = -1;
	for(i = 0; i < node->number_of_elements; i++){
		if(node->elements[i] == e){
			result = i;
			break;
		}
	}
	return result;
}

void moveChildren(struct node* node, short index){
	unsigned short i;
	for(i = node->number_of_elements; i > index; i--){
		node->children[i] = node->children[i-1];
	}
}

