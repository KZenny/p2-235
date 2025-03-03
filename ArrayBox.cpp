#include "ArrayBox.hpp"
#include <iostream>
/**
* @brief Default constructor
* @post Initializes capacity_ to 64 and size_ to 0. 
*      Allocates a dynamic array for items_ of length equal to the capacity_. 
*/
template <typename T>
ArrayBox<T>::ArrayBox() : capacity_(64), size_(0), items_(new T[capacity_]) {}

/**
* @brief Parameterized constructor
* @param capacity A const reference to an integer describing the maximum capacity of the items_ array.
*      If capacity is not positive (ie. <= 0), 64 is used instead.
* @post size_ is initialized to 0. items_ is initialized to a dynamically allocated array of length equal to 'capacity'
*/
template <typename T>
ArrayBox<T>::ArrayBox(const int& capacity) : size_(0) {
    if (capacity <= 0){
        capacity_ = 64;
        items_ = new T[capacity_]; 
        
    } else {
        capacity_ = capacity;
        items_ = new T[capacity];
    }
}

/**
 * @brief Prints out each element in items_ array
 */
template <typename T>
void ArrayBox<T>::displayArray() const {
    for (int i = 0; i < capacity_; i++) { // Loops through each element of ArrayBox and prints its content out. 
        std::cout << items_[i].getType() << " ";
    }
    std::cout << std::endl;
}

/**
* Getter for the size member
* @return Returns the integer value stored in size_
*/
template <typename T>
int ArrayBox<T>::size() const {
    return size_;
}

/**
* Getter for the capacity member
* @return Returns the integer value stored in capacity_
*/
template <typename T>
int ArrayBox<T>::capacity() const {
    return capacity_; 
}

/**
 * @brief Appends the parameter item to the `items_` array such that:
 *  1) There current size_ and target.size() is small enough 
 *      that the item can be added without exceeding the ArrayBox capacity_
 *  2) The target item takes up target.size() spaces at 
 *      starting at the leftmost non-occupied space
 * 
 * @param type A const reference to an item of type T, specifying the object to add
 * @return True if the add was successful. False otherwise.
 * @post Increment size_ if the item was added.
 * 
 * @example Given the following instructions, and a length 8 Object array:
        ArrayBox<ChessPiece> box(capacity=8);
        box.addItem(Pawn)   // Pawn size = 1
        box.addItem(Rook)   // Rook size = 2
        box.addItem(Queen)  // Queen size = 3
        box.addItem(Pawn)   // Pawn size = 1
        box.addItem(Rook)   // Rook size = 2
    
    Our `ArrayBox` will look like the following, 
    after all insertions, under the hood (assuming we print out the `type`).
        PAWN ROOK ROOK QUEEN QUEEN QUEEN PAWN NONE
        size = 7
    After this, when we tried addItem(Rook), the add would fail.
*/
template <typename T>
bool ArrayBox<T>::addItem(const T& type) {
    int startIndex = size(); //size_ is the leftmost non-occupied space's index of the array
    int itemSize = type.size();
    if(startIndex + itemSize <= capacity_) { // If adding the item will not exceed ArrayBox capacity_, add item to ArrayBox + return true. 
        for(int i = 0; i < itemSize; i++){
            items_[startIndex + i] = type;
        }
        size_ = size_ + itemSize;
        return true;
    } else { // Otherwise, ArrayBox will overfill so do not add item + return false.
        return false;
    }
}

