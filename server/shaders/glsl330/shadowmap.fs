
#version 330

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec3 lightDir;
uniform vec4 lightColor;
uniform vec4 ambient;

uniform mat4 lightVP;
uniform sampler2D shadowMap;
uniform int shadowMapResolution;

out vec4 finalColor;

void main()
{
    vec4 lightSpace = lightVP * vec4(fragPosition, 1.0);

    lightSpace.xyz /= lightSpace.w;
    lightSpace.xyz = lightSpace.xyz * 0.5 + 0.5;

    vec3 projected = lightSpace.xyz;

    float depthValue = texture(shadowMap, projected.xy).r;

    finalColor = vec4(vec3(depthValue), 1.0);
}