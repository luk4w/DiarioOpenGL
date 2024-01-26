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
#include <vector>


class Model
{
public:
    // Construtor
    Model(string const &path, bool gamma = false);

    // Desenhar o modelo
    void draw(Shader &shader);

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