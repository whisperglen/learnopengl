#version 330 core
layout (location = 0) in vec3 aPos;       // Vertex Position
layout (location = 1) in vec3 aNormal;    // Vertex Normal (Mesh)
layout (location = 2) in vec2 aTexCoords; // Texture Coordinates

// Uniforms passed from C++
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform sampler2D normalMap; // The texture
uniform float displacementStrength; // Factor to scale the deformation

out vec2 TexCoords;
out vec3 Normal; // Pass to fragment shader for lighting
out vec3 FragPos;

void main()
{
    TexCoords = aTexCoords;

    // 1. Sample the Normal Map
    // Texture values are [0, 1]. We need vectors in [-1, 1].
    vec3 rawColor = vec3(texture(normalMap, aTexCoords).rg, 0);
    vec3 mappedNormal = normalize(rawColor * 2.0 - 1.0);

    // 2. Calculate the Displacement
    // OPTION A: Vector Displacement (Move along the vector from the map)
    // Useful if your map contains specific directional data (RGB = XYZ)
    vec3 displacement = mappedNormal * displacementStrength;

    // OPTION B: Height Displacement (Move along the MESH normal)
    // If you just want to spike the mesh based on texture intensity
    //float intensity = length(rawColor); 
    //vec3 displacement = aNormal * intensity * displacementStrength;

    // 3. Apply to Vertex Position
    vec3 finalPos = aPos + displacement;

    // 4. Standard MVP transformation
    gl_Position = projection * view * model * vec4(finalPos, 1.0);
    
    // Pass normal to frag shader (You might want to update this too if deforming heavily)
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Calculate World Position for Lighting
    FragPos = vec3(model * vec4(finalPos, 1.0));
}