#include "vector_bool.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

#ifdef TEST_MOVE_SEMANTICS
FILE * ctr_asgn_dump;
#endif // !TEST_MOVE_SEMANTICS

Vector<bool>::Vector(size_t byte_capacity) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Constructor with parameter for Bool Vector was called -> %p\n", this);
    #endif // !TEST_MOVE_SEMANTICS

    if(byte_capacity < 1){
        throw MyExcp(ERR_VEC_CTOR_CAP, "Attempt to create Bool Vector with non-positive capacity in Vector constructor", __FILE__, __LINE__);
    }

    byte_capacity_ = byte_capacity;
    bit_capacity_ = byte_capacity << BYTE_SHIFT;
    bit_size_ = 0;

    data_ = new (std::nothrow) uint8_t[byte_capacity_]; ///< Nothrow exception in order to handling errors in memory allocation customly in run-time
    if(data_ == nullptr){
        throw MyExcp(ERR_VEC_CTOR_NEW_DATA, "Attempt to allocate memory for data in Bool Vector constructor has been failed", __FILE__, __LINE__);
    }

    #ifndef NDEBUG
    for(size_t i = 0; i < byte_capacity_; i++){
        data_[i] = BOOL_POISON;
    }
    #endif

}

Vector<bool>::~Vector() {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Destructor for Bool Vector was called -> %p\n", this);
    #endif // !TEST_MOVE_SEMANTICS

    delete[] data_;
    data_ = nullptr;
}

Vector<bool>::BoolProxy Vector<bool>::at(int index) {

    if(index < 0){
        throw MyExcp(ERR_VECT_AT_NEG_INDEX, "Attempt to get Bool Vector data bit with negative index in method at(int index)", __FILE__, __LINE__);
    }

    if(index >= bit_capacity_){
        throw MyExcp(ERR_VEC_AT_SIZE, "Attempt to get not filled Bool Vector data bit in method at(int index)", __FILE__, __LINE__);
    }

    return BoolProxy(this, index);
}

const Vector<bool>::BoolProxy Vector<bool>::at(int index) const {

    if(index < 0){
        throw MyExcp(ERR_VECT_AT_NEG_INDEX, "Attempt to get Bool Vector data bit with negative index in method at(int index) const", __FILE__, __LINE__);
    }

    if(index >= bit_capacity_){
        throw MyExcp(ERR_VEC_AT_SIZE, "Attempt to get not filled Bool Vector data bit in method at(int index) const", __FILE__, __LINE__);
    }

    return BoolProxy(this, index);
}

Vector<bool>::BoolProxy Vector<bool>::operator[](int index) {
    return BoolProxy(this, index);
}

const Vector<bool>::BoolProxy Vector<bool>::operator[](int index) const {
    const BoolProxy boolProxy(this, index);
    return boolProxy;
}

size_t Vector<bool>::get_size() {
    return bit_size_;
}

size_t Vector<bool>::get_size() const {
    return bit_size_;
}
size_t Vector<bool>::get_capacity() {
    return byte_capacity_;
}

size_t Vector<bool>::get_capacity() const {
    return byte_capacity_;
}


void Vector<bool>::push_back(const bool &value) {

    if(bit_size_ >= bit_capacity_){
        throw MyExcp(ERR_PUSH_BACK_FILLED, "Attempt to push new element in the end of Bool Vector while it is filled", __FILE__, __LINE__);
    }

    BoolProxy boolProxy(this, bit_size_++);
    boolProxy = value;
}

void Vector<bool>::pop_back() {

    if(bit_size_ <= 0){
        throw MyExcp(ERR_POP_BACK_EMPTY, "Attempt to pop last element in Bool Vector while it is empty", __FILE__, __LINE__);
    }

    BoolProxy boolProxy(this, bit_size_--);
    boolProxy = 0;
}

Vector<bool> operator^(const Vector<bool>& a, const Vector<bool>& b) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "XOR of Bool Vectors %p ^ %p\n", &a, &b);
    #endif // !TEST_MOVE_SEMANTICS

    size_t a_size = a.get_size();
    size_t b_size = b.get_size();

    size_t min_bit_size = (a_size > b_size ) ? b_size : a_size;

    size_t a_capacity = a.get_capacity();
    size_t b_capacity = b.get_capacity();

    size_t byte_capacity = (a_capacity > b_capacity ) ? b_capacity : a_capacity;

    if(!byte_capacity){
        throw MyExcp(ERR_BOOL_XOR_CAP, "Zero byte capacity of result Bool Vector in XOR Operator", __FILE__, __LINE__);
    }

    try {

        Vector<bool> result(byte_capacity);

        for (int i = 0; i < min_bit_size; i++) {
            //result[i] = bool(a.at(i)) ^ bool(b.at(i));
            result.push_back( bool(a.at(i)) ^ bool(b.at(i)) );
        }

        return result;

    } catch(MyExcp& myExcp) {
        throw MyExcp(new MyExcp(myExcp), true, ERR_CODE_UNKNOWN, "Exception was caught in Bool Vector XOR Operator", __FILE__, __LINE__);
    }
}

