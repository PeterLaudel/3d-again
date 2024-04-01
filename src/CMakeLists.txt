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


add_custom_command(
     TARGET src_lib POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
$<TARGET_PROPERTY:src_lib,SOURCE_DIR>/shaders/fragment.shader ${CMAKE_BINARY_DIR}/shaders/fragment.shader
)

add_custom_command(
     TARGET src_lib POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
$<TARGET_PROPERTY:src_lib,SOURCE_DIR>/shaders/vertex.shader ${CMAKE_BINARY_DIR}/shaders/vertex.shader
)