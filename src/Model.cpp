#include "Model.hpp"

#include <utility>
#include <chrono>
#include <cstring>

namespace Hybrid {
    void Model::fileLoad(FILE *handle) {
        while (!feof(handle)) {

        }
    }

    void Model::allocateLoad(FILE *handle, long size) {
        // Load the entire file into memory
        char *buffer = new char[size];
        fread(buffer, size, 1, handle);
        buffer[size] = '\0';

        std::vector<std::tuple<glm::vec3>> vertices;
        std::vector<unsigned int> faces;

        char *line = std::strtok(buffer, "\n");
        while (line != nullptr) {
            if (line[0] == 'v') {
                float x, y, z;
                if (sscanf(line, "v %f %f %f", &x, &y, &z) != 3)
                    throw ModelFailedToLoad("Invalid vertex format");
                vertices.push_back({{x, y, z}});
            } else if (line[0] == 'f') {
                int x, y, z;
                if (sscanf(line, "f %i %i %i", &x, &y, &z) != 3)
                    throw ModelFailedToLoad("Invalid face format");
                faces.emplace_back(x);
                faces.emplace_back(y);
                faces.emplace_back(z);
            }

            line = std::strtok(nullptr, "\n");
        }

        this->vertexStack.update(vertices);
        this->vertexStack.setIndices(faces);

        // Cleanup all heap allocated memory
        delete[] buffer;
    }

    void Model::loadModel() {
        auto start = std::chrono::high_resolution_clock::now();

        // Here we use "rb" for no additional overhead and straight binary streaming
        FILE *handle = fopen(this->path.c_str(), "rb");
        if (!handle)
            throw ModelFailedToLoad("Model does not exist.");

        // Calculate how big the file is and compare to the max obj size to choose which import method to use
        fseek(handle, 0, SEEK_END);
        long size = ftell(handle);
        rewind(handle);

        if (size > HYBRID_MODEL_MAX_SIZE)
            this->fileLoad(handle);
        else
            this->allocateLoad(handle, size);

        fclose(handle);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Time taken (model): " << duration.count() << " ms" << std::endl;
    }

    void Model::draw() {
        this->vertexStack.draw();
    }

    Model::Model(std::string path) : path(std::move(path)) {
        this->loadModel();
    }

    Model::~Model() = default;
}