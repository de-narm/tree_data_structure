#ifndef __BTREE_H__
#define __BTREE_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "btree_config.h"
#include "svg.h"

/*
 * pointer to a node struct
 */
typedef struct node * node_pointer;

/*
 * use unsigned integers as stdelement to make output possible
 */
typedef unsigned int stdelement;

/*
 * struct for the b-tree data structure
 */
struct node {
  node_pointer parent;
  short number_of_elements;
  stdelement elements[MAXNODE];
  node_pointer children[MAXNODE + 1];
};

struct node_element{
	node_pointer node;
	short index;
};

struct node* root;

int get_btree_depth(node_pointer tree);
int render_node_to_svg(FILE* fd, node_pointer node, int x, int y);
int save_btree_part(FILE* fd, node_pointer tree, int x, int y, int prev_stride);
int save_btree(const char* path, node_pointer tree);

short insert(stdelement e);
void insert_into_node(struct node* node, stdelement e);
short getIndex(struct node* node, stdelement e);

void delete(struct node* node, stdelement e);
void delete_leaf(struct node* node, stdelement e);

struct node_element* findElement(stdelement e);

#endif //__BTREE_H__
