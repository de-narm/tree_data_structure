#ifndef __CONFIG_H__
#define __CONFIG_H__

/**
 * @file svg_config.h
 * @brief Header file which contains required information to create a svg file.
 */
/** x offset for text in a node*/
#define NODE_TEXT_OFFSET_X 55
/** y offset for text in a node*/
#define NODE_TEXT_OFFSET_Y 15
/** height of node */
#define NODE_HEIGHT 20
/** vertical spacing of node */
#define NODE_VERT_SPACING 30
/** horizontal spacing of node */
#define NODE_HOR_SPACING 30
/** height and vertical spacing of node */
#define NODE_HEIGHT_AND_VERT_SPACING (NODE_HEIGHT + NODE_VERT_SPACING)
/** width of field */
#define FIELD_WIDTH 110
/** width of spacer of field */
#define FIELD_SPACER_WIDTH 5
/** sum of width of spacer and field*/
#define FIELD_AND_SPACER_WIDTH (FIELD_WIDTH + FIELD_SPACER_WIDTH)
/** width of node */
#define NODE_WIDTH (FIELD_WIDTH + FIELD_AND_SPACER_WIDTH * (MAXNODE - 1))
/** width of a half node */
#define HALF_NODE_WIDTH (NODE_WIDTH / 2)

/** header of svg file */
#define SVG_HEADER_STR "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n\t<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"white\"/>\n"
/** template for a line */
#define SVG_LINE_STR "\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"2\" />\n"
/** template for a rectangle */
#define SVG_RECT_STR "\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"black\" stroke-width=\"2\" fill=\"none\"/>\n"
/** template for begin of a string */
#define SVG_TEXT_BEGIN_STR "\t<g font-size=\"14\" font-family=\"sans-serif\" fill=\"black\" stroke=\"none\" text-anchor=\"middle\">\n"
/** template for a number */
#define SVG_NUMBER_TEXT_STR "\t\t<text x=\"%d\" y=\"%d\">%d</text>\n"
/**  template for end of a string */
#define SVG_TEXT_END_STR "\t</g>\n"
/** footer of svg file */
#define SVG_FOOTER_STR "</svg>\n"

#endif //__CONFIG_H__
