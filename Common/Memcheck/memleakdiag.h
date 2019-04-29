#ifndef VECTOR_MEMLEAKDIAG_H
#define VECTOR_MEMLEAKDIAG_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "err_codes.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! Tokens for parsing dump files with operators new and delete
const char * const new_tok = "new:";
const char * const del_tok = "delete:";

//! Max line size while reading dump file
const int MAX_LINE_SIZE = 1000;

int checkMemoryLeak(const char * dump_file_name, const char * out_file_name);
char * readDumpFile(const char * dump_file_name);
int parseLines(const char * dump_text, FILE * out_file);

//! Several overloading of new operators for preventing shallow copy mechanism and memory leak diagnostic
void * operator new(size_t size, const char * file, int line, FILE * dump_file);
void * operator new[](size_t size, const char * file, int line, FILE * dump_file);
void operator delete(void * ptr, const char * file, int line, FILE * dump_file);
void operator delete[](void * ptr, const char * file, int line, FILE * dump_file);

#endif //VECTOR_MEMLEAKDIAG_H
