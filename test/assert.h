#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int assert_equals_int(const int expected, const int actual);
int assert_equals_str(const char* expected, const char* actual);
int assert_equals_file(const char* expected_path, const char* actual_path, size_t max_size);

#endif //__ASSERT_H__
