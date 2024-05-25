#include "ScopedArray.h"
#include "AllocationTracker.h"
#include <algorithm> // for std::swap

// Constructor
template <typename T>
ScopedArray<T>::ScopedArray(T* rhs) 
    : data_(rhs) {}

// Destructor
template <typename T>
ScopedArray<T>::~ScopedArray() {
    delete[] data_;
}

// Move constructor
template <typename T>
ScopedArray<T>::ScopedArray(ScopedArray&& other) noexcept : data_(other.data_) {
    other.data_ = nullptr;
}

// Move assignment operator
template <typename T>
ScopedArray<T>& ScopedArray<T>::operator=(ScopedArray&& other) noexcept {
    if (this != &other) { // Self-assignment check
        delete[] data_;
        data_ = other.data_;
        other.data_ = nullptr;
    }
    return *this;
}

// [] operator (non-const) - used for modifications
template <typename T>
T& ScopedArray<T>::operator[](size_t index) {
    return data_[index];
}

// [] operator (const) - used for reading
template <typename T>
const T& ScopedArray<T>::operator[](size_t index) const {
    return data_[index];
}

// Get current pointer to the array
template <typename T>
T* ScopedArray<T>::get() const {
    return data_;
}

// Check if the current pointer is non-null
template <typename T>
bool ScopedArray<T>::isNonNull() const {
    return data_ != nullptr;
}

// Conversion operator to bool
template <typename T>
ScopedArray<T>::operator bool() const {
    return data_ != nullptr;
}

// Logical NOT operator
template <typename T>
bool ScopedArray<T>::operator!() const {
    return data_ == nullptr;
}

// Release the ownership of the array
template <typename T>
T* ScopedArray<T>::release() {
    T* temp = data_;
    data_ = nullptr;
    return temp;
}

// Reset the array to a new pointer
template <typename T>
void ScopedArray<T>::reset(T* rhs) {
    if (data_ != rhs) {
        delete[] data_;
        data_ = rhs;
    }
}

// Swap with another ScopedArray
template <typename T>
void ScopedArray<T>::swap(ScopedArray& rhs) {
    std::swap(data_, rhs.data_);
}
