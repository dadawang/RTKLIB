#include <stdlib.h>
#include <stdio.h>

#include "rtklib.h"

int main(int argc, char *argv[])
{
	FILE *fp_rover;
	int ret;
	char msg[4096];

	raw_t ubx_raw;
	init_raw(&ubx_raw);

	fp_rover = fopen("rover.log", "rb");

	while (!feof(fp_rover))
		ret = input_ubxf(&ubx_raw, fp_rover);

	prcopt_t opt = prcopt_default;
	sol_t sol = { 0 };
	sol.rr[0] = -2847955.14736368;
	sol.rr[1] = 4661263.4105009502;
	sol.rr[2] = 3281798.86141616;
//init position 31.1673468832 121.4242428504

	pntpos(ubx_raw.obs.data, ubx_raw.obs.n, &(ubx_raw.nav), &opt, &sol, NULL, NULL, msg);

	fclose(fp_rover);

	return 1;
}