cmake_minimum_required(VERSION 4.0)

project(MortalCombat)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

include(CTest)
enable_testing()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

add_subdirectory(Shared)
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(tests)