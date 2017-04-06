#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <string>
#include <vector> 
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Color.h"
#include "Sphere.h"
#include "Cyl.h"
#include "Triangle.h"
#include "Material.h"
#include "Light.h"
#include "Texture.h"

using std::vector;
using std::string;
 
typedef vector < vector <Color> > Image;

// Read from input file.
extern int width;
extern int height;
extern double fovh;
extern double dist;
extern Vec eye;
extern Vec viewDir;
extern Vec upDir;
extern Color bg;


// Lists of material colors and spheres and their counters.
extern vector <Light> lightList;
extern int lightCount;
extern vector <Material> materialList; 
extern int matCount;
extern vector <Texture*> textureList;
extern int textureCount;

extern vector <Object*> objectList; 
extern int objCount;

extern vector <Vec> vertexList;
extern int vertexCount;
extern vector <Vec> textCoordList;
extern int textCoordCount;
extern vector <Vec> normalList;
extern int normalCount;

extern bool parallel;
extern bool softShadows;
extern bool depthOfField;
extern double dist;

Vec readVec ();
Vec readVec2 ();
Color readCol ();

Light readLight ();
Material readMat ();
Texture* readTexture();

Object* readSphere ();
Object* readCylX ();
Object* readCylY ();
Object* readCylZ ();
Object* readFace ();

string readInput (string);
void writeOutput (string, Image&);

#endif
