#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "face.h"
#include <math.h>


double getArea(Vertex v1, Vertex v2, Vertex v3)
{//calculate the area of triangle face
	double a, b, c,s;
		a = calcSide(v1,v2);
		b = calcSide(v2,v3);
		c = calcSide(v3,v1);

		s = (a + b + c) / 2;

		return sqrt(s * (s - a) * (s - b) * (s - c));
}

double calcSide(Vertex v1, Vertex v2)
{//calculate distance between two point
	double ux = (double)v1.x - (double)v2.x;
	double uy = (double)v1.y - (double)v2.y;
	double uz = (double)v1.z - (double)v2.z;
	return sqrt(pow(ux, 2) + pow(uy, 2) + pow(uz, 2));
		
}