#pragma once
#include<fstream>
#include "Buff.h"
#include<vector>
#include<type_traits>
#include "../includes/ParticleContainer.h"
enum Filetype{txt,bin};
template<class T,Filetype type>
class Buffer
{
    // проверка времени компиляции на подходящие типы данных(double и long double) 
    static_assert(std::is_same_v<T,double> || std::is_same_v<T,long double>,"Only type double and long double supported"); 
    
    std::ofstream file_positions; // поток файла позиций
    std::ofstream file_conv_laws; // поток файла законов сохранения

    std::vector<Buff_posit<T>> buffer_posit; //буффер позиций частиц
    std::vector<Buff_conv_laws<T>> buffer_conv_laws; // буффер законов сохранения частиц
    public:

    Buffer():
    buffer_posit(0),
    buffer_conv_laws(0)
    {
        if constexpr(type==Filetype::txt) // проверка времени компиляции на текстовый или бинарный тип файла
        {
            file_positions.open("results/positions.txt",std::ios::app);
            file_conv_laws.open("results/conversation_laws.txt",std::ios::app);
        }
        else if constexpr(type==Filetype::bin)
        {
            file_positions.open("results/positions.bin",std::ios::app|std::ios::binary);
            file_conv_laws.open("results/conversation_laws.bin",std::ios::app|std::ios::binary);
        }else
        {
            static_assert(type==Filetype::txt||type==Filetype::bin,"File type error\n");
        }
    }

    std::ofstream& get_file_positions(){return file_positions;}
    std::ofstream& get_file_conv_laws(){return file_conv_laws;}

    inline size_t size_buff_posit(){return buffer_posit.size();}
    inline size_t size_buff_conv_laws(){return buffer_conv_laws.size();}

    void push_buff_posit(ParticleContainer<T>& ps)
    {
        Buff_posit<T> temp; // добавление данных позиций в буфер
        temp.t=ps.t;
        temp.N=ps.N;
        for(int i=0;i<ps.N;i++)
        {
            temp.x.push_back(ps.x[i]);
            temp.y.push_back(ps.y[i]);
            temp.z.push_back(ps.z[i]);
            temp.vx.push_back(ps.vx[i]);
            temp.vy.push_back(ps.vy[i]);
            temp.vz.push_back(ps.vz[i]);
        }
        buffer_posit.push_back(temp);
    }
    void push_buff_conv_laws(ParticleContainer<T>& ps)
    {
        Buff_conv_laws<T> temp; // добавление данных законов сохранения в буфер
        temp.t=ps.t;
        temp.E=ps.E;
        temp.P_module2=ps.Px*ps.Px+ps.Py*ps.Py+ps.Pz*ps.Pz;
        temp.L_module2=ps.Lx*ps.Lx+ps.Ly*ps.Ly+ps.Lz*ps.Lz;
        buffer_conv_laws.push_back(temp);

    }
    
    void saveToFile_position()
    {
        if constexpr (type==Filetype::txt)
        {

            file_positions<<std::setprecision(std::is_same_v<T,double>? 13 : 16);
            for(int i=0;i<buffer_posit.size();++i)
            {
                auto& b = buffer_posit[i];
                file_positions<<b.t<<"\n"<<b.N<<"\n";

                for(int j=0;j<b.N;++j)
                {
                    file_positions<<b.x[j]<<"\t"<<b.y[j]<<"\t"<<b.z[j]<<"\t"
                    <<b.vx[j]<<"\t"<<b.vy[j]<<b.vz[j]<<"\n";
                }
            }
            buffer_posit.clear();
        }else
        {
            for(int i=0;i<buffer_posit.size();++i)
            {
                auto& b = buffer_posit[i];
                file_positions.write(reinterpret_cast<char*>(&b.t),sizeof(T)); //запись момента времени в бинарный файл
                file_positions.write(reinterpret_cast<char*>(&b.N),sizeof(T));
                for(int j=0;j<b.N;++j)
                {
                    T temp[6]={b.x[j], b.y[j], b.z[j], b.vx[j], b.vy[j], b.vz[j]}; //запись данных позиций и скоростей в бинарный файл
                    file_positions.write(reinterpret_cast<char*>(&temp),6*sizeof(T));
                }
            }
            buffer_posit.clear();
        }
    }
    void saveToFile_conv_laws()
    {
        if constexpr(type==Filetype::txt)
        {
            file_conv_laws<<std::setprecision(std::is_same_v<T,double>? 13 : 16);
            for(int i=0;i<buffer_conv_laws.size();++i)
            {
                auto& b =buffer_conv_laws[i];
                file_conv_laws<<b.t<<"\t"<<b.E<<"\t"<<b.P_module2<<"\t"<<b.L_module2<<"\n";
            }
            buffer_conv_laws.clear();
        }else
        {
            for(int i=0;i<buffer_conv_laws.size();++i)
            {
                auto& b = buffer_conv_laws[i];
                T temp[4]={b.t, b.E, b.P_module2, b.L_module2};
                file_conv_laws.write(reinterpret_cast<char*>(&temp),4*sizeof(T));
            }
            buffer_conv_laws.clear();
        }
    }

    inline void saveToFile_position_async();
    inline void saveToFile_conv_laws_async();

};