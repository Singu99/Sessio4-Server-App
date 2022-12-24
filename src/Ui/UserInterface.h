#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <chrono>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <mutex>
#include "AppLog.h"

class UserInterface
{
public:
    UserInterface();
    ~UserInterface();

    void RenderUi();            // Render the UI in loop while main window is open

    void UiLog(const char* fmt, ...) IM_FMTARGS(2);
    void UpdateNodeVersion(const std::string& name, int version);

private:
    AppLog m_log;
    GLFWwindow* m_window;
    std::unordered_map<std::string, int> m_nodes;
    
    std::mutex m_data;

private:
    void LayerWindow(const std::string& name);
    void NodeWindow(const std::string& name);
    void ShowAppDockSpace();
    void ShowLogConsole();
};
