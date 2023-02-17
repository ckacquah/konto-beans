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

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
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
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    float zoom{};
    double delta{};
    float yaw{0.0f};
    float pitch{0.0f};

    glm::vec4 quad_color{glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)};
    glm::vec4 line_color{glm::vec4(0.2f, 1.0f, 0.0f, 1.0f)};
    glm::vec4 circle_color{glm::vec4(1.0f, 0.0f, 0.5f, 1.0f)};
    glm::vec4 background_color{glm::vec4(0.15f, 0.15f, 0.15f, 1.0f)};

    glm::vec2 square_size{glm::vec2(1.0f, 1.0f)};
    glm::vec2 square_size_prev{glm::vec2(1.0f, 1.0f)};

    glm::vec3 square_position{glm::vec3(0.0f, 0.0f, -1.0f)};
    glm::vec3 square_position_prev{glm::vec3(0.0f, 0.0f, 1.0f)};

    glm::vec2 circle_size{glm::vec2(0.725f, 0.75f)};
    glm::vec3 circle_position{glm::vec3(-1.0f, 0.0f, 1.0f)};

    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        ImGui::Begin("Playground Viewport");
        {
            ImGui::ColorEdit3("Quad Color", const_cast<float*>(glm::value_ptr(quad_color)));
            ImGui::ColorEdit3("Line Color", const_cast<float*>(glm::value_ptr(line_color)));
            ImGui::ColorEdit3("Circle Color", const_cast<float*>(glm::value_ptr(circle_color)));
            ImGui::ColorEdit3("Background Color", const_cast<float*>(glm::value_ptr(background_color)));

            ImGui::Separator();

            ImGui::SliderFloat2("Square size", reinterpret_cast<float*>(&square_size), 0.0f, 1.0f, "%.3f");
            ImGui::SliderFloat3("Square position", reinterpret_cast<float*>(&square_position), -2.0f, 2.0f, "%.3f");

            ImGui::Separator();

            ImGui::SliderFloat2("Circle size", reinterpret_cast<float*>(&circle_size), 0.0f, 1.0f, "%.3f");
            ImGui::SliderFloat3("Circle position", reinterpret_cast<float*>(&circle_position), -2.0f, 2.0f, "%.3f");

            ImGui::Separator();

            ImGui::SliderFloat("Yaw", &yaw, -180.0f, 180.0f, "%.3f");
            ImGui::SliderFloat("Pitch", &pitch, -90.0f, 90.0f, "%.3f");

            ImGui::Separator();

            ImGui::SliderFloat("Zoom", &zoom, 0.0f, 45.0f, "%.3f");
            ImGui::Separator();
        }
        ImGui::End();

        ImGui::Render();

        glViewport(0, 0, 800, 600);
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

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}