#include <filesystem>

#include "Containers/Buffer.h"
#include "Containers/ParticleContainer.h"
#include "init/init_condition.h"
#include "numerics/DIRSUMM/KDK.h"
#include "numerics/DIRSUMM/RK4.h"
#include "numerics/SPH/KDK.h"
#include "numerics/SPH/RK4.h"
#include "visualisation/Animation.h"
int main()
{
    // создание системы частиц
    int N = 1000;                  // число частиц
    int buff_size_posit = 5;       // размер буфера позиций частиц
    int buff_size_conv_laws = 10;  // размер буфера законов сохранения
    double t1 = 0, t2 = 1;         // интервал интегрирования
    double solt = 42;              // соль для задания распределения частиц
    double M = 1;                  // суммарная масса частиц
    double R = 1;                  // радиус диска

    ParticleContainer<double> ps(N, M, t1);

    // установка начальных условий системы
    InitialCondition::set_uniform_disk(ps, solt, R);
    InitialCondition::set_circle_velocity(ps, M, R);
    ps.dt = 0.0;

    // вычисление начальных законов сохранения
    DirectSumm::KDK::calculate_forces(ps);             // TODO: вычисление сил
    DirectSumm::KDK::calculate_conversation_laws(ps);  // TODO: вычисление законов сохранения

    try {
        // создание новой директории хранения
        if (!std::filesystem::exists("results"))
            std::filesystem::create_directory("results");
        else {
            int i = 1;
            while (std::filesystem::exists("results" + std::to_string(i))) {
                i++;
            }
            std::filesystem::rename("results", "results" + std::to_string(i));
            std::filesystem::create_directory("results");
        }

    } catch (const std::filesystem::filesystem_error& e) {
        std::ofstream error("error.txt");
        error << "Filesystem error: " << e.what() << '\n';
        error << "Path1: " << e.path1() << '\n';
        if (!e.path2().empty()) {
            error << "Path2: " << e.path2() << '\n';
        }
    }

    // буфер для быстрого сохранения системы частиц
    Buffer<double, Filetype::bin> psbuffer("results/positions", "results/conversation_laws");
    ps.SaveToBinaryFile_all(psbuffer.get_file_positions(), psbuffer.get_file_conv_laws());

    int counter = 1;
#pragma omp parallel
    {
#pragma omp single
        {
            while (ps.t <= t2) {
                // вычисление положения частиц
                DirectSumm::KDK::next_step(ps);
                DirectSumm::KDK::calculate_conversation_laws(ps);

                // сохранение в файлы (опционально)
                if (counter % 10 == 0) {
                    psbuffer.push_buff_posit(ps);
                    counter = 1;
                    if (psbuffer.size_buff_posit() >= buff_size_posit) {
                        psbuffer.saveToFile_position();
                    }
                }
                if (counter % 5 == 0) {
                    psbuffer.push_buff_conv_laws(ps);
                    if (psbuffer.size_buff_conv_laws() >= buff_size_conv_laws) {
                        psbuffer.saveToFile_conv_laws();
                    }
                }

                // визуализация (опционально)
                //...

                ps.t += ps.dt;
                ++counter;
            }
#pragma omp taskwait
        }
    }
}