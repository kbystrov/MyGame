#ifndef VECTOR_VECTOR_HPP
#define VECTOR_VECTOR_HPP

 /** @file */

template <typename DataT, size_t Size>
Vector<DataT, Size>::Vector(size_t capacity) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Constructor with parameter for Vector was called -> %p\n", this);
    #endif // !TEST_MOVE_SEMANTICS

    if(capacity < 1){
        throw MyExcp(ERR_VEC_CTOR_CAP, "Attempt to create Vector with non-positive capacity in Vector constructor", __FILE__, __LINE__);
    }

    capacity_ = capacity;
    size_ = 0;

    data_ = new (std::nothrow) DataT[capacity]; ///< Nothrow exception in order to handling errors in memory allocation customly in run-time
    if(data_ == nullptr){
        throw MyExcp(ERR_VEC_CTOR_NEW_DATA, "Attempt to allocate memory for data in Vector constructor has been failed", __FILE__, __LINE__);
    }

    #ifndef NDEBUG
    for(size_t i = 0; i < capacity; i++){
        data_[i] = POISON;
    }
    #endif

}

template <typename DataT, size_t Size>
Vector<DataT, Size>::~Vector() {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Destructor for Vector was called -> %p\n", this);
    #endif // !TEST_MOVE_SEMANTICS

    delete[] data_;
    data_ = nullptr;
}

template <typename DataT, size_t Size>
DataT& Vector<DataT, Size>::at(int index) {

    if(index < 0){
        throw MyExcp(ERR_VECT_AT_NEG_INDEX, "Attempt to get Vector data element with negative index in method at(int index)", __FILE__, __LINE__);
    }

    if(index >= capacity_){
        throw MyExcp(ERR_VEC_AT_SIZE, "Attempt to get not filled Vector data element in method at(int index)", __FILE__, __LINE__);
    }

    return data_[index];
}

template <typename DataT, size_t Size>
const DataT& Vector<DataT, Size>::at(int index) const {

    if(index < 0){
        throw MyExcp(ERR_VECT_AT_NEG_INDEX, "Attempt to get Vector data element with negative index in method at(int index) const", __FILE__, __LINE__);
    }

    if(index >= capacity_){
        throw MyExcp(ERR_VEC_AT_SIZE, "Attempt to get not filled Vector data element in method at(int index) const", __FILE__, __LINE__);
    }

    return data_[index];
}

template <typename DataT, size_t Size>
DataT& Vector<DataT, Size>::operator[](int index) {
    return data_[index];
}

template <typename DataT, size_t Size>
const DataT& Vector<DataT, Size>::operator[](int index) const {
    return data_[index];
}

template <typename DataT, size_t Size>
size_t Vector<DataT, Size>::get_size() {
    return size_;
}

template <typename DataT, size_t Size>
size_t Vector<DataT, Size>::get_size() const {
    return size_;
}

template <typename DataT, size_t Size>
void Vector<DataT, Size>::push_back(const DataT &value) {

    if(size_ >= capacity_){
        throw MyExcp(ERR_PUSH_BACK_FILLED, "Attempt to push new element in the end of Vector while it is filled", __FILE__, __LINE__);
    }

    data_[size_++] = value;
}

template <typename DataT, size_t Size>
void Vector<DataT, Size>::pop_back() {

    if(size_ <= 0){
        throw MyExcp(ERR_POP_BACK_EMPTY, "Attempt to pop last element in Vector while it is empty", __FILE__, __LINE__);
    }

    data_[size_--] = POISON;
}

template <typename DataT, size_t SizeLeft, size_t  SizeRight, size_t SizeRes = (SizeLeft > SizeRight) ? SizeRight : SizeLeft>
Vector<DataT, SizeRes> operator+(const Vector<DataT, SizeLeft>& a, const Vector<DataT, SizeRight>& b) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Sum of vector %p + %p\n", &a, &b);
    #endif // !TEST_MOVE_SEMANTICS

    size_t a_size = a.get_size();
    size_t b_size = b.get_size();

    size_t min_size = (a_size > b_size ) ? b_size : a_size;

    try {

        Vector<DataT, SizeRes> result;

        for (int i = 0; i < min_size; i++) {
            result[i] = a.at(i) + b.at(i);
        }

        return result;

    } catch(MyExcp& myExcp) {
        throw MyExcp(new MyExcp(myExcp), true, ERR_CODE_UNKNOWN, "Exception was caught in Vector Sum Operator", __FILE__, __LINE__);
    }
}

