#version 330

in vec3 fragNormal;
in vec4 fragColor;
in vec2 fragTexCoord;

uniform vec3 lightDir;
uniform sampler2D texture0;

out vec4 finalColor;

void main() {
    bool shadowed = false;

    vec4 texel = texture(texture0, fragTexCoord);

    float diffuse = max(dot(normalize(fragNormal), normalize(lightDir)), -0.065);

    float ambient = 0.3f;

    float brightness;

    vec3 finalRGB = texel.rgb * fragColor.rgb * brightness;

    finalColor = vec4(clamp(finalRGB, 0, 1), texel.a * fragColor.a);
}