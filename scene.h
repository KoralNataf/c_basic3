#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "linkedList.h"
#include "object.h"
#include "vertex.h"
#include "face.h"
typedef struct {
// This structure contains a Single Direction Linked List of all objects in the Scene
	List* list;
} Scene;

enum FileType { TextFormat, BinaryFormat };

Scene* createScene(char* fileName, ...);

void perform(Scene* scene, void(*ptrFunction)(Object*, void*), char* type, char* str);

void saveScene(Scene* scene, char* fileName, enum FileType type);

Scene* loadScene(char* fileName, enum FileType type);


int saveBinFormat(Scene* scene, char* fileName,int count);

int saveTxtFormat(Scene* scene, char* fileName,int count);

Scene* loadBinFormat(Scene* scene,char* fileName);

Scene* loadTxtFormat(Scene* scene,char* fileName);

int countObject(Scene* scene);

void freeScene(Scene* scene);