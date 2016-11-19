#ifndef __BTREE_H__
#define __BTREE_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "btree_config.h"
#include "svg.h"

/**
 * @file btree.h
 * @brief Header file which contains required definitions for b-tree.
 */

/**
 * pointer to a node struct
 */
typedef struct node * node_pointer;

/**
 * use unsigned integers as stdelement to make output possible
 */
typedef unsigned int stdelement;

/**
 * @brief struct for the b-tree data structure
 */
struct node {
	/** parent node of this node */
	node_pointer parent;
	/** number of stored elements */
	short number_of_elements;
	/** array to store elements in node */
	stdelement elements[MAXNODE];
	/** array of child nodes */
	node_pointer children[MAXNODE + 1];
};

/**
 * @brief struct to store reference of node and index of an element
 */
struct node_element{
	/** node where element is stored */
	node_pointer node;
	/** index of stored element */
	short index;
};

/**
 * @brief struct to store result of comparison of b-trees
 */
struct compare_result {
	/**
	 *	true (1) if the trees are equal, false (0) otherwise
	 */
    int is_equal;
    /**
     *	only valid if is_equal == false
	 *	DEPTH if the trees have a different depth
	 *	NUMBER_OF_ELEMENTS if a node was found in which the number of elements differs
	 *	ELEMENT if an element was found of which the value differs
	 */
    enum {DEPTH, NUMBER_OF_ELEMENTS, ELEMENT} difference;
    /**
     *	only valid if is_equal == false and difference != DEPTH
     *	contains the level on which a difference was found. the root node is level 0
     */
    int depth;
    /**
     *	only valid if is_equal == false and difference != DEPTH
     *	contains a path from the root node to the node in which the difference was found.
     *	so {1} means the first child of the root node and {2, 0} means the zeroth of the
     *	second child of the root node. this array contains `depth` values. if difference ==
     *	ELEMENT, this contains an additional value for the index of the elemennt.
     */
    int *path;
};
/**
 *	@brief struct which contains the root of b-tree
 */
typedef struct {
	/** root of b-tree */
    struct node *root;
} * btree;
/**
 * @brief Allocates memory for new b-tree
 * @return new created (empty) b-tree
 */
btree create_btree();
/**
 *	@brief Gives allocated memory free.
 *	@param tree tree which shall be destroyed
 */
void destroy_btree(btree tree);
/**
 * @brief Calculates depth of b-tree.
 * @param tree b-tree which depth shall be calculated
 * @return depth of b-tree
 */
int get_btree_depth(btree tree);
/**
 * @brief Writes node svg file.
 * @param fd file where node shall be stored
 * @param node node which shall be stored
 * @param x x position of node in graph
 * @param y y position of node in graph
 * @return EXIT_SUCCESS if everything went right else EXIT_FAILURE
 */
int render_node_to_svg(FILE* fd, node_pointer node, int x, int y);
/**
 * @brief Saves part of a b-tree to file
 * @param fd file where part of b-tree shall be stored
 * @param tree node from where part of b-tree shall be written
 * @param x x position of node
 * @param y y position of node
 * @param prev_stride previous stride
 * @return EXIT_SUCCESS if everything went right else EXIT_FAILURE
 */
int save_btree_part(FILE* fd, node_pointer tree, int x, int y, int prev_stride);
/**
 * @brief Saves b-tree to svg file.
 * @param path relative path and name of svg file
 * @param tree b-tree which shall be stored
 * @return status of file creation
 */
int save_btree(const char* path, btree tree);
/**
 * @brief Inserts an element to b-tree
 * @param e element which shall be inserted
 * @param tree b-tree where element shall be inserted
 */
short insert(btree tree, stdelement e);
/**
 * @brief Inserts element to node.
 * @param node node where element shall be stored
 * @param e element which shall be stored
 * @param tree b-tree where element shall be inserted
 * @return new created node if given node got split else NULL
 */
struct node *insert_into_node(btree tree, struct node* node, stdelement e);
/**
 * @brief Tries to find element in node.
 * @param node node which shall be searched for element
 * @param e element which shall be searched for
 * @return index of element in node or -1 if element is not in node
 */
short getIndex(struct node* node, stdelement e);
/**
 * @brief Moves children to next higher position.
 * @param node node which children shall be moved
 * @param index index of child where shall be started
 */
void moveChildren(struct node* node, short index);
/**
 * @brief Removes element from b-tree.
 * @param e element which shall be removed
 * @param tree tree where element shall be removed
 */
void delete(btree tree, stdelement e);
/**
 * @brief Removes element and entire leaf from b-tree.
 * @param node node which shall be removed
 * @param e element which shall be removed
 * @param tree tree where element and node shall be removed
 */
void delete_leaf(btree tree, struct node* node, stdelement e);
/**
 * @brief Tries to find element in tree.
 * @param e element which shall be searched for
 * @param tree b-tree which shall be searched
 * @return node and index where element is stored or index -1 if element is not in tree
 */
struct node_element* findElement(btree tree, stdelement e);
/**
 * @brief Function to compare two b-tree with each other.
 * This function returns true if two B-Trees are equal and false otherwise. Optionally
 * some additional informations can be given about what difference was found and where.
 *
 * @param tree_a A pointer to the root of a tree
 * @param tree_b A pointer to the root of another tree
 * @param result A struct, into which additional informations will be written.
 *               May be NULL if not needed
 * @return 1 if tree_a and tree_b are equal, 0 otherwise
 */
int compare(btree tree_a, btree tree_b, struct compare_result *result);
/**
 * @brief Compare two trees and output the findings to stdout.
 * Compare two trees and output the findings to stdout. This exists mostly for
 * debug purposes and to give an example on how to use the result struct.
 *
 * @param tree_a A pointer to the root of a tree
 * @param tree_b A pointer to the root of another tree
 */
void print_compare(btree tree_a, btree tree_b);

#endif //__BTREE_H__
