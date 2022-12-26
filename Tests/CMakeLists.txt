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

add_executable(basic_tests
        ../Grammar/CF_Grammar.cpp
        ../Earley/src/EarleyManager.cpp
        ../Earley/src/earley.cpp
		../Grammar/Parser.cpp
        psp_tests.cpp
		diff_psp_tests.cpp
		2ndFromHwTest.cpp
		Regexes_tests.cpp
		Balanced_tests.cpp
		fromCW_test.cpp
    )

add_executable( test_methods
		../Grammar/CF_Grammar.cpp
        ../Earley/src/EarleyManager.cpp
        ../Earley/src/earley.cpp
		../Grammar/Parser.cpp
		MethodTests/ManagerTester.cpp
		MethodTests/ParseTester.cpp
)


set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

target_link_libraries(basic_tests gtest gtest_main)
target_link_libraries(test_methods gtest gtest_main)
