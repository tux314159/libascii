#include <stdio.h>
#include "api.h"

int main(void)
{
	startraw();
	curs_mov(10, 10);
	buf_putstr("Hi!\n");
	buf_write();
	endraw();
}
