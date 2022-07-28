#version 330 core
out vec4 FragColor;

in vec2 TextureUV;

struct Material
{
    sampler2D diffuse;
};
uniform Material material;

void main()
{
    FragColor = texture(material.diffuse, TextureUV);
}