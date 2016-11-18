#include "test.h"

int get_btree_depth_test() {
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

  btree tree = create_btree();
  tree->root = &n;

  puts("get_btree_depth_test()");

  int depth = get_btree_depth(tree);

  free(tree);

  ret = assert_equals_int(2, depth);
  
  return ret;
}

int render_node_to_svg_test() {
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

  btree tree = create_btree();
  tree->root = &n;

  int depth = get_btree_depth(tree);
  int width = svg_get_width(depth);
  int height = svg_get_height(depth);

  puts("render_node_to_svg_test()");
  
  FILE* fd = fopen("render_node_to_svg_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_save_header(fd, width, height);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  ret = render_node_to_svg(fd, tree->root, 20, 30);
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

  free(tree);

  ret = assert_equals_file("render_node_to_svg_reference.svg", "render_node_to_svg_test.test.svg", 1024);

  return ret;
}

int render_node_to_svg_test2() {  int ret;
  
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

  btree tree = create_btree();
  tree->root = &n;

  int depth = get_btree_depth(tree);
  int width = svg_get_width(depth);
  int height = svg_get_height(depth);
  puts("render_node_to_svg_test2()");
  
  FILE* fd = fopen("render_node_to_svg_test2.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_save_header(fd, width, height);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  ret = render_node_to_svg(fd, tree->root, 20, 30);
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

  free(tree);

  ret = assert_equals_file("render_node_to_svg2_reference.svg", "render_node_to_svg_test2.test.svg", 1024);

  return ret;
}

int save_btree_part_test() {
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

  btree tree = create_btree();
  tree->root = &n;
  
  int depth = get_btree_depth(tree);
  int width = svg_get_width(depth);
  int height = svg_get_height(depth);
  puts("save_btree_part_test()");
  
  FILE* fd = fopen("save_btree_part_test.test.svg", "w");
  if(fd == NULL) {
    fprintf(stderr, "Error: Couldn't open file!\n");
    return EXIT_FAILURE;
  }

  ret = svg_save_header(fd, width, height);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    fclose(fd);
    return EXIT_FAILURE;
  }

  ret = save_btree_part(fd, tree->root, 1000, 30, 2455 - 30);
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

  free(tree);

  ret = assert_equals_file("save_btree_part_reference.svg", "save_btree_part_test.test.svg", 8192);

  return ret;
}

int save_btree_test() {
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

  btree tree = create_btree();
  tree->root = &n;
  
  puts("save_btree_test()");

  ret = save_btree("save_btree_test.test.svg", tree);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    return EXIT_FAILURE;
  }

  free(tree);

  ret = assert_equals_file("save_btree_reference.svg", "save_btree_test.test.svg", 8192);

  return ret;
}

int save_btree_test2() {
  int ret;

  struct node n11;
  n11.parent = NULL;
  n11.number_of_elements = 4;
  n11.elements[0] = 1;
  n11.elements[1] = 1000000;
  n11.elements[2] = 2;
  n11.elements[3] = 3;
  n11.children[0] = NULL;
  n11.children[1] = NULL;
  n11.children[2] = NULL;
  n11.children[3] = NULL;
  n11.children[4] = NULL;
  
  struct node n12;
  n12.parent = NULL;
  n12.number_of_elements = 4;
  n12.elements[0] = 2;
  n12.elements[1] = 1000000;
  n12.elements[2] = 2;
  n12.elements[3] = 3;
  n12.children[0] = NULL;
  n12.children[1] = NULL;
  n12.children[2] = NULL;
  n12.children[3] = NULL;
  n12.children[4] = NULL;
  
  struct node n13;
  n13.parent = NULL;
  n13.number_of_elements = 4;
  n13.elements[0] = 3;
  n13.elements[1] = 1000000;
  n13.elements[2] = 2;
  n13.elements[3] = 3;
  n13.children[0] = NULL;
  n13.children[1] = NULL;
  n13.children[2] = NULL;
  n13.children[3] = NULL;
  n13.children[4] = NULL;
  
  struct node n14;
  n14.parent = NULL;
  n14.number_of_elements = 2;
  n14.elements[0] = 4;
  n14.elements[1] = 1000000;
  n14.elements[2] = 2;
  n14.children[0] = NULL;
  n14.children[1] = NULL;
  n14.children[2] = NULL;
  n14.children[3] = NULL;
  n14.children[4] = NULL;
  
  struct node nlast;
  nlast.parent = NULL;
  nlast.number_of_elements = 2;
  nlast.elements[0] = 5;
  nlast.elements[1] = 1000000;
  nlast.children[0] = NULL;
  nlast.children[1] = NULL;
  nlast.children[2] = NULL;
  nlast.children[3] = NULL;
  nlast.children[4] = NULL;

  struct node n1;
  n1.parent = NULL;
  n1.number_of_elements = 4;
  n1.elements[0] = 1;
  n1.elements[1] = 1000000;
  n1.elements[2] = 2;
  n1.elements[3] = 3;
  n1.children[0] = &n11;
  n1.children[1] = &n12;
  n1.children[2] = NULL;
  n1.children[3] = &n13;
  n1.children[4] = &n14;
  
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
  n5.children[4] = &nlast;
  
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
  
  n11.parent = &n1;
  n12.parent = &n1;
  n13.parent = &n1;
  n14.parent = &n1;

  nlast.parent = &n5;
  
  n1.parent = &n;
  n2.parent = &n;
  n3.parent = &n;
  n4.parent = &n;
  n5.parent = &n;

  btree tree = create_btree();
  tree->root = &n;
  
  puts("save_btree_test2()");

  ret = save_btree("save_btree_test2.test.svg", tree);
  if(ret != EXIT_SUCCESS) {
    fprintf(stderr, "Error: Couldn't save file!\n");
    return EXIT_FAILURE;
  }

  free(tree);

  ret = assert_equals_file("save_btree2_reference.svg", "save_btree_test2.test.svg", 16384);

  return ret;
}
