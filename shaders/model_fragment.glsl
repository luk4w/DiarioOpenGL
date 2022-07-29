#version 330 core
out vec4 FragColor;

in vec2 TextureUV;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
    sampler2D diffuse;
};
uniform Material material;

struct Light
{
    vec3 ambient;
};
uniform Light light;

void main()
{
    vec3 ambient = light.ambient * texture(material.diffuse, TextureUV).rgb;

    FragColor = vec4(ambient, 1.0);
}