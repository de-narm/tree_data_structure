#include "btree.h"

const int BORDER_OFFSET_X = 10;
const int BORDER_OFFSET_Y = 10;
const int NODE_TEXT_OFFSET = 55;
const int NODE_HEIGHT = 20;
const int NODE_VERT_SPACING = 30;
const int NODE_HEIGHT_AND_VERT_SPACING = NODE_HEGHT + NODE_VERT_SPACING;
const int FIELD_WIDTH = 110;
const int FIELD_SPACER_WIDTH = 5;
const int FIELD_AND_SPACER_WIDTH = FIELD_WIDTH + FIELD_SPACER_WIDTH;
const int NODE_WIDTH = FIELD_WIDTH + (FIELD_AND_SPACER_WIDTH) * (MAXNODE - 1);
const int HALF_NODE_WIDTH = NODE_WIDTH / 2;

const char* SVG_HEADER_STR = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n";
const char* SVG_LINE_STR = "\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"2\" />\n";
const char* SVG_RECT_STRING = "\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"black\" stroke-width=\"2\" fill=\"none\"/>\n";
const char* SVG_TEXT_BEGIN_STR = "\t<g font-size=\"14\" font-family=\"sans-serif\" fill=\"black\" stroke=\"none\" text-anchor=\"middle\">\n";
const char* SVG_NUMBER_TEXT_STR = "\t\t<text x=\"65\" y=\"25\">%d</text>\n";
const char* SVG_TEXT_END_STR = "\t<\g>\n";
const char* SVG_FOOTER_STR = "</svg>\n";

int get_btree_depth(node_pointer tree) {
  int ret = 0;
  int i, current;
  for(i = 0; i <= MAXNODE; ++i) {
    current = get_btree_depth(tree->children[i]);
    if(current > ret)
      ret = current;
  }
  return ret + 1;
}

static int svg_get_width(int depth) {
  return NODE_WIDTH * depth * MAXNODE + 2 * BORDER_OFFSET_X;
}

static int svg_get_height(int depth) {
  return depth * (NODE_HEIGHT_AND_VERT_SPACING) + 2 * BORDER_OFFSET_Y;
}

static int svg_save_head(FILE* fd, node_pointer tree) {
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

static int svg_render_number_text(FILE* fd, int number) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_NUMBER_TEXT_STR, number);
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
  int text_offset_x = NODE_TEXT_OFFSET;
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
    ret = svg_render_number_text(fd, node->elements[i]);
    if(ret != EXIT_SUCCESS)
      return ret;
  }
  ret = svg_end_text(fd);
  return ret;
}

static int save_btree_part(FILE* fd, node_pointer tree, int x, int y, int prev_x) {
  int ret;
  int par_x, par_y, cur_x;
  int i, new_x, new_y;
  if(fd == NULL)
    return EXIT_FAILURE;
  if(tree == NULL)
    return EXIT_SUCCESS;
  ret = render_node_to_svg(fd, tree, x, y);
  //render connection to parent
  if(tree->parent != NULL) {
    old_x = prev_x + HALF_NODE_WIDTH;
    old_y = y - NODE_HEIGHT_AND_VERT_SPACING;
    cur_x = x + HALF_NODE_WIDTH;
    ret = svg_render_line(fd, old_x, old_y, cur_x, y);
    if(ret != EXIT_SUCCESS)
      return ret;
  }
  //render nodes
  for(i = 0; i < MAXNODE + 1; ++i) {
    new_x = (x + HALF_NODE_WIDTH) * 2 / (MAXNODE + 1) - HALF_NODE_WIDTH;
    new_y = y + NODE_HEIGHT_AND_VERT_SPACING;
    ret = save_btree_part(fd, tree->children[i], new_x, new_y, x);
    if(ret != EXIT_SUCCESS)
      return ret;
  }
  return ret;
}

int save_btree(const char* path, node_pointer tree) {
  int ret;
  int x;
  FILE* f = fopen(path, "w");
  if(f == NULL)
    return EXIT_FAILURE;
  ret = svg_save_header(fd, tree);
  if(ret != EXIT_SUCCESS)
    return ret;
  x = svg_get_width(get_btree_depth(tree)) / 2 - HALF_NODE_WIDTH;
  ret = save_btree_part(f, tree, x, START_OFFSET_Y, 0);
  if(ret != EXIT_SUCCESS) {
    fclose(f);
    return ret;
  }
  ret = svg_save_footer(fd);
  if(ret != EXIT_SUCCESS) {
    fclose(f);
    return ret;
  }
  ret = fclose(f);
  return ret;
}
