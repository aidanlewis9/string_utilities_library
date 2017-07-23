/* stringutils.c: String Utilities */

#include "stringutils.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>

/**
 * Convert all characters in string to lowercase.
 * @@param   s       String to convert
 * @@return          Pointer to beginning of modified string
 **/
char *	string_lowercase(char *s) {
    for (char *c = s; *c; c++)
    {
        *c = tolower(*c);
    }
    return s;
}

/**
 * Convert all characters in string to uppercase.
 * @@param   s       String to convert
 * @@return          Pointer to beginning of modified string
 **/
char *	string_uppercase(char *s) {
    for (char *c = s; *c; c++)
    {
        *c = toupper(*c);
    }
    return s;
}

/**
 * Returns whether or not the 's' string starts with given 't' string.
 * @@param   s       String to search within
 * @@param   t       String to check for
 * @@return          Whether or not 's' starts with 't'
 **/
bool	string_startswith(char *s, char *t) {
    char *c1 = s;
    for (char *c2 = t; *c2; c2++)
    {
        if (*c1 != *c2)
        {
            return false;
        }
        c1++;
    }
    return true;
}

/**
 * Returns whether or not the 's' string ends with given 't' string.
 * @@param   s       String to search within
 * @@param   t       String to check for
 * @@return          Whether or not 's' ends with 't'
 **/
bool	string_endswith(char *s, char *t) {
    if (strlen(s) >= strlen(t))
    {
        char *c1 = s + strlen(s) - 1;
        for (char *c2 = t + strlen(t) - 1; *c2; c2--)
        {
            if (*c1 != *c2)
            {
                return false;   
            }
            c1--;
        }
        return true;
    }
    else { return false; }
}

/**
 * Removes trailing newline (if present).
 * @@param   s       String to modify
 * @@return          Pointer to beginning of modified string
 **/
char *	string_chomp(char *s) {
    if (*(s+strlen(s)-1) == '\n')
    { *(s+strlen(s)-1) = '\0'; }
    return s;
}

/**
 * Removes whitespace from front and back of string (if present).
 * @@param   s       String to modify
 * @@return          Pointer to beginning of modified string
 **/
char *	string_strip(char *s) {
    for (char *c = s + strlen(s) - 1; *c == ' '; c--) { *c = 0; }
    while (*s == ' ') { s++; }
    return s;
}

/**
 * Reverses a string given the provided from and to pointers.
 * @@param   from    Beginning of string
 * @@param   to      End of string
 * @@return          Pointer to beginning of modified string
 **/
static char *	string_reverse_range(char *from, char *to) {
    for (char *start = from; start < to; start++, to--)
    {
        char temp = *start;
        *start = *to;
        *to = temp;
    }
    return from;
}

/**
 * Reverses a string.
 * @@param   s       String to reverse
 * @@return          Pointer to beginning of modified string
 **/
char *	string_reverse(char *s) {
    s = string_reverse_range(s, s+strlen(s)-1);
    return s;
}

/**
 * Reverses all words in a string.
 * @@param   s       String with words to reverse
 * @@return          Pointer to beginning of modified string
 **/
char *	string_reverse_words(char *s) {
    s = string_reverse_range(s, s+strlen(s)-1);
    char *start = s;
    char *end = s;
    while (true)
    {
        if (*end != ' ' && *end) { end++; }
        else 
        {
            string_reverse_range(start, end - 1);
            if (!*end) { break; }
            start = ++end;
        }
    }
    return s;
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @@param   s       String to translate
 * @@param   from    String with letter to replace
 * @@param   to      String with corresponding replacment values
 * @@return          Pointer to beginning of modified string
 **/
char *	string_translate(char *s, char *from, char *to) {
    if (!*to) { return s; }
    for (char *c = s; *c; c++)
    {
        char *toC = to;
        for (char *fromC = from; *fromC; fromC++, toC++)
        {
            if (*c == *fromC)
            {
                *c = *toC;
                break;
            }
        }
    }
    return s;
}

/**
 * Converts given string into an integer.
 * @@param   s       String to convert
 * @@param   base    Integer base
 * @@return          Converted integer value
 **/
int	string_to_integer(char *s, int base) {
    int sum = 0;
    int power = 1;
    for (char *c = s + strlen(s) - 1; c >= s; c--)
    {
        if (isalpha(*c)) { sum += (toupper(*c) - '7')*power; }
        else { sum += (*c - '0')*power; }
        power *= base; 
    }
    return sum;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
