
#include "getting_started.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb/stb_image.h"
#include <math.h>

// 0 VAOs, 2 VBOs, 2 EBOs, 0 Shader Programs (Fixed-Function), 2 Textures
struct sample_data_arb vboebo_sample(0, 2, 2, 0, 2);

// --- Data Structures ---
struct Vertex {
    float x, y, z;
    float u1, v1; // Base texture
    float u2, v2; // Lightmap texture
};

#if 0
// Simplified geometry (8 vertices for a cube, 5 for a pyramid) to test EBOs.
// Note: Texture mapping will wrap weirdly on shared vertices, but it validates the EBO pipeline.
Vertex cubeVertices[] = {
    {-1, -1,  1,  0, 0,  0, 0}, { 1, -1,  1,  1, 0,  1, 0},
    { 1,  1,  1,  1, 1,  1, 1}, {-1,  1,  1,  0, 1,  0, 1},
    {-1, -1, -1,  1, 0,  1, 0}, { 1, -1, -1,  0, 0,  0, 0},
    { 1,  1, -1,  0, 1,  0, 1}, {-1,  1, -1,  1, 1,  1, 1}
};

unsigned int cubeIndices[] = {
    0, 1, 2, 2, 3, 0, // Front
    1, 5, 6, 6, 2, 1, // Right
    7, 6, 5, 5, 4, 7, // Back
    4, 0, 3, 3, 7, 4, // Left
    4, 5, 1, 1, 0, 4, // Bottom
    3, 2, 6, 6, 7, 3  // Top
};

Vertex pyramidVertices[] = {
    { 0.0f,  1.0f,  0.0f,  0.5f, 1.0f,  0.5f, 1.0f}, // Top
    {-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, 0.0f}, // Front-Left
    { 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  1.0f, 0.0f}, // Front-Right
    { 1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  1.0f, 1.0f}, // Back-Right
    {-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, 1.0f}  // Back-Left
};

unsigned int pyramidIndices[] = {
    0, 1, 2, // Front
    0, 2, 3, // Right
    0, 3, 4, // Back
    0, 4, 1, // Left
    1, 4, 3, 3, 2, 1 // Base
};
#else
// Each face has its own vertices because a shared position can require
// different texture coordinates on different faces.
Vertex cubeVertices[] = {
    // Front (+Z)
    {-1, -1,  1,  0, 0,  0, 0}, { 1, -1,  1,  1, 0,  1, 0},
    { 1,  1,  1,  1, 1,  1, 1}, {-1,  1,  1,  0, 1,  0, 1},
    // Right (+X)
    { 1, -1,  1,  0, 0,  0, 0}, { 1, -1, -1,  1, 0,  1, 0},
    { 1,  1, -1,  1, 1,  1, 1}, { 1,  1,  1,  0, 1,  0, 1},
    // Back (-Z)
    { 1,  1, -1,  0, 0,  0, 0}, {-1,  1, -1,  1, 0,  1, 0},
    {-1, -1, -1,  1, 1,  1, 1}, { 1, -1, -1,  0, 1,  0, 1},
    // Left (-X)
    {-1, -1, -1,  0, 0,  0, 0}, {-1, -1,  1,  1, 0,  1, 0},
    {-1,  1,  1,  1, 1,  1, 1}, {-1,  1, -1,  0, 1,  0, 1},
    // Bottom (-Y)
    {-1, -1, -1,  0, 0,  0, 0}, { 1, -1, -1,  1, 0,  1, 0},
    { 1, -1,  1,  1, 1,  1, 1}, {-1, -1,  1,  0, 1,  0, 1},
    // Top (+Y)
    {-1,  1,  1,  0, 0,  0, 0}, { 1,  1,  1,  1, 0,  1, 0},
    { 1,  1, -1,  1, 1,  1, 1}, {-1,  1, -1,  0, 1,  0, 1}
};

unsigned int cubeIndices[] = {
    0, 1, 2, 2, 3, 0,       // Front
    4, 5, 6, 6, 7, 4,       // Right
    8, 9, 10, 10, 11, 8,    // Back
    12, 13, 14, 14, 15, 12, // Left
    16, 17, 18, 18, 19, 16, // Bottom
    20, 21, 22, 22, 23, 20  // Top
};

