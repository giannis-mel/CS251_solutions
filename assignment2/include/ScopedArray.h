#ifndef SCOPED_ARRAY_H
#define SCOPED_ARRAY_H

#include <cstddef> // for std::size_t

template <typename T>
class ScopedArray {
public:
    // Constructor that accepts pointer 
    ScopedArray(T* rhs = nullptr);

    // Destructor
    ~ScopedArray();

    // Move constructor
    ScopedArray(ScopedArray&& other) noexcept;

    // Move assignment operator
    ScopedArray& operator=(ScopedArray&& other) noexcept;

    // [] operator versions
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T* get() const;
    bool isNonNull() const;
    operator bool() const;
    bool operator!() const;
    T* release();
    void reset(T* rhs = nullptr);
    void swap(ScopedArray& rhs);

    // Do not generate copy semantics
    ScopedArray(const ScopedArray&) = delete;
    ScopedArray& operator=(const ScopedArray&) = delete;

private:
    T* data_;
};

#include "../src/ScopedArray.cpp"
#endif // SCOPED_ARRAY_H
