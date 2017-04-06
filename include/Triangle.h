
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "VecI.h"
#include <vector>

extern std::vector <Vec> vertexList;
extern int vertexCount;
extern std::vector <Vec> textCoordList;
extern int textCoordCount;
extern std::vector <Vec> normalList;
extern int normalCount;

class Triangle : virtual public Object {
	VecI verts;
	VecI textCoords;
	VecI norms;
	
	double alpha;
	double beta;
	double gamma;

public:
	
	Triangle (int, int, VecI, VecI, VecI);
	Triangle (const Triangle&);
	
	void setVerts (VecI);
	VecI getVerts ();
	void setTextCoords(VecI);
	VecI getTextCoords();
	void setNormInds (VecI);
	VecI getNormInds ();
			
	double getIsecT(Vec dir, Vec origin);
	Vec getNorm (Vec isect);
	double getU (Vec);
	double getV (Vec);
	
	void print(); 	
};	
	
#endif
