
#include "getting_started.h"


static int basic();

int call_loop_unit1(int& selection)
{
	int retcode = 0;

	void* ptrs[] =
	{
		basic,
		triangle,
		rectangle,
		multitris,
		0
	};

	void* fcn = basic;
	for (int i = 0; ptrs[i] && i <= selection; i++)
	{
		fcn = ptrs[i];
	}

	retcode = ((int(*)())fcn)();

	return retcode;
}

static int basic()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	return 0;
}

