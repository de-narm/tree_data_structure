/*
 * search.h
 *
 *  Created on: 11.11.2016
 *      Author: Matthias Nickel
 */

#ifndef SEARCH_H_
#define SEARCH_H_

#include"btree.h"

struct node_element{
	node_pointer node;
	short index;
};

struct node_element* findElement(stdelement e);

#endif /* SEARCH_H_ */
