# galaxymodel
__galaxymodel__ - это библиотека состоящая из нескольких взаимосвязанных модулей и исполнимого файла, которая позволяет моделировать взаимодействие N-частиц прямым методом суммирования и методом SPH. Она включет методы интегрирования RungeKutta4 и KDK(Kick-Drift-Kick). исполнимый файл может быть заменен на собственный при необходимости. 

__модули:__
- *containers* - содержит шаблоные классы контейнеры хранящие данные и классы буферов позволяющие накапливать и сохранять данные в файлы;
- *numerics* - содержит шаблонные функции для выполнения вычислений;
- *visualisation* - содержит функции визуализации вычисленных данных;

# Использование
пример исполнимого файла для библиотеки без использования буферизации для сохранения:
``` cpp
#include <filesystem>
#include <fstream>
#include "Containers/Buffer.h"
#include "Containers/ParticleContainer.h"
#include "init/init_condition.h"
#include "numerics/DIRSUMM/KDK.h"
int main()
{
    // создание системы частиц
    int N = 1000;                  // число частиц
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
        std::ofstream eror("error.txt");
        eror << "Filesystem error: " << e.what() << '\n';
        eror << "Path1: " << e.path1() << '\n';
        if (!e.path2().empty()) {
            eror << "Path2: " << e.path2() << '\n';
        }
    }

    std::ofstream file_pos("results/positions.txt");
    std::ofstream file_conv("results/conversation_laws.txt");
    ps.saveToFile_all(file_pos,file_conv);
    int counter = 1;

    while (ps.t <= t2) {
        // вычисление положения частиц
        DirectSumm::KDK::next_step(ps);
        DirectSumm::KDK::calculate_conversation_laws(ps);

        // сохранение в файлы (опционально)
        if (counter % 10 == 0) {
            ps.SaveToFile_positions(file_pos);
        }
        if (counter % 5 == 0) {
            ps.SaveToFile_conv_laws(file_conv);
        }
        ps.t += ps.dt;
        ++counter;
    }
}
```
после выполнения этого кода результаты моделирования будут сохранены в файлы и могут быть визуализированны например с помощью matplot или gnuplot или любой другой графической библиотеки.