#pragma once

#include <stdlib.h>
#include <string.h>
#include <glad33/glad.h>
#include <GLFW/glfw3.h>

inline int pos(int a)
{
	return a >= 0 ? a : 0;
}

#define POS(X) pos((int)(X))

inline int min(int a, int b)
{
	return a < b ? a : b;
}

inline int max(int a, int b)
{
	return a > b ? a : b;
}

#define RET_ON_FAIL(X) do { int res = (X); if(0 != res) { return res; } } while(0)
#define RET_ON_FAIL_CLEANUP(X, Y) do { int res = (X); if(0 != res) { (Y); return res; } } while(0)

GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

struct sample_data
{
	int initialised;
	GLuint* VAOs;
	int num_vao;
	GLuint* VBOs;
	int num_vbo;
	GLuint* EBOs;
	int num_ebo;
	GLuint* programs;
	int num_progs;
	GLuint* textures;
	int num_tex;

	sample_data(int num_vao, int num_vbo, int num_ebo, int num_progs) :
		initialised(0), VAOs(0), num_vao(num_vao), VBOs(0), num_vbo(num_vbo),
		EBOs(0), num_ebo(num_ebo), programs(0), num_progs(num_progs),
		textures(0), num_tex(0)
	{
	}

	sample_data(int num_vao, int num_vbo, int num_ebo, int num_progs, int num_tex) :
		initialised(0), VAOs(0), num_vao(num_vao), VBOs(0), num_vbo(num_vbo),
		EBOs(0), num_ebo(num_ebo), programs(0), num_progs(num_progs),
		textures(0), num_tex(num_tex)
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
			if (num_tex)
			{
				textures = (GLuint*)malloc(num_tex * sizeof(GLuint));
				if (!textures) break;
				glGenTextures(num_tex, textures);
			}

			rtn = 0;
		} while (0);

		return rtn;
	}
};

int loadTexture(GLuint tex, GLint repeat, const char* file);
