#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; 

in vec3 Normal;
in vec3 FragPos;

void main()
{
    // Iluminação ambiente
    float ambientLighting = 0.2;
    vec3 ambient = ambientLighting * lightColor;

    // Iluminação difusa
    // normalize(u); calcula o vetor unitário na mesma direção do vetor original
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    // max(-1, 2); retorna o maior valor
    // dot(u, w); calcula o produto escalar de dois vetores
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}