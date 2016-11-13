#ifndef __BTREE_H__
#define __BTREE_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * defines the minimum filled elements in one node
 */
#define ORDER 2

/*
 * defines the maximum filled elements in one node
 */
#define MAXNODE (2 * ORDER)

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

int get_btree_depth(node_pointer tree);
int save_btree(const char* path, node_pointer tree);

struct node* root;

#endif //__BTREE_H__
