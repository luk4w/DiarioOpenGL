#include "mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    // Definir os buffers de vertice e os ponteiros para os atributos
    setupMesh();
}

void Mesh::draw(Shader &shader) 
{
    unsigned int diffuseCount = 1;
    unsigned int specularCount = 1;
    unsigned int normalCount = 1;
    unsigned int heightCount = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        // Ativar unidade de textura apropriada antes de vincular
        glActiveTexture(GL_TEXTURE0 + i);

        // Recuperar o número da textura (o N de material.diffuseN)
        string number;
        string name = textures[i].type;
        if(name == "material.diffuse")
        {
            number = std::to_string(diffuseCount++);
        }    
        else if (name == "material.specular")
        {
            number = std::to_string(specularCount++);
        }       
        else if (name == "material.normal")
        {
            number = std::to_string(normalCount++);
        }   
        else if (name == "material.height")
        {
            number = std::to_string(heightCount++);
        }

        // Definir a unidade da textura e vincular
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // Vincular VAO ao OpenGL
    glBindVertexArray(VAO);

    // Desenhar a malha
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Vincular VAO, VBO e EBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Copiar os dados dos vertices para o VBO vinculado
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    // Copiar os dados dos indices para o EBO vinculado
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Atribuir ponteiros para os vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribuir ponteiros para as normais
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // Atribuir ponteiros para as coordenadas de textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureUV));
    glEnableVertexAttribArray(2);

    // Atribuir ponteiros para as tangentes
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    // Atribuir ponteiros para as bitangentes
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    glEnableVertexAttribArray(4);

    // Atribuir ponteiros para os boneIDs
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs));
    glEnableVertexAttribArray(5);

    // Atribuir ponteiros para os weights
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));
    glEnableVertexAttribArray(6);

    glBindVertexArray(0);
}