#version 330

in vec3 fragNormal;
in vec4 fragColor;

uniform vec3 lightDir;
uniform int shadow;

out vec4 finalColor;

void main() {
    float diffuse = max(dot(normalize(fragNormal), normalize(lightDir)), -0.065);

    float ambient = 0.2;

    float brightness;
    if (shadow == 0) {
        brightness = ambient + diffuse;
    } else {
        brightness = ambient;
    }

    vec3 finalRGB = fragColor.rgb * brightness;

    finalColor = vec4(clamp(finalRGB, 0, 1), fragColor.a);
}