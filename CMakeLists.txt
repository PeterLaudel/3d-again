cmake_minimum_required(VERSION 3.28.1)
project(3DAgain LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_custom_target(
  files ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/tests/files ${CMAKE_BINARY_DIR}/files)

add_custom_target(
  shaders ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shaders
          ${CMAKE_BINARY_DIR}/shaders)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} src_lib)

add_dependencies(${PROJECT_NAME} files)
add_dependencies(${PROJECT_NAME} shaders)

enable_testing()
add_subdirectory(tests)
