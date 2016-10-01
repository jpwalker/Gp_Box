/*
 * argument_parse.c
 *
 *  Created on: Sep 29, 2016
 *      Author: jpwalker
 */

#include <glib.h>
#include "Gp_box.h"

extern gdouble rlim[2];
extern gint rnum;
extern gdouble box_L;
extern gchar ** filename;


// ARGUMENT DEFAULTS
gdouble rlim[2] = {RMIN, RMAX};
gint rnum = RNUM;
gdouble box_L = L;
gchar ** filename = NULL;

// Main Group and Context's strings
static const gchar * short_summary = "- create G_p(r) for a box geometry.";
static const gchar * summary = "Program calculates G_p(r), assuming periodic "
		"boundary conditions, for radial bins inside a box. Program uses the rad optional parameters";
static const gchar * description = "Created by Jean P. Walker Soler";

// Radial Group's strings
static const gchar * radial_group_name = "r";
static const gchar * radial_group_help = "Radial binning parameters.";
static const gchar * radial_group_det_help =  "Radial binning parameters used "
		"to create the radial bins for output.";

static const GOptionEntry radial_arg[] =
{
	{"min", 0, G_OPTION_FLAG_NONE, G_OPTION_ARG_DOUBLE, &rlim[0],
		"Left edge of smallest radial bin.", "r_min [0]"},
	{"max", 0, G_OPTION_FLAG_NONE, G_OPTION_ARG_DOUBLE, &rlim[1],
		"Right edge of largest radial bin.", "r_max [100]" },
	{"num", 0, G_OPTION_FLAG_NONE, G_OPTION_ARG_INT64, &rnum,
		"Number of radial bins used.", "r_num [100]"},
	{NULL}};

static const GOptionEntry main_arg[] =
{
	{"box", 0x4C, G_OPTION_FLAG_IN_MAIN, G_OPTION_ARG_DOUBLE, &box_L,
		"Side length of box (cube).", "L [100]"},
	{G_OPTION_REMAINING, 0, G_OPTION_FLAG_IN_MAIN,
			G_OPTION_ARG_FILENAME_ARRAY, &filename, "Output file to ", "Output_File"},
	{NULL}
};

GOptionContext * setup_arg_parse() {
	// Setup context
	GOptionContext * context = g_option_context_new(short_summary);
	g_option_context_set_summary (context, summary);
	g_option_context_set_description (context, description);
	g_option_context_add_main_entries(context, main_arg, NULL);

	// Creating group
	GOptionGroup *radial = g_option_group_new(radial_group_name,
			radial_group_help, radial_group_det_help, NULL, NULL);
	g_option_group_add_entries(radial, radial_arg);
	g_option_context_add_group(context, radial);
	return context;
}
