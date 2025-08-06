cmake_minimum_required(VERSION 3.10.0)
project(MAGE_Project VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(MAGE_Project 
src/main.cpp
src/glad.h
src/glad.c
src/shader.h
src/glm/glm.hpp
src/glm/gtc/matrix_transform.hpp
src/glm/gtc/type_ptr.hpp
)

target_link_libraries(MAGE_Project 
glfw
OpenGL::GL
)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
