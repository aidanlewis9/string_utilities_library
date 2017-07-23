/* stringutils.h: String Utilities */

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <stdbool.h>

/* Case */
char *	string_lowercase(char *s);
char *	string_uppercase(char *s);

/* Comparison */
bool	string_startswith(char *s, char *t);
bool	string_endswith(char *s, char *t);

/* Strip */
char *  string_chomp(char *s);
char *	string_strip(char *s);

/* Reverse */
char *	string_reverse(char *s);
char *	string_reverse_words(char *s);

/* Translation */
char *	string_translate(char *s, char *from, char *to);

/* Integer Conversion */
int	string_to_integer(char *s, int base);

#endif

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
