#pragma once

#include <glad33/glad.h>
#include <GLFW/glfw3.h>

#include "helpers.h"
#include "shaders.h"
#include <iostream>
#include <stdint.h>

#define RSRCDIR ".\\01_gettingstarted\\"
#define RSRC(A) RSRCDIR##A

int triangle();
int rectangle();
int multitris();
