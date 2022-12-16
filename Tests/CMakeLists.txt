cmake_minimum_required(VERSION 3.6)
project(gtest)

enable_testing()

include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)




add_subdirectory(
        lib/googletest
)

add_executable(BasicTests
        ../Grammar/CF_Grammar.cpp
        ../Earley/src/EarleyManager.cpp
        ../Earley/src/earley.cpp
        psp_tests.cpp
        diff_psp_tests.cpp
        2ndFromHwTest.cpp
        Regexes_tests.cpp
        Balanced_tests.cpp
        fromCW_test.cpp
            )



set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

target_link_libraries(BasicTests gtest gtest_main)

