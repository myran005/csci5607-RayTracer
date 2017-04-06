#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include "Color.h"

typedef std::vector < std::vector <Color> > Image;

class Texture {

public: 
	int width;
	int height;
	Image* texture;
	
	Texture (int width, int height) ;
	~Texture();
	
	
	void setW(int);
	int getW();
	
	void setH(int);
	int getH();

	void setXY(int, int, Color);
	Color getXY(int, int);
};


#endif