/**
* @brief Removes the first instance in `items_` of an object whose `getType()` equals the parameter given
*      To maximize contiguous space available to add objects later, we shift 
*      all elements over by the size of the object we just removed.
*      
*      `size_` is also decremented by the size of the object we just removed.
* 
*      Instead of lazy-deletion, all values that are not counted as part of the valid subarray, ie. not from indices [0, size_)
*      are set to a default-initialized object
* 
*      If no object of the given type is found, nothing happens.
*
* @param type A const reference to a string specifying the type of the object to remove
*
* @post Objects after the removed instance are shifted elements over by the size of the object we just removed
* 
* @return True if the remove operation was successfully performed. False otherwise.
* 
* @example Given the resuls from the previous example, 
*       Before: "PAWN ROOK ROOK QUEEN QUEEN QUEEN PAWN NONE"
*       After removing `QUEEN`: "PAWN ROOK ROOK PAWN NONE NONE NONE NONE"
*       where `null` = ChessPiece()
*/
template <typename T>
bool ArrayBox<T>::remove(const std::string& type){
    int removeIndex = -1;
    for (int i = 0; i < size_; i++) { // Loops to find if an item in ArrayBox matches the paramter string
        if (items_[i].getType() == type) {
            removeIndex = i;
            break;
        }
    }
    if (removeIndex == -1) { // Returns false if removeIndex remains -1 (Parameter String was not found in ArrayBox)
        return false;
    }

    int itemSize = items_[removeIndex].size(); 
    for (int i = removeIndex; i < size_ - itemSize; i++) { // Shifts all elements left + Removing first instance of 'type' from ArrayBox
        items_[i] = items_[i + itemSize];
    }

    size_ -= itemSize;

    for (int i = size_; i < size_ + itemSize; i++) { //Set the empty indicies as default-initialized object ("NONE")
        items_[i] = T(); 
    }
    return true;
}

/**
 *  @brief Searches a subarray of `items_` for an item of the given type. 
 *      Returns the *leftmost* index of the item if it is found within 
 *      the subarray from [start, end). Return -1 if not found.
 * 
 *  @param type A const reference to a string denoting the `type` of the object to search for
 *  @param start An integer representing the start of the subarray to search
 *  @param end An integer representing the end of the subarray to search (non-inclusive)
 * 
 *  @return Either the index target in the subarray within items_ as an integer
 *  or -1, if the subarray does not contain an object of that type
 * 
 *  @note [start, end) means we look at all values from index = start, up to but 
 *  not including index = end
 *  a) If `start` is negative or >= size_
 *  b) If `end` is negative or > size_
 *  c) If `start` >= `end`
    The search is fails to execute, and -1 is returned.
**/
template <typename T>
int ArrayBox<T>::getIndexOf(const std::string& type, int start, int end) const{
    if(start < 0 || start >= size_ || end < 0 || end > size_ || start >= end) { // If not [start,end) range, return -1
        return -1;
    }

    for(int i = start; i < end; i++){
        if(items_[i].getType() == type){ // If 'type' is found within range, returns leftmost index
            return i; 
        }
    }

    return -1; // 'type' is not found within range. Return -1
}

/**
* @brief Counts the number of distinct intances of the 
*        given type within items_ from indices [0, size_)
*        A singular instance of an object is the block of indices from [a, a + a.size())
* 
* @param type A const reference to a string denoting the type of the item to search for
* @return An integer representing the number of 
*         distinct instances of objects 
*         whose `getType()` is equal to the parameter.
* 
* @example If given Pawn size = 1 and Queen size = 3 and an items_ array such as
*       PAWN PAWN QUEEN QUEEN QUEEN NONE
*       There are 2 instances of PAWN (since their size = 1, so they each only occupy one cell)
*       There is 1 instance of QUEEN (since its size = 3, so one Queen will occupy three cells)
*/
template <typename T>
int ArrayBox<T>::count(const std::string& type) const{
    int count = 0;
    int lastIndex = 0;
    for (int i = 0; i < size_; i++){ //Loops to find if an item in ArrayBox matches the parameter 'type'
        if(items_[i].getType() == type){
            lastIndex = i; //stores the last index of found 'type'
            count++; //updates the number of instances everytime 'type' is found
        }
    }
    if(count == 0){
        return 0; // if 'type' is not found, return 0 instances
    }

    return count/items_[lastIndex].size(); // returns number of instances of 'type' 
}


/**
* @param type A const reference to a string denoting the type of the item to search for
* @return True if items_ contains an object whose getType() equals the given parameter
*/
template <typename T>
bool ArrayBox<T>::contains(const std::string& type) const{
    for (int i = 0; i < size_; i++) { // Loops to find if an item in ArrayBox matches the paramter string
        if (items_[i].getType() == type) {
            return true; // returns true if an object whose getType() equals given parameter
        }
    }
    return false; // If no match is found, return false
}