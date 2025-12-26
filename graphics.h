#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include<string>
#include "color.h"
#include "point.h"

class Graphics {
private:
    unsigned int shaderProgram;
    unsigned int VAO, VBO;
    std::vector<float> vertices;
    int windowWidth;
    int windowHeight;

    void setupShaders();
    void updateBuffer();
    const float PI = 3.14159265359f;

public:
    Graphics(int width, int height);
    ~Graphics();

    void clear(float r, float g, float b, float a = 1.0f);
    void clear(const Color& color) {
        clear(color.r, color.g, color.b, color.a);
    }
    void point(float x, float y, float size = 5.0f);
    void point(const Point& p, float size = 5.0f) {
        point(p.x, p.y, size);
    }
    void line(float x1, float y1, float x2, float y2);
    void line(const Point& p1, const Point& p2) {
        line(p1.x, p1.y, p2.x, p2.y);
    }
    void line_loop(const std::vector<Point>& points);
    void circle(float x, float y, float radius, bool filled = false);
    void circle(const Point& center, float radius, bool filled = false) {
        circle(center.x, center.y, radius, filled);
    }
    void rect(float x, float y, float width, float height, bool filled = false);
    void rect(const Point& topLeft, float width, float height, bool filled = false) {
        rect(topLeft.x, topLeft.y, width, height, filled);
    }
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3, bool filled = true);
    void triangle(const Point& p1, const Point& p2, const Point& p3, bool filled = true) {
        triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, filled);
    }
    
    // Color control
    void setColor(float r, float g, float b, float a = 1.0f);
    void setColor(const Color& color);
    
    // Utility
    void beginDraw();
    void endDraw();
    
    int getWidth() { return windowWidth; }
    int getHeight() { return windowHeight; }
};

#endif // GRAPHICS_H
