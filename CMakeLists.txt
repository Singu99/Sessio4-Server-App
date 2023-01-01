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
add_executable(WindowsAppTemplate src/main.cpp src/Controller.cpp src/Ui/UserInterface.cpp src/Server/WebSocketServer.cpp src/Ui/AppLog.cpp)

target_include_directories(WindowsAppTemplate PUBLIC dependencies/glfw-3.3.7/include dependencies/glad/include dependencies/imgui dependencies/imgui/backends dependencies/glm/glm dependencies/crow/include src)
target_link_directories(WindowsAppTemplate PUBLIC dependencies/crow/lib)
target_link_libraries(WindowsAppTemplate glfw OpenGL::GL glad imgui glm )  

# Add a custom command to copy the file next to the executable
add_custom_command(TARGET WindowsAppTemplate POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/window_layout/imgui.ini
                   $<TARGET_FILE_DIR:WindowsAppTemplate>)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
