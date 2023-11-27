#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstring>

#define _GLIBCXX_VECTOR 1
#include "myvector.h"

#ifdef _WIN32
int main(int argc, char* argv[])
{
    int result = Catch::Session().run(argc, argv);
    return result;
}
#endif

class MyVectorExtended : public MyVector{
public:
    Thing* get_data(){ return data;}
    size_t get_n_items(){ return n_items; }
    size_t get_n_allocated(){ return n_allocated;}
};

MyVectorExtended* getNewMyVector(){
    MyVectorExtended* buf = (MyVectorExtended*)malloc(sizeof(MyVectorExtended));
    std::memset(buf,1, sizeof(MyVectorExtended));
    new (buf) MyVectorExtended;
    return buf;
}

TEST_CASE("ConstructorTests"){
    // Don't look at this code, it will make you sad :(
    auto buf = getNewMyVector();
    Thing* data = buf->get_data();
    SECTION("Initialise Data Members"){
        INFO("Make sure that data points to null in a newly constructed MyVector.");
        REQUIRE(data == nullptr);
    }
    SECTION("n_items"){
        INFO("Make sure that n_items is 0 in a newly constructed MyVector.")
                size_t n_items = buf->get_n_items();
        REQUIRE(n_items == 0);
    }
    SECTION("n_allocated"){
        INFO("Make sure that n_allocated is 0 in a newly constructed MyVector.")
                size_t n_allocated = buf->get_n_allocated();
        REQUIRE(n_allocated == 0);
    }
    // Intentional memory leak to avoid calling the destructor.
}


TEST_CASE_METHOD(MyVector, "SizeAndAllocationFunctions"){
    INFO("Check that the size() and allocated_length() report "
         "the values in n_items and n_allocated.");

    SECTION("Empty List"){
        REQUIRE(n_items == 0);
        REQUIRE(n_allocated == 0);
    }
    SECTION("Manually changing n_items/n_allocated"){
        INFO("Here I manually change the value of the variable "
             "to a random number to check that you're outputting"
             " the variable correctly.");

        size_t r1 = rand();
        size_t r2 = rand();
        n_items = r1;
        n_allocated = r2;
        REQUIRE(size() == r1);
        REQUIRE(allocated_length() == r2);
    }
}
TEST_CASE_METHOD(MyVector, "BufferReallocation"){
    SECTION("Is reallocate() working?"){
        INFO("Here I use your reallocate function to allocate a random number of blocks. I check that you allocate the correct amount.")
        Thing::last_alloc = 0;
        size_t random_number = rand() % 10;
        ++random_number;
        reallocate(random_number);
        REQUIRE(random_number == Thing::last_alloc);
    }
    SECTION("Is reallocate() working?"){
        INFO("Here I use your reallocate function to allocate a random number of blocks. I check that you don't have a memory leak.")
        Thing::last_alloc = 0;
        size_t random_number = rand() % 10;
        ++random_number;
        n_items = random_number;
        n_allocated = random_number;
        data = new Thing[random_number];
        void* original_buffer = data;
        reallocate(2*random_number);
        void* last_deleted_address = Thing::last_ptr;
        REQUIRE(original_buffer == last_deleted_address);
    }
    SECTION("Is reallocate() working?"){
        INFO("Here I use your reallocate function to allocate a double the number of allocated blocks. I check that you copy the Things across and update the relevant data in the MyVector class.")
        Thing::last_alloc = 0;
        size_t random_number = rand() % 10;
        int offset = rand() % 100;
        ++random_number;
        n_items = random_number;
        n_allocated = random_number;
        data = new Thing[random_number];

        int it = n_items;
        for(int i = n_allocated-1; it > 0; it--, i--){
            data[i].i = it*it*it + offset;
        }
        auto original_n_items = n_items;
        auto new_n_allocated = 2*n_items;
        reallocate(2*random_number);
        REQUIRE(n_items == original_n_items);
        REQUIRE(n_allocated == new_n_allocated);
        it = n_items;
        for(int i = n_allocated-1; it > 0; it--, i--){
            int val = it*it*it + offset;
            REQUIRE(data[i].i == val);
        }
    }
    SECTION("Is reallocate() working?"){
        INFO("Here I use your reallocate function to half the number of allocated blocks. I check that you copy the Things across and update the relevant data in the MyVector class.")
        Thing::last_alloc = 0;
        size_t random_number = rand() % 10;
        int offset = rand() % 100;
        ++random_number; ++random_number; ++random_number;
        n_items = random_number;
        random_number *= 2;
        n_allocated = random_number;
        data = new Thing[random_number];
        int it = n_items;
        for(int i = n_allocated-1; it > 0; it--, i--){
            data[i].i = it*it*it + offset;
        }
        auto original_n_items = n_items;
        auto new_n_allocated = random_number/2;
        reallocate(random_number/2);
        REQUIRE(n_items == original_n_items);
        REQUIRE(n_allocated == new_n_allocated);
        it = n_items;
        for(int i = n_allocated-1; it > 0; it--, i--){
            int val = it*it*it + offset;
            REQUIRE(data[i].i == val);
        }
    }
    SECTION("Is reallocate() working?"){
        INFO("Here I use your reallocate function to half the number of allocated blocks but there are now more items that there is allocated memory. You should throw an error when the new_size is too small to fit the current number of items in the vector. You can throw any type of error, for example throw std::out_of_range(\"New size is too small for items.\")")
        Thing::last_alloc = 0;
        size_t random_number = rand() % 10;
        int offset = rand() % 100;
        ++random_number; ++random_number; ++random_number;
        random_number *= 2;
        n_items = random_number-3;
        n_allocated = random_number;
        data = new Thing[random_number];
        int it = n_items;
        for(int i = n_allocated-1; it > 0; it--, i--){
            data[i].i = i*i*i + offset;
        }
        REQUIRE_THROWS(reallocate(random_number/2));
    }
}
TEST_CASE_METHOD(MyVector, "PushAndPop"){
    SECTION("Checking reallocation, push_front, and pop_front"){
        INFO("None");
        Thing::last_alloc = 0;
        INFO("Empty Vector");
        REQUIRE(size() == 0);
        INFO("Pushed 1st thing");
        push_front(Thing(0));
        REQUIRE(size() == 1);
        REQUIRE(Thing::last_alloc == 1);
        INFO("Pushed 2nd thing");
        push_front(Thing(1));
        REQUIRE(size() == 2);
        REQUIRE(Thing::last_alloc == 2);
        INFO("Pushed 3rd thing");
        push_front(Thing(2));
        REQUIRE(size() == 3);
        REQUIRE(Thing::last_alloc == 4);
        INFO("Pushed 4th thing");
        push_front(Thing(3));
        REQUIRE(size() == 4);
        REQUIRE(Thing::last_alloc == 4);
        INFO("Pushed 5th thing");
        push_front(Thing(4));
        REQUIRE(size() == 5);
        REQUIRE(Thing::last_alloc == 8);
        INFO("Pushed 6th thing");
        push_front(Thing(5));
        REQUIRE(size() == 6);
        REQUIRE(Thing::last_alloc == 8);
        INFO("Pushed 7th thing");
        push_front(Thing(6));
        REQUIRE(size() == 7);
        REQUIRE(Thing::last_alloc == 8);
        INFO("Pushed 9th thing");
        push_front(Thing(7));
        REQUIRE(size() == 8);
        REQUIRE(Thing::last_alloc == 8);
        INFO("Pushed 9th thing");
        push_front(Thing(8));
        REQUIRE(size() == 9);
        REQUIRE(Thing::last_alloc == 16);
        INFO("Popped 9th thing");
        pop_front();
        REQUIRE(size() == 8);
        REQUIRE(Thing::last_alloc == 16);
        INFO("Popped 8th thing");
        pop_front();
        REQUIRE(size() == 7);
        REQUIRE(Thing::last_alloc == 16);
        INFO("Popped 7th thing");
        pop_front();
        REQUIRE(size() == 6);
        REQUIRE(Thing::last_alloc == 16);
        INFO("Popped 6th thing");
        pop_front();
        REQUIRE(size() == 5);
        REQUIRE(Thing::last_alloc == 16);
        INFO("Popped 5th thing");
        pop_front();
        REQUIRE(size() == 4);
        REQUIRE(Thing::last_alloc == 16);
        INFO("Popped 4th thing");
        pop_front();
        REQUIRE(size() == 3);
        REQUIRE(Thing::last_alloc == 8);
        INFO("Popped 3rd thing");
        pop_front();
        REQUIRE(size() == 2);
        REQUIRE(Thing::last_alloc == 8);
        INFO("Popped 2nd thing");
        pop_front();
        REQUIRE(size() == 1);
        REQUIRE(Thing::last_alloc == 4);
        INFO("Popped 1st thing");
        pop_front();
        REQUIRE(size() == 0);
        REQUIRE(Thing::last_alloc == 2);
    }
}

