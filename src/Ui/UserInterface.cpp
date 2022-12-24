#include "UserInterface.h"

void TextCentered(const std::string& text) {
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth   = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text(text.c_str());
}


UserInterface::UserInterface()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(1280, 860, "Example", nullptr, nullptr);
    if (!m_window)
        throw std::runtime_error("Error creating glfw window");
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    if (!gladLoadGL())
        throw std::runtime_error("Error initializing glad");

    /**
     * Initialize ImGui
     */
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 450 core");

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEBUG_OUTPUT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    io.Fonts->AddFontFromFileTTF("../../dependencies/imgui/imgui/misc/fonts/Roboto-Medium.ttf", 16.0f);
}

UserInterface::~UserInterface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();   
}

void UserInterface::RenderUi()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ShowAppDockSpace();
        
        ShowLogConsole();

        LayerWindow("Core Layer");
        LayerWindow("Layer one");
        LayerWindow("Layer two");

        NodeWindow("A1");
        NodeWindow("A2");
        NodeWindow("A3");
        NodeWindow("B1");
        NodeWindow("B2");
        NodeWindow("C1");
        NodeWindow("C2");

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(m_window);
        glClear(GL_COLOR_BUFFER_BIT);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void UserInterface::UpdateNodeVersion(const std::string& name, int version)
{
    std::lock_guard<std::mutex> lck(m_data);
    m_nodes[name] = version;
}

void UserInterface::LayerWindow(const std::string &name)
{
    ImGui::Begin(name.c_str());
    ImGui::Text("Transmitting to next layer...");
    ImGui::End();
}

void UserInterface::NodeWindow(const std::string &name)
{
    ImGui::Begin(name.c_str());
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Text("Name: %s", name.c_str());
    ImGui::Separator();
    ImGui::Text("Version: %d", m_nodes[name]);
    ImGui::Separator();
    ImGui::End();
}

void UserInterface::ShowAppDockSpace()
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("Web Socket server app", nullptr, window_flags);

    ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    ImGui::End();
}

void UserInterface::ShowLogConsole()
{
    static const char* windowName = "Log console";

    // For the demo: add a debug button _BEFORE_ the normal log window contents
    // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
    // Most of the contents of the window will be added by the log.Draw() call.
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin(windowName, nullptr);
    TextCentered("LOG CONSOLE");
    ImGui::End();

    // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
    m_log.Draw(windowName, nullptr);
}


void UserInterface::UiLog(const char* fmt, ...) IM_FMTARGS(2)
{
    va_list args;
    va_start(args, fmt);
    m_log.AddLog(fmt, args);
    va_end(args);
}