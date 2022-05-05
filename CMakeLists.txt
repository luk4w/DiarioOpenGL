# Definir a versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Configurações de compilação da GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Definir nome do projeto, versão e linguagens suportadas
project(DiarioOpenGL VERSION 1.0 LANGUAGES C CXX)

# Incluir diretório(s)
include_directories(include)

# Adicionar subdiretório libs
add_subdirectory(libs)

# Definir nome do executável e o(s) arquivo(s) fonte
add_executable(${PROJECT_NAME} main.cpp src/shader.cpp)

# Vincular a(s) biblioteca(s) ao executável
target_link_libraries(${PROJECT_NAME} glad glfw) 