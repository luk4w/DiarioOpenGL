#version 330 core
out vec4 FragColor;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 lightPos; 
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    // Iluminação ambiente
    vec3 ambient = material.ambient * light.ambient;

    // Iluminação difusa
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;

    // Iluminação especular
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);  
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = (material.specular * spec) * light.specular;  

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}