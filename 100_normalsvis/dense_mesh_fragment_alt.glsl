#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;       // From Vertex Shader (interpolated)
in vec3 FragPos;      // World space position of the fragment

uniform sampler2D normalMap;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D texture1;

void main()
{
    vec3 fdx = dFdx(FragPos); // Rate of change in X
    vec3 fdy = dFdy(FragPos); // Rate of change in Y
    vec3 derivedNormal = normalize(cross(fdx, fdy)); // The actual physical normal

    // --- LIGHTING CALCULATIONS ---

    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0); // White light
  
    // Diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(derivedNormal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, derivedNormal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);  

    // Combine results
    vec3 colorTex = texture(texture1, TexCoords).rgb;
    vec3 colorGray = vec3(0.7, 0.7, 0.7);
    vec3 result = (ambient + diffuse + specular) * colorGray;
    FragColor = vec4(result, 1.0);
}