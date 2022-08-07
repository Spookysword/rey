#include "grey/grey/obj.hpp"
#include "mrey/mrey.h"
#include <vector>

std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
std::vector<Vec3> temp_vertices;
std::vector<Vec2> temp_uvs;
std::vector<Vec3> temp_normals;

Vertices loadObj(const char* objFile) {
    FILE* file = fopen(objFile, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", objFile);
        exit(1);
    }

    while (1) {
        char lineHeader[128];

        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
    }
    
}