#include "Renderer.hpp"
#include "Color.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

namespace Hybrid {
    void Renderer::error_callback(int error, const char *description) {
        fprintf(stderr, "GLFW error %i: %s\n", error, description);
    }

    void Renderer::loop(const std::function<int(double)>& function) {
        double lastTime = glfwGetTime();

        for (;;) {
            double currentTime = glfwGetTime();
            this->deltaTime = currentTime - lastTime;

            if (function(this->deltaTime) != 0)
                break;

            glfwSwapBuffers(this->window);
            glfwPollEvents();

            if (glfwWindowShouldClose(this->window))
                break;
        }
    }

    void Renderer::clear(GLbitfield mask) {
        glClear(mask);
    }

    void Renderer::clearColor(Color color) {
        glClearColor(HYBRID_GL_COLOR_CONVERT(color));
    }

    GLFWwindow *Renderer::getWindow() {
        return this->window;
    }

    Renderer::Renderer(int width,
                       int height,
                       const std::string &title,
                       GLFWmonitor *monitor,
                       GLFWwindow *share) :
                       window(nullptr),
                       deltaTime(0.0) {
        if (glfwInit() != GLFW_TRUE)
            throw RendererInitException();

        glfwSetErrorCallback(Renderer::error_callback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        this->window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
        if (!this->window)
            throw RendererInitException();

        glfwMakeContextCurrent(this->window);
        gladLoadGL(glfwGetProcAddress);

        glViewport(0, 0, width, height);
    }

    Renderer::~Renderer() {
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }

} // Hybrid