#pragma once

#include <string>
#include <utility>

#include "VertexStack.hpp"

/**
 * The format of each vertex that the model imported will use.
 */
#define HYBRID_MODEL_VERTEX glm::vec3

/**
 * The amount of bytes before using the file stream loading method by default,
 * this is to prevent memory being overloaded.
 */
#define HYBRID_MODEL_MAX_SIZE 10000000

namespace Hybrid {
    enum class ModelLoadMethod {
        FILE,
        ALLOCATE
    };

    class ModelFailedToLoad : public std::exception {
    private:
        std::string why;
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return std::string("Failed to load model: \"" + this->why + "\"").c_str();
        }
        explicit ModelFailedToLoad(std::string why = "unknown") : why(std::move(why)) {}
    };

    /**
     * Model is used for importing .obj files & more in the future,
     * under the hood C functionality is used for optimal performance.
     */
    class Model {
    private:
        std::string path;
        VertexStack<HYBRID_MODEL_VERTEX> vertexStack;

        /**
         * Load the model by reading directly from the model's file
         */
        void fileLoad(FILE *handle);

        /**
         * Load the model by pre-allocating the file's content into memory
         */
        void allocateLoad(FILE *handle, long size);

        void loadModel();

    public:
        void draw();

        /**
         * Construct a model
         * @param path The filepath to the model
         */
        explicit Model(std::string path);
        ~Model();
    };
}