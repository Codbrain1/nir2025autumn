#pragma once
#include "Buff.h"
#include<vector>
enum Filetype{txt,bin};
template<class T>
class Buffer
{

    std::ofstream file_positions;
    std::ofstream file_conv_laws;

    public:
    std::vector<Buff_posit<T>> buffer_posit;
    std::vector<Buff_conv_laws<T>> buffer_conv_laws;
    Buffer(T& ps,Filetype type):
    buffer_posit(0),
    buffer_conv_laws(0)
    {
        if(type==Filetype::txt)
        {
            file_positions.open("results/positions.txt",std::ios::app);
            file_conv_laws.open("results/conversation_laws.txt"+text_type,std::ios::app);
        }
        else if(type=Filetype::bin)
        {
            file_positions.open("results/positions.bin",std::ios::app|std::ios::bin);
            file_conv_laws.open("results/conversation_laws.bin"+text_type,std::ios::app|std::ios::bin);
        }else
        {
            throw "file type error\n";
            return 1;
        }
    }

    std::ofstream& get_file_positions(){return file_positions;}
    std::ofstream& get_file_conv_laws(){return file_conv_laws;}

    void push_buff(T& ps){}
    void clear(){}
    void saveToFile();
    void saveToBinaryFile();
    void saveToFile_async();
    void saveToBinaryFile_async();
};