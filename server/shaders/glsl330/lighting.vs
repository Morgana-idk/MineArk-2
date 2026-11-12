#version 330

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec3 vertexColor;

uniform mat4 mvp;
uniform mat4 matNormal;

out vec3 fragNormal;
out vec4 fragColor;

void main() {
    gl_Position = mvp * vec4(vertexPosition, 1.0);

    fragNormal = mat3(matNormal) * vertexNormal;

    fragColor = vertexColor;
}