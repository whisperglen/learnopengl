#pragma once

int loadShader(const char* filename, char** out);
int programCompilation(const char* vertex, const char* fragment, unsigned int& program);