#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "service_http.h"

char scheme(char uri[], char test_scheme[]){
    regex_t re;
    int value;
    value = regcomp(&re, test_scheme, REG_EXTENDED);
    value = regexec(&re, uri, 0, NULL, 0);
    regfree(&re);

    if (value == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "[ ERROR ] Received 0 arguments but expected 1. The `uri` parameter is missing.\n");
        return 1;
    }

    if (argc > 2) {
        fprintf(stdout, "[ WARN ] Received more than 1 argument but expected 1.\n");
        fprintf(stdout, "[ INFO ] Parsing first argument and ignoring the rest.\n");
    }

    if (scheme(argv[1], "http") == 0) {
        service_http_get(argv[1]);
    } else {
        fprintf(stderr, "[ ERROR ] Unsupported URI scheme.");
    }

    return 0;
}