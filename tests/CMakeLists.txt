find_package(GTest REQUIRED)

file(GLOB tests ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp)

add_executable(${PROJECT_NAME}_test ${tests})
target_include_directories(${PROJECT_NAME}_test PUBLIC ${GTest_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}_test GTest::gtest GTest::gtest_main
                      GTest::gmock src_lib)
add_test(
  NAME ${PROJECT_NAME}_test
  COMMAND ${PROJECT_NAME}_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
