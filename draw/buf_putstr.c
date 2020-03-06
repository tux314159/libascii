
#include "../base.h"
void buf_putstr(char *str)
{
	str_append(_gls->abuf, str, strlen(str));
	return;
}
