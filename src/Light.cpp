#include "Light.h"
#include <iostream>
using std::cout;

// Light object class. Currently has some unused functions.

Light::Light( Vec coord, bool dir, Color col) {
	vec.set(coord);
	isPoint = dir;
	color.set(col);
	okay();
}

Light::Light (const Light& in)
: vec( in.vec ), isPoint( in.isPoint ), color ( in.color ) {
}

void Light::okay() {
	if ((!isPoint) && (vec.vLen() < EPS)) {
		cout << isPoint;
		vec.print();
		throw "Error, directional light vector cannot be 0.\n";
	}
}

void Light::setVec (Vec coord) {
	vec.set(coord);
}
void Light::setIsPoint (bool d) {
	isPoint = d;
}
void Light::setCol (Color c) {
	color = c;
}
void Light::set (Vec c, bool d, Color col) {
	setVec( c );
	setIsPoint( d );
	setCol( col );
	okay();
}
void Light::set(Light a) {
	setVec( a.getVec() );
	setIsPoint ( a.getIsPoint() );
	setCol ( a.getCol() );
	okay();
}

Vec Light::getVec () {
	return vec;
}
bool Light::getIsPoint () {
	return isPoint;
}
Color Light::getCol () {
	return color;
}

void Light::print() {
	cout << "Vec: ";
	vec.print();
	if (isPoint) {
		cout << "Point\n";
	}
	else {
		cout << "Directional\n";
	}
	cout << "Color: ";
	color.print();
}
