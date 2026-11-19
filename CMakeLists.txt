cmake_minimum_required(VERSION 3.10)
project(A_B_Problem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server
    src/main.cpp
    src/utils.cpp
    src/routes.cpp
)

if(WIN32)
    target_compile_definitions(server PRIVATE _WIN32_WINNT=0x0A00)
    target_link_libraries(server PRIVATE ws2_32)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(server PRIVATE -static-libgcc -static-libstdc++)
endif()

target_include_directories(server PRIVATE
    include
    lib
)

find_package(Threads REQUIRED)
target_link_libraries(server PRIVATE Threads::Threads)
