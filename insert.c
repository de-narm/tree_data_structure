/*
 * insert.c
 *
 *  Created on: Nov 11, 2016
 *      Author: Matthias Nickel
 */

#include "insert.h"
#include "search.h"

short insert(stdelement e){
	struct node* node = root;
	if(!(node == NULL)){
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

void insert_into_node(struct node* node, stdelement e){
	short i, index = getIndex(node, e);
	//case: node already has maximum number of elements
	if(node->number_of_elements >= MAXNODE){
		stdelement extra;
		if(index == MAXNODE){
			extra = e;
		} else{
			extra = node->elements[MAXNODE - 1];
			for(i = index; i < MAXNODE - 1; i++){
				node->elements[i + 1] = node->elements[i];
			}
			node->elements[index] = e;
		}

		stdelement middle = node->elements[ORDER];
		struct node* newNode = malloc(sizeof(struct node));

		for(i = 0; i < ORDER - 1; i++){
			newNode->elements[i] = node->elements[ORDER + 1 + i];
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
			insert_into_node(node->parent, middle);
			newNode->parent = node->parent;
			for(i = 0; i < node->parent->number_of_elements; i++){
				if(node->parent->elements[i] == middle){
					node->parent->children[i+1] = newNode;
					break;
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
}

short getIndex(struct node* node, stdelement e){
	short i;
	for(i = 0; i < node->number_of_elements; i++){
		if(node->elements[i] > e) break;
	}
	return i;
}

