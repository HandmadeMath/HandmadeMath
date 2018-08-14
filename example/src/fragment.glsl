#version 330 core

in vec3 fragmentPosition_world;
in vec3 fragmentColor;
in vec3 fragmentNormal_world;
in vec2 fragmentUV;

out vec3 color;

void main() {
    vec3 ambient = vec3(0.1, 0.1, 0.1);

    vec3 toLight_world = normalize(vec3(1, 1, 1));

    float cosTheta = clamp(dot(normalize(fragmentNormal_world), toLight_world), 0.1, 1);

    color = cosTheta * fragmentColor + ambient;
}
