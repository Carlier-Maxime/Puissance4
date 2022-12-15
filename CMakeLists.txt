cmake_minimum_required(VERSION 3.23)
project(Puissance4 C)

set(CMAKE_C_STANDARD 99)
find_library(CUNIT_LIB cunit)
add_executable(Puissance4 src/main.c src/grid.h src/grid.c src/view.h src/viewTerminal.c src/viewTerminal.h)
add_executable(Test test/main.c src/grid.h src/grid.c)
target_link_libraries(Test cunit)