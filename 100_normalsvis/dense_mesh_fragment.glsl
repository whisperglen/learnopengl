#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;       // From Vertex Shader (interpolated)
in vec3 FragPos;      // World space position of the fragment

uniform sampler2D normalMap;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
    // 1. Retrieve normal from normal map
    // The texture stores normals in range [0, 1].
    vec3 textureNormal = texture(normalMap, TexCoords).rgb;
    
    // Transform normal vector to range [-1, 1]
    textureNormal = normalize(textureNormal * 2.0 - 1.0);

    // --- LIGHTING CALCULATIONS ---

    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0); // White light
  
    // Diffuse
    // We use the textureNormal instead of the mesh geometry normal
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(textureNormal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, textureNormal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);  

    // Combine results
    vec3 colorTex = texture(texture1, TexCoords).rgb;
    vec3 colorGray = vec3(0.7, 0.7, 0.7);
    vec3 result = (ambient + diffuse + specular) * colorTex;
    FragColor = vec4(result, 1.0);
}