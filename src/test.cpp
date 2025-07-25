#include <fstream>
#include <vector>
#include <filesystem>
#include <cmath>
#include<iostream>
// Глобальные переменные (как в вашем примере)
int N = 10;
std::vector<double> x(N,0), y(N,0), z(N,0);
std::vector<double> vx(N,1), vy(N,1), vz(N,1);
double E = 0;
double Px = 0, Py = 0, Pz = 0;
double Lx = 0, Ly = 0, Lz = 0;
double t = 0, dt = 0.1;

// Ваша функция записи (с небольшими улучшениями)
void SaveToBinaryFile_all(std::ofstream& positions, std::ofstream& conv_laws) {
    // 1. Записываем текущее время
    positions.write(reinterpret_cast<const char*>(&t), sizeof(double));
    
    // 2. Записываем данные всех частиц
    for(int i = 0; i < N; i++) {
        double posit[6] = {x[i], y[i], z[i], vx[i], vy[i], vz[i]};
        positions.write(reinterpret_cast<const char*>(posit), 6 * sizeof(double));
    }
    
    // 3. Записываем законы сохранения
    double convlaws[4] = {t, E, Px*Px + Py*Py + Pz*Pz, Lx*Lx + Ly*Ly + Lz*Lz};
    conv_laws.write(reinterpret_cast<const char*>(&convlaws), 4 * sizeof(double));
}

int main() {
    // Создаем директорию для результатов
    try {
        if(!std::filesystem::exists("results")) {
            std::filesystem::create_directory("results");
        } else {
            int i = 1;
            while(std::filesystem::exists("results" + std::to_string(i))) {
                i++;
            }
            std::filesystem::rename("results", "results" + std::to_string(i));
            std::filesystem::create_directory("results");
        }
    } catch(const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return 1;
    }

    // Открываем файлы для записи
    std::ofstream pos_file("results/positions.bin", std::ios::binary);
    std::ofstream laws_file("results/conservation_laws.bin", std::ios::binary);
    
    if(!pos_file || !laws_file) {
        std::cerr << "Error opening output files\n";
        return 1;
    }

    // Моделируем 10 шагов по времени
    for(int step = 0; step < 10; step++) {
        // Вычисляем физические величины
        for(int i=0;i<N;i++)
        {
            x[i]+=1;
            y[i]+=2;
            z[i]+=3;
            vx[i]+=i*vx[i];
            vy[i]+=2*i*vy[i];
            vz[i]+=3*i*vz[i];
        }
        E=step*step;
        Px+=Px*step+1;
        Py+=Py*step+1;
        Pz+=Pz*step+1;

        Lx+=Lx*step+1;
        Ly+=Ly*step+1;
        Lz+=Lz*step+1;
        // Записываем данные в файлы
        SaveToBinaryFile_all(pos_file, laws_file);
        
        t++;
    }

    // Закрываем файлы
    pos_file.close();
    laws_file.close();

    std::cout << "Data successfully written to binary files.\n";
    return 0;
}