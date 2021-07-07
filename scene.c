#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "scene.h"

Scene* createScene(char* fileName, ...)
{//create the scene from the files
	Scene* scene = (Scene*)malloc(sizeof(Scene));
	if (!scene) return NULL;

	scene->list = (List*)malloc(sizeof(List));
	if (!(scene->list)) return NULL;

	BOOL b =L_init(scene->list);
	if (!b) return NULL;

	va_list files;
	va_start(files, fileName);

	Object* ob=createObject(fileName);
	Node* temp=L_insert(&scene->list->head, ob);

	char* file= va_arg(files, char*);
	while (file && temp && ob)
	{
		ob = createObject(file);
		temp = L_insert(temp, ob);
		file = va_arg(files, char*);
	}
	
	return scene;
}

void perform(Scene* scene, void(*ptrFunction)(Object*, void*), char* type, char* str)
{//get function pointer and calculate different things for each function
	printf("%s ", str);
	Node* n = scene->list->head.next;
	void* numPtr;
	void* tempSum;
	 
	switch (*type)
	{
	case 'I':
		numPtr = (int*)calloc(1,sizeof(int));
		tempSum = (int*)calloc(1, sizeof(int));
		break;
	case 'D':
		numPtr = (double*)calloc(1,sizeof(double));
		tempSum = (int*)calloc(1, sizeof(double));
		break;
	case 'C':
		numPtr = (char*)calloc(1,sizeof(char));
		tempSum = (int*)calloc(1, sizeof(char));
		break;
	case 'S':
		numPtr = (int*)calloc(100,sizeof(char));
		tempSum = (int*)calloc(100, sizeof(char));
		break;

	default:
		numPtr = (int*)calloc(1,sizeof(double));
		tempSum = (int*)calloc(1, sizeof(double));
		break;
	}
	if (!numPtr || !tempSum) return NULL;

	while (n)
	{
		ptrFunction(n->value, numPtr);
		if (*type == 'I')
			*(int*)tempSum += *(int*)numPtr;
		else if (*type == 'D')
			*(double*)tempSum += *(double*)numPtr;
		n = n->next;
	}
	if (*type == 'I')
		printf("%d\n", *(int*)tempSum);
	else if (*type == 'D')
		printf("%lf\n", *(double*)tempSum);

	free(numPtr);
	free(tempSum);
	
}

void saveScene(Scene* scene, char* fileName, enum FileType type)
{//save the scene to file by user option text or binary
	int succsess=0;
	int count = countObject(scene);
	if (type)
	 succsess=saveBinFormat(scene, fileName,count);//binary file
	else
	 succsess=saveTxtFormat(scene, fileName,count);//txt file
	
	if (succsess == 0)
		printf("Faild save scene to file..\n");
}

Scene* loadScene(char* fileName, enum FileType type)
{//load the scene in 2 option from file(binary or txt)
	Scene* scene = (Scene*)malloc(sizeof(Scene));
	if (!scene) return NULL;

	scene->list = (List*)malloc(sizeof(List));
	if (!(scene->list)) return NULL;

	BOOL b = L_init(scene->list);
	if (!b) return NULL;

	if (type)
		scene = loadBinFormat(scene,fileName);
	else
		scene = loadTxtFormat(scene,fileName);

	if (scene == NULL) printf("Failed load scene from file....\n");

	return scene;
	
}

int saveBinFormat(Scene* scene, char* fileName, int count)
{//save the scene to file in binary format.
	FILE* f = fopen(fileName, "wb");
	if (!f)
		return 0;

	Node* n = scene->list->head.next;

	fwrite(&count, sizeof(int), 1, f);

	for (int i = 0; i < count; i++)
	{
		saveBinObject(n->value, f);
		n = n->next;
	}
	fclose(f);
	return 1;
}

int saveTxtFormat(Scene * scene, char* fileName,int count)
{//save the scene to text file
	FILE* f = fopen(fileName, "w");
	if (!f)
		return 0;

	Node* n = scene->list->head.next;
	fprintf(f, "%d\n", count);

	for (int i = 0; i < count; i++)
	{
		fprintf(f, "%d\n", n->value->numberOfVertexes);
		for (int i = 0; i < n->value->numberOfVertexes; i++)
			fprintf(f, "%f %f %f\n", n->value->vertexes[i].x, n->value->vertexes[i].y, n->value->vertexes[i].z);
		fprintf(f, "%d\n", n->value->numberOfFaces);
		for (int i = 0; i < n->value->numberOfFaces; i++) {
			fprintf(f, "%d\n", n->value->faces[i].size);
			for (int j = 0; j < n->value->faces[i].size; j++) {
				fprintf(f, "%d\n", n->value->faces[i].vertex[j]);
			}
		}
		n = n->next;
	}
	fclose(f);
	return 1;
}

Scene* loadBinFormat( Scene* scene, char* fileName)
{//load scene from binary file format
	FILE* f = fopen(fileName, "rb");
	if (!f)
		return NULL;
	int count;
	Object* ob;
	Node* n = &scene->list->head;

	fread(&count, sizeof(int), 1, f);
	for (int i = 0; i < count; i++)
	{
		ob = loadBinObject(f);
		n = L_insert(n, ob);
	}

	fclose(f);
	return scene;
}

Scene* loadTxtFormat(Scene* scene,char* fileName)
{///create scene from text file
	Object* ob;
	Node* n = &scene->list->head;
	FILE* f = fopen(fileName, "r");
	if (!f)
		return NULL;//check that file opening sucsses
	int count, num;

	num = fscanf(f, "%d", &count);

	for (int i = 0; i < count; i++)
	{
		ob = (Object*)malloc(sizeof(Object));
		num = fscanf(f, "%d", &ob->numberOfVertexes);
		ob->vertexes = (Vertex*)malloc(ob->numberOfVertexes * sizeof(Vertex));
		if (!ob->vertexes) return NULL;

		for (int i = 0; i < ob->numberOfVertexes; i++)
		{
			num = fscanf(f, "%f", &ob->vertexes[i].x);
			num = fscanf(f, "%f", &ob->vertexes[i].y);
			num = fscanf(f, "%f", &ob->vertexes[i].z);
		}
		num = fscanf(f, "%d", &ob->numberOfFaces);
		ob->faces = (Face*)malloc(sizeof(Face) * ob->numberOfFaces);
		if (!ob->faces) return NULL;

		for (int i = 0; i < ob->numberOfFaces; i++)
		{
			num = fscanf(f, "%d", &ob->faces[i].size);
			ob->faces[i].vertex = (int*)malloc(ob->faces[i].size * sizeof(int));
			if (!ob->faces[i].vertex) return NULL;
			for (int j = 0; j < ob->faces[i].size; j++)
				num = fscanf(f, "%d", &ob->faces[i].vertex[j]);
		}
		n = L_insert(n, ob);
	}
	fclose(f);
	return scene;
}

int countObject(Scene* scene)
{//count the number of object in scene
	int count = 0;
	Node* n = scene->list->head.next;
	while (n)
	{
		count++;
		n = n->next;
	}

	return count;
}

void freeScene(Scene* scene)
{//free scene 
	int count = countObject(scene);
	Node* n = scene->list->head.next;
	for (int i = 0; i < count; i++)
	{
		freeObject(n->value);
		n = n->next;
	}
	L_free(scene->list);
	free(scene);

}