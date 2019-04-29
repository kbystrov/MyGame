#ifndef VECTOR_VECTOR_BOOL_H
#define VECTOR_VECTOR_BOOL_H

#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <algorithm>
#include "err_codes.h"
#include "MyExcp.h"
#include "vector.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */


const size_t BYTE_SIZE = sizeof(uint8_t) << 3;
const size_t BYTE_SHIFT = 3 * sizeof(uint8_t);
const uint8_t BOOL_POISON = 0;

//!@class Vector class - class for data container
template <> ///< @todo Приватный класс прокси на index бита и битовый сдвиг для бита
class Vector<bool> {
private:
    size_t  byte_capacity_; ///< @param capacity_ The maximum number of bytes in Vector
    size_t  bit_capacity_; ///< @param capacity_ The maximum number of bits in Vector
    size_t  bit_size_; ///< @param bit_size_ The current number of filled bits in Vector
    uint8_t * data_; ///< @param data_ The pointer to bytes array in Vector

    class BoolProxy {
    private:
        const Vector * vector_ = nullptr;
        size_t bit_pos_;
        size_t byte_pos_;
    public:
        explicit BoolProxy(Vector * vector, size_t bit_index);
        explicit BoolProxy(const Vector * vector, size_t bit_index);
        ~BoolProxy();
        BoolProxy& operator=( bool x );
        BoolProxy& operator=( const BoolProxy& x );
        operator bool() const;
        void flip();
    };

    void swap(Vector<bool>& rhs);

public:
    Vector<bool>():///< Default constructor without input parameters and with Initialization List
            Vector<bool>(DEF_VECTOR_SIZE)
    {}
    Vector<bool>(size_t bit_capacity); ///< Parametrized constructor
    ~Vector<bool>(); ///< Class destructor

    BoolProxy at(int index);
    const BoolProxy at(int index) const;
    BoolProxy operator[] (int index); ///< Ссылка на прокси-класс
    const BoolProxy operator[] (int index) const;
    size_t get_size();
    size_t get_size() const;
    size_t get_capacity();
    size_t get_capacity() const;

    void push_back(const bool& value);
    void pop_back();

    Vector<bool>(const Vector<bool>& rhs);  ///< Deep copy constructor. For guarding from shallow copy. Errno should be assigned to zero before using this constructor.

    #ifdef PLACEMENT_NEW_DEEP_COPY
    Vector<bool>& operator= (const Vector<bool>& rhs); ///< Deep copy assignment operator by using placement new. For guarding from shallow copy.
    #else
    #ifdef COPY_ASSIGN_REF_INPUT
    Vector<bool>& operator= (const Vector<bool>& rhs); ///< Deep copy assignment operator by swapping this with input copy object. For guarding from shallow copy.
    #else
    Vector<bool>& operator= (Vector<bool> rhs); ///< Deep copy assignment operator by swapping this with input copy object. For guarding from shallow copy.
    #endif // !COPY_ASSIGN_REF_INPUT
    #endif // !PLACEMENT_NEW_DEEP_COPY

    #ifdef MOVE_SEMANTICS
    Vector<bool>(Vector<bool>&& rhs); ///< Move constructor. For temporary objects for which copy elision is not performed:
    Vector<bool>& operator= (Vector<bool>&& rhs); ///<  Move assignment operator for temporary objects.
    #endif // !MOVE_SEMANTICS
};


Vector<bool> operator^(const Vector<bool>& a, const Vector<bool>& b);

#endif // !VECTOR_VECTOR_BOOL_H

