/*
 * search.c
 *
 *  Created on: 11.11.2016
 *      Author: Matthias Nickel
 */

#include "btree.h"
#include "search.h"

short findElement(struct node* node, stdelement e){
	short i, result = -1;
	node_pointer newNode;
	do{
		newNode = NULL;
		for(i = 0; i < node->number_of_elements; i++){
			//check if wanted value is in current node
			if(node->elements[i] == e){
				//set index of element
				result = i;
				break;
			//if value of node element is larger than e set new node
			} else if(node->elements[i] > e){
				newNode = node->children[i];
				break;
			}
		}
		//case e is larger than all elements in current node
		if(newNode == NULL && result == -1){
			newNode = node->children[i];
		}
		//set current node to child node
		if(newNode != NULL && result == -1){
			node = newNode;
		}
	//stop loop if element was found or current node has no child node
	}while(newNode != NULL);
	//return index of element in current select node or -1 if element could not be found
	return result;
}
