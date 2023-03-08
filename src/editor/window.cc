#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <GLFW/glfw3.h>

#include "window.h"

namespace Konto::Editor
{

bool Window::is_closed() const
{
    return glfwWindowShouldClose(handle_);
}

void Window::update()
{
    glfwPollEvents();
    glfwGetFramebufferSize(handle_, (int*)&width_, (int*)(&height_));
}

void Window::destroy()
{
    if (handle_)
    {
        glfwDestroyWindow(handle_);
        glfwTerminate();

        handle_ = nullptr;
    }
}

Window::~Window()
{
    destroy();
}

Window::Window(const std::string& title, uint32_t width, uint32_t height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    name_ = title;
    width_ = width;
    height_ = height;

    handle_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (handle_ == nullptr)
    {
        std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(handle_);
    glfwSwapInterval(1); // Enable vsync
}

} // namespace Konto::Editor
