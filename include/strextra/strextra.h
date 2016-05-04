/*
 * strextra.h - Extra String functions used by SiriDB
 *
 * author       : Jeroen van der Heijden
 * email        : jeroen@transceptor.technology
 * copyright    : 2016, Transceptor Technology
 *
 * changes
 *  - initial version, 19-03-2016
 *
 */
#pragma once

#include <stdbool.h>

void strx_upper_case(char * sptr);
void strx_lower_case(char * sptr);
void strx_replace_char(char * sptr, char orig, char repl);

/* do not use trim when the char is created with *alloc */
void strx_trim(char ** str, char chr);
bool strx_is_empty(const char * str);
bool strx_is_int(const char * str);
bool strx_is_float(const char * str);
bool strx_is_graph(const char * str);

/* important: 'dest' needs to be freed */
void strx_extract_string(char * dest, const char * source, size_t len);
