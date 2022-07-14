#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; 

in vec3 Normal;
in vec3 FragPos;

void main()
{
    float ambientLighting = 0.2;

    vec3 result = ambientLighting * lightColor * objectColor;
    FragColor = vec4(result, 1.0);
}