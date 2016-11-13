/*
 * search.c
 *
 *  Created on: 11.11.2016
 *      Author: Matthias Nickel
 */

#include "btree.h"

struct node_element* findElement(stdelement e){
	short i;
	struct node* next = root;
	struct node_element* selectedNode = malloc(sizeof(struct node_element));
	selectedNode->index = -1;
	do{
		selectedNode->node = next;
		next = NULL;
		for(i = 0; i < selectedNode->node->number_of_elements; i++){
			//check if wanted value is in current node
			if(selectedNode->node->elements[i] == e){
				//set index of element
				selectedNode->index = i;
				break;
			//if value of node element is larger than e set new node
			} else if(selectedNode->node->elements[i] > e){
				next = selectedNode->node->children[i];
				break;
			}
		}
		//case e is larger than all elements in current node
		if(next == NULL && selectedNode->index == -1){
			next = selectedNode->node->children[i];
		}
	//stop loop if element was found or current node has no child node
	}while(next != NULL);
	//return index of element in current select node or -1 if element could not be found
	return selectedNode;
}
