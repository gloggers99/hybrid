#pragma once

#include "glad/gl.h"

#include <string>
#include <vector>

#include "Uniform.hpp"

/**
 * Shader is the backbone of all shaders, uniforms and more can be updated from here.
 */
class Shader {
protected:
    GLuint vertexShader, fragmentShader, shaderProgram;

    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    bool compiled;

    /**
     * Construct the shader using a vertex source string and a fragment source string
     *
     * @param vertexShaderSource Vertex Shader Source
     * @param fragmentShaderSource Fragment Shader Source
     */
    Shader(std::string vertexShaderSource, std::string fragmentShaderSource);
public:
    /**
     * Compile the given shader
     *
     * @param shader The shader to compile
     */
    static void compile(Shader &shader);
    static void use(Shader &shader);

};