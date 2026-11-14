#version 330

in vec3 fragNormal;
in vec4 fragColor;
in vec2 fragTexCoord;

uniform vec3 lightDir;

uniform int shadowTop;
uniform int shadowBottom;
uniform int shadowRight;
uniform int shadowLeft;
uniform int shadowFront;
uniform int shadowBack;

uniform sampler2D texture0;

out vec4 finalColor;

void main() {
    bool shadowed = false;

    vec4 texel = texture(texture0, fragTexCoord);

    float diffuse = max(dot(normalize(fragNormal), normalize(lightDir)), -0.065);

    float ambient = 0.3f;

    if (fragNormal.y > 0.9) shadowed = shadowTop == 1;
    if (fragNormal.y < -0.9) shadowed = shadowBottom == 1;

    if (fragNormal.x > 0.9) shadowed = shadowRight == 1;
    if (fragNormal.x < -0.9) shadowed = shadowLeft == 1;
    
    if (fragNormal.z > 0.9) shadowed = shadowFront == 1;
    if (fragNormal.z < -0.9) shadowed = shadowBack == 1;

    float brightness;

    if (!shadowed) {
        brightness = ambient + diffuse;
    } else {
        brightness = ambient;
    }

    vec3 finalRGB = texel.rgb * fragColor.rgb * brightness;

    finalColor = vec4(clamp(finalRGB, 0, 1), texel.a * fragColor.a);
}