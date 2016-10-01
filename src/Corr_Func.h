/*
 * Corr_Func.h
 *
 *  Created on: Oct 1, 2016
 *      Author: jpwalker
 */

#ifndef CORR_FUNC_H_
#define CORR_FUNC_H_

#include <stdio.h>

#define HEADER "radii,\tCF(r),\tDD(r),\tRR(r)"
#define HEADER_FMT "%s\n%ul\n"
#define DATA_FMT "%d,\t%d,\t%d,\t%d"

// Error Messages
#define WARN "Warning: %s\n"
#define EFILE "File I/O Error"

typedef struct corr_func
{
	const unsigned long long num;
	double * r;
	double * xi;
	double * RR;
	double * DD;
} corr_func;

// Functions
corr_func* corr_func_init(const unsigned long);
void corr_func_destructor(corr_func *);
void corr_func_writefile(FILE *, corr_func *, const unsigned long);

#endif /* CORR_FUNC_H_ */
