#include <GLFW/glfw3.h>

#include <iostream>
using std::cout;
using std::endl;

const unsigned int WIDTH = 800; 
const unsigned int HEIGHT = 600;

int main()
{
    // Inicializar biblioteca GLFW
    glfwInit();

    // Instanciar GLFWwindow
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "DiarioOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Falha ao criar GLFWwindow!" << endl;
        return -1;
    }

    // Loop de renderização principal
    while (!glfwWindowShouldClose(window))
    {
        // Processar todos os eventos pendentes
        glfwPollEvents();
    }

    glfwDestroyWindow(window); // Opcional
    glfwTerminate(); // Terminar biblioteca GLFW

    return 0;
} 