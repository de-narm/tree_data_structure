#include "btree.h"

#define NODE_TEXT_OFFSET_X 55
#define NODE_TEXT_OFFSET_Y 15
#define NODE_HEIGHT 20
#define NODE_VERT_SPACING 30
#define NODE_HOR_SPACING 30
#define NODE_HEIGHT_AND_VERT_SPACING (NODE_HEIGHT + NODE_VERT_SPACING)
#define FIELD_WIDTH 110
#define FIELD_SPACER_WIDTH 5
#define FIELD_AND_SPACER_WIDTH (FIELD_WIDTH + FIELD_SPACER_WIDTH)
#define NODE_WIDTH (FIELD_WIDTH + FIELD_AND_SPACER_WIDTH * (MAXNODE - 1))
#define HALF_NODE_WIDTH (NODE_WIDTH / 2)

const char* SVG_HEADER_STR = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n";
const char* SVG_LINE_STR = "\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"2\" />\n";
const char* SVG_RECT_STR = "\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"black\" stroke-width=\"2\" fill=\"none\"/>\n";
const char* SVG_TEXT_BEGIN_STR = "\t<g font-size=\"14\" font-family=\"sans-serif\" fill=\"black\" stroke=\"none\" text-anchor=\"middle\">\n";
const char* SVG_NUMBER_TEXT_STR = "\t\t<text x=\"%d\" y=\"%d\">%d</text>\n";
const char* SVG_TEXT_END_STR = "\t</g>\n";
const char* SVG_FOOTER_STR = "</svg>\n";

int get_btree_depth(node_pointer tree) {
  int ret = 0;
  int i, current;
  if(tree == NULL)
    return 0;
  for(i = 0; i <= MAXNODE; ++i) {
    current = get_btree_depth(tree->children[i]);
    if(current > ret)
      ret = current;
  }
  return ret + 1;
}

static int svg_get_width(int depth) {
  if(depth <= 0)
    return 0;
  int max_elem = pow(MAXNODE + 1, depth - 1);
  return (NODE_HOR_SPACING + NODE_WIDTH) * max_elem + NODE_HOR_SPACING;
}

static int svg_get_height(int depth) {
  return depth * (NODE_HEIGHT_AND_VERT_SPACING) + NODE_VERT_SPACING;
}

static int svg_save_header(FILE* fd, node_pointer tree) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  int depth = get_btree_depth(tree);
  int width = svg_get_width(depth);
  int height = svg_get_height(depth);
  ret = fprintf(fd, SVG_HEADER_STR, width, height);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

static int svg_save_footer(FILE* fd) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_FOOTER_STR);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

static int svg_render_rect(FILE* fd, int x, int y, int width, int height) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_RECT_STR, x, y, width, height);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}
static int svg_render_line(FILE* fd, int x1, int y1, int x2, int y2) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_LINE_STR, x1, y1, x2, y2);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

static int svg_begin_text(FILE* fd) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_TEXT_BEGIN_STR);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

static int svg_render_number_text(FILE* fd, int number, int x, int y) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_NUMBER_TEXT_STR, number, x, y);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

static int svg_end_text(FILE* fd) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_TEXT_END_STR);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

static int render_node_to_svg(FILE* fd, node_pointer node, int x, int y) {
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

static int save_btree_part(FILE* fd, node_pointer tree, int x, int y, int prev_stride) {
  int ret;
  int cur_x = x;
  int stride = prev_stride / (MAXNODE + 1);
  int i;
  int new_x = (x + HALF_NODE_WIDTH) - prev_stride / 2 - HALF_NODE_WIDTH;
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

int save_btree(const char* path, node_pointer tree) {
  int ret;
  int width, x, prev_stride;
  FILE* fd = fopen(path, "w");
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = svg_save_header(fd, tree);
  if(ret != EXIT_SUCCESS)
    return ret;
  width = svg_get_width(get_btree_depth(tree));
  x = width / 2 - HALF_NODE_WIDTH;
  prev_stride = width - 2 * NODE_HOR_SPACING;
  ret = save_btree_part(fd, tree, x, NODE_HOR_SPACING, prev_stride);
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
