#pragma once

#include <glad33/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "helpers.h"
#include "shaders.h"
#include <iostream>
#include <stdint.h>

#define RSRCDIR ".\\100_normalsvis\\"
#define RSRC(A) RSRCDIR##A

int basic();

int dense_mesh();

#ifdef NORMALS_VIS_DATA

static void* normals_vis_ptrs[] =
{
	dense_mesh,
	0
};

#endif