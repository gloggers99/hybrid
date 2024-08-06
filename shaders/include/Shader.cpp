#include "Shader.hpp"

#include <stdexcept>
#include <format>
#include <utility>

Shader::Shader(std::string vertexShaderSource,
               std::string fragmentShaderSource) :
               vertexShaderSource(std::move(vertexShaderSource)),
               fragmentShaderSource(std::move(fragmentShaderSource)),
               compiled(false) {}

void Shader::compile(Shader &shader) {
    const char *vertexSource = shader.vertexShaderSource.c_str();
    shader.vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader.vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(shader.vertexShader);

    const char *fragmentSource = shader.fragmentShaderSource.c_str();
    shader.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader.fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(shader.fragmentShader);

    shader.shaderProgram = glCreateProgram();
    glAttachShader(shader.shaderProgram, shader.vertexShader);
    glAttachShader(shader.shaderProgram, shader.fragmentShader);
    glLinkProgram(shader.shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shader.shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader.shaderProgram, 512, nullptr, infoLog);
        throw std::runtime_error(std::format("\n{}", infoLog));
    }

    shader.compiled = true;
}

void Shader::use(Shader &shader) {
    if (shader.compiled)
        glUseProgram(shader.shaderProgram);
}