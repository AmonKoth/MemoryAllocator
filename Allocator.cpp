#include "Allocator.h"

template<class T>
ArenaAllocator<T>::ArenaAllocator(std::size_t size) :arenaSize(size), arena(static_cast<char*>(malloc(size))), currentPosition(0) {
    if (!arena) {
        std::cerr << "Failed to allocate memory for the arena!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

template<class T>
ArenaAllocator<T>::~ArenaAllocator()
{
    free(arena);
}

template<class T>
T* ArenaAllocator<T>::allocate(std::size_t numOfElements)
{
    if (currentPosition + numOfElements *sizeof(T) > arenaSize) {
        std::cerr << "Out of memory in the arena!" << std::endl;
        return nullptr;
    }

    T* ptr = reinterpret_cast<T*>(arena + currentPosition);
    currentPosition += numOfElements *sizeof(T);
    return ptr;
}

template<class T>
void ArenaAllocator<T>::reset()
{
    currentPosition = 0;
}


template struct ArenaAllocator<int>;