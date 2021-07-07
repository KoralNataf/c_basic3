#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "object.h"
#define MAX_LINE 250

void transformObject(char* originalObjectFileName, char* deformedObjectFileName)
{//copy the file and stansform the vertexes
	FILE* fsrc = fopen(originalObjectFileName,"r");
	FILE* fdst= fopen(deformedObjectFileName,"w");
	if (!fsrc || !fdst)
	{
		_fcloseall();
		printf("Failed opening file...");
		return;
	}
	while (!feof(fsrc))
	{
		char line[MAX_LINE];
		if(fgets(line, MAX_LINE, fsrc)== NULL) break;
	
			if (line[0] == 'v' && line[1] == ' ')
				copyTransformVertex(fsrc,fdst,line);
			else
				fprintf(fdst,"%s", line);
	}
	_fcloseall();
}

Object* createObject(char* filename)
{//create object from file ditailes
	Object* o = (Object*)malloc(sizeof(Object));
	if (!o) return NULL;
	FILE* f = fopen(filename, "r");
	if (!f)
	{
		printf("Failed opening file...");
		return NULL;
	}
	countVF(o,f);
	o->vertexes = (Vertex*)calloc(o->numberOfVertexes , sizeof(Vertex));
	if (!o->vertexes) return NULL;
	o->faces = (Face*)calloc(o->numberOfFaces , sizeof(Face));
	if (!o->faces) return NULL;
	addVertexesAndFaces(o, f);
	fclose(f);
	
	return o;
}

void countVF(Object* o,FILE* f)
{//count vertect && faces
	int numofV = 0, numofF = 0;
	char line[MAX_LINE];
	while (!feof(f))
	{
		if(fgets(line, MAX_LINE, f)==NULL)
			break;
		if (line[0] == 'v' && line[1] == ' ')
			numofV++;
		else if (line[0] == 'f' && line[1] == ' ')
			numofF++;
	}
	o->numberOfVertexes = numofV;
	o->numberOfFaces = numofF;
	fseek(f, 0, SEEK_SET);
}

void addVertexesAndFaces(Object* o, FILE* f)
{//adding vertexes and faces to the object from file
	char line[MAX_LINE];
	int num,iV=0,iF=0;
	while(!feof(f))
	{
		if(fgets(line, MAX_LINE, f)== NULL)
			break;
		if (line[0] == 'v'&& line[1]==' ')
		{
			num = sscanf(line, "%*c %f %f %f", &o->vertexes[iV].x, &o->vertexes[iV].y, &o->vertexes[iV].z);
			iV++;
		}
		else if (line[0] == 'f' && line[1] == ' ')
		{
			blank(line);
		addFace(o, line,iF);
		iF++;
		}	
	}
}

void blank(char* line) {//this methos reduce the spaces in the line
	int i = 0, j = 0, first = 0;
	while (line[i]) {
		if (line[i] != ' ') {
			first = 1;
			line[j++] = line[i++];
		}
		else if (first) {
			line[j++] = line[i++];
			first = 0;
		}
		else
			i++;
	}
	if (line[j] == ' ') j--;
	line[j] = '\0';
}

void addFace(Object* o, char* line,int iF)
{//add the face to the faces array
	int num= countVertexInLine(line), r;
	o->faces[iF].size = num;
	o->faces[iF].vertex = (int*)malloc(num* sizeof(int));
	if (!o->faces[iF].vertex) return NULL;
	char* c = strtok(line, " ");
	for (int i = 0; i < num; i++)
	{
		c = strtok(NULL, " ");
		r=sscanf(c, "%d", &o->faces[iF].vertex[i]);
	}
}

void printFaces(Object* ptr, void* numberOfTriangularFaces)
{// Count the number of all Triangular faces in one object 
	*(int*)numberOfTriangularFaces = 0;
	for (int i = 0; i < ptr->numberOfFaces; i++)
		if (ptr->faces[i].size == 3)
			(*(int*)numberOfTriangularFaces)++;
	
}

void printVertexes(Object* ptr, void* numberOfVertexes)
{// get the number of vertexes in object
	*(int*)numberOfVertexes = ptr->numberOfVertexes;
}

void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces) 
{// Count the total area of all Triangular faces in one object 
	double totalArea = 0;
	Vertex v1, v2, v3;
	for (int i = 0; i < ptr->numberOfFaces; i++)
	{
		if (ptr->faces[i].size == 3)
		{
			v1 = ptr->vertexes[ptr->faces[i].vertex[0]-1];
			v2 = ptr->vertexes[ptr->faces[i].vertex[1]-1];
			v3 = ptr->vertexes[ptr->faces[i].vertex[2]-1];
			totalArea += getArea(v1,v2,v3);
		}

	}
	*(double*)totalAreaOfTriangularFaces = totalArea;
}

void freeObject(Object* ob)
{//free object
	free(ob->vertexes);
	for (int i = 0; i < ob->numberOfFaces; i++)
		free(ob->faces[i].vertex);
	free(ob->faces);
	free(ob);
}

Object* loadBinObject(FILE* f)
{//load object from file in binary format
	Object* ob = (Object*)malloc(sizeof(Object));

	fread(&ob->numberOfVertexes, sizeof(int), 1, f);
	ob->vertexes = (Vertex*)malloc(sizeof(Vertex) * ob->numberOfVertexes);
	fread(ob->vertexes, sizeof(Vertex), ob->numberOfVertexes, f);
	fread(&ob->numberOfFaces, sizeof(int), 1, f);
	ob->faces = (Face*)malloc(sizeof(Face) * ob->numberOfFaces);

	for (int i = 0; i < ob->numberOfFaces; i++)
	{
		fread(&ob->faces[i].size, sizeof(int), 1, f);
		ob->faces[i].vertex = (int*)malloc(sizeof(int) * ob->faces[i].size);
		fread(ob->faces[i].vertex, sizeof(int), ob->faces[i].size, f);
	}
	return ob;
}

void saveBinObject(Object* ob, FILE* f)
{// save the object to file in binary format
	fwrite(&ob->numberOfVertexes, sizeof(int), 1, f);
	fwrite(ob->vertexes, sizeof(Vertex), ob->numberOfVertexes, f);
	fwrite(&ob->numberOfFaces, sizeof(int), 1, f);

	for (int i = 0; i < ob->numberOfFaces; i++)
	{
		fwrite(&ob->faces[i].size, sizeof(int), 1, f);
		fwrite(ob->faces[i].vertex, sizeof(int), ob->faces[i].size, f);
	}

}