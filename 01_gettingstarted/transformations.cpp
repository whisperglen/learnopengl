
#include "getting_started.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;
using namespace std;

int transformations()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	static bool ran_once = false;
	if (ran_once)
		return 0;
	else ran_once = true;


	vec4 vec(1.0, 0.0, 0.0, 1.0);
	mat4 trans = mat4(1.0);
	trans = translate(trans, vec3(1.0, 1.0, 0.0));
	vec = trans * vec;
	cout << vec.x << vec.y << vec.z << endl;

	trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	return 0;
}