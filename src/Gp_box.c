/*
 * Gp_box.c
 *
 *  Created on: Sep 22, 2016
 *      Author: jpwalker
 */

#include <gsl/gsl_histogram.h>
#include <glib.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Gp_box.h"

extern gdouble rlim[2];
extern gint rnum;
extern gdouble box_L;
extern gchar ** filename;

double calculate_box_RR(gsl_histogram * RR)
{
	const double alpha = box_L / 2.;
	const double box_vol = 8. * pow(alpha, 3.);
	for (unsigned int i = 0; i < rnum; i++)
	{
		double vol[2];
		double r[2] = {0, 0};
		gsl_histogram_get_range(RR, i, &r[0], &r[1]);
		double r_center = (r[1] + r[0]) / 2;
		for (unsigned int i = 0; i <= 1; i++)
		{
			if (r[i] <= alpha)
			{
				RR[i] = 4. / 3. * PI * pow(r[i], 3.);
			}
			else if (r[i] > alpha && r[i] <= alpha * SQ2)
			{
				RR[i] = 6. * alpha * PI * pow(r[i], 2.) - 8. * PI *
						pow(r[i], 3.) / 3.f - pow(alpha, 3.) * PI  * 2.;
			}
			else if (r[i] > SQ2 * alpha && r[i] < SQ3 * alpha)
			{
				RR[i] = 0. / 0.;
			}
			else
			{
				RR[i] = box_vol;
			}
		}
		gsl_histogram_accumulate(RR, r_center, (vol[1] - vol[0]) / box_vol);
	}
}

void parse_arguments(int argc, char ** argv)
{
	GOptionContext * context =  setup_arg_parse();
	GError * error;
	if (!g_option_context_parse(context, &argc, &argv, &error)) {
		fprintf(stderr, "Input Error: %s\n", error->message);
		exit(EXIT_FAILURE);
	}

	// Check inputed arguments
	if (rlim[0] >= rlim[1])
	{
		fprintf(stderr, EARG, "r_min should be greater than r_max.");
		exit(EXIT_FAILURE);
	}
	if (rnum <= 0)
	{
		fprintf(stderr, EARG, "r_num should be greater than 0.");
		exit(EXIT_FAILURE);
	}
	if (filename == NULL)
	{
		fprintf(stderr, EARG, "Please enter an output filename.");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char ** argv)
{
	parse_arguments(argc, argv);
	gsl_histogram * Gp;
	if ((Gp = gsl_histogram_alloc(rnum)) == NULL)
	{
		fprintf(stderr, EMEM, "Unable to allocate memory for radial bins");
		exit(EXIT_FAILURE);
	}
	gsl_histogram_set_ranges_uniform(Gp, rlim[0], rlim[1]);
	calculate_box_RR()
	gsl_histogram_free(Gp);
	return EXIT_SUCCESS;
}
