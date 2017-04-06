
#ifndef LIGHT_H
#define LIGHT_H

#include "Vec.h"
#include "Color.h"

class Light {
	Vec vec;	
	bool isPoint;
	Color color;
	void okay();
	
public:
	Light (Vec, bool, Color);
	Light (const Light&);
	
	void setVec (Vec);
	void setIsPoint (bool);
	void setCol (Color);
	void set (Vec, bool, Color);
	void set (Light);
		
	Vec getVec();
	bool getIsPoint();
	Color getCol();
	
	void print(); 	
};	
	
#endif
