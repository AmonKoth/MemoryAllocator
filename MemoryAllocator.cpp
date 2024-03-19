#include <iostream>
#include <chrono>


#include "Allocator.h"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds miliseconds;

const int numAllocations = 10000;
const size_t allocationSize = 1000000;

const size_t testAmount = 5;



//void* operator new(std::size_t size)
//{
//    static ArenaAllocator arena(1000000);
//    return arena.allocate(size);
//}

//_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(_Size) _VCRT_ALLOCATOR
//void* __cdecl operator new(size_t _Size)
//{
//    // allocate using arena
//}

void timeConsumingMemoryOperations()
{
    for (int i = 0; i < numAllocations; ++i) {
        int* memoryBlock = new int[allocationSize];
        for (size_t j = 0; j < allocationSize; ++j) {
            memoryBlock[j] = j % 256;
        }
        delete[] memoryBlock;
    }
}

void timeConsumingMemoryOperationsArenaAllocator(ArenaAllocator<int> &arena)
{
    for (int i = 0; i < numAllocations; ++i) {
        int* memoryBlock = arena.allocate(allocationSize);

        for (size_t j = 0; j < allocationSize; ++j) {
            memoryBlock[j] = j % 256;
        }
        arena.reset();
    }
}


int main()
{
    
    for (int i = 0; i < testAmount; ++i)
    {
        Clock::time_point t0 = Clock::now();
        //timeConsumingMemoryOperations();
        ArenaAllocator<int> arenaAllocator(10000000);
        timeConsumingMemoryOperationsArenaAllocator(arenaAllocator);
        Clock::time_point t1 = Clock::now();
        miliseconds ms = std::chrono::duration_cast<miliseconds>(t1 - t0);
        std::cout << "\n" << ms.count() << " ms ";
    }
    return 0;
}
