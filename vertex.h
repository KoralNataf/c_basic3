#pragma once
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	float x; // Coordinates of Vertex
	float y;
	float z;
} Vertex;

int countVertexInLine(char* line);

void copyTransformVertex(FILE* fsrc, FILE* fdst, char* line);