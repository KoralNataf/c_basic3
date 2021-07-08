# c_basic3
First C course hw3 - Files, Linked lists, Pointers to functions and Variadic Functions.
This progran running on Visual Studio.

In this exercise a number of actions have to be performed on files describing shapes of three-dimensional bodies in space.
Use these files in the field of 3D printing, virtual reality display and more.
Several companies have developed applications for creating three-dimensional bodies in virtual space. 
Most of them define the body as a collection of polygons that "envelop" it. 
For this purpose, a large number of points (vertexes) are defined on the body and in addition the poles (faces) are defined whose vertices are from the collection of points defined earlier.
In this exercise we will refer to objects defined in OBJ format.

1. Write a function
void transformObject (char * originalObjectFileName, char * deformedObjectFileName);
The function transforms on a given Obj file. It gets names of two files in OBJ format. 
The original and the one that will contain the object after transformation on any Vertex defined in the original file according to the following validity:
x1 = 0.3*x
y1=y
z1=z

2. Write a function that gets the name of an OBJ format file and builds an Object structure accordingly.
Object * createObject (char * filename)

3. Write a function that constructs a Scene structure consisting of several objects as a linked list.
Scene * createScene (char * fileName, ...);
The function that receives an unknown number of pointers for file names, in each OBJ format object definition file. The last parameter is NULL. 
The function creates and returns a Scene structure that contains a one-way linked list of all objects.

4. Write functions that perform various actions on the object. The uniform signature of the functions will help in generic writing in the next section.

a. A function that accepts the pointer to the Object and calculates the number of faces of the object that have three Vertexes.
void printFaces (Object * ptr, void * numberOfTriangularFaces)

b. A function that receives the pointer on the Object returns the number of vertexes of the object
void printVertexes (Object * ptr, void * numberOfVertexes)

c. A function that accepts the pointer to the Object calculates the total area of all the faces of the object that have three Vertexes.
void getTotalArea (Object * ptr, void * totalAreaOfTriangularFaces)

5. Write a function that receives, Scene points to a function of the type defined in section 4, a string that specifies the type of the print variable, and points to a string. The perform function goes through all the objects in the Scene and performs a reading with the help of the pointer to the function. At the end it prints the string and the sum of all the results. Possible print type INT, DOUBLE, STR, CHAR

6. Write functions that save / upload the Scene in a file / text file or binary of the user's choice. There is no specific requirement for the file format as long as reading the saved file produces a proper Scene Back
void saveScene (Scene * scene, char * fileName, enum FileType type);
Scene * loadScene (char * fileName, enum FileType type);
In the loadScene function all the required memory allocations were made in creating all the new structures that make up the newly created scene.
7. Write a function that frees up all the memory allocated during the construction of the scene

void freeScene (Scene * scene)
