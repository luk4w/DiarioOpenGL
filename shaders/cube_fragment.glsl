#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight directionalLight;

uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexturePos;

// Protótipos de função
vec3 getDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDirection = normalize(viewPos - FragPos);
    
    vec3 result = getDirectionalLight(directionalLight, norm, viewDirection);

    FragColor = vec4(result, 1.0);
}

vec3 getDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(-light.direction);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexturePos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexturePos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexturePos));
    return (ambient + diffuse + specular);
}