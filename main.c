#include "btree.c"
#include <string.h>

static int assert_equals_int(const int expected, const int actual) {
  if(expected == actual)
    return EXIT_SUCCESS;
  fprintf(stderr, "ERROR: expected %d, but was %d!\n", expected, actual);
  return EXIT_FAILURE;
}

static int assert_equals_str(const char* expected, const char* actual) {
  if(expected == actual)
    return EXIT_SUCCESS;
  if(expected == NULL || actual == NULL) {
    fprintf(stderr, "ERROR: one string was empty!\n");
    return EXIT_FAILURE;
  }
  if(strcmp(expected, actual) == 0)
    return EXIT_SUCCESS;
  fprintf(stderr, "ERROR: expected \"%s\", but was \"%s\"!\n", expected, actual);
  return EXIT_FAILURE;
}

static int assert_equals_file(const char* expected_path, const char* actual_path, size_t max_size) {
  if(expected_path == actual_path)
    return EXIT_SUCCESS;
  if(expected_path == NULL || actual_path == NULL) {
    fprintf(stderr, "ERROR: one path is empty!\n");
    return EXIT_FAILURE;
  }
  char* buffer_expected = (char*)malloc(sizeof(char) * max_size);
  if(buffer_expected == NULL) {
    fprintf(stderr, "FATAL ERROR: couldn't allocate enough memory! Please rerun the tests with more memory!\n");
    return EXIT_FAILURE;
  }
  char* buffer_actual = (char*)malloc(sizeof(char) * max_size);
  if(buffer_actual == NULL) {
    fprintf(stderr, "FATAL ERROR: couldn't allocate enough memory! Please rerun the tests with more memory!\n");
    free(buffer_expected);
    return EXIT_FAILURE;
  }
  FILE* f_expected = fopen(expected_path, "r");
  if(f_expected == NULL) {
    fprintf(stderr, "FATAL ERROR: couldn't open file '%s'!\n", expected_path);
    free(buffer_expected);
    free(buffer_actual);
    return EXIT_FAILURE;
  }
  FILE* f_actual = fopen(actual_path, "r");
  if(f_actual == NULL) {
    fprintf(stderr, "FATAL ERROR: couldn't open file '%s'!\n", actual_path);
    free(buffer_expected);
    free(buffer_actual);
    fclose(f_expected);
    return EXIT_FAILURE;
  }
  int size_expected = fread(buffer_expected, sizeof(char), max_size, f_expected);
  int size_actual = fread(buffer_actual, sizeof(char), max_size, f_actual);
  if(size_expected != size_actual) {
    fprintf(stderr, "ERROR: the files are unequal ('%s', '%s')!\n", expected_path, actual_path);
    free(buffer_expected);
    free(buffer_actual);
    fclose(f_expected);
    fclose(f_actual);
    return EXIT_FAILURE;
  }
  if(memcmp(buffer_expected, buffer_actual, max_size) == 0) {
    free(buffer_expected);
    free(buffer_actual);
    fclose(f_expected);
    fclose(f_actual);
    return EXIT_SUCCESS;
  }
  fprintf(stderr, "ERROR: the files are unequal ('%s', '%s')!\n", expected_path, actual_path);
  free(buffer_expected);
  free(buffer_actual);
  fclose(f_expected);
  fclose(f_actual);
  return EXIT_FAILURE;
}

static int get_btree_depth_test() {
  int ret;
  struct node n2;
  n2.parent = NULL;
  n2.number_of_elements = 4;
  n2.elements[0] = 0;
  n2.elements[1] = 1;
  n2.elements[2] = 2;
  n2.elements[3] = 3;
  n2.children[0] = NULL;
  n2.children[1] = NULL;
  n2.children[2] = NULL;
  n2.children[3] = NULL;
  n2.children[4] = NULL;
  
  struct node n;
  n.parent = NULL;
  n.number_of_elements = 4;
  n.elements[0] = 0;
  n.elements[1] = 1;
  n.elements[2] = 2;
  n.elements[3] = 3;
  n.children[0] = &n2;
  n.children[1] = NULL;
  n.children[2] = NULL;
  n.children[3] = NULL;
  n.children[4] = NULL;

  puts("get_btree_depth_test()");

  int depth = get_btree_depth(&n);

  ret = assert_equals_int(2, depth);
  
  return ret;
}

static int svg_get_width_test() {
  int ret;
  int depth = 2;

  puts("svg_get_width_test()");
  
  //((110 + (5 + 110) * ( 2 * 2 - 1) + 30) * (2 * 2 + 1) ^ (2 - 1) + 30)
  int exp_width = 2455;
  int svg_width = svg_get_width(depth);

  ret = assert_equals_int(exp_width, svg_width);
  
  return ret;
}

