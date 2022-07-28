#include "model.h"

#include <iostream>
using std::cout;
using std::endl;

// Protótipo de função
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

Model::Model(string const &path, bool gamma) : gammaCorrection(gamma)
{
    loadModel(path);
}

void Model::draw(Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(shader);
    }
}

void Model::loadModel(string const &path)
{
    // Ler o arquivo via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    // Verificar erros
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "Erro ao importar modelo ASSIMP " << importer.GetErrorString() << endl;
        return;
    }

    // Recuperar o caminho do diretório do arquivo
    directory = path.substr(0, path.find_last_of('/'));

    // Processar o nó raiz do ASSIMP recursivamente
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // Processar cada malha localizada do nó atual
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // Processar recursivamente cada um dos nós filhos, se houver algum
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // Percorrer cada um dos vértices da malha
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; 

        // Posição
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        //  Normal
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // Coordenada de textura
        if(mesh->mTextureCoords[0]) // Verificar se a malha possui coordenada de textura
        {   

            glm::vec2 vec;
            // Um vértice pode conter até 8 coordenadas de textura diferentes
            // Ignorar e pegar apenas o primeiro conjunto
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.textureUV = vec;

            // Tangente
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;

            // Bitangente
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
        {
            vertex.textureUV = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    // Percorrer cada uma das faces da malha e recuperar os indices dos verrtices correspondentes
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        // Recuperar todos os indices da face e armazenar no vetor de indices
        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);     
        }
    }

    // Processar os materiais
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
    // Pressupõe uma convenção para os nomes nos shaders:
    // Cada textura difusa deve ser nomeada como "material.diffuseN" onde N é um número sequencial que varia de 1 a MAX_SAMPLER_NUMBER.
    // O mesmo se aplica a outras texturas conforme a lista a seguir:
    // diffuse: material.diffuseN
    // specular: material.specularN
    // normal: material.normalN

    // 1. diffuse maps
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "material.diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // 2. specular maps
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "material.specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "material.normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "material.height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // Retornar a malha, que foi criada a partir dos dados extraídos
    return Mesh(vertices, indices, textures);
}

// Verificar todas as texturas de material de um determinado tipo e carregar as texturas não carregadas
vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        // Verificar se a textura já foi carregada
        for(unsigned int j = 0; j < texturesLoaded.size(); j++)
        {
            if(std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(texturesLoaded[j]);
                skip = true; // Pular se existir uma textura com o mesmo diretório já carregada
                break;
            }
        }

        // Carregar textura, caso não esteja carregada
        if(!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            // Armazenar como uma textura carregada, para garantir que não seja carregada duas ou mais vezes
            texturesLoaded.push_back(texture);  
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        cout << "Falha ao carregar textura " << path << endl;
        stbi_image_free(data);
    }

    return textureID;
}