#include "MyExcp.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

char MyExcp::my_excp_buf_[excp_buf_max_size] = {};
char * MyExcp::my_excp_buff_pos_ = my_excp_buf_;
size_t MyExcp::my_excp_buf_least_mem_ = excp_buf_max_size;

char MyExcp::tmp_excp_buf_[excp_buf_max_size] = {};
char * MyExcp::tmp_excp_buff_pos_ = tmp_excp_buf_;
size_t MyExcp::tmp_excp_buf_least_mem_ = excp_buf_max_size;

void MyExcp::cpy_str_to_buf(const char * src, excp_str dest_type) {

    char * dest = nullptr;

    size_t dest_least_mem = 0;
    char * dest_buf_pos = nullptr;

    if(tmp_flg_){
        dest_least_mem = tmp_excp_buf_least_mem_;
        dest_buf_pos = tmp_excp_buff_pos_;
    } else {
        dest_least_mem = my_excp_buf_least_mem_;
        dest_buf_pos = my_excp_buff_pos_;
    }

    if(dest_type == EXCP_STR_FILE){
        file_ = dest_buf_pos;
        dest = file_;
    } else {
        err_msg_ = dest_buf_pos;
        dest = err_msg_;
    }

    if(src == nullptr){
        src = no_info;
    }

    size_t msg_len = strlen(src) + 1;

    if(msg_len > dest_least_mem){
        fprintf(stderr, "Not enough memory for error message during exception creation!\n");
        std::terminate();
    } else {
        dest = dest_buf_pos;
        for(int i = 0, text_len = msg_len - 1; i < text_len; i++){
            dest[i] = src[i];
        }
        dest[msg_len] = '\0';
        dest_least_mem -= msg_len;
        dest_buf_pos += msg_len;
    }

    if(tmp_flg_){
        tmp_excp_buf_least_mem_ = dest_least_mem;
        tmp_excp_buff_pos_ = dest_buf_pos;
    } else {
        my_excp_buf_least_mem_ = dest_least_mem;
        my_excp_buff_pos_ = dest_buf_pos;
    }

}

MyExcp::MyExcp(Errors err_code, const char * msg, const char * file, int lnum, bool tmp_flg) {

    tmp_flg_ = tmp_flg;

    err_code_ = err_code;

    cpy_str_to_buf(msg, EXCP_STR_MSG);

    cpy_str_to_buf(file, EXCP_STR_FILE);

    lnum_ = lnum;

    reason_ = nullptr;
}

MyExcp::~MyExcp() {

    size_t dest_least_mem = 0;
    char * dest_buf_pos = nullptr;

    if(tmp_flg_){
        dest_least_mem = tmp_excp_buf_least_mem_;
        dest_buf_pos = tmp_excp_buff_pos_;
    } else {
        dest_least_mem = my_excp_buf_least_mem_;
        dest_buf_pos = my_excp_buff_pos_;
    }

    size_t file_len = strlen(file_) + 1;

    if (dest_least_mem + file_len > excp_buf_max_size){
        fprintf(stderr, "Trying to free not allocated memory in MyExcp Destructor! Nothing is performed!\n");
    } else {
        dest_least_mem += file_len;
        dest_buf_pos -= file_len;
    }

    size_t msg_len = strlen(err_msg_) + 1;

    if (dest_least_mem + msg_len > excp_buf_max_size){
        fprintf(stderr, "Trying to free not allocated memory in MyExcp Destructor! Nothing is performed!\n");
    } else {
        dest_least_mem += msg_len;
        dest_buf_pos -= msg_len;
    }

    if(tmp_flg_){
        tmp_excp_buf_least_mem_ = dest_least_mem;
        tmp_excp_buff_pos_ = dest_buf_pos;
    } else {
        my_excp_buf_least_mem_ = dest_least_mem;
        my_excp_buff_pos_ = dest_buf_pos;
    }

    if(reason_ && !reason_->tmp_flg_) {
        delete reason_;
    }
}

void * MyExcp::operator new(size_t size) {

    if ( size > my_excp_buf_least_mem_) {
        fprintf(stderr, "Not enough memory for exception creation!\n");
        return NULL;
    } else {
        void * ptr = my_excp_buff_pos_;
        my_excp_buf_least_mem_ -= size;
        my_excp_buff_pos_ += size;
        return ptr;
    }

}

void MyExcp::operator delete(void * ptr) {

    if (my_excp_buf_least_mem_ + obj_size > excp_buf_max_size){
        fprintf(stderr, "Trying to free not allocated memory for exception! Nothing is performed!\n");
    } else {
        my_excp_buf_least_mem_ += obj_size;
        my_excp_buff_pos_ -= obj_size;
    }

}

const char * MyExcp::what() const noexcept {
    return err_msg_;
}

void MyExcp::all_what(FILE * dest) const {

    if(dest == nullptr){
        dest = stderr;
    }

    fprintf(dest, "Error: %s\n", what());
    if(reason_){
        fprintf(dest, "Reason => ");
        reason_->all_what(dest);
    }
}

void MyExcp::all_dump(FILE * dest) const {

    if(dest == nullptr){
        dest = stderr;
    }

    fprintf(dest, "Error message: %s in FILE: %s in LINE %d. Error code: %d\n", what(), file_, lnum_, err_code_);
    if(reason_){
        fprintf(dest, "Reason => ");
        reason_->all_dump(dest);
    }
}
