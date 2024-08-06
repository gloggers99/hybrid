#pragma once

#include "Uniform.hpp"

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

    class Camera {
    private:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;

        float fov;

        bool firstMouse;
        float yaw;
        float pitch;

        float lastX;
        float lastY;

        glm::mat4 createViewMatrix();
        glm::mat4 createProjectionMatrix();

        /**
         * Combination of both Camera::createViewMatrix() and Camera::createProjectionMatrix()
         */
        glm::mat4 createCameraMatrix();

    public:
        void move(Direction direction, float speed);

        explicit Camera(Renderer &renderer);
        ~Camera();
    };

}
