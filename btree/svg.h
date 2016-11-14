#ifndef __SVG_H__
#define __SVG_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "btree_config.h"
#include "svg_config.h"

int svg_get_width(int depth);
int svg_get_height(int depth);
int svg_save_header(FILE* fd, int width, int height);
int svg_save_footer(FILE* fd);
int svg_render_rect(FILE* fd, int x, int y, int width, int height);
int svg_render_line(FILE* fd, int x1, int y1, int x2, int y2);
int svg_begin_text(FILE* fd);
int svg_render_number_text(FILE* fd, int number, int x, int y);
int svg_end_text(FILE* fd);

#endif //__SVG_H__
