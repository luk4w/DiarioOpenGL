#include "renderer_manager.h"
#include "shader_type.h"
#include <iostream>

RendererManager::RendererManager(Camera *cam, float w, float h)
    : camera(cam), width(w), height(h) {}

void RendererManager::initialize()
{
    // Inverter as texturas carregadas no eixo y
    stbi_set_flip_vertically_on_load(true);

    // Habilitar teste do buffer de profundidade
    glEnable(GL_DEPTH_TEST);

    // Inicialização de Shaders
    shaderModel = Shader("shaders/model_vertex.glsl", "shaders/model_fragment.glsl");
    shaderLamp = Shader("shaders/lamp_vertex.glsl", "shaders/lamp_fragment.glsl");

    // Carregar os modelos
    Model bp("models/backpack/backpack.obj");
    bp.setShaderType(BASIC_SHADER);
    models.push_back(bp);

    Model cube("models/cube/cube.obj");
    cube.setShaderType(LAMP_SHADER);
    cube.setPosition(lampPosition);
    cube.setScale(glm::vec3(0.2f, 0.2f, 0.2f));
    models.push_back(cube);
}

void RendererManager::render()
{
    // Limpar os buffers
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definir as matrizes comuns a ambos os shaders
    glm::mat4 projection = glm::perspective(glm::radians(camera->fov), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 view = camera->getViewMatrix();

    for (auto &model : models)
    {
        Shader *shader = model.getShaderType() == BASIC_SHADER ? &shaderModel : &shaderLamp;
        shader->use();

        if (model.getShaderType() == BASIC_SHADER)
            configureLighting(*shader);

        shader->setVec3("viewPos", camera->position);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);

        // Configuração da matriz de modelo específica para cada objeto
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, model.getPosition());
        modelMatrix = glm::scale(modelMatrix, model.getScale());
        shader->setMat4("model", modelMatrix);
        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));

        model.draw(*shader);
    }
}

void RendererManager::configureLighting(Shader &shader)
{
    shaderModel.setFloat("material.shininess", 32.0f);

    // Luz direcional
    shaderModel.setVec3("directionalLight.direction", -0.2f, -1.0f, -0.3f);
    shaderModel.setVec3("directionalLight.ambient", 0.05f, 0.05f, 0.05f);
    shaderModel.setVec3("directionalLight.diffuse", 0.4f, 0.4f, 0.4f);
    shaderModel.setVec3("directionalLight.specular", 0.5f, 0.5f, 0.5f);

    // Ponto de luz
    shaderModel.setVec3("pointLight.position", lampPosition);
    shaderModel.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
    shaderModel.setVec3("pointLight.diffuse", 1.0f, 1.0f, 1.0f);
    shaderModel.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
    shaderModel.setFloat("pointLight.constant", 1.0f);
    shaderModel.setFloat("pointLight.linear", 0.09f);
    shaderModel.setFloat("pointLight.quadratic", 0.032f);

    // Holofote
    shaderModel.setVec3("spotLight.position", camera->position);
    shaderModel.setVec3("spotLight.direction", camera->front);
    shaderModel.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    shaderModel.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    shaderModel.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    shaderModel.setFloat("spotLight.constant", 1.0f);
    shaderModel.setFloat("spotLight.linear", 0.09f);
    shaderModel.setFloat("spotLight.quadratic", 0.032f);
    shaderModel.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shaderModel.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}
