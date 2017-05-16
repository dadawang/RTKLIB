#include <stdlib.h>
#include <stdio.h>

#include "rtklib.h"

int main(int argc, char *argv[])
{
	FILE *fp_rover;
	int ret;

	raw_t ubx_raw;
	init_raw(&ubx_raw);

	fp_rover = fopen("rover.log", "rb");

	while (!feof(fp_rover))
		ret = input_ubxf(&ubx_raw, fp_rover);

	fclose(fp_rover);

	return 1;
}