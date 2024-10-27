
#include "getting_started.h"

struct sample_data color_sample(1, 1, 1, 1);

static int color_do_init()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	color_sample.allocate();

	glBindVertexArray(color_sample.VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, color_sample.VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	programCompilation(RSRC("shaders_vs.glsl"), RSRC("shaders_fs.glsl"), color_sample.programs[0]);

	color_sample.initialised = 1;

	return 0;
}

int color()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!color_sample.initialised)
	{
		RET_ON_FAIL(color_do_init());
	}

	glUseProgram(color_sample.programs[0]);
	glBindVertexArray(color_sample.VAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	return 0;
}

struct sample_data uniform_sample(1, 1, 1, 1);

static int uniform_do_init()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	uniform_sample.allocate();

	glBindVertexArray(uniform_sample.VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, uniform_sample.VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	programCompilation(RSRC("triangle_vs.glsl"), RSRC("shaders_uniform_fs.glsl"), uniform_sample.programs[0]);

	uniform_sample.initialised = 1;

	return 0;
}

int uniform()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!uniform_sample.initialised)
	{
		RET_ON_FAIL(uniform_do_init());
	}

	float timeValue = (float)glfwGetTime();
	float greenValue = (float)(sin(timeValue) / 2.0f) + 0.5f;

	glUseProgram(uniform_sample.programs[0]);
	int vertexColorLocation = glGetUniformLocation(uniform_sample.programs[0], "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glBindVertexArray(uniform_sample.VAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	return 0;
}

struct sample_data attributes_sample(1, 1, 1, 1);

static int attributes_do_init()
{
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	attributes_sample.allocate();

	glBindVertexArray(attributes_sample.VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, attributes_sample.VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	programCompilation(RSRC("shaders_attributes_vs.glsl"), RSRC("shaders_attributes_fs.glsl"), attributes_sample.programs[0]);

	attributes_sample.initialised = 1;

	return 0;
}

int attributes()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!attributes_sample.initialised)
	{
		RET_ON_FAIL(attributes_do_init());
	}

	float timeValue = (float)glfwGetTime();
	float posValue = (sin(timeValue) / 2.0f); //-0.5 .. 0.5

	glUseProgram(attributes_sample.programs[0]);
	int offsetPosLocation = glGetUniformLocation(attributes_sample.programs[0], "offsetPos");
	glUniform1f(offsetPosLocation, posValue);

	glBindVertexArray(attributes_sample.VAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	return 0;
}