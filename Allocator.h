#pragma once

#include <cstdlib>
#include <iostream>

template<class T>
struct ArenaAllocator
{


public:

    ArenaAllocator(std::size_t size);
    ~ArenaAllocator();

    T* allocate(std::size_t numOfElements = 1);

    void reset();

protected:
    std::size_t arenaSize;
    char* arena;
    std::size_t currentPosition;

};