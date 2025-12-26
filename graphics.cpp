#include "graphics.h"
#include <iostream>

// Shader sources
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 uColor;\n"
"void main()\n"
"{\n"
"   FragColor = uColor;\n"
"}\n\0";

Graphics::Graphics(int width, int height) 
    : windowWidth(width), windowHeight(height) {
    setupShaders();
    
    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    // Set default color to white
    setColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Enable point size control
    glEnable(GL_PROGRAM_POINT_SIZE);
}

Graphics::~Graphics() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

void Graphics::setupShaders() {
    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Graphics::updateBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
}

void Graphics::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::setColor(float r, float g, float b, float a) {
    glUseProgram(shaderProgram);
    int colorLoc = glGetUniformLocation(shaderProgram, "uColor");
    glUniform4f(colorLoc, r, g, b, a);
}

void Graphics::setColor(const Color& color) {
    setColor(color.r, color.g, color.b, color.a);
}

void Graphics::beginDraw() {
    vertices.clear();
}

void Graphics::endDraw() {
    // This is called automatically by each draw function
}

void Graphics::point(float x, float y, float size) {
    vertices.clear();
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(0.0f);
    
    updateBuffer();
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glPointSize(size);
    glDrawArrays(GL_POINTS, 0, 1);
}

void Graphics::line(float x1, float y1, float x2, float y2) {
    vertices.clear();
    vertices.push_back(x1);
    vertices.push_back(y1);
    vertices.push_back(0.0f);
    vertices.push_back(x2);
    vertices.push_back(y2);
    vertices.push_back(0.0f);
    
    updateBuffer();
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
}

void Graphics::line_loop(const std::vector<Point>& points) {
    vertices.clear();
    for (const auto& p : points) {
        vertices.push_back(p.x);
        vertices.push_back(p.y);
        vertices.push_back(0.0f);
    }
    
    updateBuffer();
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, points.size());
}

void Graphics::circle(float x, float y, float radius, bool filled) {
    vertices.clear();
    int segments = 50;
    
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float cx = x + radius * cos(angle);
        float cy = y + radius * sin(angle);
        vertices.push_back(cx);
        vertices.push_back(cy);
        vertices.push_back(0.0f);
    }
    
    updateBuffer();
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(filled ? GL_TRIANGLE_FAN : GL_LINE_LOOP, 0, segments + 1);
}

void Graphics::rect(float x, float y, float width, float height, bool filled) {
    vertices.clear();
    
    // Bottom-left corner is at (x, y)
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(0.0f);
    
    vertices.push_back(x + width);
    vertices.push_back(y);
    vertices.push_back(0.0f);
    
    vertices.push_back(x + width);
    vertices.push_back(y + height);
    vertices.push_back(0.0f);
    
    vertices.push_back(x);
    vertices.push_back(y + height);
    vertices.push_back(0.0f);
    
    updateBuffer();
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    
    if (filled) {
        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
        // Simple alternative without indices
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    } else {
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}

void Graphics::triangle(float x1, float y1, float x2, float y2, float x3, float y3, bool filled) {
    vertices.clear();
    vertices.push_back(x1);
    vertices.push_back(y1);
    vertices.push_back(0.0f);
    
    vertices.push_back(x2);
    vertices.push_back(y2);
    vertices.push_back(0.0f);
    
    vertices.push_back(x3);
    vertices.push_back(y3);
    vertices.push_back(0.0f);
    
    updateBuffer();
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(filled ? GL_TRIANGLES : GL_LINE_LOOP, 0, 3);
}
