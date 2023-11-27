#ifndef MYVECTOR_H
#define MYVECTOR_H
#define _GLIBCXX_VECTOR 1

#include <iostream>

class Thing{
public:
    int i;
    static bool verbose;
    static size_t last_alloc;
    static void* last_ptr;

    Thing() : i(-1){}
    Thing(int i) : i(i){}

    ~Thing(){
        if(Thing::verbose){
            std::cout << "Deleting thing with value " << i << std::endl;
        }
    }

    /**
     * @brief operator new[]
     * @param sz
     * @return
     * Ignore this function completely... its just here to help mark.
     */
    void* operator new[](size_t sz){
        size_t count = (sz - sizeof(size_t)) / sizeof(Thing);
        if(verbose){
           std::cout << "Allocated space for " << count << " thing(s)" << std::endl;
        }
        last_alloc = count;
        void* buffer = malloc(sz);
        return buffer;
    }
    void operator delete[](void* ptr, std::size_t sz){
        if(verbose){
           std::cout << "Deallocated space for " << sz << " thing(s)" << std::endl;
        }
        last_ptr = (size_t*)ptr +1;
        ::operator delete[](ptr);
    }

};

class MyVector
{
public:
    MyVector();
    ~MyVector();

    void print() const;

    size_t size() const;
    size_t allocated_length() const;

    void push_front(const Thing& t);
    void pop_front();

    Thing& front();
    Thing& back();

    Thing* begin();
    Thing* end();

    Thing& operator[](size_t i);
    Thing& at(size_t i);

protected:
    void reallocate(size_t new_size);

    Thing* data;
    size_t n_items, n_allocated;
};

#endif // MYVECTOR_H
