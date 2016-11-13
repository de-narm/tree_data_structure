#ifndef __CONFIG_H__
#define __CONFIG_H__

#define NODE_TEXT_OFFSET_X 55
#define NODE_TEXT_OFFSET_Y 15
#define NODE_HEIGHT 20
#define NODE_VERT_SPACING 30
#define NODE_HOR_SPACING 30
#define NODE_HEIGHT_AND_VERT_SPACING (NODE_HEIGHT + NODE_VERT_SPACING)
#define FIELD_WIDTH 110
#define FIELD_SPACER_WIDTH 5
#define FIELD_AND_SPACER_WIDTH (FIELD_WIDTH + FIELD_SPACER_WIDTH)
#define NODE_WIDTH (FIELD_WIDTH + FIELD_AND_SPACER_WIDTH * (MAXNODE - 1))
#define HALF_NODE_WIDTH (NODE_WIDTH / 2)

#define SVG_HEADER_STR "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n\t<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"white\"/>\n"
#define SVG_LINE_STR "\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"2\" />\n"
#define SVG_RECT_STR "\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"black\" stroke-width=\"2\" fill=\"none\"/>\n"
#define SVG_TEXT_BEGIN_STR "\t<g font-size=\"14\" font-family=\"sans-serif\" fill=\"black\" stroke=\"none\" text-anchor=\"middle\">\n"
#define SVG_NUMBER_TEXT_STR "\t\t<text x=\"%d\" y=\"%d\">%d</text>\n"
#define SVG_TEXT_END_STR "\t</g>\n"
#define SVG_FOOTER_STR "</svg>\n"

#endif //__CONFIG_H__
