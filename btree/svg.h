#ifndef __SVG_H__
#define __SVG_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "btree_config.h"
#include "svg_config.h"

/**
 * @file svg.h
 * @brief Header file which contains definitions to write b-tree into svg file.
 */

/**
 * @brief calculates width of b-tree
 * @param depth depth of b-tree
 * @return width of b-tree
 */
int svg_get_width(int depth);
/**
 * @brief calculates high of b-tree
 * @param depth depth of b-tree
 * @return height of b-tree
 */
int svg_get_height(int depth);
/**
 * @brief writes header to svg file
 * @param fd svg file where header shall be written into
 * @param width width of b-tree
 * @param height height of b-tree
 * @return EXIT_SUCCESS if everything went right else EXIT_FAILURE
 */
int svg_save_header(FILE* fd, int width, int height);
/**
 * @brief writes footer to svg file
 * @param fd svg file where footer shall be written into
 * @return EXIT_SUCCESS if everything went right else EXIT_FAILURE
 */
int svg_save_footer(FILE* fd);
/**
 * @brief creates rectangle for node and writes into svg file
 * @param fd svg file where rectangle shall be stored
 * @param x x position of rectangle
 * @param y y position of rectangle
 * @param width width of rectangle
 * @param height height of rectangle
 * @return EXIT_SUCCESS if everything went right else EXIT_FAILURE
 */
int svg_render_rect(FILE* fd, int x, int y, int width, int height);
/**
 * @brief writes line which connects child and parent node into file
 * @param fd svg file where line shall be stored
 * @param x1 x position where line starts
 * @param y1 y position where line starts
 * @param x2 x position where line ends
 * @param y2 y position where line ends
 * @return EXIT_SUCCESS if everything went right else EXIT_FAILURE
 */
int svg_render_line(FILE* fd, int x1, int y1, int x2, int y2);
/**
 * @brief writes begin information to store string to svg file
 * @param fd svg file where string shall be stored
 * @return EXIT_SUCCESS if everything went right else EXIT_FAILURE
 */
int svg_begin_text(FILE* fd);
/**
 * @brief writes number to svg file
 * @param fd svg file number shall be stored
 * @param number number which shall be stored
 * @param x x position of number
 * @param y y position of number
 * @return EXIT_SUCCESS if everything went right else EXIT_FAILURE
 */
int svg_render_number_text(FILE* fd, int number, int x, int y);
/**
 * @brief writes end information to store string to svg file
 * @param fd svg file where string shall be stored
 * @return EXIT_SUCCESS if everything went right else EXIT_FAILURE
 */
int svg_end_text(FILE* fd);

#endif //__SVG_H__
