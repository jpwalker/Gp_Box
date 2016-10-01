/*
 * Corr_Func.c
 *
 *  Created on: Oct 1, 2016
 *      Author: jpwalker
 */

#include <stdlib.h>
#include "Corr_Func.h"

corr_func * corr_func_init(const unsigned long num)
{
	corr_func* ret = (corr_func*) malloc(sizeof(corr_func));
	ret->num = num;
	ret->r = (double*) calloc(num, sizeof(double));
	ret->xi = (double*) calloc(num, sizeof(double));
	ret->RR = (double*) calloc(num, sizeof(double));
	ret->DD = (double*) calloc(num, sizeof(double));
	return ret;
}

void corr_func_destructor(corr_func* pointer)
{
	free(pointer->r);
	free(pointer->xi);
	free(pointer->RR);
	free(pointer->DD);
	free(pointer);
}

void corr_func_writefile(FILE * file, corr_func* data, const unsigned long num)
{
	if (ferror(file) != 0) perror(EFILE);
	if (data->num != 0)
	{
		fprintf(file, HEADER_FMT, HEADER, num * (num - 1) / 2);
		for (int i = 0; i < data->num; i++)
		{
			fprintf(file, DATA_FMT, data->r[i], data->xi[i],
					data->DD[i], data->RR[i]);
			if (i != num - 1)
			{
				fprintf("\n");
			}
		}
		if (ferror(file) !=0) perror(EFILE);
	}
	else fprintf(stderr, WARN "No data in passed corr_func.");
}
