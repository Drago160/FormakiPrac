cmake_minimum_required(VERSION 3.23)
project(FormalkiPrac)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" ${CMAKE_SOURCE_DIR}/cmake)


add_executable(run
        main.cpp
        Grammar/CF_Grammar.cpp
        Earley/src/EarleyManager.cpp
        Earley/src/earley.cpp
        Earley/include/EarleyManager.h
        Grammar/Parser.cpp
        )

include_directories(
        Grammar
        Earley/include
        Tests/FriendTester
        )

add_subdirectory(Tests)
