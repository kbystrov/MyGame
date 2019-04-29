#ifndef VECTOR_PRINT_HPP
#define VECTOR_PRINT_HPP

/** @file */

template <typename DataT, typename... Others>
void print(FILE * outstream, const char * str, DataT arg, Others... args){
    size_t arg_num = check_args(str, arg, args...);
    fprint(outstream, str, arg_num, arg, args...);
}

template <typename DataT, typename... Others>
size_t check_args(const char * str, DataT arg, Others... args) {

    size_t str_args = 0;

    while(*str){
        if(*str++ == PRINT_SPEC_SYMBL){
            str_args++;
        }
    }

    if(str_args != (sizeof...(args) + !!arg) ){ ///< @note Нормально ли кидать в кастомном принте исключение при неправильном числе аргументов? Или лучше через errno?
        ///@note Как вариант можно проверять через "if constexpr" условие и кидать static_assert - тогда проверка на этапе компиляции. Но есть только в C++17 и в моей версии GCC не поддерживается.
        throw MyExcp(ERR_PRINT_ARGS, "No matching number of input arguments and number of argument specifier in print function", __FILE__, __LINE__);
    }

    return str_args;
}

template <typename DataT, typename... Others>
void fprint(FILE * outstream, const char * str, size_t arg_num, DataT arg, Others... args) {

    if(outstream == nullptr){ ///< @note Нормально ли кидать в кастомном принте исключение при неправильном числе аргументов? Или лучше через errno?
        throw MyExcp(ERR_PRINT_FILESTREAM, "Output filestream is nullptr in print function", __FILE__, __LINE__);
    }

    if(str == nullptr){ ///< @note Нормально ли кидать в кастомном принте исключение при неправильном числе аргументов? Или лучше через errno?
        throw MyExcp(ERR_PRINT_STR, "Input string is nullptr in print function", __FILE__, __LINE__);
    }

    const char * pos = strchr(str, PRINT_SPEC_SYMBL);
    if (pos){
        size_t str_tok_len = pos - str;
        fwrite(str, 1, str_tok_len, outstream);
        str += str_tok_len;
    } else {
        fprint(outstream, str, 0);
    }

    if(arg_num > 0){
        fprintf(outstream, type_names[std::type_index(typeid(DataT))], arg);
        arg_num--;
        fprint(outstream, str + 1, arg_num, args...);
        return;
    }

}

#endif // !VECTOR_PRINT_HPP
