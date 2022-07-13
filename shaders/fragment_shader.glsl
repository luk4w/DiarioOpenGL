#version 330 core
out vec4 FragColor;

in vec2 TextureCoordinate;

uniform sampler2D uniformTexture;

void main()
{
    FragColor = texture(uniformTexture, TextureCoordinate);
}