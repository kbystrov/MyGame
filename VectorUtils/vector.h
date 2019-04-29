#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <algorithm>
#include "err_codes.h"
#include "MyExcp.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

#define PLACEMENT_NEW_DEEP_COPY

#ifdef PLACEMENT_NEW_DEEP_COPY
#undef SWAP_DEEP_COPY
#else
#define SWAP_DEEP_COPY
#endif

#define COPY_ASSIGN_OBJ_INPUT

#if defined(SWAP_DEEP_COPY) && defined(COPY_ASSIGN_OBJ_INPUT)
#undef COPY_ASSIGN_REF_INPUT
#else
#define COPY_ASSIGN_REF_INPUT
#endif // !(SWAP_DEEP_COPY && COPY_ASSIGN_OBJ_INPUT)

#define MOVE_SEMANTICS

#define TEST_MOVE_SEMANTICS

//! Default stack size
const size_t DEF_VECTOR_SIZE = 10;
//! Special value which is filled in Vector's not used data
const int POISON = 666;

//!@class Vector class - class for data container
template <typename DataT, size_t Size = DEF_VECTOR_SIZE>
class Vector {
private:
    size_t  capacity_; ///< @param capacity_ The maximum number of elements in Vector
    size_t  size_; ///< @param size_ The current number of filled elements in Vector
    DataT * data_; ///< @param data_ The pointer to elements array in Vector

    void swap(Vector& rhs);

public:
    Vector():///< Default constructor without input parameters and with Initialization List
        Vector(Size)
    {}
    Vector(size_t capacity); ///< Parametrized constructor
    ~Vector(); ///< Class destructor

    DataT& at(int index);
    const DataT& at(int index) const;
    DataT& operator[] (int index);
    const DataT& operator[] (int index) const;
    size_t get_size();
    size_t get_size() const;

    void push_back(const DataT& value);
    void pop_back();

    Vector<DataT, Size>(const Vector<DataT, Size>& rhs);  ///< Deep copy constructor. For guarding from shallow copy. Errno should be assigned to zero before using this constructor.

    #ifdef PLACEMENT_NEW_DEEP_COPY
    Vector<DataT, Size>& operator= (const Vector<DataT, Size>& rhs); ///< Deep copy assignment operator by using placement new. For guarding from shallow copy.
    #else
    #ifdef COPY_ASSIGN_REF_INPUT
    Vector<DataT, Size>& operator= (const Vector<DataT, Size>& rhs); ///< Deep copy assignment operator by swapping this with input copy object. For guarding from shallow copy.
    #else
    Vector<DataT, Size>& operator= (Vector<DataT, Size> rhs); ///< Deep copy assignment operator by swapping this with input copy object. For guarding from shallow copy.
    #endif // !COPY_ASSIGN_REF_INPUT
    #endif // !PLACEMENT_NEW_DEEP_COPY

    #ifdef MOVE_SEMANTICS
    Vector<DataT, Size>(Vector<DataT, Size>&& rhs); ///< Move constructor. For temporary objects for which copy elision is not performed:
    Vector<DataT, Size>& operator= (Vector<DataT, Size>&& rhs); ///<  Move assignment operator for temporary objects.
    #endif // !MOVE_SEMANTICS
};

template <typename DataT, size_t SizeLeft, size_t  SizeRight, size_t SizeRes = (SizeLeft > SizeRight) ? SizeRight : SizeLeft>
Vector<DataT, SizeRes> operator+ (const Vector<DataT, SizeLeft>& a, const Vector<DataT, SizeRight>& b);


#ifdef TEST_MOVE_SEMANTICS
extern FILE * ctr_asgn_dump;
#endif // !TEST_MOVE_SEMANTICS

#include "vector.hpp"

#endif //VECTOR_VECTOR_H
