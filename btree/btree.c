#include "btree.h"

btree create_btree() {
    return calloc(1, sizeof(btree));
}

void destroy_btree_node(node_pointer node) {
    if(!node)
        return;
    for(int i = 0; i <= node->number_of_elements; i++)
        destroy_btree_node(node->children[i]);
    free(node);
}

void destroy_btree(btree tree) {
    destroy_btree_node(tree->root);
    free(tree);
}

int get_btree_depth(btree tree) {
    node_pointer node = tree->root;
    int i = 0;
    while(node) {
        node = node->children[0];
        i++;
    }
    return i;
}

int render_node_to_svg(FILE* fd, node_pointer node, int x, int y) {
  int ret;
  int i;
  int text_offset_x = NODE_TEXT_OFFSET_X + x;
  int text_offset_y = NODE_TEXT_OFFSET_Y + y;
  int line_offset_x = FIELD_WIDTH + x;
  if(fd == NULL)
    return EXIT_FAILURE;
  //render rect
  ret = svg_render_rect(fd, x, y, NODE_WIDTH, NODE_HEIGHT);
  if(ret != EXIT_SUCCESS)
    return ret;
  //render seperation lines
  for(i = 0; i < MAXNODE - 1; ++i) {
    ret = svg_render_line(fd, line_offset_x, y, line_offset_x, y + NODE_HEIGHT);
    if(ret != EXIT_SUCCESS)
      return ret;
    ret = svg_render_line(fd, line_offset_x + 5, y, line_offset_x + 5, y + NODE_HEIGHT);
    if(ret != EXIT_SUCCESS)
      return ret;
    line_offset_x += FIELD_AND_SPACER_WIDTH;
  }
  //render number content
  ret = svg_begin_text(fd);
  if(ret != EXIT_SUCCESS)
    return ret;
  for(i = 0; i < MAXNODE; ++i) {
    if(i < node->number_of_elements) {
      ret = svg_render_number_text(fd, text_offset_x, text_offset_y, node->elements[i]);
      text_offset_x += (FIELD_AND_SPACER_WIDTH);
      if(ret != EXIT_SUCCESS)
	return ret;      
    }
  }
  ret = svg_end_text(fd);
  return ret;
}

int save_btree_part(FILE* fd, node_pointer tree, int x, int y, int prev_stride) {
  int ret;
  int i;
  int cur_x = x;
  int stride = prev_stride / (MAXNODE + 1);
  int new_x = (x + HALF_NODE_WIDTH) - prev_stride / 2 + stride / 2 - HALF_NODE_WIDTH;
  int new_y = y + NODE_HEIGHT_AND_VERT_SPACING;
  if(fd == NULL)
    return EXIT_FAILURE;
  if(tree == NULL)
    return EXIT_SUCCESS;
  ret = render_node_to_svg(fd, tree, x, y);
  if(ret != EXIT_SUCCESS)
    return ret;
  
  //render nodes with lines
  for(i = 0; i < MAXNODE + 1; ++i) {
    if(tree->children[i] != NULL) {
      //render the child
      ret = save_btree_part(fd, tree->children[i], new_x, new_y, stride);
      if(ret != EXIT_SUCCESS)
	return ret;
    
      //render line to child
      ret = svg_render_line(fd, new_x, new_y, cur_x, y + NODE_HEIGHT);
      if(ret != EXIT_SUCCESS)
      return ret;
    }
      
    //calculate the position of the child
    new_x += stride;
    cur_x += FIELD_AND_SPACER_WIDTH;
    
    //substract the spacer
    if(i == MAXNODE - 1)
    cur_x -= FIELD_SPACER_WIDTH;
  }
  return ret;
}

int save_btree(const char* path, btree tree) {
  int ret;
  int depth, width, height, x, prev_stride;
  FILE* fd = fopen(path, "w");
  if(fd == NULL)
    return EXIT_FAILURE;
  depth = get_btree_depth(tree);
  width = svg_get_width(depth);
  height = svg_get_height(depth);
  x = width / 2 - HALF_NODE_WIDTH;
  prev_stride = width - NODE_HOR_SPACING;
  ret = svg_save_header(fd, width, height);
  if(ret != EXIT_SUCCESS)
    return ret;
  ret = save_btree_part(fd, tree->root, x, NODE_HOR_SPACING, prev_stride);
  if(ret != EXIT_SUCCESS) {
    fclose(fd);
    return ret;
  }
  ret = svg_save_footer(fd);
  if(ret != EXIT_SUCCESS) {
    fclose(fd);
    return ret;
  }
  ret = fclose(fd);
  return ret;
}
