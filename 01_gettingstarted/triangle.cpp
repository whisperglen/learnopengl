
#include "getting_started.h"

static int tri_init_done = 0;
static unsigned int triangle_program = UINT_MAX;
static unsigned int triangle_VAO = UINT_MAX;
static int triangle_do_init();

int triangle()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!tri_init_done)
		RET_ON_FAIL(triangle_do_init());

	glUseProgram(triangle_program);
	glBindVertexArray(triangle_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	return 0;
}

static int triangle_do_init()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	programCompilation(RSRC("triangle_vs.glsl"), RSRC("triangle_fs.glsl"), triangle_program);

	triangle_VAO = VAO;
	tri_init_done = 1;

	return 0;
}

static int rect_init_done = 0;
static unsigned int rectangle_program = UINT_MAX;
static unsigned int rectangle_VAO = UINT_MAX;
static int rectangle_do_init();

int rectangle()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!rect_init_done)
		RET_ON_FAIL(rectangle_do_init());


	glUseProgram(rectangle_program);
	glBindVertexArray(rectangle_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	return 0;
}

static int rectangle_do_init()
{
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	programCompilation(RSRC("triangle_vs.glsl"), RSRC("triangle_fs.glsl"), rectangle_program);

	rectangle_VAO = VAO;
	rect_init_done = 1;

	return 0;
}

GLuint multitris_program1;
GLuint multitris_program2;
GLuint multitris_VAO1;
GLuint multitris_VAO2;
GLuint multitris_EBO1;
GLuint multitris_EBO2;
int multitris_init_done = 0;
static int multitris_do_init();

int multitris()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!multitris_init_done)
		RET_ON_FAIL(multitris_do_init());

	glUseProgram(multitris_program1);
	glBindVertexArray(multitris_VAO1);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, multitris_EBO1);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glUseProgram(multitris_program2);
	glBindVertexArray(multitris_VAO2);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, multitris_EBO2);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	return 0;
}

static int multitris_do_init()
{
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f   // top left 
	};
	float vertices2[] = {
		0.3f,  0.3f, 0.0f,  // top right
		0.3f, -0.3f, 0.0f,  // bottom right
	   -0.3f, -0.3f, 0.0f,  // bottom left
	   -0.3f,  0.3f, 0.0f   // top left 
	};
	unsigned int indices1[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
	};
	unsigned int indices2[] = {  // note that we start from 0!
		1, 2, 3    // second triangle
	};

	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);

	unsigned int VBO1;
	glGenBuffers(1, &VBO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO1;
	glGenBuffers(1, &EBO1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glBindVertexArray(0);

	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);

	unsigned int VBO2;
	glGenBuffers(1, &VBO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	unsigned int EBO2;
	glGenBuffers(1, &EBO2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	programCompilation(RSRC("triangle_vs.glsl"), RSRC("triangle_fs.glsl"), multitris_program1);
	programCompilation(RSRC("triangle_vs.glsl"), RSRC("triangle_color2_fs.glsl"), multitris_program2);

	glBindVertexArray(0);

	multitris_VAO1 = VAO1;
	multitris_EBO1 = EBO1;
	multitris_VAO2 = VAO2;
	multitris_EBO2 = EBO2;
	multitris_init_done = 1;

	return 0;
}
