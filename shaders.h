#pragma once

#include <glad33/glad.h>
#include <GLFW/glfw3.h>

int loadShader(const char* filename, char** out);
int programCompilation(const char* vertex, const char* fragment, unsigned int& program);