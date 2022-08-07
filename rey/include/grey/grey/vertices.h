// A vertice struct.
typedef struct Vertice {
    float x, y, z;
    float r, g, b, a;
    float u, v;
    float nx, ny, nz;
} Vertice;

// A struct of verticies.
typedef struct Vertices {
    Vertice* vertices;
    int size;
} Vertices;