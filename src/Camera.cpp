#include <stdexcept>

#include "Camera.hpp"
#include "Renderer.hpp"

#include <glm/ext.hpp>

namespace Hybrid {
    glm::mat4 Camera::createViewMatrix() {
        return glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
    }

    glm::mat4 Camera::createProjectionMatrix() {
        int width, height;
        glfwGetWindowSize(renderer.getWindow(), &width, &height);

        return glm::perspective(glm::radians(this->fov), static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
    }

    glm::mat4 Camera::createCameraMatrix() {
        return this->createProjectionMatrix() * this->createViewMatrix();
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

    glm::mat4 Camera::update(){
        double xpos;
        double ypos;
        glfwGetCursorPos(this->renderer.getWindow(), &xpos, &ypos);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
        front.y = std::sin(glm::radians(pitch));
        front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);

        return this->createCameraMatrix();
    }

    Camera::Camera(Renderer &renderer) :
    renderer(renderer),

    cameraPos(glm::vec3(0.0f, 0.0f, 0.0f)),
    cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),

    fov(90.0f),

    firstMouse(true),
    yaw(-90.0f),
    pitch(0.0f),

    mouseSensitivity(0.5f) {
        int width, height;
        glfwGetWindowSize(renderer.getWindow(), &width, &height);

        this->lastX = static_cast<float>(width) / 2.0f;
        this->lastY = static_cast<float>(height) / 2.0f;
    }

    Camera::~Camera() = default;
}
