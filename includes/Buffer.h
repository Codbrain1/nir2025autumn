#pragma once
#include "Buff.h"
#include<vector>
template<class T>
class Buffer
{
    public:
    std::vector<Buff<T>> buffer;
    void saveToFile();
    void saveToBinaryFile();
    void saveToFile_async();
    void saveToBinaryFile_async();
};