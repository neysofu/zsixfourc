#ifndef ZULOID_TEST_UTILS_H
#define ZULOID_TEST_UTILS_H

#include <stdio.h>

struct Lines;

char *
lines_nth(struct Lines *lines, long long i);

size_t
lines_count(struct Lines *lines);

void
lines_delete(struct Lines *lines);

struct Lines *
file_line_by_line(FILE *stream);

#endif