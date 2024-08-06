#include <stdexcept>

#include "Camera.hpp"
#include "Renderer.hpp"

#include <glm/ext.hpp>

namespace Hybrid {
    glm::mat4 Camera::createViewMatrix() {
        return glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
    }

    glm::mat4 Camera::createProjectionMatrix() {
        return glm::perspective(glm::radians(this->fov), )
    }

    glm::mat4 Camera::createCameraMatrix() {

    }

    void Camera::move(Direction direction, float speed) {
        switch (direction) {
            case Direction::FORWARD:
                this->cameraPos += cameraFront * speed;
                break;
            case Direction::BACKWARD:
                this->cameraPos -= cameraFront * speed;
                break;
            case Direction::LEFT:
                this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * speed;
                break;
            case Direction::RIGHT:
                this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * speed;
                break;
            default:
                throw std::runtime_error("Invalid direction provided.");
        }
    }

    Camera::Camera(Renderer &renderer) :
    cameraPos(glm::vec3(0.0f, 0.0f, 0.0f)),
    cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),

    fov(90.0f),

    firstMouse(true),
    yaw(-90.0f),
    pitch(0.0f) {
        int width, height;
        glfwGetWindowSize(renderer.getWindow(), &width, &height);

        this->lastX = static_cast<float>(width) / 2.0f;
        this->lastY = static_cast<float>(height) / 2.0f;
    }

    Camera::~Camera() = default;
}
