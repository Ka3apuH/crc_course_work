cmake_minimum_required(VERSION 3.16-3.22)
project(crc)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(benchmark)
add_subdirectory(tests)

#[[add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../crc_main
)]]
