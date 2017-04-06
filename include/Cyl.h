#ifndef CYL_H
#define CYL_H

#include "Object.h"

class Cyl : virtual public Object {
    Vec center;
	double radius;
	int axis;

public:
	
	Cyl (int, int, Vec, double, int = 0 );
	Cyl (const Cyl&);
	
    void setCenter (Vec);
	Vec getCenter();
    
	void setRadius (double);
	double getRadius();	
	void setAxis (int);
	int getAxis ();
	
	
			
	double getIsecT(Vec dir, Vec origin);
	Vec getNorm (Vec isect);
	double getU (Vec);
	double getV (Vec);
	
	void print(); 	
};	
	
#endif
