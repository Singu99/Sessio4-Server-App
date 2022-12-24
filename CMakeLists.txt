cmake_minimum_required(VERSION 3.0.0)
project(WindowsAppTemplate VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(dependencies/glfw-3.3.7)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/imgui)
add_subdirectory(dependencies/glm)

find_package(OpenGL REQUIRED)

set(BUILD_SHARED_LIBS OFF)
add_executable(WindowsAppTemplate main.cpp)

target_include_directories(WindowsAppTemplate PUBLIC dependencies/glfw-3.3.7/include dependencies/glad/include dependencies/imgui dependencies/imgui/backends dependencies/glm/glm dependencies/crow/include)
target_link_directories(WindowsAppTemplate PUBLIC dependencies/crow/lib)
target_link_libraries(WindowsAppTemplate glfw OpenGL::GL glad imgui glm )  

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
