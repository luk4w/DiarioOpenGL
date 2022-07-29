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
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
};
uniform Light light;

void main()
{
    // Iluminação ambiente
    vec3 ambient = light.ambient * texture(material.diffuse, TextureUV).rgb;

    // Iluminação difusa
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TextureUV).rgb;

    FragColor = vec4(ambient + diffuse, 1.0);
}