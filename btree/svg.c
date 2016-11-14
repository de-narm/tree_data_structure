#include "svg.h"

int svg_get_width(int depth) {
  if(depth <= 0)
    return 0;
  int max_elem = pow(MAXNODE + 1, depth - 1);
  return (NODE_HOR_SPACING + NODE_WIDTH) * max_elem + NODE_HOR_SPACING;
}

int svg_get_height(int depth) {
  return depth * (NODE_HEIGHT_AND_VERT_SPACING) + NODE_VERT_SPACING;
}

int svg_save_header(FILE* fd, int width, int height) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_HEADER_STR, width, height, width, height);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

int svg_save_footer(FILE* fd) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_FOOTER_STR);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

int svg_render_rect(FILE* fd, int x, int y, int width, int height) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_RECT_STR, x, y, width, height);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}
int svg_render_line(FILE* fd, int x1, int y1, int x2, int y2) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_LINE_STR, x1, y1, x2, y2);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

int svg_begin_text(FILE* fd) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_TEXT_BEGIN_STR);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

int svg_render_number_text(FILE* fd, int number, int x, int y) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_NUMBER_TEXT_STR, number, x, y);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}

int svg_end_text(FILE* fd) {
  int ret;
  if(fd == NULL)
    return EXIT_FAILURE;
  ret = fprintf(fd, SVG_TEXT_END_STR);
  if(ret > 0)
    ret = EXIT_SUCCESS;
  return ret;
}