template <typename DataT, size_t Size>
void Vector<DataT, Size>::swap(Vector<DataT, Size>& rhs) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Swapping objects: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    std::swap(capacity_, rhs.capacity_);
    std::swap(size_, rhs.size_);
    std::swap(data_, rhs.data_);
}

template <typename DataT, size_t Size>
Vector<DataT, Size>::Vector(const Vector<DataT, Size> &vector) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Deep copy constructor for Vector was called: Vector %p = %p\n", this, &vector);
    #endif // !TEST_MOVE_SEMANTICS

    try {
        new(this) Vector(vector.capacity_);
    } catch(MyExcp& myExcp){
        throw MyExcp(new MyExcp(myExcp), true, ERR_CODE_UNKNOWN, "Exception was caught in Vector Deep Copy Constructor", __FILE__, __LINE__);
    }

    if (vector.size_ > vector.capacity_) {
        size_ = vector.capacity_;
    } else {
        size_ = vector.size_;
    }

    for (size_t i = 0; i < vector.size_; i++) {
        data_[i] = vector.data_[i];
    }

}

#ifdef PLACEMENT_NEW_DEEP_COPY
template <typename DataT, size_t Size>
Vector<DataT, Size>& Vector<DataT, Size>::operator=(const Vector<DataT, Size>& rhs) {
    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Deep copy assignment operator for Vector was called: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    if(this != &rhs) { ///< Preventing redundant copy in self-assignment operation
        this->~Vector();
        try {
            new(this) Vector(rhs);
        } catch(MyExcp& myExcp){
            throw MyExcp(new MyExcp(myExcp), true, ERR_CODE_UNKNOWN, "Exception was caught in Vector Deep copy assignment operator", __FILE__, __LINE__);
        }
    }

    return *this;
}
#else

#ifdef COPY_ASSIGN_REF_INPUT
template <typename DataT, size_t Size>
Vector<DataT, Size>& Vector<DataT, Size>::operator=(const Vector<DataT, Size> &rhs) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(dump_file, "Deep copy assignment operator with swapping for Vector was called with input reference: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    if(this != &rhs) { ///< Preventing redundant copy in self-assignment operation
        Vector tmp(rhs);
        swap(tmp);
    }

    return *this;
}
#else
template <typename DataT, size_t Size>
Vector<DataT, Size>& Vector<DataT, Size>::operator=(Vector<DataT, Size> rhs) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(dump_file, "Deep copy assignment operator with swapping for Vector was called with input temporary object: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    swap(rhs);
    return *this;
}
#endif //!COPY_ASSIGN_REF_INPUT

#endif // !PLACEMENT_NEW_DEEP_COPY

#ifdef MOVE_SEMANTICS

template <typename DataT, size_t Size>
Vector<DataT, Size>::Vector(Vector<DataT, Size>&& rhs) {
    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Move constructor for Vector was called: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data_ = rhs.data_;
    rhs.data_ = nullptr;
}

template <typename DataT, size_t Size>
Vector<DataT, Size>& Vector<DataT, Size>::operator=(Vector<DataT, Size>&& rhs) {

    #ifdef TEST_MOVE_SEMANTICS
    fprintf(ctr_asgn_dump, "Move assignment operator with swapping for Vector was called: %p = %p\n", this, &rhs);
    #endif // !TEST_MOVE_SEMANTICS

    if(this != &rhs) { ///< Preventing redundant swapping in self-assignment operation
        swap(rhs);
    }

    return *this;
}

#endif // !MOVE_SEMANTICS

#endif // !VECTOR_VECTOR_HPP

