#pragma once

inline int pos(int a)
{
	return a >= 0 ? a : 0;
}

#define POS(X) pos((int)(X))

inline int min(int a, int b)
{
	return a < b ? a : b;
}

inline int max(int a, int b)
{
	return a > b ? a : b;
}

#define RET_ON_FAIL(X) do { int res = (X); if(0 != res) { return res; } } while(0)
