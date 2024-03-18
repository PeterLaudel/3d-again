find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)
find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h)

add_library(src_lib ${src})
target_link_libraries(src_lib PUBLIC glm::glm glad::glad glfw)

target_include_directories(
  src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${GLAD_INCLUDE_DIRS}
                 ${GLFW_INCLUDE_DIRS})
