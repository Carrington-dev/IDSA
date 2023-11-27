#include "myvector.h"
bool Thing::verbose = false;
size_t Thing::last_alloc = 0;
void* Thing::last_ptr = nullptr;

/**
 * @brief MyVector::MyVector Construct a vector with size 0
 *
 * Remember that the data pointer should point to nothing, and
 * counter variables should be initialised.
 */
MyVector::MyVector()
{
    data = nullptr;
    n_items = 0;
    n_allocated = 0;

}

/**
 * @brief MyVector::~MyVector Free any memory that you have allocated
 */
MyVector::~MyVector()
{
//    delete [] data;
}
/**
 * @brief MyVector::print Prints the contents of the memory buffer. This may be useful for debugging.
 */
void MyVector::print() const
{
    std::cout << "[";
    if(n_allocated > 0){
        for(size_t i = 0; i < n_allocated - 1; ++i)
            std::cout << data[i].i << ",";
        std::cout << data[n_allocated-1].i;
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief MyVector::size
 * @return The number of items in the vector
 */
size_t MyVector::size() const
{
    return n_items;
}


/**
 * @brief MyVector::allocated_length
 * @return The lenght of the allocated data buffer
 */
size_t MyVector::allocated_length() const
{
    return  n_allocated;
}

/**
 * @brief MyVector::push_front
 * @param t The thing to add
 *
 * Add a thing to the front of the vector.
 * Remember to check if there is enough space to insert it first.
 * If there is not enough space, then you should reallocate the buffer
 * and copy each thing accross. When expanding the buffer, double the
 * allocated size.
 */
void MyVector::push_front(const Thing &t)
{
    if(n_allocated == 0)
    {
        n_allocated = 1;
        reallocate(n_allocated);
        data[0] = t;
    }
    else if(n_items < n_allocated)
    {
         data[n_allocated - n_items - 1] = t;
    }else{
         reallocate(2*n_allocated);
         data[n_allocated - n_items - 1] = t;
    }
    n_items += 1;
}

/**
 * @brief MyVector::pop_back
 * Remove the last item from the back.
 * Reallocate with half the space if less than a quarter of the vector is used.
 */
void MyVector::pop_front()
{
    n_items--;
    if(n_items < n_allocated/4)
    {
        reallocate(n_allocated/2);
    }
    //    data[n_allocated - n_items - 1];
}

/**
 * @brief MyVector::front
 * @return A reference to the first item in the array.
 * I will never call this on an empty list.
 */
Thing &MyVector::front()
{
    return data[n_allocated-1];
}

/**
 * @brief MyVector::back
 * @return A reference to the last item in the array.
 *
 * Note that this might not be the back of the data buffer.
 * I will never call this on an empty list.
 */
Thing &MyVector::back()
{
    /*
     * 0 1 2 3 4 5
     *     4 5 6 6
     */
    return  data[n_allocated - n_items];
}

/**
 * @brief MyVector::begin
 * @return A pointer to the first thing.
 */
Thing *MyVector::begin()
{
    return &data[n_allocated-1];
}

/**
 * @brief MyVector::end
 * @return A pointer to the memory address following the last thing.
 */
Thing *MyVector::end()
{
    return &data[n_allocated-n_items];
}

/**
 * @brief MyVector::operator []
 * @param i
 * @return A reference to the ith item in the list.
 */
Thing &MyVector::operator[](size_t i)
{
    return data[n_allocated-i];
}

/**
 * @brief MyVector::at
 * @param i
 * @return A reference to the ith item in the list after checking
 * that the index is not out of bounds.
 * @throws throw std::out_of_range("Index out of bounds") if the index is out of bounds.
 */
Thing &MyVector::at(size_t i)
{
    if(i < n_items)
        return data[n_allocated-i];
    else{
        throw std::out_of_range("Index out of bounds");
    }
}

/**
 * @brief MyVector::reallocate
 * @param new_size
 * Reallocate the memory buffer to be "new_size" length, using new Thing[new_size]
 * Copy all items from the old buffer into the new one.
 * Delete the old buffer using delete[]
 */
void MyVector::reallocate(size_t new_size)
{
    if(new_size < n_items)
    {
       throw std::out_of_range("This size is too small for items");
    }

    if(new_size > n_allocated)
    {
        std::cout << "before" << std::endl;
        print();
        Thing* new_data = new Thing[new_size];

        for(size_t i = 0; i < n_items; i++)
        {
            /*size_t nw = new_size - i;
            new_data[nw] = data[n_items-i];*/
            size_t nw = n_items + i + 1;
            new_data[nw] = data[i];
        }
        n_allocated = new_size;
        delete [] data;
        data = new_data;
        std::cout << "After" << std::endl;
        print();
    }else{
        std::cout << "before else" << std::endl;
        print();
        Thing* new_data = new Thing[new_size];

        for(size_t i = 0; i < n_items; i++)
        {
            new_data[i] = data[n_items + i + 1];
        }
        n_allocated = new_size;
        delete [] data;
        data = new_data;
        std::cout << "After else" << std::endl;
        print();
    }

        /*
         * 0    1   2   3   4   5   6   7   8   9   10
         * 01   23  34  32  23
         *
         * -1   -1  -1  -1  -1  01  23  34  32  23;
         *
         *
         */
//    }

}

