cmake_minimum_required(VERSION 3.28)
project(hybrid)

set(CMAKE_CXX_STANDARD 20)

add_custom_target(
        EmbedShaders ALL
        COMMAND ${CMAKE_COMMAND} -E env python3 ${CMAKE_SOURCE_DIR}/scripts/shader_embedder.py
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Embedding shaders"
)

add_library(hybrid STATIC
        src/Hybrid.hpp
        src/Renderer.cpp
        src/Renderer.hpp
        shaders/include/Shader.hpp
        shaders/include/Shader.cpp
        shaders/include/Uniform.hpp
        src/VertexStack.hpp
        shaders/include/Color.hpp
        src/Model.cpp
        src/Model.hpp
        src/Camera.cpp
        src/Camera.hpp
)
add_dependencies(hybrid EmbedShaders)
target_include_directories(hybrid PUBLIC include)
target_link_libraries(hybrid PUBLIC glfw3)

add_executable(hybrid_test main.cpp)
target_include_directories(hybrid PUBLIC shaders/include/)
target_link_libraries(hybrid_test PRIVATE hybrid)