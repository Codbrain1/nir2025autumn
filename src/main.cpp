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
    int buff_size=5;
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
    Buffer psbuffer(ps,Filetype::bin);
    ps.SaveToFile_all(
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
            psbuffer.push_buff(ps);
            counter=1;
            if(psbuffer.buffer.size()==buff_size)
            {
                psbuffer.saveToFile();
                psbuffer.clear();
            }
        }

        //визуализация (опционально)
        //...
        
        ps.t+=ps.dt;
        ++counter;
    }
    

}