void Vector<bool>::swap(Vector<bool>& rhs) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Swapping Vector Bool objects: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    std::swap(byte_capacity_, rhs.byte_capacity_);
    std::swap(bit_capacity_, rhs.bit_capacity_);
    std::swap(bit_size_, rhs.bit_size_);
    std::swap(data_, rhs.data_);
}

Vector<bool>::Vector(const Vector<bool> &vector) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Deep copy constructor for Bool Vector was called: Vector %p = %p\n", this, &vector);
    #endif // !TEST_MOVE_SEMANTICS

    try {
        new(this) Vector(vector.byte_capacity_);
    } catch(MyExcp& myExcp){
        throw MyExcp(new MyExcp(myExcp), true, ERR_CODE_UNKNOWN, "Exception was caught in Bool Vector Deep Copy Constructor", __FILE__, __LINE__);
    }

    if (vector.bit_size_ > (vector.byte_capacity_ << BYTE_SHIFT) ) {
        bit_size_ = (vector.byte_capacity_ << BYTE_SHIFT);
        byte_capacity_ = vector.byte_capacity_;
        bit_capacity_ = bit_size_;
    } else {
        bit_size_ = vector.bit_size_;
        byte_capacity_ = vector.byte_capacity_;
        bit_capacity_ = vector.bit_capacity_;
    }

    if(!byte_capacity_){
        throw MyExcp(ERR_CODE_UNKNOWN, "Zero byte capacity in Deep Copy Constructor for Bool Vector", __FILE__, __LINE__);
    }

    for (size_t i = 0; i < byte_capacity_; i++) {
        data_[i] = vector.data_[i];
    }

}

#ifdef PLACEMENT_NEW_DEEP_COPY
Vector<bool>& Vector<bool>::operator=(const Vector<bool>& rhs) {
    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Deep copy assignment operator for Bool Vector was called: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    if(this != &rhs) { ///< Preventing redundant copy in self-assignment operation
        this->~Vector();
        try {
            new(this) Vector<bool>(rhs);
        } catch(MyExcp& myExcp){
            throw MyExcp(new MyExcp(myExcp), true, ERR_CODE_UNKNOWN, "Exception was caught in Vector Deep copy assignment operator", __FILE__, __LINE__);
        }
    }

    return *this;
}
#else

#ifdef COPY_ASSIGN_REF_INPUT
Vector<bool>& Vector<bool>::operator=(const Vector<bool> &rhs) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(dump_file, "Deep copy assignment operator with swapping for Vector was called with input reference: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    if(this != &rhs) { ///< Preventing redundant copy in self-assignment operation
        Vector<bool> tmp(rhs);
        swap(tmp);
    }

    return *this;
}
#else
Vector<bool>& Vector<bool>::operator=(Vector<bool> rhs) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(dump_file, "Deep copy assignment operator with swapping for Vector was called with input temporary object: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    swap(rhs);
    return *this;
}
#endif //!COPY_ASSIGN_REF_INPUT

#endif // !PLACEMENT_NEW_DEEP_COPY

#ifdef MOVE_SEMANTICS

Vector<bool>::Vector(Vector<bool>&& rhs) {
    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Move constructor for Bool Vector was called: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    bit_size_ = rhs.bit_size_;
    bit_capacity_ = rhs.bit_capacity_;
    byte_capacity_ = rhs.byte_capacity_;
    data_ = rhs.data_;
    rhs.data_ = nullptr;
}

Vector<bool>& Vector<bool>::operator=(Vector<bool>&& rhs) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Move assignment operator with swapping for Bool Vector was called: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    if(this != &rhs) { ///< Preventing redundant swapping in self-assignment operation
        swap(rhs);
    }

    return *this;
}

#endif // !MOVE_SEMANTICS

Vector<bool>::BoolProxy::BoolProxy(Vector * vector, size_t bit_index) {
    vector_ = vector;
    bit_pos_ = bit_index;
    byte_pos_ = bit_index >> BYTE_SHIFT;
}

Vector<bool>::BoolProxy::BoolProxy(const Vector * vector, size_t bit_index) {
    vector_ = vector;
    bit_pos_ = bit_index;
    byte_pos_ = bit_index >> BYTE_SHIFT;
}

Vector<bool>::BoolProxy::~BoolProxy() {
}

Vector<bool>::BoolProxy& Vector<bool>::BoolProxy::operator=(bool x) {
    vector_->data_[byte_pos_] = (vector_->data_[byte_pos_] & ~(1 << bit_pos_) ) | ( x << bit_pos_);
    return *this;
}

Vector<bool>::BoolProxy::operator bool() const {
    return vector_->data_[byte_pos_] & (1 << bit_pos_);
}

Vector<bool>::BoolProxy& Vector<bool>::BoolProxy::operator=(const Vector<bool>::BoolProxy& x) {
    *this = bool(x);
    return *this;
}

void Vector<bool>::BoolProxy::flip() {
    vector_->data_[byte_pos_] = vector_->data_[byte_pos_] ^ (1 << bit_pos_);
}







