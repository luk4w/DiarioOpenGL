#version 330 core
out vec4 FragColor;

in vec2 TextureUV;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 viewPos;

void main()
{
    // Iluminação ambiente
    vec3 ambient = light.ambient * texture(material.diffuse, TextureUV).rgb;

    // Iluminação difusa
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TextureUV).rgb;

    // Iluminação especular
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.specular;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}