#pragma once

#include <glad33/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

struct sample_data
{
	int initialised;
	GLuint *VAOs;
	int num_vao;
	GLuint* VBOs;
	int num_vbo;
	GLuint *EBOs;
	int num_ebo;
	GLuint* programs;
	int num_progs;

	sample_data(int num_vao, int num_vbo, int num_ebo, int num_progs) :
		initialised(0), VAOs(0), num_vao(num_vao), VBOs(0), num_vbo(num_vbo),
		EBOs(0), num_ebo(num_ebo), programs(0), num_progs(num_progs)
	{
	}

	int allocate()
	{
		int rtn = -1;

		do {
			if (num_vao)
			{
				VAOs = (GLuint*)malloc(num_vao * sizeof(GLuint));
				if (!VAOs) break;
				glGenVertexArrays(num_vao, VAOs);
			}
			if (num_vbo)
			{
				VBOs = (GLuint*)malloc(num_vbo * sizeof(GLuint));
				if (!VBOs) break;
				glGenBuffers(num_vbo, VBOs);
			}
			if (num_ebo)
			{
				EBOs = (GLuint*)malloc(num_ebo * sizeof(GLuint));
				if (!EBOs) break;
				glGenBuffers(num_ebo, EBOs);
			}
			if (num_progs)
			{
				programs = (GLuint*)malloc(num_progs * sizeof(GLuint));
				if (!programs) break;
				memset(programs, 0, num_progs * sizeof(GLuint));
			}

			rtn = 0;
		} while (0);

		return rtn;
	}
};

int loadShader(const char* filename, char** out);
int programCompilation(const char* vertex, const char* fragment, unsigned int& program);