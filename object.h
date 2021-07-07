#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "vertex.h"
#include "face.h"

typedef struct {
	// Array of all Vertexes
	int numberOfVertexes;
	 Vertex* vertexes;
	// Array of all Faces
	int  numberOfFaces;
	Face* faces;
} Object;

void transformObject(char* originalObjectFileName, char* deformedObjectFileName);
Object* createObject(char* filename);
void countVF(Object* o, FILE* f);
void addVertexesAndFaces(Object* o, FILE* f);
void blank(char* sentence);
void addFace(Object* o, char* line,int num);
void printFaces(Object* ptr, void* numberOfTriangularFaces);
void printVertexes(Object* ptr, void* numberOfVertexes);
void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces);
void freeObject(Object* ob);
Object* loadBinObject(FILE* f);
void saveBinObject(Object* ob, FILE* f);