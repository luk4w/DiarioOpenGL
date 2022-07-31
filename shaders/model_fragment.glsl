#version 330 core
out vec4 FragColor;

in vec2 TextureUV;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct Light
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

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
uniform PointLight pointLight;

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

// Protótipos de função
vec3 getDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);  
vec3 getSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);

void main()
{
    // Iluminação difusa
    vec3 norm = normalize(Normal);
    vec3 viewDirection = normalize(viewPos - FragPos);
    
    // Iluminação directional
    vec3 result = getDirectionalLight(directionalLight, norm, viewDirection);

    // Ponto de luz
    result += getPointLight(pointLight, norm, FragPos, viewDirection);  

    // Holofote
    //result += getSpotLight(spotLight, norm, FragPos, viewDirection);    
    
    FragColor = vec4(result, 1.0);
}

// Obter uma luz direcional
vec3 getDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(-light.direction);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureUV));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextureUV));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TextureUV));

    return (ambient + diffuse + specular);
}

vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureUV));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextureUV));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TextureUV));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
} 

vec3 getSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    float theta = dot(lightDirection, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureUV));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextureUV));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TextureUV));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}