#include "renderer.h"
#include <iostream>

Renderer::Renderer(Camera *cam, int w, int h)
    : camera(cam), width(w), height(h) {}

void Renderer::initialize()
{
    // Inverter as texturas carregadas no eixo y
    stbi_set_flip_vertically_on_load(true);

    // Habilitar teste do buffer de profundidade
    glEnable(GL_DEPTH_TEST);

    // Inicialização de Shaders
    shaderModel = Shader("shaders/model_vertex.glsl", "shaders/model_fragment.glsl");
    shaderLamp = Shader("shaders/lamp_vertex.glsl", "shaders/lamp_fragment.glsl");
}

void Renderer::drawScene(Scene &scene)
{
    // Limpar os buffers
    glClearColor(0.05f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definir as matrizes comuns a ambos os shaders
    glm::mat4 projection = glm::perspective(glm::radians(camera->fov), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 view = camera->getViewMatrix();

    // Obter apenas a leitura dos objetos e as luzes da cena
    const std::vector<Object> &objects = scene.getObjects();
    const std::vector<LightObject> &lights = scene.getLights();

    // Logica das luzes
    for (const std::vector<LightObject>::const_iterator::value_type light : lights)
    {
        Shader *shader = &shaderLamp;
        shader->use();

        shader->setVec3("viewPos", camera->position);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);

        // Configuração da matriz de modelo específica para cada objeto
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        modelMatrix = glm::translate(modelMatrix, light.getPosition());

        if(light.getRotation().angle != 0.0f)
            modelMatrix = glm::rotate(modelMatrix, glm::radians(light.getRotation().angle), light.getRotation().axis);

        modelMatrix = glm::scale(modelMatrix, light.getScale());

        shader->setMat4("model", modelMatrix);
        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));

        light.model->draw(*shader);
    }

    // Logica de renderização dos objetos normais
    for (const std::vector<Object>::const_iterator::value_type obj : objects)
    {
        Shader *shader = &shaderModel;
        shader->use();

        // Luzes
        std::vector<glm::vec3> lightPositions;
        for (const std::vector<LightObject>::const_iterator::value_type light : lights)
        {
            lightPositions.push_back(light.getPosition());
        }
        setLighting(lightPositions);

        shader->setVec3("viewPos", camera->position);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);

        // Configuração da matriz de modelo específica para cada objeto
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        modelMatrix = glm::translate(modelMatrix, obj.getPosition());

        if(obj.getRotation().angle != 0.0f)
            modelMatrix = glm::rotate(modelMatrix, glm::radians(obj.getRotation().angle), obj.getRotation().axis);
        
        modelMatrix = glm::scale(modelMatrix, obj.getScale());

        shader->setMat4("model", modelMatrix);
        shader->setMat3("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));

        obj.model->draw(*shader);
    }
}

void Renderer::setLighting(std::vector<glm::vec3> & lightPositions)
{
    shaderModel.setFloat("material.shininess", 32.0f);

    // Luz direcional
    shaderModel.setVec3("directionalLight.direction", -0.2f, -1.0f, -0.3f);
    shaderModel.setVec3("directionalLight.ambient", 0.05f, 0.05f, 0.05f);
    shaderModel.setVec3("directionalLight.diffuse", 0.4f, 0.4f, 0.4f);
    shaderModel.setVec3("directionalLight.specular", 0.5f, 0.5f, 0.5f);

    // Lâmpada 1
    shaderModel.setVec3("pointLights[0].position", lightPositions[0]);
    shaderModel.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    shaderModel.setVec3("pointLights[0].diffuse", 1.0f, 1.0f, 1.0f);
    shaderModel.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    shaderModel.setFloat("pointLights[0].constant", 1.0f);
    shaderModel.setFloat("pointLights[0].linear", 0.09f);
    shaderModel.setFloat("pointLights[0].quadratic", 0.032f);

    // Lâmpada 2
    shaderModel.setVec3("pointLights[1].position", lightPositions[1]);
    shaderModel.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    shaderModel.setVec3("pointLights[1].diffuse", 1.0f, 1.0f, 1.0f);
    shaderModel.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    shaderModel.setFloat("pointLights[1].constant", 1.0f);
    shaderModel.setFloat("pointLights[1].linear", 0.09f);
    shaderModel.setFloat("pointLights[1].quadratic", 0.032f);

    // Holofote
    shaderModel.setBool("spotlightOn", spotlightState);
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

void Renderer::toggleSpotlight()
{
    spotlightState = !spotlightState;
}
