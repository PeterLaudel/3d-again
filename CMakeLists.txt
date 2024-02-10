cmake_minimum_required(VERSION 3.28.1)
project(3DAgain LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

file(GLOB src "${PROJECT_SOURCE_DIR}/src/**/*.cpp")

add_custom_target(
  files ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/tests/files ${CMAKE_BINARY_DIR}/files)

add_custom_target(
  shaders ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shaders
          ${CMAKE_BINARY_DIR}/shaders)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_library(src_lib ${src})
target_link_libraries(src_lib PUBLIC glfw glad::glad glm::glm)
add_executable(${PROJECT_NAME} main.cpp)

add_dependencies(${PROJECT_NAME} files)
add_dependencies(${PROJECT_NAME} shaders)
target_link_libraries(${PROJECT_NAME} src_lib OpenGL::GL GLUT::GLUT)

target_include_directories(
  ${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS}
                         ${GLFW_INCLUDE_DIRS})

find_package(GTest REQUIRED)
enable_testing()

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.cpp"
     "${PROJECT_SOURCE_DIR}/tests/**/*.cpp")

add_executable(${PROJECT_NAME}_test ${tests})
target_include_directories(${PROJECT_NAME}_test PUBLIC ${GTest_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}_test GTest::gtest GTest::gtest_main
                      GTest::gmock src_lib)
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
