#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;

out vec2 textureCoordinate;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    textureCoordinate = vec2(aTexture.x, aTexture.y);
}