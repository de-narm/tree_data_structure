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
		root = malloc(sizeof(struct node));
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
		stdelement extra;
		if(index == MAXNODE){
			extra = e;
		} else{
			extra = node->elements[MAXNODE - 1];
			for(i = MAXNODE - 1; i > index; i--){
				node->elements[i] = node->elements[i-1];
			}
			node->elements[index] = e;
		}

		stdelement middle = node->elements[ORDER];
		newNode = malloc(sizeof(struct node));
		short right = ORDER + 1;
		short ci = (index >= ORDER) ? right : ORDER;

		for(i = 0; i < ORDER; i++){
			newNode->elements[i] = node->elements[right + i];
			newNode->children[i] = node->children[ci + i];
			node->elements[right + i] = 0;
			node->children[ci + i] = NULL;
			if(newNode->children[i] != NULL){
				newNode->children[i]->parent = newNode;
			}
		}

		newNode->children[i] = node->children[MAXNODE];
		node->children[MAXNODE] = NULL;
		if(newNode->children[i] != NULL){
			newNode->children[i]->parent = newNode;
		}
		newNode->elements[ORDER - 1] = extra;

		node->number_of_elements = ORDER;
		newNode->number_of_elements = ORDER;

		if(node == root){
			root = NULL;
			insert(middle);
			root->children[0] = node;
			root->children[1] = newNode;
			node->parent = root;
			newNode->parent = root;
		}else{
			struct node* newParent = insert_into_node(node->parent, middle);
			i = getIndex(node->parent, middle);
			if(newParent == NULL){
				newNode->parent = node->parent;

				moveChildren(node->parent, i);
				node->parent->children[i] = node;
				node->parent->children[i+1] = newNode;
 			} else{
 				if(i == -1){
 					i = getIndex(newParent, middle);
 					newNode->parent = newParent;

 					if(i == -1){
 						moveChildren(newParent, 0);
 						node->parent->children[ORDER] = node;
 						newParent->children[0] = newNode;
 					} else{
 						node->parent = newParent;

 						moveChildren(newParent, i);
 						newParent->children[i+1] = newNode;
 					}
 				}else{
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
	unsigned short i, result = -1;
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

