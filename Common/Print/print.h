#ifndef VECTOR_PRINT_H
#define VECTOR_PRINT_H

#include <stddef.h>
#include <typeindex>
#include <unordered_map>
#include "err_codes.h"
#include "MyExcp.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

const char PRINT_SPEC_SYMBL = '#';

static std::unordered_map<std::type_index, const char *> generate_type_names(){

    std::unordered_map<std::type_index, const char *> types;

    types[std::type_index(typeid(int))] = "%d";
    types[std::type_index(typeid(unsigned int))] = "%u";
    types[std::type_index(typeid(long))] = "%ld";
    types[std::type_index(typeid(double))] = "%lg";
    types[std::type_index(typeid(float))] = "%f";
    types[std::type_index(typeid(char))] = "%c";
    types[std::type_index(typeid(const char *))] = "%s";
    types[std::type_index(typeid(size_t))] = "%z";
    types[std::type_index(typeid(ptrdiff_t))] = "%t";

    types[std::type_index(typeid(void *))] = "%p";
    types[std::type_index(typeid(int *))] = "%p";
    types[std::type_index(typeid(long *))] = "%p";
    types[std::type_index(typeid(float *))] = "%p";
    types[std::type_index(typeid(double *))] = "%p";

    types[std::type_index(typeid(void))] = "%n";

    return types;
}

static std::unordered_map<std::type_index, const char *> type_names = generate_type_names();

void print(FILE * outstream, const char * str);

template <typename DataT, typename... Others>
void print(FILE * outstream, const char * str, DataT arg, Others... args);

template <typename DataT, typename... Others>
size_t check_args(const char * str, DataT arg, Others... args);

void fprint(FILE * outstream, const char * str, size_t arg_num);

template <typename DataT, typename... Others>
void fprint(FILE * outstream, const char * str, size_t arg_num, DataT arg, Others... args);

#include "print.hpp"

#endif // !VECTOR_PRINT_H
