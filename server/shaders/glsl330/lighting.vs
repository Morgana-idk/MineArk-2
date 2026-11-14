#version 330

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;
in vec2 vertexTexCoord;

uniform mat4 mvp;
uniform mat4 matNormal;

out vec3 fragNormal;
out vec4 fragColor;
out vec2 fragTexCoord;

void main() {
    gl_Position = mvp * vec4(vertexPosition, 1.0);

    fragNormal = mat3(matNormal) * vertexNormal;

    fragColor = vertexColor;

    fragTexCoord = vertexTexCoord;
}