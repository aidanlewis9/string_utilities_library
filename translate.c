/* translate.c: string translator */

#include "stringutils.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

enum {
    STRIP = 1<<1,
    REVERSE_STRING = 1<<2,
    REVERSE_WORD = 1<<3,
    LOWER = 1<<4,
    UPPER = 1<<5
};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s     Strip whitespace\n");
    fprintf(stderr, "   -r     Reverse line\n");
    fprintf(stderr, "   -w     Reverse words in line\n");
    fprintf(stderr, "   -l     Convert to lowercase\n");
    fprintf(stderr, "   -u     Convert to uppercase\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, int mode) {
    /* TODO */
    char buffer[BUFSIZ];
    char *begin;
    while (fgets(buffer, BUFSIZ, stream))
    {
        string_chomp(buffer);
        begin = string_translate(buffer, source, target);
        if (mode & STRIP) {
            begin = string_strip(buffer);
        }
        if (mode & REVERSE_STRING) {
            string_reverse(begin); 
        }
        if (mode & REVERSE_WORD) {
            string_reverse_words(begin);
        }
        if (mode & LOWER) {
            string_lowercase(begin);
        }
        if (mode & UPPER) {
            string_uppercase(begin);
        }
        fputs(begin, stdout);
    }
    printf("\n");
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    int argind = 1;
    int mode = 0;
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-')
    {
        char *arg = argv[argind++];
        switch (arg[1])
        {
            case 'h':
                usage(0);
                break;
            case 's':
                mode |= STRIP;
                break;
            case 'r':
                mode |= REVERSE_STRING;
                break;
            case 'w':
                mode |= REVERSE_WORD;
                break;
            case 'l':
                mode |= LOWER;
                break;
            case 'u':
                mode |= UPPER;
                break;
            default:
                usage(1);
                break;
        }
    }
    char *from = " ";
    char *to = " ";
    if (argind < argc)
    {
        from = argv[argind++];
        to = argv[argind];
    }

    /* Translate Stream */
    translate_stream(stdin, from, to, mode);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
