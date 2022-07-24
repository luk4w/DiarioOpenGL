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

struct PointLight
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define POINT_LIGHTS 4
uniform PointLight pointLights[POINT_LIGHTS];

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};
uniform SpotLight spotLight;


uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexturePos;

// Protótipos de função
vec3 getDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);
vec3 getSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDirection = normalize(viewPos - FragPos);
    
    vec3 result = getDirectionalLight(directionalLight, norm, viewDirection);

    for(int i = 0; i < POINT_LIGHTS; i++)
    {
        result += getPointLight(pointLights[i], norm, FragPos, viewDirection);
    }

    result += getSpotLight(spotLight, norm, FragPos, viewDirection);    
        
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

vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexturePos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexturePos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexturePos));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 getSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexturePos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexturePos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexturePos));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}