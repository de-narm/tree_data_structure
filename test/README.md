# Overview

To run the tests use `make test`.

Cleaning up can be done with `make clean`.

## Test Framework

[assert.h](/test/assert.h) -- definitions of jUnit-style assert functions

[assert.c](/test/assert.c) -- implementation of the assert functions

## Tests

[svg_test.c](/test/svg_test.c) -- test for the svg functions

[btree_test.c](/test/btree_test.c) -- tests for the btree functions

[compare_test.c](/test/compare_test.c) -- tests for the compare functions

## Reference Outputs

[render_node_to_svg_reference.svg](/test/render_node_to_svg_reference.svg) -- reference output for render_node_to_svg()

[render_node_to_svg2_reference.svg](/test/render_node_to_svg2_reference.svg) -- reference output for render_node_to_svg()

[save_btree_part_reference.svg](/test/save_btree_part_reference.svg) -- reference output for save_btree_part()

[save_btree_reference.svg](/test/save_btree_reference.svg) -- reference output for save_btree()

[save_btree2_reference.svg](/test/save_btree2_reference.svg) -- reference output for save_btree()
