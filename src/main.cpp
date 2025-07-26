#include "../includes/Animation.h"
#include "../includes/Buffer.h"
#include "../includes/ParticleContainer.h"
#include "../includes/DIRSUMM/KDK.h"
#include "../includes/DIRSUMM/RK4.h"
#include "../includes/SPH/KDK.h"
#include "../includes/SPH/RK4.h"
#include "../includes/init_condition.h"

#include<filesystem>
int  main()
{
    // создание системы частиц
    int N=1000;
    int buff_size_posit=5;
    int buff_size_conv_laws=10;
    double M=1;
    double t1=0,t2=1;

    ParticleContainer<double> ps(N,M,t1);
    
    //установка начальных условий системы
    InitialConditoin::set_uniform_disk(ps); 
    InitialConditoin::set_circle_velocity(ps);
    ps.t=0.001;

    //вычисление начальных законов сохранения
    DirectSumm::KDK::calculate_forces(ps);              //TODO: вычисление сил
    DirectSumm::KDK::calculate_conversation_laws(ps);   //TODO: вычисление законов сохранения

    try
    {
        //создание новой директории хранения
        if(!std::filesystem::exists("results"))
            std::filesystem::create_directory("results");
        else
        {
            int i=1;
            while (std::filesystem::exists("results"+std::to_string(i)))
            {
                i++;
            }
            std::filesystem::rename("results","results"+std::to_string(i));
            std::filesystem::create_directory("results");
        }

    }catch(const std::filesystem::filesystem_error& e)
    {
        std::ofstream eror("error.txt");
        eror << "Filesystem error: " << e.what() << '\n';
        eror << "Path1: " << e.path1() << '\n';
        if (!e.path2().empty()) {
            eror<< "Path2: " << e.path2() << '\n';
        }
    }

    //буффер для быстрого сохранения системы частиц
    Buffer<double, Filetype::bin> psbuffer;
    ps.SaveToBinaryFile_all(
        psbuffer.get_file_positions(),
        psbuffer.get_file_conv_laws()
    );

    int counter=1;

    while(ps.t<=t2)
    {
        //вычисление положения частиц
        DirectSumm::KDK::next_step(ps);
        DirectSumm::KDK::calculate_conversation_laws(ps);

        //сохранение в файлы (опционально)
        if(counter%10==0)
        {
            psbuffer.push_buff_posit(ps);
            counter=1;
            if(psbuffer.size_buff_posit()>=buff_size_posit)
            {
                psbuffer.saveToFile_position();
            }
        }
        if(counter%5==0)
        {
            psbuffer.push_buff_conv_laws(ps);
            if(psbuffer.size_buff_conv_laws()>=buff_size_conv_laws)
            {
                psbuffer.saveToFile_conv_laws();
            }
        }

        //визуализация (опционально)
        //...
        
        ps.t+=ps.dt;
        ++counter;
    }
    

}