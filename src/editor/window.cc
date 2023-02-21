#include <cstdio>
#include <cstdlib>
#include <iostream>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "window.h"

namespace Konto::Editor
{

WindowData Window::context_{};

void Window::end()
{
    ImGui::Render();

    glfwGetFramebufferSize(context_.handle, (int*)&context_.width, (int*)(&context_.height));
    glViewport(0, 0, context_.width, context_.width);
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

    glfwSwapBuffers(context_.handle);
}

bool Window::is_closed()
{
    return glfwWindowShouldClose(context_.handle);
}

void Window::begin()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void Window::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(context_.handle);
    glfwTerminate();

    context_.handle = nullptr;
}

void Window::start(const std::string& title, uint32_t width, uint32_t height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    context_.name = title;
    context_.width = width;
    context_.height = height;

    context_.handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (context_.handle == nullptr)
    {
        std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(context_.handle);
    glfwSwapInterval(1); // Enable vsync

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
    ImGui_ImplGlfw_InitForOpenGL(context_.handle, true);
}

} // namespace Konto::Editor
