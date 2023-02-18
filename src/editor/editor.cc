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

#include <kontomire.h>

#include "konto.h"

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
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    std::shared_ptr<Knt::FrameBuffer> framebuffer{};

    Knt::FramebufferSpecification framebuffer_specs{};

    framebuffer_specs.attachments = {Knt::FramebufferTextureFormat::DEPTH, Knt::FramebufferTextureFormat::RGBA8,
                                     Knt::FramebufferTextureFormat::RED_INTEGER};
    framebuffer_specs.width = 800;
    framebuffer_specs.height = 600;
    framebuffer = Knt::FrameBuffer::create(framebuffer_specs);

    Konto::Scene scene{};

    auto camera = scene.create_entity("Camera Entity");
    camera.add<Konto::CameraComponent>();

    auto& component = camera.get<Konto::CameraComponent>();
    component.primary = true;
    component.camera.set_viewport_size(800, 600);

    auto& transform = camera.get<Konto::TransformComponent>();

    glm::vec3 camera_scale{transform.scale};
    glm::vec3 camera_rotation{transform.rotation};
    glm::vec3 camera_translation{transform.translation};

    scene.resize_viewport(800, 600);

    auto library = std::make_shared<Knt::ShaderLibrary>();
    library->add("quad", Knt::Shader::create("assets/shaders/2D/quad.glsl"));
    library->add("line", Knt::Shader::create("assets/shaders/2D/line.glsl"));
    library->add("circle", Knt::Shader::create("assets/shaders/2D/circle.glsl"));

    Knt::Renderer::set_line_width(1.0f);
    Knt::Renderer2D::init(library);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        framebuffer->bind();

        Knt::Renderer::set_clear_color(glm::vec4(0.5f, 0.0f, 1.0f, 1.0f));
        Knt::Renderer::clear();

        transform.scale = camera_scale;
        transform.rotation = camera_rotation;
        transform.translation = camera_translation;

        scene.update(1.0f);

        framebuffer->clear_attachment(1, -1);
        framebuffer->unbind();

        uint32_t texture_id = framebuffer->color_attachment();

        ImGui::Begin("Playground Viewport");
        {
            ImGui::BeginChild("Viewport");
            ImGui::Image(reinterpret_cast<void*>(texture_id), ImGui::GetWindowSize(), ImVec2{0, 1}, ImVec2{1, 0});
            ImGui::EndChild();
        }
        ImGui::End();

        ImGui::Begin("Camera Settings");
        {
            ImGui::SliderFloat3("Scale", reinterpret_cast<float*>(&camera_scale), -2.0f, 2.0f, "%.3f");
            ImGui::SliderFloat3("Rotation", reinterpret_cast<float*>(&camera_rotation), -2.0f, 2.0f, "%.3f");
            ImGui::SliderFloat3("Translation", reinterpret_cast<float*>(&camera_translation), -2.0f, 2.0f, "%.3f");
        }
        ImGui::End();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
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
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}