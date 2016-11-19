#ifndef __BTREE_CONFIG_H__
#define __BTREE_CONFIG_H__

/**
 * @file btree_config.h
 * @brief Header file which contains order and maximum size of nodes.
 */

/**
 * defines the minimum filled elements in one node
 */
#define ORDER 2

/**
 * defines the maximum filled elements in one node
 */
#define MAXNODE (2 * ORDER)

#endif //__BTREE_CONFIG_H__
