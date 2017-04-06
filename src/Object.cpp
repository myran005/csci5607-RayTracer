#include "Object.h"


using std::cout;
using std::endl;

Object::Object ( int mat, int tex ) {
    setMatIndex (mat);
	setTextureIndex (tex);
}

Object::~Object(){
}

// Need material property to be set for blinn-phong shading.
void Object::setMatIndex( int m ) {
    matIndex = m;
	if (matIndex < 0) {
		throw "Error, object defined before mtlcolor.\n";
	}
}
int Object::getMatIndex() {
	return matIndex;
}

// Can be -1 if untextured.
void Object::setTextureIndex( int t ) {	
    textureIndex = t;
}
int Object::getTextureIndex () {
	return textureIndex;
}

void Object::print() {
	cout << "Material Index: " << matIndex << " textureIndex: " << textureIndex << endl;
}


