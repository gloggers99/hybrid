#pragma once

#include <string>
#include <utility>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

class UniformInvalidTypeException : public std::exception {
    [[nodiscard]] const char *what() const noexcept override {
        return "Uniform has a non supported or invalid type.";
    }
};

template<typename T>
class Uniform {
private:
    std::string name;
    GLuint *parentProgram;

public:
    void operator=(const T &uniform) const {
        GLint location = glGetUniformLocation(*this->parentProgram, this->name.c_str());
        if (location == -1) {
            throw std::runtime_error("Uniform location not found: " + this->name);
        }

        if constexpr (std::is_same_v<T, glm::mat4>) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
        } else if constexpr (std::is_same_v<T, glm::vec3>) {
            glUniform3fv(location, glm::value_ptr(uniform));
        } else if constexpr (std::is_same_v<T, glm::vec2>) {
            glUniform2fv(location, glm::value_ptr(uniform));
        } else if constexpr (std::is_arithmetic_v<T>) {
            glUniform1f(location, static_cast<GLfloat>(uniform));
        } else {
            throw UniformInvalidTypeException();
        }
    }

    Uniform(std::string name, GLuint *parentProgram) : name(std::move(name)), parentProgram(parentProgram) {}
};
