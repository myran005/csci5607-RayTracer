
#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : virtual public Object {
	Vec center;
	double radius;
	

public:
	
	Sphere (int, int, Vec, double);
	Sphere (const Sphere&);
	
	void setRadius (double);
	double getRadius ();

    void setCenter (Vec);
	Vec getCenter();
    		
	double getIsecT(Vec dir, Vec origin);
	Vec getNorm (Vec isect);
	double getU (Vec);
	double getV (Vec);
	
	void print(); 	
};	
	
#endif
