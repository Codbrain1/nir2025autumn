#выбор версии cmake
cmake_minimum_required(VERSION 4.0.1)

#версия и название проекта
project(galaxymodel VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_CUDA "включить поддержку CUDA" OFF)
option(ENABLE_TESTS "включить тесты" OFF)
option(ENABLE_VISUAL "включить визуализацию" ON)

#поиск библиотеки OPENMP
find_package(OpenMP REQUIRED COMPONENTS CXX)

# проверка на использование CUDA
if(ENABLE_CUDA)
    enable_language(CUDA)
    find_package(CUDAToolkit REQUIRED)
    if(CUDAToolkit_FOUND)
        message(STATUS "поддержка CUDA ключена")
        enable_language(CUDA)
        set(CUDA_ARCHITECTURES "native")
    else()
        message(SEND_ERROR,"CUDA not found, сборка без использования gpu")
        set(ENABLE_CUDA OFF)
    endif()
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

# модуль контейнеры
add_library(containers
    includes/Containers/Buff.h
    includes/Containers/Buffer.h
    includes/Containers/ParticleContainer.h
    src/Containers/ParticleContainer.cpp
)

target_link_libraries(containers PUBLIC OpenMP::OpenMP_CXX)

# модуль вычисления
add_library(numerics 
    includes/numerics/DIRSUMM/KDK.h
    includes/numerics/DIRSUMM/RK4.h
    includes/numerics/SPH/KDK.h
    includes/numerics/SPH/RK4.h
    includes/init/init_condition.h
    src/init/init_condition.cpp
)
target_link_libraries(numerics PUBLIC OpenMP::OpenMP_CXX containers)

if(ENABLE_CUDA AND CUDAToolkit_FOUND)
    add_library(numerics_cuda
        src/numerics/DIRSUMM/KDK.cu
        src/numerics/DIRSUMM/RK4.cu
        src/numerics/SPH/KDK.cu
        src/numerics/SPH/RK4.cu
    )
    target_link_libraries(numerics_cuda PRIVATE containers)
    set_property(TARGET numerics_cuda PROPERTY CUDA_SEPARABLE_COMPILATION ON)
endif()

## Модуль визуализации
if(ENABLE_VISUAL)
# Поиск OpenCV с явным указанием MODULE или CONFIG режима
find_package(OpenCV 4 REQUIRED COMPONENTS core highgui imgproc)

if(OpenCV_FOUND)
    message(STATUS "OpenCV found: ${OpenCV_VERSION}")
    message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
    message(STATUS "OpenCV include dir: ${OpenCV_INCLUDE_DIRS}")

    # Создаем библиотеку визуализации
    add_library(visualisation
        includes/visualisation/Animation.h
        src/visualisation/Animation.cpp
    )
    
    # Настройка include-путей
    target_include_directories(visualisation PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${OpenCV_INCLUDE_DIRS}
    )
    
    # Альтернативный вариант линковки
    target_link_libraries(visualisation PRIVATE ${OpenCV_LIBS})
    
else()
    message(WARNING "OpenCV not found, visualization will be disabled")
    set(ENABLE_VISUAL OFF)
endif()
else()
message(STATUS "Модуль визуализации отключен")
endif()

# главный исполняемый файл
add_executable(galaxymodel src/main.cpp)
target_link_libraries(galaxymodel PRIVATE containers numerics)

if(ENABLE_CUDA AND CUDAToolkit_FOUND)
    target_link_libraries(galaxymodel PRIVATE numerics_cuda)
    target_compile_definitions(galaxymodel PRIVATE USE_CUDA)
endif()

if(ENABLE_VISUAL AND OpenCV_FOUND)
    target_link_libraries(galaxymodel PRIVATE visualisation)
    target_compile_definitions(galaxymodel PRIVATE USE_ANIMATION)
endif()

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS galaxymodel DESTINATION bin)
install(DIRECTORY includes/ DESTINATION include)
 