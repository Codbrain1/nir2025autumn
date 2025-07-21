#выбор версии cmake
cmake_minimum_required(VERSION 4.0.1)

#версия и название проекта
project(galaxymodel VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)

add_executable(galaxymodel)
target_sources( galaxymodel PRIVATE
    src/DIRSUMM/KDK.cpp
    src/DIRSUMM/RK4.cpp
    src/SPH/KDK.cpp
    src/SPH/RK4.cpp
    src/init_condition.cpp
    src/main.cpp
)
target_include_directories(galaxymodel PRIVATE
    include/Animation.h
    include/Buff.h
    include/BUffer.h
    include/ParticleContainer.h
)