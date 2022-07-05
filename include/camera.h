#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum cameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Valores padrões da câmera
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float fov;

    // Construtor com vetores
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // Construtor com valores escalares
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // Retornar a View Matrix transformada
    glm::mat4 GetViewMatrix();

    // Processar a entrada de teclado
    void ProcessKeyboard(cameraMovement direction, float deltaTime);

    // Processar a entrada de mouse, recebe os valores da direção x e y
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // Processar a entrada do scroll
    void ProcessMouseScroll(float yoffset);

private:
    // Calcular o vetor frontal dos Ângulos de Euler da Câmera
    void updateCameraVectors();
};
#endif