
#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <math.h>
#include "Vec.h"

extern const double PI;

class Object {
protected:
    int matIndex;
	int textureIndex;
    
public:
    Object (int, int);
    virtual ~Object();
    
    void setMatIndex (int);
	int getMatIndex();
	
	void setTextureIndex (int);
    int getTextureIndex();
	
	// Returns minimum positive t for ray-object intersection.
    virtual double getIsecT (Vec origin, Vec dir) = 0;
	// Returns the object's normal vector.
	virtual Vec getNorm (Vec isect) = 0;
	// Returns coordinates in range [0..1] for texture mapping 
	virtual double getU(Vec) = 0;
	virtual double getV(Vec) = 0;
	
    void print();   
};  
    
#endif

