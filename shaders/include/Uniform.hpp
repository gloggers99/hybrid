#pragma once

#include <string>
#include <utility>
#include <glm/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

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
    void operator=(T uniform) {
        GLint location = glGetUniformLocation(*this->parentProgram, this->name.c_str());
        if constexpr (std::is_same_v<T, glm::vec3>)
            glUniform3fv(location, uniform);
        if constexpr (std::is_same_v<T, glm::vec2>)
            glUniform2fv(location, uniform);
        else if constexpr (std::is_arithmetic_v<T>)
            glUniform1f(location, uniform);
        else
            throw UniformInvalidTypeException();
    }

    Uniform(std::string name, GLuint *parentProgram) : name(std::move(name)), parentProgram(parentProgram) {}
};
