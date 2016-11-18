#include "../btree/btree.h"

int compare_equal_test() {
    puts("compare_equal_test()");

    btree tree = create_btree();

    insert(tree, 43);
    insert(tree, 63);
    insert(tree, 66);
    insert(tree, 67);
    insert(tree, 82);
    insert(tree, 52);
    insert(tree, 25);
    insert(tree, 81);
    insert(tree, 48);
    insert(tree, 23);
    insert(tree, 42);
    insert(tree, 29);
    insert(tree, 41);

    struct node c1 = {
        .number_of_elements = 2,
        .elements = {23, 25},
    };

    struct node c2 = {
        .number_of_elements = 3,
        .elements = {41, 42, 43},
    };

    struct node c3 = {
        .number_of_elements = 2,
        .elements = {52, 63},
    };

    struct node c4 = {
        .number_of_elements = 3,
        .elements = {67, 81, 82},
    };

    struct node croot = {
        .number_of_elements = 3,
        .elements = {29, 48, 66},
        .children = {&c1, &c2, &c3, &c4},
    };

    c1.parent = &croot;
    c2.parent = &croot;
    c3.parent = &croot;
    c4.parent = &croot;

    btree tree2 = create_btree();
    tree2->root = &croot;

    int ret = !compare(tree, tree2, NULL);

    destroy_btree(tree);
    free(tree2);

    if(ret)
        puts("Expected trees to be equal but they aren't.");
    return ret;
}

int compare_unequal_test() {
    puts("compare_unequal_test()");

    btree tree = create_btree();

    insert(tree, 43);
    insert(tree, 63);
    insert(tree, 66);

    struct node croot = {
        .number_of_elements = 3,
        .elements = {29, 48, 66},
    };

    btree tree2 = create_btree();
    tree2->root = &croot;

    int ret = compare(tree, tree2, NULL);

    destroy_btree(tree);
    free(tree2);

    if(ret)
        puts("Expected trees not to be equal but they are.");
    return ret;
}
