#include <iostream>
#include "Heap.h"
#include <random>
#include "Printer.h"

int main()
{
    Heap<int> heap;

    std::random_device rd;

    std::mt19937 mersenne(rd()); 
    
    int temp;

    for (size_t i = 0; i < 25; i++)
    {
        temp = mersenne() % 200;

        std::cout << temp << '\t';
        
        heap.Push(temp);
    }

    std::cout << std::endl;

    Printer::PrettyPrint(heap);

    std::cout << std::endl;
    
    return 0;
}