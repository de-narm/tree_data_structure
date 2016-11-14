#include "test.h"

int svg_get_width_test() {
  int ret;
  int depth = 2;

  puts("svg_get_width_test()");
  
  //((110 + (5 + 110) * ( 2 * 2 - 1) + 30) * (2 * 2 + 1) ^ (2 - 1) + 30)
  int exp_width = 2455;
  int svg_width = svg_get_width(depth);

  ret = assert_equals_int(exp_width, svg_width);
  
  return ret;
}

int svg_get_width_test2() {
  int ret;
  int depth = 1;

  puts("svg_get_width_test2()");
  
  //((110 + (5 + 110) * ( 2 * 2 - 1) + 30) * (2 * 2 + 1) ^ (1 - 1) + 30)
  int exp_width = 515;
  int svg_width = svg_get_width(depth);

  ret = assert_equals_int(exp_width, svg_width);
  
  return ret;
}

int svg_get_width_test3() {
  int ret;
  int depth = 0;

  puts("svg_get_width_test3()");
  
  int exp_width = 0;
  int svg_width = svg_get_width(depth);

  ret = assert_equals_int(exp_width, svg_width);
  
  return ret;
}

int svg_get_height_test() {
  int ret;
  int depth = 2;
  int exp_height = 130;

  puts("svg_get_height_test()");
  
  //2 * (20 + 30) + 30
  int svg_height = svg_get_height(depth);

  ret = assert_equals_int(exp_height, svg_height);

  return ret;
}

int svg_save_header_test() {
  int ret;

  puts("svg_save_header_test()");
  
  char* expected = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"2455\" height=\"130\">";
  char* actual = NULL;
  
  FILE* fd = fopen("svg_save_header_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_save_header(fd, 2455, 130);
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

int svg_save_footer_test() {
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

int svg_render_rect_test() {
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

int svg_render_line_test() {
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

int svg_begin_text_test() {
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

int svg_render_number_text_test() {
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

int svg_end_text_test() {
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
