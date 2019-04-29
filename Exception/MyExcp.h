#ifndef VECTOR_MYEXCP_H
#define VECTOR_MYEXCP_H

#include <stdlib.h>
#include <stdio.h>
#include <exception>
#include <memory.h>
#include "err_codes.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

const size_t excp_buf_max_size = 5000; ///< Max size of static buffer for my exception objects

const char * const no_info = "No info";

enum excp_str{
    EXCP_STR_MSG = 1,
    EXCP_STR_FILE,
};

///! Статический буфер внутри класса и переопределени new оператора - будет не димн.паямть дергать, а статическую использовать
///! throw MyExcp("blabla", new MyExcp(e))
///! @todo Спецификация вектора под bool

class MyExcp : public std::exception {
private:
    static char my_excp_buf_[excp_buf_max_size]; ///< Static buffer for my exception object allocation
    static char * my_excp_buff_pos_; ///< Current position of free space in static buffer for my exception objects
    static size_t my_excp_buf_least_mem_; ///< Current position of free space in static buffer for my exception objects

    static char tmp_excp_buf_[excp_buf_max_size]; ///< Static buffer for temporary objects of MyExcp
    static char * tmp_excp_buff_pos_; ///< Current position of free space in static buffer for temporary objects of MyExcp
    static size_t tmp_excp_buf_least_mem_; ///< Current position of free space in static buffer for temporary objects of MyExcp

    Errors err_code_;
    char * err_msg_;
    char * file_;
    int lnum_;
    MyExcp * reason_ = nullptr;

    bool tmp_flg_; ///< Flag which identifies that thrown exception is temporary object and should be located in separate buffer for temporary exception objects

    void cpy_str_to_buf(const char * src, excp_str dest_type);
public:
    explicit MyExcp(Errors err_code = ERR_CODE_UNKNOWN, const char * msg = no_info, const char * file = no_info, int lnum = -1, bool tmp_flg = true);
    explicit MyExcp(MyExcp * reason, bool tmp_flg = false, Errors err_code = ERR_CODE_UNKNOWN, const char * msg = no_info, const char * file = no_info, int lnum = -1):
            MyExcp(err_code, msg, file, lnum, tmp_flg)
            {
                reason_ = reason;
            }

    virtual ~MyExcp() override;

    void * operator new(size_t size);
    void operator delete(void * ptr);

    virtual const char * what() const noexcept override;
    void all_what(FILE * dest) const;
    void all_dump(FILE * dest) const;
};

const size_t obj_size = sizeof(MyExcp);

#endif //VECTOR_MYEXCP_H
