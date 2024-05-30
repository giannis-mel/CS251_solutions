#include "ArrayList.h"
#include <algorithm>
#include <stdexcept>
#include <sstream>

// Default constructor
template <typename T>
ArrayList<T>::ArrayList() : mArray(nullptr), mSize(0), mCapacity(0) {}

// Constructor with size and value
template <typename T>
ArrayList<T>::ArrayList(const uint32_t& size, const T& value) : mArray(new T[size]), mSize(size), mCapacity(size) {
    std::fill(mArray.get(), mArray.get() + size, value);
}

// Copy constructor
template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& src) : mArray(new T[src.mSize]), mSize(src.mSize), mCapacity(src.mCapacity) {
    std::copy(src.mArray.get(), src.mArray.get() + src.mSize, mArray.get());
}

// Move constructor
template <typename T>
ArrayList<T>::ArrayList(ArrayList<T>&& src) noexcept : mArray(std::move(src.mArray)), mSize(src.mSize), mCapacity(src.mCapacity) {
    src.mArray = nullptr;
    src.mSize = 0;
    src.mCapacity = 0;
}

// Copy assignment operator
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& src) {
    if (this != &src) {
        ArrayList<T> temp(src);
        std::swap(mArray, temp.mArray);
        std::swap(mSize, temp.mSize);
        std::swap(mCapacity, temp.mCapacity);
    }
    return *this;
}

// Move assignment operator
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>&& src) noexcept {
    if  (this != &src) {
        mArray = std::move(src.mArray);
        mSize = src.mSize;
        mCapacity = src.mCapacity;
        src.mSize = 0;
        src.mCapacity = 0;
    }
    return *this;
}

// Adds the provided element to the end of the list
template <typename T>
const uint32_t& ArrayList<T>::add(const T& value) {
    return add(mSize, value); // Use add(index, value)
}

// Resizes the current array
template<typename T>
void ArrayList<T>::resize_array() {
    uint32_t newCapacity = (mCapacity == 0) ? 1 : mCapacity * 2;
    ScopedArray<T> newArray(new T[newCapacity]);
    std::move(mArray.get(), mArray.get() + mSize, newArray.get());
    mArray.swap(newArray);
    mCapacity = newCapacity;
}


// Adds the provided element at the specified index
template <typename T>
const uint32_t& ArrayList<T>::add(const uint32_t& index, const T& value) {
    if (index > mSize) {
        // If the index is beyond the current size, resize and fill with default values up to the index
        while(index >= mCapacity) {
            resize_array();
        }
        std::fill(mArray.get() + mSize, mArray.get() + index, T());
        mArray[index] = value;
        mSize = index + 1;
    } else {
        // If array is currently full
        if (mSize == mCapacity) {
            resize_array();
        }
        // Move elements one position to the right to make space for the new element
        std::move_backward(mArray.get() + index, mArray.get() + mSize, mArray.get() + mSize + 1);
        mArray[index] = value;
        ++mSize;
    }
    return mCapacity;
}

// Clears the list
template <typename T>
void ArrayList<T>::clear() {
    mArray = nullptr;
    mSize = 0;
    mCapacity = 0;
}

// Gets the element at the specified index
template <typename T>
T& ArrayList<T>::get(const uint32_t& index) {
    if (index >= mSize) {
        throw std::out_of_range(std::to_string(index));
    }
    return mArray[index];
}

// Gets the element at the specified index (const version)
template <typename T>
const T& ArrayList<T>::get(const uint32_t& index) const {
    if (index >= mSize) {
        throw std::out_of_range(std::to_string(index));
    }
    return mArray[index];
}

// Subscript operator for accessing elements
template <typename T>
T& ArrayList<T>::operator[](const uint32_t& index) {
    return get(index);
}

// Subscript operator for accessing elements (const version)
template <typename T>
const T& ArrayList<T>::operator[](const uint32_t& index) const {
    return get(index);
}

// Checks if the list is empty
template <typename T>
bool ArrayList<T>::isEmpty() const {
    return mSize == 0;
}

// Removes the element at the specified index and returns it
template <typename T>
T ArrayList<T>::remove(const uint32_t& index) {
    if (index >= mSize) {
        throw std::out_of_range(std::to_string(index));
    }
    T removedElement = mArray[index];
    for(uint32_t i = index; i < mSize - 1; ++i) {
        mArray[i] = std::move(mArray[i + 1]);
    }
    mSize--;
    return removedElement;
}

// Sets the element at the specified index to the given value
template <typename T>
void ArrayList<T>::set(const uint32_t& index, const T& value) {
    if (index >= mSize) {
        throw std::out_of_range(std::to_string(index));
    }
    mArray[index] = value;
}

// Returns the size of the list
template <typename T>
uint32_t ArrayList<T>::size() const {
    return mSize;
}

// Swaps the contents of this list with another list
template <typename T>
void ArrayList<T>::swap(ArrayList<T>& src) noexcept {
    std::swap(mArray, src.mArray);
    std::swap(mSize, src.mSize);
    std::swap(mCapacity, src.mCapacity);
}