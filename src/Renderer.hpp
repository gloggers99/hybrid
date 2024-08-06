#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>
#include <exception>
#include <functional>

#include <Color.hpp>

namespace Hybrid {
    /**
     * RendererInitException is thrown when Renderer fails to initialize
     */
    class RendererInitException : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Failed to initialize Hybrid::Renderer";
        }
    };

    /**
     * Rendering is handled by the Renderer class.
     */
    class Renderer {
    private:
        static void error_callback(int error, const char *description);

        GLFWwindow *window;

        double deltaTime;

    public:
        /**
         * Make the renderer loop a drawing function
         */
        void loop(const std::function<int(double)>& function);

        void clear(GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        void clearColor(Color color);

        GLFWwindow *getWindow();

        Renderer(int width,
                 int height,
                 const std::string &title,
                 GLFWmonitor *monitor = nullptr,
                 GLFWwindow *share = nullptr);
        ~Renderer();
    };

} // Hybrid
