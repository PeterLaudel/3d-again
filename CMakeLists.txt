cmake_minimum_required(VERSION 3.16)
project(
    3DAgain
    LANGUAGES CXX
)


file(GLOB src "src/**/*.cpp") 
add_library(src_lib ${src})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(3DAgain src_lib)

find_package(GTest REQUIRED)

enable_testing()

file(GLOB tests "tests/*.cpp")
add_executable(${PROJECT_NAME}_test ${tests})
target_include_directories(${PROJECT_NAME}_test PUBLIC ${GTest_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}_test GTest::gtest GTest::gtest_main GTest::gmock ${src_lib})

add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)