#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

enum ShaderType
{
    BASIC_SHADER,
    LAMP_SHADER,
};

class Model
{
    ShaderType shaderType;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

public:
    // Construtor
    Model(string const &path, bool gamma = false);

    // Desenhar o modelo
    void draw(Shader &shader);

    void setShaderType(ShaderType type = BASIC_SHADER) { shaderType = type; }
    ShaderType getShaderType() const { return shaderType; }

    void setPosition(const glm::vec3 &pos) { position = pos; }
    void setScale(const glm::vec3 &sc) { scale = sc; }
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getScale() const { return scale; }

private:
    // Dados do modelo
    vector<Texture> texturesLoaded;
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    // Carregar um modelo com extensões ASSIMP suportadas e armazenar as malhas resultantes no vetor "meshes"
    void loadModel(string const &path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif