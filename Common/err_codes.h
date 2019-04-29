#ifndef VECTOR_ERR_CODES_H
#define VECTOR_ERR_CODES_H
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

#define err_tostr(err_code) #err_code

//!@enum Enumeration of error codes
enum Errors {
    //! Error code: Unknown error code
            ERR_CODE_UNKNOWN = -1,
    //! Error code: input capacity is not positive value in Vector constructor
            ERR_VEC_CTOR_CAP = 1,
    //! Error code: operator new[] has returned NULL in nothrow mode in Vector constructor
            ERR_VEC_CTOR_NEW_DATA,
    //! Error code: negative index in method at(int index)
            ERR_VECT_AT_NEG_INDEX,
    //! Error code: input index is more than capacity of elements in Vector
            ERR_VEC_AT_SIZE,
    //! Error code: output file name is NULL in memory leak checking utility
            ERR_CHECK_MEMLEAK_OUT,
    //! Error code: error while opening output file in memory leak checking utility
            ERR_CHECK_MEMLEAK_OUT_FOPEN,
    //! Error code: input file name is NULL in memory leak checking utility
            ERR_READ_DUMP_INPUT,
    //! Error code: error while opening dump file in memory leak checking utility
            ERR_READ_DUMP_FOPEN,
    //! Error code: dump file has zero length in memory leak checking utility
            ERR_READ_DUMP_LEN,
    //! Error code: no memory was allocated for temporary buffer for dump text in memory leak checking utility
            ERR_READ_DUMP_MLC,
    //! Error code: zero bytes were read from dump file in memory leak checking utility
            ERR_READ_DUMP_LEN_DIFF,
    //! Error code: read dump file function has returned NULL in memory leak checking utility
            ERR_CHECK_MEMLEAK_TEXT,
    //! Error code: dump text is NULL in parse line function in memory leak checking utility
            ERR_PARSE_LINES_INPUT_TEXT,
    //! Error code: the pointer to output file is NULL in parse line function in memory leak checking utility
            ERR_PARSE_LINES_INPUT_FILE,
    //! Error code: Vector is filled in push back function
            ERR_PUSH_BACK_FILLED,
    //! Error code: Vector is empty in pop back function
            ERR_POP_BACK_EMPTY,
    //! Error code: Zero byte capacity in result Vector Bool in XOR Operator
            ERR_BOOL_XOR_CAP,
    //! Error code: Input string is nullptr in custom print
            ERR_PRINT_STR,
    //! Error code: Input arguments not equal to format specifier number is format string in custom print
            ERR_PRINT_ARGS,
    //! Error code: Output filestream is nullptr custom print
            ERR_PRINT_FILESTREAM,
};

#endif //VECTOR_ERR_CODES_H
