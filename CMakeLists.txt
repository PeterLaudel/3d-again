cmake_minimum_required(VERSION 3.28.1)
project(3DAgain LANGUAGES CXX)

file(GLOB src "${PROJECT_SOURCE_DIR}/src/**/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(src_lib ${src})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} src_lib)
add_custom_target(
  run
  COMMAND ${PROJECT_NAME}
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})
find_package(GTest REQUIRED)

enable_testing()

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.cpp"
     "${PROJECT_SOURCE_DIR}/tests/**/*.cpp")

MESSAGE(${CMAKE_CXX_COMPILER_ID})
add_executable(${PROJECT_NAME}_test ${tests})
target_include_directories(${PROJECT_NAME}_test PUBLIC ${GTest_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}_test GTest::gtest GTest::gtest_main
                      GTest::gmock src_lib)
add_test(
  NAME ${PROJECT_NAME}_test
  COMMAND ${PROJECT_NAME}_test
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests/files
)
