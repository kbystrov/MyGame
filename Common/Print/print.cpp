#include "print.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

void print(FILE * outstream, const char * str) {
    fprint(outstream, str, 0);
}

void fprint(FILE * outstream, const char * str, size_t arg_num) {
    if(str){
        fprintf(outstream, "%s", str);
    }
}
