#include "window_manager.h"

WindowManager::WindowManager(const std::string &title, int width, int height)
    : window(nullptr), width(width), height(height), title(title)
{
}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool WindowManager::initialize()
{

    // Inicializar GLFW
    if (!glfwInit())
    {
        std::cerr << "Falha ao inicializar GLFW!" << std::endl;
        return false;
    }

    // Configurar versão do OpenGL e perfil
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Inicializar window
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    // Verificar GLFW
    if (window == nullptr)
    {
        std::cerr << "Falha ao criar GLFWwindow!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    // Definir função de retorno de chamada para o redimensionamento da janela
    glfwSetFramebufferSizeCallback(window, WindowManager::framebufferSizeCallback);

    // Verificar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Nao foi possivel carregar o contexto OpenGL!" << std::endl;
        glfwTerminate();
        return false;
    }

    return true;
}

GLFWwindow *WindowManager::getWindow() const
{
    return window;
}

bool WindowManager::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void WindowManager::swapBuffers()
{
    glfwSwapBuffers(window);
}

void WindowManager::pollEvents()
{
    glfwPollEvents();
}

void WindowManager::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
