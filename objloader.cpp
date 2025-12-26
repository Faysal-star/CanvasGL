#include "objloader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

OBJModel OBJLoader::loadOBJ(const std::string& filepath) {
    OBJModel model;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << filepath << std::endl;
        return model;
    }
    
    std::string line;
    std::set<std::pair<int, int>> edgeSet;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        
        if (type == "v") {
            // Parse vertex: v x y z
            float x, y, z;
            iss >> x >> y >> z;
            model.vertices.push_back(Point(x, y, z));
        }
        else if (type == "f") {
            // Parse face: f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
            std::vector<int> faceIndices;
            std::string token;
            
            while (iss >> token) {
                int vertexIndex = parseVertexIndex(token);
                if (vertexIndex > 0) {
                    // Convert from 1-based to 0-based indexing
                    faceIndices.push_back(vertexIndex - 1);
                }
            }

            model.faces.push_back(faceIndices);
            
            // Extracting edges from face (connect consecutive vertices)
            for (size_t i = 0; i < faceIndices.size(); i++) {
                int v1 = faceIndices[i];
                int v2 = faceIndices[(i + 1) % faceIndices.size()];
                
                // Store edge (ensure v1 < v2 to avoid duplicates)
                if (v1 > v2) std::swap(v1, v2);
                edgeSet.insert({v1, v2});
            }
        }
    }
    
    file.close();
    
    // edge set to edge map format
    for (const auto& edge : edgeSet) {
        model.edges.push_back({edge.first, edge.second});
    }
    
    std::cout << "Loaded OBJ: " << model.vertices.size() << " vertices, " 
              << model.faces.size() << " faces, " 
              << model.edges.size() << " edges" << std::endl;
    
    return model;
}

int OBJLoader::parseVertexIndex(const std::string& token) {
    // Parse formats : "23/1/23" or "23//23" or "23/1" or "23"
    size_t firstSlash = token.find('/');
    
    if (firstSlash == std::string::npos) {
        // Format: "23" - just vertex index
        return std::stoi(token);
    }
    
    // Format: "23/..." - extract vertex index before first slash
    return std::stoi(token.substr(0, firstSlash));
}
