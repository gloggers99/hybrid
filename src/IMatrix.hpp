#pragma once

#include "Uniform.hpp"

namespace Hybrid {
    class IMatrix {
    private:
        glm::mat4 matrix;

    protected:
        /**
         * Update the matrix with new data, this function MUST return a valid glm::mat4
         */
        virtual glm::mat4 update() = 0;

    public:
        /**
         * Update a uniform with the corresponding matrix
         *
         * @param uniform The uniform to assign
         */
        void correlate(Uniform<glm::mat4> &uniform) {
            this->matrix = this->update();
            uniform = matrix;
        }

        IMatrix() : matrix(glm::mat4(1.0f)) {}
    };
}