#include "grey/grey/obj.hpp"
#include "OBJ_Loader.h"

Vertices loadObj(const char* objFile, bool autoCalcNormals, Color color) {
    objl::Loader loader;
    if (!loader.LoadFile(objFile)) return Vertices();
    std::vector<Vertice> v;
    for (int i = 0; i < loader.LoadedIndices.size(); i++) {
        objl::Vertex vert = loader.LoadedVertices[loader.LoadedIndices[i]];
        Vertice mvert = Vertice_create(Vec3_new(vert.Position.X, vert.Position.Y, vert.Position.Z), color, Vec2_new(vert.TextureCoordinate.X, vert.TextureCoordinate.Y), Vec3_new(vert.Normal.X, vert.Normal.Y, vert.Normal.Z));
        v.push_back(mvert);
    } 
    Vertices vs;
    vs.size = v.size();
    vs.vertices = new Vertice[vs.size];
    for (int i = 0; i < vs.size; i++) {
        vs.vertices[i] = v[i];
    }
    if (autoCalcNormals) vs = calcNormals(vs);
    return vs;
}