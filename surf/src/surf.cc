// Copyright 2023 The Surf Authors

#include <iostream>

#include "surf.h"

int main (int argc, char* argv[]) {

    if (argc == 1) {
        fprintf(stderr, "[ ERROR ] Received 0 arguments but expected 1. The `uri` parameter is missing.\n");
        return 1;
    }

    if (argc > 2) {
        fprintf(stdout, "[ WARN ] Received %d arguments but expected 1.\n", argc - 1);
        fprintf(stdout, "[ INFO ] Parsing first argument and ignoring the rest.\n");
    }

    return 0;
}