#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "application.h"
#include "konto.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace Konto::Editor
{

std::shared_ptr<EditorContext> Application::context_{};

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    context_->dispatcher.post(
        MouseButtonEvent(static_cast<Input::Mouse::Button>(button), static_cast<Input::Action>(action)));
}

void Application::keyboard_button_callback(GLFWwindow* window, int button, int scancode, int action, int mods)
{
    context_->dispatcher.post(
        KeyboardButtonEvent(static_cast<Input::Keyboard::Button>(button), static_cast<Input::Action>(action)));
}

void Application::cursor_position_callback(GLFWwindow* window, double x, double y)
{
    context_->dispatcher.post(MouseCursorEvent(x, y));
}

void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    context_->dispatcher.post(ScrollInputEvent(xoffset, yoffset));
}

Application::~Application()
{
    destroy();
}

void Application::destroy()
{
    if (window_)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        window_->destroy();
        window_ = nullptr;
    }
}

bool Application::closed()
{
    return window_->is_closed();
}

void Application::start(const std::string& name, uint32_t width, uint32_t height)
{
    window_ = std::make_unique<Window>(name, width, height);
    context_ = std::make_shared<EditorContext>(width, height);

    glfwSetCursorPosCallback(window_->handle(), cursor_position_callback);
    glfwSetMouseButtonCallback(window_->handle(), mouse_button_callback);
    glfwSetKeyCallback(window_->handle(), keyboard_button_callback);
    glfwSetScrollCallback(window_->handle(), scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::runtime_error("Failed to initialize GLAD");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.IniFilename = "editor.ini";
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    ImGui_ImplOpenGL3_Init("#version 420");
    ImGui_ImplGlfw_InitForOpenGL(window_->handle(), true);
}

void Application::begin_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void Application::end_frame()
{
    ImGui::Render();

    window_->update();

    glViewport(0, 0, window_->height(), window_->width());
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window_->handle());
}

} // namespace Konto::Editor