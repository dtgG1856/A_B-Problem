cmake_minimum_required(VERSION 3.10)
project(A_B_Problem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server
    src/main.cpp
    src/utils.cpp
    src/routes.cpp
)

target_include_directories(server PRIVATE
    include
    lib
)

find_package(Threads REQUIRED)
target_link_libraries(server Threads::Threads)
