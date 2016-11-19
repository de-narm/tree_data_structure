#include "btree.h"

#define false 0
#define true 1

/*
 * Method used internaly for recursing through the tree. Params and return value are the same
 * as for compare().
 */
int inner_compare(node_pointer tree_a, node_pointer tree_b, struct compare_result *result) {
    // if the trees are NULL, this was a leaf node
    if(!tree_a || !tree_b) {
        // if one tree pointer is null and the other is not, either the trees would have
        // different depths or single leafs of it would. the former one should have been
        // handled by compare(), the later one means the b-tree is errornous. so in case
        // this happens give an invalid result
        if(tree_a || tree_b) {
            if(result)
                result->difference = -1;
            return false;
        }
        return true;
    }

    if(tree_a->number_of_elements != tree_b->number_of_elements) {
        if(result) {
            result->is_equal = false;
            result->difference = NUMBER_OF_ELEMENTS;
        }
        return false;
    }
    for(int i = 0; i < tree_a->number_of_elements; i++) {
        if(tree_a->elements[i] != tree_b->elements[i]) {
            if(result) {
                result->is_equal = false;
                result->difference = ELEMENT;
                result->path[result->depth] = i;
            }
            return false;
        }
    }

    // increase depth before recursing and decrease it afterwards
    if(result)
        result->depth++;
    for(int i = 0; i < tree_a->number_of_elements + 1; i++) {
        if(result)
            result->path[result->depth - 1] = i;
        if(!inner_compare(tree_a->children[i], tree_b->children[i], result))
            return false;
    }
    if(result)
        result->depth--;
    return true;
}

int compare(btree tree_a, btree tree_b, struct compare_result *result) {
    // compare the depth of the two trees
    int depth;
    if((depth = get_btree_depth(tree_a)) != get_btree_depth(tree_b)) {
        if(result) {
            result->is_equal = false;
            result->difference = DEPTH;
        }
        return false;
    }
    if(result) {
        result->path = calloc(depth, sizeof(result->path[0]));
        result->depth = 0;
    }

    // recursively compare the trees
    if(!inner_compare(tree_a->root, tree_b->root, result))
        return false;

    if(result)
        result->is_equal = true;
    return true;
}

void print_compare(btree tree_a, btree tree_b) {
    struct compare_result result;
    compare(tree_a, tree_b, &result);
    if(result.is_equal) {
        printf("Both trees are equal.\n");
        return;
    }
    if(result.difference == DEPTH) {
        printf("The trees have different depths.\n");
        return;
    }
    // iterate through the tree to find the node marked in result
    struct node *node_a = tree_a->root, *node_b = tree_b->root;
    for(int i = 0; i < result.depth; i++) {
        node_a = node_a->children[result.path[i]];
        node_b = node_b->children[result.path[i]];
    }
    if(result.difference == NUMBER_OF_ELEMENTS) {
        printf("Different number of elements in ");
        if(result.depth > 0) {
            printf("node");
            for(int i = 0; i < result.depth; i++)
                printf(" -> %d", result.path[i]);
            printf(" below ");
        }
        printf("root node.\n");
        printf("[");
        for(int i = 0; i < node_a->number_of_elements - 1; i++)
            printf("%d, ", node_a->elements[i]);
        printf("%d] != [", node_a->elements[node_a->number_of_elements - 1]);
        for(int i = 0; i < node_b->number_of_elements - 1; i++)
            printf("%d, ", node_b->elements[i]);
        printf("%d]\n", node_b->elements[node_b->number_of_elements - 1]);
    } else {
        printf("Different element at index %d in ", result.path[result.depth]);
        if(result.depth > 0) {
            printf("node");
            for(int i = 0; i < result.depth; i++)
                printf(" -> %d", result.path[i]);
            printf(" below ");
        }
        printf("root node.\n");
        printf("%d != %d\n", node_a->elements[result.path[result.depth]], node_b->elements[result.path[result.depth]]);
    }
}
