#include "draw.h"
#include "objloader.h"
#include <vector>
#include <iostream>

const float FPS = 90; 
float dz = 1.0f;
float angle = 0;
const double PI = 1.0 * acos(-1.0f);

// Global model data
OBJModel objModel;
bool useOBJModel = false;  // Toggle between cube and OBJ model
float modelScale = 1.0f;
Point modelCenter = Point(0.0f, 0.0f, 0.0f);

// model normalization
void normalizeModel(OBJModel& model) {
    if (model.vertices.empty()) return;

    float minX = model.vertices[0].x, maxX = model.vertices[0].x;
    float minY = model.vertices[0].y, maxY = model.vertices[0].y;
    float minZ = model.vertices[0].z, maxZ = model.vertices[0].z;
    
    for (const auto& v : model.vertices) {
        minX = std::min(minX, v.x); maxX = std::max(maxX, v.x);
        minY = std::min(minY, v.y); maxY = std::max(maxY, v.y);
        minZ = std::min(minZ, v.z); maxZ = std::max(maxZ, v.z);
    }

    modelCenter = Point((minX + maxX) / 2.0f, (minY + maxY) / 2.0f, (minZ + maxZ) / 2.0f);
    
    float sizeX = maxX - minX;
    float sizeY = maxY - minY;
    float sizeZ = maxZ - minZ;
    float maxSize = std::max({sizeX, sizeY, sizeZ});
    
    modelScale = (maxSize > 0) ? (1.0f / maxSize) : 1.0f;
    
    std::cout << "Model bounds: X[" << minX << ", " << maxX << "] "
              << "Y[" << minY << ", " << maxY << "] "
              << "Z[" << minZ << ", " << maxZ << "]" << std::endl;
    std::cout << "Model center: (" << modelCenter.x << ", " << modelCenter.y << ", " << modelCenter.z << ")" << std::endl;
    std::cout << "Model scale: " << modelScale << std::endl;
}

void setup(Graphics& gfx) {
    objModel = OBJLoader::loadOBJ("./3d_models/low_poly_car.obj");
    
    if (!objModel.vertices.empty()) {
        useOBJModel = true;
        normalizeModel(objModel);
        std::cout << "Using OBJ model for rendering" << std::endl;
    } else {
        std::cout << "Using default cube" << std::endl;
    }
}

void frame(Graphics& gfx) {
    const float dt = 1.0f / FPS;
    //dz += 1 * dt;
    angle += PI * dt;

    gfx.clear(COLOR_BLACK);

    std::vector<Point> points;
    std::vector<std::vector<int>> edge_map;
    
    if (useOBJModel) {
        points = objModel.vertices;

        for (auto& p : points) {
            // Center model
            p.x -= modelCenter.x;
            p.y -= modelCenter.y;
            p.z -= modelCenter.z;
            
            // Scale to fit viewport
            p.x *= modelScale;
            p.y *= modelScale;
            p.z *= modelScale;
        }
        
        edge_map = objModel.edges;
    } else {
        // Default cube
        points = {
            {  0.25f,  0.25f, 0.25f },
            { -0.25f,  0.25f, 0.25f },
            { -0.25f, -0.25f, 0.25f },
            {  0.25f, -0.25f, 0.25f },

            {  0.25f,  0.25f, -0.25f },
            { -0.25f,  0.25f, -0.25f },
            { -0.25f, -0.25f, -0.25f },
            {  0.25f, -0.25f, -0.25f },
        };

        edge_map = {
            {0,1,2,3},
            {4,5,6,7}, 
            {0, 4},
            {1, 5},
            {2, 6},
            {3, 7}
        };
    }

    gfx.setColor(COLOR_CYAN);
    for (auto& p : points) {
        p = project(translateZ(rot_xz(p, angle), dz));
        //gfx.point(p, 5.0f);
    }

    // Render edges/wireframe
    for (auto& em : edge_map) {
        if (em.size() == 2) {
            gfx.line(points[em[0]].x, points[em[0]].y, 
                     points[em[1]].x, points[em[1]].y);
        } else {
            std::vector<Point> loop;
            for (int i = 0; i < std::size(em); i++) {
                loop.push_back(points[em[i]]);
            }
            gfx.line_loop(loop);
        }
    }
}

void draw(Graphics& gfx, float deltaTime) {
    frame(gfx);
}
