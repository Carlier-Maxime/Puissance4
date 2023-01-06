cmake_minimum_required(VERSION 3.23)
project(Puissance4 C)

set(CMAKE_C_STANDARD 99)
find_library(CUNIT_LIB cunit)
add_executable(Puissance4 src/main.c src/grid.h src/grid.c src/view.h src/viewTerminal.c src/viewTerminal.h src/error.h src/error.c src/player.h src/playerHuman.h src/playerHuman.c src/player.c src/view.c src/playerAIEasy.h src/playerAIEasy.c src/playerAIBase.h src/playerAIBase.c src/playerAINormal.h src/playerAINormal.c src/playerAIHard.h src/playerAIHard.c)
add_executable(Test test/main.c src/grid.h src/grid.c test/grid.h test/grid.c test/viewTerminal.h test/viewTerminal.c src/viewTerminal.c src/viewTerminal.h src/error.h src/error.c test/player.h test/player.c test/playerHuman.h test/playerHuman.c src/player.h src/playerHuman.h src/playerHuman.c src/player.c src/view.c src/playerAIEasy.h src/playerAIEasy.c src/playerAIBase.h src/playerAIBase.c test/playerAIEasy.h test/playerAIEasy.c src/playerAINormal.h src/playerAINormal.c src/playerAIHard.h src/playerAIHard.c)
target_link_libraries(Test cunit)