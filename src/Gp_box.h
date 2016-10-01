/*
 * Gp_box.h
 *
 *  Created on: Sep 22, 2016
 *      Author: jpwalker
 */

#ifndef SRC_GP_BOX_H_
#define SRC_GP_BOX_H_

#include <glib.h>

#define PI 3.14159265358979323846264338327950288419716939937510
#define SQ2 1.41421356237309504880168872420969807856967187537694
#define SQ3 1.73205080756887729352744634150587236694280525381038

// Default arguments
#define RMIN 0
#define RMAX 100
#define RNUM 100
#define L 100

// Error Messages
#define EARG "Input Error: %s\n"
#define EMEM "Memory Error: %s\n"

// Functions arg_parse.c
GOptionContext *  setup_arg_parse(void);

// Functions Gp_box.c
void parse_arguments(int, char **);
double calculate_box_RR(gsl_histogram *);

#endif /* SRC_GP_BOX_H_ */
