#include "SimpleArray.h"

/* Constructor and Destructor */ 
SimpleArray::SimpleArray(AllocationTracker* ptr) : mArray(ptr) {}

SimpleArray::~SimpleArray() {
    delete[] mArray;
}

/* Accessors */

// get: Returns the current pointer to the array
AllocationTracker* SimpleArray::get() const {
    return mArray;
}

// isNonNull: Checks if the current pointer is non-null
bool SimpleArray::isNonNull() const {
    return mArray != nullptr;
}


/**
 *  getReference: Returns a reference to the element at the specified index
 *  Throws an exception if the array is null
 *  @param i Index of the element to access
 *  @return Reference to the element at the specified index
*/
AllocationTracker& SimpleArray::getReference(const uint32_t i) const {
    return mArray[i];
}

/* Mutators */

// release: Releases the current pointer and returns it
// Sets the internal pointer to nullptr
AllocationTracker* SimpleArray::release() {
    AllocationTracker* temp = mArray;
    mArray = nullptr; // Set pointer to nullptr
    return temp; // Return the previous pointer
}

// reset: Sets the pointer to a new value, deallocating the old array if necessary
// @param rhs Pointer to the new array (default is nullptr)
void SimpleArray::reset(AllocationTracker* rhs) {
    delete[] mArray;  // Deallocate existing array
    mArray = rhs;     // Set pointer to new array
}

// swap: Swaps the pointers of two SimpleArray objects
// @param rhs SimpleArray object to swap with
void SimpleArray::swap(SimpleArray& rhs) {
    AllocationTracker* temp = mArray;
    mArray = rhs.mArray;
    rhs.mArray = temp;
}