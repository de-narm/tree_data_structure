#include "test.h"

int main(void){
  int res = 0;
  int num_test = 0;
  
  res += get_btree_depth_test();
  ++num_test;
  res += svg_get_width_test();
  ++num_test;
  res += svg_get_width_test2();
  ++num_test;
  res += svg_get_width_test3();
  ++num_test;
  res += svg_get_height_test();
  ++num_test;
  res += svg_save_header_test();
  ++num_test;
  res += svg_save_footer_test();
  ++num_test;
  res += svg_render_rect_test();
  ++num_test;
  res += svg_render_line_test();
  ++num_test;
  res += svg_begin_text_test();
  ++num_test;
  res += svg_render_number_text_test();
  ++num_test;
  res += svg_end_text_test();
  ++num_test;
  res += render_node_to_svg_test();
  ++num_test;
  res += render_node_to_svg_test2();
  ++num_test;
  res += save_btree_part_test();
  ++num_test;
  res += save_btree_test();
  ++num_test;
  res += save_btree_test2();
  ++num_test;
  
  printf("Number of tests: %d\nNumber of failed tests: %d\n", num_test, res);
  return res;
}
