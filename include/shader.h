#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
using std::string;

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    void use();
private:
    unsigned int ID;
    void checkCompileErrors(unsigned int shader, string type);
};
#endif