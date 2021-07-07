#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "vertex.h"

int countVertexInLine(char* line)
{//count the number of Vertex in line
	int count = 0;
	for (int i = 0; i < strlen(line); i++)
		if (line[i] == ' ')
			count++;

	return count;
}

void copyTransformVertex(FILE* fsrc, FILE* fdst, char* line)
{//copy vertex after transformation
	float x, y, z;
	int num = sscanf(line, "%*c %f %f %f", &x, &y, &z);
	x *= 0.3;
	fprintf(fdst, "v   %f	%f	%f\n", x, y, z);
}