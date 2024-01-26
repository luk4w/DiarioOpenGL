#include "shader.h"

#include <fstream>
using std::ifstream;

#include <sstream>
using std::stringstream;

#include <iostream>
using std::cout;
using std::endl;

Shader::Shader()
{
}

Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
{
    // Recuperar o código-fonte dos arquivos
    string vertexCode;
    string fragmentCode;
    string geometryCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    ifstream gShaderFile;
    // Verificar se os objetos ifstream podem lançar exceções
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try
    {
        // Abrir arquivos
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        // Ler arquivos
        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Fechar os manipuladores de arquivos
        vShaderFile.close();
        fShaderFile.close();

        // Transformar stream em string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        // Carregar Geometry Shader se != nullptr
        if (geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (ifstream::failure &e)
    {
        cout << "Falha ao ler arquivo de codigo-fonte GLSL " << endl
             << e.what() << endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "Vertex Shader");

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "Fragment Shader");

    unsigned int geometryShader;
    if (geometryPath != nullptr)
    {
        const char *gShaderCode = geometryCode.c_str();
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &gShaderCode, NULL);
        glCompileShader(geometryShader);
        checkCompileErrors(geometryShader, "Geometry Shader");
    }

    // Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    if (geometryPath != nullptr)
        glAttachShader(ID, geometryShader);
    glLinkProgram(ID);
    checkCompileErrors(ID, "Shader Program");

    // Deletar shaders inutilizados
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometryPath != nullptr)
        glDeleteShader(geometryShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

// Verificar erros de compilação e vinculação
void Shader::checkCompileErrors(unsigned int shader, string type)
{
    int success;
    char infoLog[1024];
    if (type != "Shader Program")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            cout << "Erro ao vincular " << type << endl
                 << infoLog << endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            cout << "Erro ao vincular " << type << endl
                 << infoLog << endl;
        }
    }
}
