CXX=g++ -g -std=c++11 -Wall -pedantic -Werror=vla
all: tests

tests: tests.o tests.cpp myvector.cpp myvector.h
	$(CXX) -o a.out tests.o myvector.cpp
tests.o: tests.cpp
	$(CXX) -c -o tests.o tests.cpp