Vertex pyramidVertices[] = {
    // Front (+Z)
    { 0.0f,  1.0f,  0.0f,  0.5f, 1.0f,  0.5f, 1.0f},
    {-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, 0.0f},
    { 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  1.0f, 0.0f},
    // Right (-X to -Z)
    { 0.0f,  1.0f,  0.0f,  0.5f, 1.0f,  0.5f, 1.0f},
    { 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, 0.0f},
    { 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  1.0f, 0.0f},
    // Back (-Z)
    { 0.0f,  1.0f,  0.0f,  0.5f, 1.0f,  0.5f, 1.0f},
    { 1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  0.0f, 0.0f},
    {-1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  1.0f, 0.0f},
    // Left (-X)
    { 0.0f,  1.0f,  0.0f,  0.5f, 1.0f,  0.5f, 1.0f},
    {-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  0.0f, 0.0f},
    {-1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  1.0f, 0.0f},
    // Base (-Y)
    {-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, 0.0f},
    {-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, 1.0f},
    { 1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  1.0f, 1.0f},
    { 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  1.0f, 0.0f}
};

unsigned int pyramidIndices[] = {
    0, 1, 2,       // Front
    3, 4, 5,       // Right
    6, 7, 8,       // Back
    9, 10, 11,     // Left
    12, 13, 14, 14, 15, 12 // Base
};
#endif



static int vboebo_do_init()
{
    vboebo_sample.allocate();

    // --- Texture Loading ---
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data;

    // Load Base/Diffuse Texture
    data = stbi_load(".\\textures\\tileable3c.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, vboebo_sample.textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (nrChannels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
        if(glGenerateMipmap) glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }

    // Load Lightmap Texture
    data = stbi_load(".\\textures\\snow1.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, vboebo_sample.textures[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (nrChannels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
        if (glGenerateMipmap) glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }

    // --- Geometry Buffers ---
    // Cube VBO & EBO
    glBindBufferARB(GL_ARRAY_BUFFER, vboebo_sample.VBOs[0]);
    glBufferDataARB(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, vboebo_sample.EBOs[0]);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // Pyramid VBO & EBO
    glBindBufferARB(GL_ARRAY_BUFFER, vboebo_sample.VBOs[1]);
    glBufferDataARB(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);

    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, vboebo_sample.EBOs[1]);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramidIndices), pyramidIndices, GL_STATIC_DRAW);

    vboebo_sample.initialised = 1;

    return 0;
}

static int idx_cube = 0;
static int idx_pyramid = 1;

int vbo_ebo()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if (!vboebo_sample.initialised)
    {
        RET_ON_FAIL(vboebo_do_init());
    }

    glEnable(GL_DEPTH_TEST);

    // The fixed-function pipeline has no shader uniforms for the camera
    // matrices. Install the same camera view and projection used by the
    // shader-based examples on the compatibility profile matrix stacks.
    const glm::mat4 viewMatrix = getViewMatrix();
    const glm::mat4 projectionMatrix = getProjMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    glMatrixMode(GL_MODELVIEW);

    // Setup Multitexturing States
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, vboebo_sample.textures[0]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, vboebo_sample.textures[1]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // Blend lightmap

    // Enable Client States
    glEnableClientState(GL_VERTEX_ARRAY);
    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE1);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Calculate pulse scale
    float scale = 1.0f + 0.2f * sin(getTime() * 3.0f);

    // === DRAW CUBE (LEFT) ===
    glLoadMatrixf(glm::value_ptr(viewMatrix));
    glTranslatef(-2.0f, 0.0f, -6.0f); // Move left and into screen
    glRotatef(getTime() * 50.0f, 1.0f, 1.0f, 0.0f); // Spin
    glScalef(scale, scale, scale); // Pulse

    glBindBufferARB(GL_ARRAY_BUFFER, vboebo_sample.VBOs[idx_cube]);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);
    glClientActiveTexture(GL_TEXTURE0);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glClientActiveTexture(GL_TEXTURE1);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)(5 * sizeof(float)));

    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, vboebo_sample.EBOs[idx_cube]);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // === DRAW PYRAMID (RIGHT) ===
    glLoadMatrixf(glm::value_ptr(viewMatrix));
    glTranslatef(2.0f, 0.0f, -6.0f); // Move right and into screen
    glRotatef(-getTime() * 50.0f, 0.0f, 1.0f, 1.0f); // Spin opposite
    glScalef(scale, scale, scale); // Pulse

    glBindBufferARB(GL_ARRAY_BUFFER, vboebo_sample.VBOs[idx_pyramid]);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);
    glClientActiveTexture(GL_TEXTURE0);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glClientActiveTexture(GL_TEXTURE1);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)(5 * sizeof(float)));

    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, vboebo_sample.EBOs[idx_pyramid]);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

    // Cleanup States
    glDisableClientState(GL_VERTEX_ARRAY);
    glClientActiveTexture(GL_TEXTURE0);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE1);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);


    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_DEPTH_TEST);

    // Leave the fixed-function matrix state in a neutral state for the next
    // sample selected by the application.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return 0;
}
