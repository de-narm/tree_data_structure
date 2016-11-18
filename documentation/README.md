# Documentation

The list below shows the most important Functions. Other function (e.g. svg_get_width() ) are mainly used internally and not useful for other applications. 

The order of the B-Tree is configureable in [btree_config.h](/btree/btree_config.h).

The SVG output of the save_btree() function can be modified in [svg_config.h](/btree/svg_config.h).

**Important Note: Changing configurations will cause the tests located in [test](/test/) to fail!**

## create_btree()

This function allocates memory for the btree struct and initializes it to an empty tree.

## destroy_btree()

This function deletes all tree nodes recursively and frees the btree struct at the end.

## get_btree_depth()

This command takes a btree struct as argument and returns the depth of the tree. The root node is counted as the first layer.

## save_btree()

Renders a tree into an svg file and stores this at the given paths.

## compare()

Compares two trees, stores the result in the compare_result struct and returns true (1) if the trees are equal. Otherwise it erturns false.
The compare_result struct contains information on the type and location of unequalities.

(For more information read the comments in [compare.c](/btree/compare.c) )

## print_compare()

Compares two trees and prints the result and (additional information if they aren't equal) to the console. 
