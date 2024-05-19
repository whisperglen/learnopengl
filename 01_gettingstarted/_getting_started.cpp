
#define GETTING_STARTED_DATA
#include "getting_started.h"


int call_loop_unit1(int& selection)
{
	int retcode = 0;

	void* fcn = basic;
	for (int i = 0; getting_started_ptrs[i] && i <= selection; i++)
	{
		fcn = getting_started_ptrs[i];
	}

	retcode = ((int(*)())fcn)();

	return retcode;
}

int basic()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	return 0;
}

