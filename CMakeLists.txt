project("othello_board")

cmake_minimum_required(VERSION 2.6)

if (CMAKE_VERSION VERSION_LESS "3.1")
  add_definitions(-std=c++11)
else()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(game game.c board.c points.c tree.c)
target_link_libraries(game ncurses)

#add_executable(board_tests board_tests.cc board.c points.c)
#target_link_libraries(board_tests ${GTEST_LIBRARIES} -lncurses)

add_executable(points_tests points_tests.cc points.c)
target_link_libraries(points_tests ${GTEST_LIBRARIES} -lncurses)

add_executable(tree_tests tree_tests.cc tree.c board.c points.c)
target_link_libraries(tree_tests ${GTEST_LIBRARIES} -lncurses)

add_executable(tree_visual tree_visual.c board.c points.c tree.c)
target_link_libraries(tree_visual ncurses)
