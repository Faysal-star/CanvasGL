#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <string>
#include "point.h"

struct OBJModel {
    std::vector<Point> vertices;
    std::vector<std::vector<int>> edges;
    std::vector<std::vector<int>> faces; 
};

class OBJLoader {
public:
    static OBJModel loadOBJ(const std::string& filepath);
    
private:
    static int parseVertexIndex(const std::string& token);
};

#endif // OBJLOADER_H
