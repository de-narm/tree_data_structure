#include "../btree/btree.h"

int compare_equal_test() {
    puts("compare_equal_test()");
    insert(43);
    insert(63);
    insert(66);
    insert(67);
    insert(82);
    insert(52);
    insert(25);
    insert(81);
    insert(48);
    insert(23);
    insert(42);
    insert(29);
    insert(41);

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

    if(!compare(root, &croot, NULL)) {
        puts("Expected trees to be equal but they aren't.");
        return 1;
    }
    return 0;
}

int compare_unequal_test() {
    puts("compare_unequal_test()");
    insert(43);
    insert(63);
    insert(66);

    struct node croot = {
        .number_of_elements = 3,
        .elements = {29, 48, 66},
    };

    if(compare(root, &croot, NULL)) {
        puts("Expected trees not to be equal but they are.");
        return 1;
    }
    return 0;
}