static int svg_get_width_test2() {
  int ret;
  int depth = 1;

  puts("svg_get_width_test2()");
  
  //((110 + (5 + 110) * ( 2 * 2 - 1) + 30) * (2 * 2 + 1) ^ (1 - 1) + 30)
  int exp_width = 515;
  int svg_width = svg_get_width(depth);

  ret = assert_equals_int(exp_width, svg_width);
  
  return ret;
}

static int svg_get_width_test3() {
  int ret;
  int depth = 0;

  puts("svg_get_width_test3()");
  
  int exp_width = 0;
  int svg_width = svg_get_width(depth);

  ret = assert_equals_int(exp_width, svg_width);
  
  return ret;
}

static int svg_get_height_test() {
  int ret;
  int depth = 2;
  int exp_height = 130;

  puts("svg_get_height_test()");
  
  //2 * (20 + 30) + 30
  int svg_height = svg_get_height(depth);

  ret = assert_equals_int(exp_height, svg_height);

  return ret;
}

static int svg_save_header_test() {
  int ret;
  
  struct node n2;
  n2.parent = NULL;
  n2.number_of_elements = 4;
  n2.elements[0] = 0;
  n2.elements[1] = 1;
  n2.elements[2] = 2;
  n2.elements[3] = 3;
  n2.children[0] = NULL;
  n2.children[1] = NULL;
  n2.children[2] = NULL;
  n2.children[3] = NULL;
  n2.children[4] = NULL;
  
  struct node n;
  n.parent = NULL;
  n.number_of_elements = 4;
  n.elements[0] = 0;
  n.elements[1] = 1;
  n.elements[2] = 2;
  n.elements[3] = 3;
  n.children[0] = &n2;
  n.children[1] = NULL;
  n.children[2] = NULL;
  n.children[3] = NULL;
  n.children[4] = NULL;


  puts("svg_save_header_test()");
  
  char* expected = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"2455\" height=\"130\">";
  char* actual = NULL;
  
  FILE* fd = fopen("svg_save_header_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_save_header(fd, &n);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);
  
  fd = fopen("svg_save_header_test.test.svg", "r");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }
  actual = (char*)malloc(strlen(expected + 1));
  if(actual == NULL) {
    fprintf(stderr, "Error: Couldn't allocate memory!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fread(actual, sizeof(char), strlen(expected), fd);

  actual[strlen(expected)] = '\0';

  fclose(fd);

  ret = assert_equals_str(expected, actual);

  return ret;
}

static int svg_save_footer_test() {
  int ret;
  char* expected = "</svg>";
  char* actual = NULL;

  puts("svg_save_footer_test()");
  
  FILE* fd = fopen("svg_save_footer_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_save_footer(fd);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);
  
  fd = fopen("svg_save_footer_test.test.svg", "r");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }
  actual = (char*)malloc(strlen(expected + 1));
  if(actual == NULL) {
    fprintf(stderr, "Error: Couldn't allocate memory!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fread(actual, sizeof(char), strlen(expected), fd);

  actual[strlen(expected)] = '\0';

  fclose(fd);

  ret = assert_equals_str(expected, actual);

  return ret;
}

static int svg_render_rect_test() {
  int ret;
  char* expected = "\t<rect x=\"3\" y=\"5\" width=\"20\" height=\"10\" stroke=\"black\" stroke-width=\"2\" fill=\"none\"/>";
  char* actual = NULL;

  puts("svg_render_rect_test()");
  
  FILE* fd = fopen("svg_render_rect_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_render_rect(fd, 3, 5, 20, 10);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);
  
  fd = fopen("svg_render_rect_test.test.svg", "r");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }
  actual = (char*)malloc(strlen(expected + 1));
  if(actual == NULL) {
    fprintf(stderr, "Error: Couldn't allocate memory!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fread(actual, sizeof(char), strlen(expected), fd);

  actual[strlen(expected)] = '\0';

  fclose(fd);

  ret = assert_equals_str(expected, actual);

  return ret;
}

static int svg_render_line_test() {
  int ret;
  char* expected = "\t<line x1=\"30\" y1=\"50\" x2=\"2\" y2=\"1\" stroke=\"black\" stroke-width=\"2\" />";
  char* actual = NULL;

  puts("svg_render_line_test()");
  
  FILE* fd = fopen("svg_render_line_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_render_line(fd, 30, 50, 2, 1);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);
  
  fd = fopen("svg_render_line_test.test.svg", "r");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }
  actual = (char*)malloc(strlen(expected + 1));
  if(actual == NULL) {
    fprintf(stderr, "Error: Couldn't allocate memory!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fread(actual, sizeof(char), strlen(expected), fd);

  actual[strlen(expected)] = '\0';

  fclose(fd);

  ret = assert_equals_str(expected, actual);

  return ret;
}

static int svg_begin_text_test() {
  int ret;
  char* expected = "\t<g font-size=\"14\" font-family=\"sans-serif\" fill=\"black\" stroke=\"none\" text-anchor=\"middle\">";
  char* actual = NULL;
  
  puts("svg_begin_text_test()");
  
  FILE* fd = fopen("svg_begin_text_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_begin_text(fd);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);
  
  fd = fopen("svg_begin_text_test.test.svg", "r");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }
  actual = (char*)malloc(strlen(expected + 1));
  if(actual == NULL) {
    fprintf(stderr, "Error: Couldn't allocate memory!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fread(actual, sizeof(char), strlen(expected), fd);

  actual[strlen(expected)] = '\0';

  fclose(fd);

  ret = assert_equals_str(expected, actual);

  return ret;
}

static int svg_render_number_text_test() {
  int ret;
  char* expected = "\t\t<text x=\"45\" y=\"100\">200</text>";
  char* actual = NULL;

  puts("svg_render_number_text_test()");
  
  FILE* fd = fopen("svg_render_number_text_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_render_number_text(fd, 45, 100, 200);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);
  
  fd = fopen("svg_render_number_text_test.test.svg", "r");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }
  actual = (char*)malloc(strlen(expected + 1));
  if(actual == NULL) {
    fprintf(stderr, "Error: Couldn't allocate memory!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fread(actual, sizeof(char), strlen(expected), fd);

  actual[strlen(expected)] = '\0';

  fclose(fd);

  ret = assert_equals_str(expected, actual);

  return ret;
}

static int svg_end_text_test() {
  int ret;
  char* expected = "\t</g>";
  char* actual = NULL;

  puts("svg_end_text_test()");
  
  FILE* fd = fopen("svg_end_text_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_end_text(fd);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);
  
  fd = fopen("svg_end_text_test.test.svg", "r");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }
  actual = (char*)malloc(strlen(expected + 1));
  if(actual == NULL) {
    fprintf(stderr, "Error: Couldn't allocate memory!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fread(actual, sizeof(char), strlen(expected), fd);

  actual[strlen(expected)] = '\0';

  fclose(fd);

  ret = assert_equals_str(expected, actual);

  return ret;
}

static int render_node_to_svg_test() {
  int ret;
  
  struct node n;
  n.parent = NULL;
  n.number_of_elements = 4;
  n.elements[0] = 0;
  n.elements[1] = 2000000000;
  n.elements[2] = 2;
  n.elements[3] = 500000000;
  n.children[0] = NULL;
  n.children[1] = NULL;
  n.children[2] = NULL;
  n.children[3] = NULL;
  n.children[4] = NULL;

  puts("render_node_to_svg_test()");
  
  FILE* fd = fopen("render_node_to_svg_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_save_header(fd, &n);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  ret = render_node_to_svg(fd, &n, 20, 30);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  ret = svg_save_footer(fd);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);

  ret = assert_equals_file("render_node_to_svg_reference.svg", "render_node_to_svg_test.test.svg", 1024);

  return ret;
}

static int render_node_to_svg_test2() {  int ret;
  
  struct node n;
  n.parent = NULL;
  n.number_of_elements = 2;
  n.elements[0] = 0;
  n.elements[1] = 2000000000;
  n.children[0] = NULL;
  n.children[1] = NULL;
  n.children[2] = NULL;
  n.children[3] = NULL;
  n.children[4] = NULL;

  puts("render_node_to_svg_test2()");
  
  FILE* fd = fopen("render_node_to_svg_test2.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_save_header(fd, &n);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  ret = render_node_to_svg(fd, &n, 20, 30);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  ret = svg_save_footer(fd);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);

  ret = assert_equals_file("render_node_to_svg2_reference.svg", "render_node_to_svg_test2.test.svg", 1024);

  return ret;
}

static int save_btree_part_test() {
  int ret;

  struct node n1;
  n1.parent = NULL;
  n1.number_of_elements = 4;
  n1.elements[0] = 1;
  n1.elements[1] = 1000000;
  n1.elements[2] = 2;
  n1.elements[3] = 3;
  n1.children[0] = NULL;
  n1.children[1] = NULL;
  n1.children[2] = NULL;
  n1.children[3] = NULL;
  n1.children[4] = NULL;
  
  struct node n2;
  n2.parent = NULL;
  n2.number_of_elements = 4;
  n2.elements[0] = 2;
  n2.elements[1] = 1000000;
  n2.elements[2] = 2;
  n2.elements[3] = 3;
  n2.children[0] = NULL;
  n2.children[1] = NULL;
  n2.children[2] = NULL;
  n2.children[3] = NULL;
  n2.children[4] = NULL;
  
  struct node n3;
  n3.parent = NULL;
  n3.number_of_elements = 4;
  n3.elements[0] = 3;
  n3.elements[1] = 1000000;
  n3.elements[2] = 2;
  n3.elements[3] = 3;
  n3.children[0] = NULL;
  n3.children[1] = NULL;
  n3.children[2] = NULL;
  n3.children[3] = NULL;
  n3.children[4] = NULL;
  
  struct node n4;
  n4.parent = NULL;
  n4.number_of_elements = 2;
  n4.elements[0] = 4;
  n4.elements[1] = 1000000;
  n4.elements[2] = 2;
  n4.children[0] = NULL;
  n4.children[1] = NULL;
  n4.children[2] = NULL;
  n4.children[3] = NULL;
  n4.children[4] = NULL;
  
  struct node n5;
  n5.parent = NULL;
  n5.number_of_elements = 2;
  n5.elements[0] = 5;
  n5.elements[1] = 1000000;
  n5.children[0] = NULL;
  n5.children[1] = NULL;
  n5.children[2] = NULL;
  n5.children[3] = NULL;
  n5.children[4] = NULL;
  
  struct node n;
  n.parent = NULL;
  n.number_of_elements = 3;
  n.elements[0] = 0;
  n.elements[1] = 1;
  n.elements[2] = 2000000000;
  n.elements[3] = 3;
  n.children[0] = &n1;
  n.children[1] = &n2;
  n.children[2] = &n3;
  n.children[3] = &n4;
  n.children[4] = &n5;
  n.parent = NULL;
  
  n1.parent = &n;
  n2.parent = &n;
  n3.parent = &n;
  n4.parent = &n;
  n5.parent = &n;
  
  puts("save_btree_part_test()");
  
  FILE* fd = fopen("save_btree_part_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_save_header(fd, &n);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  ret = save_btree_part(fd, &n, 2455 / 2, 30, 2455 - 60);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  ret = svg_save_footer(fd);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  fclose(fd);

  ret = assert_equals_file("save_btree_part_reference.svg", "save_btree_part_test.test.svg", 1024);

  return ret;
}

static int save_btree_test() {
  int ret;

  struct node n1;
  n1.parent = NULL;
  n1.number_of_elements = 4;
  n1.elements[0] = 1;
  n1.elements[1] = 1000000;
  n1.elements[2] = 2;
  n1.elements[3] = 3;
  n1.children[0] = NULL;
  n1.children[1] = NULL;
  n1.children[2] = NULL;
  n1.children[3] = NULL;
  n1.children[4] = NULL;
  
  struct node n2;
  n2.parent = NULL;
  n2.number_of_elements = 4;
  n2.elements[0] = 2;
  n2.elements[1] = 1000000;
  n2.elements[2] = 2;
  n2.elements[3] = 3;
  n2.children[0] = NULL;
  n2.children[1] = NULL;
  n2.children[2] = NULL;
  n2.children[3] = NULL;
  n2.children[4] = NULL;
  
  struct node n3;
  n3.parent = NULL;
  n3.number_of_elements = 4;
  n3.elements[0] = 3;
  n3.elements[1] = 1000000;
  n3.elements[2] = 2;
  n3.elements[3] = 3;
  n3.children[0] = NULL;
  n3.children[1] = NULL;
  n3.children[2] = NULL;
  n3.children[3] = NULL;
  n3.children[4] = NULL;
  
  struct node n4;
  n4.parent = NULL;
  n4.number_of_elements = 2;
  n4.elements[0] = 4;
  n4.elements[1] = 1000000;
  n4.elements[2] = 2;
  n4.children[0] = NULL;
  n4.children[1] = NULL;
  n4.children[2] = NULL;
  n4.children[3] = NULL;
  n4.children[4] = NULL;
  
  struct node n5;
  n5.parent = NULL;
  n5.number_of_elements = 2;
  n5.elements[0] = 5;
  n5.elements[1] = 1000000;
  n5.children[0] = NULL;
  n5.children[1] = NULL;
  n5.children[2] = NULL;
  n5.children[3] = NULL;
  n5.children[4] = NULL;
  
  struct node n;
  n.parent = NULL;
  n.number_of_elements = 3;
  n.elements[0] = 0;
  n.elements[1] = 17;
  n.elements[2] = 2000000000;
  n.elements[3] = 3;
  n.children[0] = &n1;
  n.children[1] = &n2;
  n.children[2] = &n3;
  n.children[3] = &n4;
  n.children[4] = &n5;
  n.parent = NULL;
  
  n1.parent = &n;
  n2.parent = &n;
  n3.parent = &n;
  n4.parent = &n;
  n5.parent = &n;
  
  puts("save_btree_test()");

  ret = save_btree("save_btree_test.test.svg", &n);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    return EXIT_FAILURE;
  }

  ret = assert_equals_file("save_btree_reference.svg", "save_btree_test.test.svg", 1024);

  return ret;
}

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
  
  printf("Number of tests: %d\nNumber of failed tests: %d\n", num_test, res);
  return res;
}
