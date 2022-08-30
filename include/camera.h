#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UPWARD,
    DOWNWARD
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
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float fov;

    // Construtor com vetores
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // Construtor com valores escalares
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // Retornar a View Matrix transformada
    glm::mat4 getViewMatrix();

    // Processar a entrada de teclado
    void processKeyboard(Movement direction, float deltaTime);

    // Processar a entrada de mouse, recebe os valores da direção x e y
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // Processar a entrada do scroll
    void processMouseScroll(float yoffset);

private:
    void updateCameraVectors();
};
#endif
