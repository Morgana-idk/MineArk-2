#version 330

in vec3 fragNormal;
in vec4 fragColor;

uniform vec3 lightDir;

out vec4 finalColor;

void main() {
    float diffuse = max(dot(normalize(fragNormal), normalize(lightDir)), 0);

    float ambient = 0.2;

    float brightness = ambient + diffuse;

    vec3 finalRGB = fragColor.rgb * brightness;

    finalColor = vec4(clamp(finalRGB, 0, 1), fragColor.a);
}