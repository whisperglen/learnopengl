
//if the assert fails the type of optimus enable variable may need to be changed; originally it was DWORD
static char assert_size_of_long_type[sizeof(unsigned long) == 4];
static char assert_size_of_int_type[sizeof(int) == 4];
_declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;