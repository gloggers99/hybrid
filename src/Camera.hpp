#pragma once

#include "Uniform.hpp"
#include "IMatrix.hpp"

#include <glm/glm.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Hybrid {
    class Renderer;

    enum class Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class Camera : public IMatrix {
    private:
        Renderer &renderer;

        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;

        float fov;

        bool firstMouse;
        float yaw;
        float pitch;

        float lastX;
        float lastY;

        float mouseSensitivity;

        glm::mat4 createViewMatrix();
        glm::mat4 createProjectionMatrix();

        /**
         * Combination of both Camera::createViewMatrix() and Camera::createProjectionMatrix()
         */
        glm::mat4 createCameraMatrix();

    public:
        void move(Direction direction, float speed);

        /**
         * Call to handle the mouse and update the underlying matrix
         */
        glm::mat4 update() override;

        explicit Camera(Renderer &renderer);
        ~Camera();
    };

}
