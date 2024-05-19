
#include "shaders.h"
#include <iostream>
#include <fstream>
#include "helpers.h"

static int checkShaderCompile(unsigned int shader);
static int checkProgramCompile(unsigned int program);

int programCompilation(const char* vertex, const char* fragment, unsigned int& program)
{
	char* shaderSource = 0;
	loadShader(vertex, &shaderSource);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	glCompileShader(vertexShader);

	RET_ON_FAIL(checkShaderCompile(vertexShader));

	loadShader(fragment, &shaderSource);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderSource, NULL);
	glCompileShader(fragmentShader);

	RET_ON_FAIL(checkShaderCompile(fragmentShader));

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	RET_ON_FAIL(checkProgramCompile(program));

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	free(shaderSource);

	return 0;
}

static int checkShaderCompile(unsigned int shader)
{
	int  success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (GL_TRUE != success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -5001;
	}
	return 0;
}

static int checkProgramCompile(unsigned int program)
{
	int  success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (GL_TRUE != success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -5002;
	}
	return 0;
}

int loadShader(const char* filename, char** out)
{
	int ret = 0;
	char* data = *out;

	std::ifstream file(filename, std::ios::binary);
	if (file.is_open())
	{
		// get length of file:
		file.seekg(0, file.end);
		int length = (int)file.tellg();
		file.seekg(0, file.beg);

		if (data == 0)
		{
			data = (char*)malloc(length + 1);
		}
		else
		{
			char* tmp = (char*)realloc(data, length + 1);
			if (tmp)
			{
				data = tmp;
			}
		}
		if (data == 0) return -1;
		//memset(data, 0, length + 1);

		file.read(data, length);
		std::streamsize bytes = file.gcount();
		if (bytes == length)
		{
			ret = 1;
		}

		data[min(POS(bytes), length)] = 0;
		*out = data;
	}

	return ret;
}