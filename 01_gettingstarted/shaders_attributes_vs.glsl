#version 330 core
layout(location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout(location = 1) in vec3 aColor; // the color variable has attribute position 1

uniform float offsetPos; // we set this variable in the OpenGL code.

out vec3 ourColor; // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos.x + offsetPos, aPos.y, aPos.z, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}