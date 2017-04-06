
#include "Vec.h"
using namespace std;

// Vector object class. Note that this is essentially just 3 doubles with some extra operations defined.
// Currently this class is also used to contain points, for which some operations do not make sense (unitize, isZero). 
// These problems are avoided in implementation by being careful.

Vec::Vec (const Vec& v) : x(v.x), y(v.y), z(v.z) {
}
	
Vec::Vec(double x, double y, double z) : x(x), y(y), z(z) {
}


void Vec::set (Vec v) {
	x = v.x;
	y = v.y;
	z = v.z;
}
void Vec::set(double a, double b, double c) {
	x = a;
	y = b;
	z = c;
}


void Vec::setx (double in) {
	x = in;
}	
void Vec::sety (double in) {
	y = in;
}	
void Vec::setz (double in) {
	z = in;
}

double Vec::getx () {
	return x;
}
double Vec::gety () {
	return y;
}	
double Vec::getz () {
	return z;
}

Vec Vec::operator* (double c) {
	Vec out(c*x, c*y, c*z);
	return out;
}
/* Shouldn't be necessary, ints will just get cast to double automatically.
Vec Vec::operator* (int c) {
	Vec out(c*x, c*y, c*z);
	return out;
}*/
Vec Vec::operator+= (Vec v) {
	Vec out(x + v.getx(), y + v.gety(), z + v.getz());
	return out;	
}
Vec Vec::operator+ (Vec v) {
	Vec out(x + v.getx(), y + v.gety(), z + v.getz());
	return out;
}
Vec Vec::operator- (Vec v) {
	Vec out(x - v.getx(), y - v.gety(), z - v.getz());
	return out;
}
bool Vec::operator== (Vec v) {
	return ( (x == v.getx()) && (y == v.gety()) && (z == v.getz()) );
}

bool Vec::isZero () {
	return (x == 0 && y == 0 && z == 0);
}

double Vec::vLen () {
	double ans = x*x + y*y + z*z;
	return sqrt(ans);	

}
void Vec::vScale (double c) {
	setx(c*x);
	sety(c*y);
	setz(c*z);
}	

void Vec::unitize () {
	double len = vLen();
	if (len < EPS) {
		throw ( "Error, cannot unitize zero vector.\n");
	}
	if ( len - 1 > EPS || len - 1 < -1*EPS) {
		vScale(1/len);
	}	
	return;  	
}

double Vec::dot (Vec v) {
	return ( (x * v.getx()) + (y * v.gety()) + (z * v.getz()) );
}

Vec Vec::cross (Vec v) {
	Vec out( y*v.getz() - z*v.gety(),
			 z*v.getx() - x*v.getz(),
			 x*v.gety() - y*v.getx() );
	return out;	
}

void Vec::print() {
	printf ("<%f, %f, %f> \n", x, y, z);
} 

