#ifndef MESH_H
#define MESH_H
#define MAX_BONE_INFLUENCE 4

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <vector>
using std::vector;

// Dados dos vertices 
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureUV;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    int boneIDs[MAX_BONE_INFLUENCE];
    float weights[MAX_BONE_INFLUENCE];
};

// Dados da textura
struct Texture
{
    unsigned int id;
    string type;
    string path;
};
class Mesh 
{
public:
    // Vertex Array Object
    unsigned int VAO;

    // Dados da malha
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // Construtor da classe
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    // Desenhar a malha
    void draw(Shader &shader);

private:
    // Vertex Buffer Object
    unsigned int VBO;

    // Element Buffer Object
    unsigned int EBO;

    // Configurar a malha
    void setupMesh();
};

#endif 