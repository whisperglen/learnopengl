#pragma once

#include <glad33/glad.h>
#include <GLFW/glfw3.h>

#include "helpers.h"
#include "shaders.h"
#include <iostream>
#include <stdint.h>

#define RSRCDIR ".\\01_gettingstarted\\"
#define RSRC(A) RSRCDIR##A

int basic();

int triangle();
int rectangle();
int multitris();

int color();
int uniform();
int attributes();
int texture();
int transformations();

#ifdef GETTING_STARTED_DATA

static void* getting_started_ptrs[] =
{
	basic,
	triangle,
	rectangle,
	multitris,
	color,
	uniform,
	attributes,
	texture,
	transformations,
	0
};

#endif