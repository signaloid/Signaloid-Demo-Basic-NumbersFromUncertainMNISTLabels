/*
 *	Authored 2021, Phillip Stanley-Marbell.
 *	All rights reserved.
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions
 *	are met:
 *	*	Redistributions of source code must retain the above
 *		copyright notice, this list of conditions and the following
 *		disclaimer.
 *	*	Redistributions in binary form must reproduce the above
 *		copyright notice, this list of conditions and the following
 *		disclaimer in the documentation and/or other materials
 *		provided with the distribution.
 *	*	Neither the name of the author nor the names of its
 *		contributors may be used to endorse or promote products
 *		derived from this software without specific prior written
 *		permission.
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uxhw.h>

enum
{
	kMnist2NumberConstLabelsInDistribution	= 47,
} Mnist2NumberConst;

static void	loadDoubleDistFromPath(const char *  filename, int sampleCount, double *  returnValue);


int
main(int argc, char *  argv[])
{
	double	value, digit1621, digit1901, digit2462, digit2597, digit2654, digit3520, digit3558, digit5937;

	loadDoubleDistFromPath("1621.csv", kMnist2NumberConstLabelsInDistribution, &digit1621);
	loadDoubleDistFromPath("1901.csv", kMnist2NumberConstLabelsInDistribution, &digit1901);
	loadDoubleDistFromPath("2462.csv", kMnist2NumberConstLabelsInDistribution, &digit2462);
	loadDoubleDistFromPath("2597.csv", kMnist2NumberConstLabelsInDistribution, &digit2597);
	loadDoubleDistFromPath("2654.csv", kMnist2NumberConstLabelsInDistribution, &digit2654);
	loadDoubleDistFromPath("3520.csv", kMnist2NumberConstLabelsInDistribution, &digit3520);
	loadDoubleDistFromPath("3558.csv", kMnist2NumberConstLabelsInDistribution, &digit3558);
	loadDoubleDistFromPath("5937.csv", kMnist2NumberConstLabelsInDistribution, &digit5937);

	value	=	pow(10.0, 7.0)*digit1621 +
			pow(10.0, 6.0)*digit1901 +
			pow(10.0, 5.0)*digit2462 +
			pow(10.0, 4.0)*digit2597 +
			pow(10.0, 3.0)*digit2654 +
			pow(10.0, 2.0)*digit3520 +
			pow(10.0, 1.0)*digit3558 +
			pow(10.0, 0.0)*digit5937;

	UxHwDoublePrint(value);

	return 0;
}

void
loadDoubleDistFromPath(const char *  filename, int sampleCount, double *  returnValue)
{
	FILE *		fp;
	double *	samples;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("error: could not open input file");
		exit(EXIT_FAILURE);
	}

	printf("Number of samples from %s: %d\n", filename, sampleCount);

	samples = malloc(sampleCount * sizeof(double));
	if (samples == NULL)
	{
		perror("error: could not allocate memory for samples");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < sampleCount; i++)
	{
		fscanf(fp, "%lf\n", &samples[i]);
	}

	*returnValue = UxHwDoubleDistFromSamples(samples, sampleCount);

	if (fclose(fp) != 0)
	{
		perror("warning: could not close input file");
	}
	free(samples);

	return;
}
