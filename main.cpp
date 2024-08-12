#include "src/Hybrid.hpp"

#include <glad/gl.h>

#include <shaders/shader.hcs>

int main() {
    Hybrid::Renderer renderer(640, 480, "Hybrid");
    Hybrid::Camera camera(renderer);

    Shader::compile(shader);
    Shader::use(shader);

    Hybrid::Model model("test.obj");

    renderer.loop([&](double deltaTime) {
        renderer.clear();
        renderer.clearColor(Hybrid::Color(0.0f, 1.0f));

        camera.correlate(shader.camera);

        //stack.draw();
        model.draw();

        if (renderer.getKey(GLFW_KEY_W))
            camera.move(Hybrid::Direction::FORWARD, deltaTime * 1.0f);
        if (renderer.getKey(GLFW_KEY_S))
            camera.move(Hybrid::Direction::BACKWARD, deltaTime * 1.0f);
        if (renderer.getKey(GLFW_KEY_A))
            camera.move(Hybrid::Direction::LEFT, deltaTime * 1.0f);
        if (renderer.getKey(GLFW_KEY_D))
            camera.move(Hybrid::Direction::RIGHT, deltaTime * 1.0f);

        return 0;
    });

    return 0;
}
