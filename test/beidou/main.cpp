#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "rtklib.h"

int main(int argc, char *argv[])
{
	FILE *fp_rover, *fp_res;
	int ret = -1;
	char msg[4096];

	double plh[3] = { 0.0 };

	prcopt_t opt = prcopt_default;
	sol_t sol = { 0 };
	sol.rr[0] = -2847955.14736368;
	sol.rr[1] = 4661263.4105009502;
	sol.rr[2] = 3281798.86141616;
	//init position 31.1673468832 121.4242428504

	raw_t ubx_raw;
	init_raw(&ubx_raw);

	fp_rover = fopen("rover.log", "rb");
	fp_res = fopen("single_point_sol.txt", "wt");

	while (!feof(fp_rover)) {
		ret = input_ubxf(&ubx_raw, fp_rover);
		
		if (ret == 1) {
			double gpst = time2gpst(ubx_raw.obs.data[0].time, NULL);
			printf("Processing epoch %.3f\n", gpst);

			if (fabs(gpst - 346218.0) < 0.1){
				printf("The 1st epoch to have solution.\n");
			}

			if (pntpos(ubx_raw.obs.data, ubx_raw.obs.n, &(ubx_raw.nav), &opt, &sol, NULL, NULL, msg)) {
				ecef2pos(sol.rr, plh);
				printf("Solution: lat - %.10f, lon - %.10f, hgt - %.3f\n", plh[0]*R2D, plh[1]*R2D, plh[2]);
				fprintf(fp_res, "%.3f\t%.10f\t%.10f\t%.3f\n", gpst, plh[0] * R2D, plh[1] * R2D, plh[2]);
			}

		}
		/*switch (ret) {
		case -1:

			break;
		case 0:

			break;
		case 1:

			break;
		}*/

	}
		

	fclose(fp_rover);
	fclose(fp_res);

	return 1;
}