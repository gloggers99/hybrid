#include "src/Hybrid.hpp"

#include <glad/gl.h>

#include <shaders/shader.hcs>

int main() {
    Hybrid::Renderer renderer(640, 480, "Hybrid");
    Hybrid::Camera camera(renderer);

    Shader::compile(shader);
    Shader::use(shader);

    Hybrid::VertexStack stack = Hybrid::VertexStack<glm::vec3>();
    stack.update({
                         {{0.5f, -0.5f, 0.0f}},
                         {{-0.5, -0.5, 0.0f}},
                         {{0.0, 0.5, 0.0f}}
                 });

    Hybrid::Model model("test.obj");

    renderer.loop([&](double deltaTime) {
        renderer.clear();
        renderer.clearColor(Hybrid::Color(0.0f, 1.0f));

        //stack.draw();
        model.draw();

        return 0;
    });

    return 0;
}
