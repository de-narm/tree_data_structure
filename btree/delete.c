#include "btree.h"

void delete_leaf(struct node* node, stdelement e) {
  //get index of e
  int i;
  for(i = 0; i < node->number_of_elements; i++) {
    if(node->elements[i] == e)
      break;
  } 
  //if element dosen't exist in target node, stop
  if(i == node->number_of_elements)
    return;

  //delete e
  for(; i < (node->number_of_elements-1); i++) {
    node->elements[i] = node->elements[i+1];
  }
  node->number_of_elements--;

  //restore balance if necessary
  if(node->number_of_elements < ORDER) {
    struct node* parent = node->parent;
    int i;
    for (i = 0; i < (MAXNODE+1); i++) {
      if(parent->children[i] == node)
        break;
    }  
    //test left/right neighbours
    if(i != 0 && parent->children[i-1]->number_of_elements > ORDER) {
        struct node* left = parent->children[i-1];
        int j;
        //shift element
        for(j = (MAXNODE-1); j > 0; j--) {
          node->elements[i] = node->elements[i-1];
        }
        node->elements[0] = parent->elements[i-1];
        parent->elements[i-1] = left->elements[left->number_of_elements-1];
        node->number_of_elements++;
        left->number_of_elements--;
        return;
    }
    if(i != MAXNODE && parent->children[i+1]->number_of_elements > ORDER) {
        struct node* right = parent->children[i+1];
        //shift element
        node->elements[node->number_of_elements] = parent->elements[i];
        parent->elements[i] = right->elements[0];
        int j;
        for(j = 0; j < MAXNODE; j++) {
          right->elements[j] = right->elements[j+1];
        }
        node->number_of_elements++;
        right->number_of_elements--;
        return;
    }

    //if both neighbours fail, merge with preference for the right one
    struct node* right;
    if(i != (MAXNODE))
      right = parent->children[i+1];
    else {
      right = node;
      node = parent->children[i-1];
      i--;
    }
    int j;
    node->elements[node->number_of_elements] = parent->elements[i];
    for(j = (node->number_of_elements+1); j < MAXNODE; j++) {
      node->elements[j] = right->elements[j-(node->number_of_elements+1)];
    }
    node->number_of_elements += (right->number_of_elements+1);
    
    //delete the pointer to right neighbour
    for(j = i+1; j < MAXNODE; j++) {
      parent->children[j] = parent->children[j+1];
    }
    parent->children[MAXNODE] = NULL;
    delete_leaf(parent, parent->elements[i]);
  }
  return;
}

void delete(stdelement e) {
  struct node_element* node_e = findElement(e);
  if (!node_e)
    return;
  struct node* node = node_e->node;
  if(!node->children[0])
    delete_leaf(node, e);
  else { 
    int i = node_e->index;
    //get next larger value
    struct node* child = node->children[i+1];
    while(child->children[0]) {
      child = child->children[0];
    }
    node->elements[i] = child->elements[0];
    delete_leaf(child, child->elements[0]);
  }  
}
