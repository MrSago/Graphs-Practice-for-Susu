cmake_minimum_required(VERSION 3.10)
project(Graphs-Practice)

set(TARGET Graphs-Practice)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wshadow -Wformat=2 -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Debug/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/Release/)

set(MAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)
file(GLOB_RECURSE SRC_GRAPHS ${CMAKE_CURRENT_SOURCE_DIR}/graphs/*.cc)

add_executable(${TARGET} ${MAIN_FILE} ${SRC_GRAPHS})

target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/graphs
    ${CMAKE_CURRENT_SOURCE_DIR}/graphs/algo)