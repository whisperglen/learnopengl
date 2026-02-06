#define NORMALS_VIS_DATA
#include "normals_vis.h"


int call_loop_unit100(int& selection)
{
	int retcode = 0;

	int i;
	void* fcn = basic;
	for (i = 0; normals_vis_ptrs[i] && (i <= selection || selection < 0); i++)
	{
		fcn = normals_vis_ptrs[i];
	}
	selection = i > 0 ? i - 1 : 0;
	retcode = ((int(*)())fcn)();

	return retcode;
}
