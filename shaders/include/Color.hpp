#pragma once

#define HYBRID_GL_COLOR_CONVERT(color) color.r, color.g, color.b, color.a

namespace Hybrid {
    class Color {
    public:
        float r, g, b, a;

        explicit Color(float scalar) : r(scalar), g(scalar), b(scalar), a(1.0f) {}
        Color(float scalar, float alpha) : r(scalar), g(scalar), b(scalar), a(alpha) {}
        Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {}
        Color(float r, float g, float b, float a) : r(r), b(b), g(g), a(a) {}
    };
}