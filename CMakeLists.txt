#выбор версии cmake
cmake_minimum_required(VERSION 4.0.1)

#версия и название проекта
project(galaxymodel VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)

add_executable(galaxymodel)
target_sources( galaxymodel PRIVATE
    
    src/main.cpp
)
target_include_directories(galaxymodel PRIVATE
    includes/Animation.h
    includes/Buff.h
    includes/BUffer.h
    includes/ParticleContainer.h
    includes/DIRSUMM/KDK.h
    includes/DIRSUMM/RK4.h
    includes/SPH/KDK.h
    includes/SPH/RK4.h
    includes/init_condition.h
)