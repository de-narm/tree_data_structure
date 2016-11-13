#ifndef __TEST_H__
#define __TEST_H__

#include <math.h>

#include "assert.h"
#include "../btree/btree.h"

/*
 * svg tests
 */
int svg_get_width_test();
int svg_get_width_test2();
int svg_get_width_test3();
int svg_get_height_test();
int svg_save_header_test();
int svg_save_footer_test();
int svg_render_rect_test();
int svg_render_line_test();
int svg_begin_text_test();
int svg_render_number_text_test();
int svg_end_text_test();

/*
 * btree tests
 */
int get_btree_depth_test();
int render_node_to_svg_test();
int render_node_to_svg_test2();
int save_btree_part_test();
int save_btree_test();
int save_btree_test2();

#endif //__TEST_H__
