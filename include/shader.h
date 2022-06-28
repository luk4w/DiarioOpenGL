#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
using std::string;

class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    void use();
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    };
private:
    void checkCompileErrors(unsigned int shader, string type);
};
#endif