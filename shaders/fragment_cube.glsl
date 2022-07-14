#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 Normal;

void main()
{
    float ambientLighting = 0.2;

    vec3 result = ambientLighting * lightColor * objectColor;
    FragColor = vec4(result, 1.0);
}