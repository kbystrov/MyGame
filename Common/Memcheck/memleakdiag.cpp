#include "memleakdiag.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */


/**
 * @brief Checks dump file for case of memory leak - when operator new or new[] were called but not subsequent call operator delete or delete[] were made for specific object.
 * @param dump_file_name Name of dump file
 * @param out_file_name Name of output file with memory leak diagnostic parameters
 * @return If there is no errors - zero, else - special error code
 */
int checkMemoryLeak(const char * dump_file_name, const char * out_file_name) {
    int err_code = 0;
    FILE * out_file = nullptr;

    //! Opening output file for memory leak diagnostics
    if(out_file_name == nullptr){
        return ERR_CHECK_MEMLEAK_OUT;
    }

    if ( !(out_file = fopen(out_file_name, "w")) ){
        return ERR_CHECK_MEMLEAK_OUT_FOPEN;
    }

    //! Reading the dump file into char array
    errno = 0;
    char * dump_text = readDumpFile(dump_file_name);
    err_code = errno;

    if(err_code || (dump_text == nullptr) ){
        free(dump_text);
        fclose(out_file);
        return (dump_text == nullptr) ? ERR_CHECK_MEMLEAK_TEXT : err_code;
    }

    //! Parsing dump text for checking memory leaks
    err_code = parseLines(dump_text, out_file);

    free(dump_text);
    fclose(out_file);

    return err_code;
}

/**
 * @brief Reads input dump file into dynamic char arrays
 * @param dump_file_name Name of dump file to be read
 * @return The pointer to dynamic char array with text from dump file
 */
char * readDumpFile(const char * dump_file_name) {
    FILE * dump_file = nullptr;

    if(dump_file_name == nullptr){
        errno = ERR_READ_DUMP_INPUT;
        return nullptr;
    }

    if ( !(dump_file = fopen(dump_file_name, "r")) ){
        errno = ERR_READ_DUMP_FOPEN;
        return nullptr;
    }

    //! Get the length of the input file in bytes
    fseek(dump_file, 0, SEEK_END);
    size_t input_file_length = ftell(dump_file);
    rewind(dump_file);

    if(!input_file_length){
        fclose(dump_file);
        errno = ERR_READ_DUMP_LEN;
        return nullptr;
    }

    //!Create temporary array of chars and read dump text into it.
    char * dump_text = (char *) malloc(input_file_length);
    if(dump_text == nullptr){
        fclose(dump_file);
        errno = ERR_READ_DUMP_MLC;
        return nullptr;
    }

    size_t read_res = fread(dump_text, 1, input_file_length, dump_file);

    if (!read_res) {
        free(dump_text);
        fclose(dump_file);
        errno = ERR_READ_DUMP_LEN_DIFF;
        return nullptr;
    }

    fclose(dump_file);

    return dump_text;
}

/**
 * @brief Parses lines of dump text for finding addresses for which memory was allocated but was not freed
 * @param dump_text The pointer to dynamic char array with text from dump file
 * @param out_file Output file to be written with memory leak diagnostic info
 * @return If there is no errors - zero, else - special error code
 */
int parseLines(const char * dump_text, FILE * out_file) {

    if(dump_text == nullptr){
        return ERR_PARSE_LINES_INPUT_TEXT;
    }

    if(out_file == nullptr){
        return ERR_PARSE_LINES_INPUT_FILE;
    }

    const char * new_line = dump_text;
    const char * pos = dump_text;
    const char * addr_pos = nullptr;
    const char * del_pos = nullptr;
    char addr_str[MAX_LINE_SIZE] = {};

    while (pos = strstr(new_line, new_tok)){ ///< Finds one by one all new operators call in dump text
        new_line = pos;
        //! Finds address after new operator call and write it into temporary buffer
        if ( !(addr_pos = strstr(pos, "0x")) ){
            break;
        }

        int word_len = strcspn(addr_pos, " \0");
        if (word_len >= MAX_LINE_SIZE){
            word_len = MAX_LINE_SIZE - 1;
        }
        strncpy(addr_str, addr_pos, word_len);
        addr_str[word_len] = '\0';

        int str_len = strcspn(new_line, "\n");

        //! Then tries to find next appearance of that address in dump text
        pos = addr_pos + word_len;
        if ( !(del_pos = strstr(pos, addr_str)) ){ ///< If it was not found then previous read line with new operator is written into output file
            char * dump_line = (char *) malloc(str_len);
            strncpy(dump_line, new_line, str_len);
            fprintf(out_file, "%s\n", dump_line);
            free(dump_line);
        } else { ///< If it was found then checks if this address was freed in current line

            while(del_pos[0] != '\n'){
                del_pos--;
            }

            if ( !(strspn(del_pos + 1, del_tok)) ){ ///< If it is not freed then it is memory leak -> writes previous read line with new operator is written into output file
                char * dump_line = (char *) malloc(str_len);
                strncpy(dump_line, new_line, str_len);
                fprintf(out_file, "%s\n", dump_line);
                free(dump_line);
            }
        }

        new_line++;
    }

    return 0;
}

void * operator new(size_t size, const char * file, int line, FILE * dump_file) {
    if(dump_file == nullptr){
        dump_file = stderr;
    }
    void * ptr = new char[size];
    fprintf(dump_file, "new: %p in FILE: %s at LINE: %d\n", ptr, file, line);
    return ptr;
}

void * operator new[](size_t size, const char * file, int line, FILE * dump_file) {
    return operator new(size, file, line, dump_file);
}

void operator delete(void * ptr, const char *file, int line, FILE * dump_file) {
    if(dump_file == nullptr){
        dump_file = stderr;
    }
    delete[] (char *) ptr;
    fprintf(dump_file, "delete: %p in FILE: %s at LINE: %d\n", ptr, file, line);
    return;
}

void operator delete[](void * ptr, const char * file, int line, FILE * dump_file) {
    return operator delete(ptr, file, line, dump_file);
}
