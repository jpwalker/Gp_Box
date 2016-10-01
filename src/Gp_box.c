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
#include "Corr_Func.h"

extern gdouble rlim[2];
extern gint rnum;
extern gdouble box_L;
extern gchar ** filename;

void calculate_box_RR(gsl_histogram * RR)
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
				vol[i] = 4.f / 3.f * PI * pow(r[i], 3.f);
			}
			else if (r[i] > alpha && r[i] <= alpha * SQ2)
			{
				vol[i] = 6.f * alpha * PI * pow(r[i], 2.f) - 8.f * PI *
						pow(r[i], 3.f) / 3.f - pow(alpha, 3.f) * PI  * 2.f;
			}
			else if (r[i] > SQ2 * alpha && r[i] < SQ3 * alpha)
			{
				vol[i] = 6.f * alpha * PI * pow(r[i], 2.f) - 8.f * PI *
						pow(r[i], 3.f) / 3.f - pow(alpha, 3.f) * PI  * 2.f;
				// Pre-calculations for numbers that will be used alot.
				double t1 = sqrt(r[i] * r[i] - alpha * alpha);
				double t2 = sqrt(r[i] * r[i] - 2.f * alpha * alpha);
				// Correction to formula from the case above.
				double correction =  PI / 6.f * pow(r[i], 3.f) + alpha / 6.f *
						(alpha * alpha - 3.f * r[i] * r[i]) * acos(alpha / t1) -
						pow(r[i], 3.f) / 3.f * atan(alpha * alpha / (r[i] * t2)) +
						pow(alpha, 4.f) / 3.f * t2 / t1 / t1 + alpha / 6.f *
						(alpha * alpha - 3.f * r[i] * r[i]) * atan(t2 / alpha) +
						alpha * alpha / 3.f * pow(t2, 3.f) / t1 / t1;
				vol[i] += 24.f * correction;
			}
			else
			{
				vol[i] = box_vol;
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
	calculate_box_RR(Gp);
	corr_func* corr_Gp = corr_func_init(rnum);

	gsl_histogram_free(Gp);
	return EXIT_SUCCESS;
}
