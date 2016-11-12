/*
 * insert.c
 *
 *  Created on: Nov 11, 2016
 *      Author: Matthias Nickel
 */

#include "btree.h"


static void insert_into_node(struct node* node, stdelement e){
	short i;
	//case: node already has maximum number of elements
	if(node->number_of_elements >= MAXNODE){

	} else{
		i = getIndex(node, e);
		//case: new element is greater than all other values of node
		if(i + 1 == node->number_of_elements){
			node->elements[i] = e;
		//case: new element is first or between other elements
		} else{

		}
	}
}

short getIndex(struct node* node, stdelement e){
	short i;
	for(i = 0; i < node->number_of_elements; i++){
		if(node->elements[i] > e) break;
	}
	return i;
}

