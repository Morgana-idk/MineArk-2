
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
    vec3 normal = normalize(fragNormal);
    vec3 light = normalize(-lightDir);

    // Iluminação direta
    float diffuse = max(dot(normal, light), 0.0);

    // Cor original do bloco
    vec4 texelColor = texture(texture0, fragTexCoord) * fragColor * colDiffuse;

    // Transformar a posição para o espaço da luz
    vec4 lightSpace = lightVP * vec4(fragPosition, 1.0);

    lightSpace.xyz /= lightSpace.w;
    lightSpace.xyz = lightSpace.xyz * 0.5 + 0.5;

    vec3 projected = lightSpace.xyz;

    float shadow = 0.0;

    // Verificar se o ponto está dentro do mapa da luz
    if (
        projected.x >= 0.0 && projected.x <= 1.0 &&
        projected.y >= 0.0 && projected.y <= 1.0 &&
        projected.z >= 0.0 && projected.z <= 1.0
    )
    {
        float bias = max(
            0.0005 * (1.0 - dot(normal, light)),
            0.00005
        );

        vec2 texelSize = vec2(1.0 / float(shadowMapResolution));

        // PCF: suavização das bordas da sombra
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                float depth = texture(
                    shadowMap,
                    projected.xy + vec2(x, y) * texelSize
                ).r;

                if (projected.z - bias > depth)
                    shadow += 1.0;
            }
        }

        shadow /= 9.0;
    }

    // Iluminação ambiente + iluminação direta
    vec3 lighting =
        ambient.rgb +
        lightColor.rgb * diffuse * (1.0 - shadow);

    finalColor = vec4(texelColor.rgb * lighting, texelColor.a);
}