TEST_CASE_METHOD(MyVector, "TestingIndexOperatorAndAt"){
    int n = 10;// + rand() % 10;
    for(int i = 0; i < n; ++i){
        push_front(Thing(i));
    }
    SECTION("Checking operator[]"){
        for(int i = 0; i < n; ++i){
            Thing& myThing = operator[](i);
            decltype(myThing.i) val = n - i - 1;
            REQUIRE(myThing.i == val);
        }
    }
    SECTION("Checking at()"){
        for(int i = 0; i < n; ++i){
            Thing& myThing = at(i);
            decltype(myThing.i) val = n - i - 1;
            REQUIRE(myThing.i == val);
        }

        REQUIRE_THROWS(at(15));
        REQUIRE_THROWS(at(-1));
    }
}

TEST_CASE_METHOD(MyVector, "BeginEndFrontBack"){
    REQUIRE(begin() == nullptr);
    REQUIRE(end() == nullptr);

    push_front(Thing(42));
    REQUIRE(begin()->i == 42);
    REQUIRE((end()-1)->i == 42);
    REQUIRE(front().i == 42);
    REQUIRE(back().i == 42);

    for(int i = 0; i < 10; ++i){
        push_front(Thing(i));
        REQUIRE(begin()->i == i);
        REQUIRE(front().i == i);
        REQUIRE(back().i == 42);
        REQUIRE((end()-1)->i == 42);
    }
}

TEST_CASE_METHOD(MyVector, "MemoryLayout"){
    INFO("The last item should be at the back of the buffer and the first item should be after the last empty space.");
    for(int i = 9; i >= 0; --i){
        push_front(Thing(2*i));
    }
    auto forward_iterator = begin();
    for(int i = 0; i < 10; ++i){
        REQUIRE(forward_iterator->i == 2*i);
        forward_iterator++;
    }
    auto backward_iterator = end()-1;
    for(int i = 9; i >= 0; --i){
        REQUIRE(backward_iterator->i == 2*i);
        backward_iterator--;
    }
}

TEST_CASE( "Destructor"){
    INFO("Checking that the destructor frees the memory.");
    int n = rand() % 100;
    n += 10;
    MyVectorExtended* vec = getNewMyVector();
    for(int i = 9; i >= 0; --i){
        vec->push_front(Thing(2*i));
    }
    auto last_memory_buffer = vec->get_data();
    delete vec;

    auto last_deleted_address = Thing::last_ptr;
    REQUIRE(last_memory_buffer == last_deleted_address);
}
