#include "Cyl.h"
using std::cout;
using std::endl;

// Infinite cylinder object class. There are 3 axis orientations.
 
Cyl::Cyl( int m, int t, Vec coord, double r, int axis) : Object(m, t) {
	setCenter(coord);
	setRadius (r);
	setAxis(axis);
}

Cyl::Cyl (const Cyl& in) : Object ( in.matIndex, in.textureIndex) {
	setCenter(in.center);
	setRadius(in.radius);
	setAxis(in.axis);
}

void Cyl::setCenter (Vec c) {
	center.set(c);
}
Vec Cyl::getCenter() {
	return center;
}

void Cyl::setRadius (double r) {
	radius = r;
	if (r <= 0) {
		throw "Error, sphere has invalid radius.\n";
	}
}
double Cyl::getRadius () {
	return radius;
}

void Cyl::setAxis (int a) {
	axis = a;
}
int Cyl::getAxis () {
	return axis;
}


double Cyl::getIsecT(Vec origin, Vec dir) {
	double tOut = -1;
	double A;
	double B;
	double C;
	Vec oms = origin - center;

	switch (axis) {
  case 3:
		oms.setz(0);
		A = pow(dir.getx(), 2) + pow(dir.gety(), 2);
		B = 2*oms.getx()*dir.getx() + 2*oms.gety()*dir.gety();
		C = oms.dot(oms) - pow(radius, 2);
	  break;
	case 2: 
		oms.sety(0);
		A = pow(dir.getx(), 2) + pow(dir.getz(), 2);
		B = 2*oms.getx()*dir.getx() + 2*oms.getz()*dir.getz();
		C = oms.dot(oms) - pow(radius, 2);
	  break;
	case 1:
		oms.setx(0);		
		A = pow(dir.gety(), 2) + pow(dir.getz(), 2);
		B = 2*oms.gety()*dir.gety() + 2*oms.getz()*dir.getz();
		C = oms.dot(oms) - pow(radius, 2);
	  break;	
	default: //else {
		cout << axis << endl;
	}
	double discrim = pow (B, 2) - 4*A*C;
	if (discrim > EPS) {
		double t1 = ( (-1)*B + sqrt(discrim) )/(2*A);
		double t2 = ( (-1)*B - sqrt(discrim) )/(2*A);			
		if (t1 > EPS) {
			tOut = t1;
		}
		if (t2 > EPS && (tOut - t2) > EPS ) {
			tOut = t2;
		}	
	}	
	else if (discrim == 0) {
		double t = (-1/2) * B;
		if ( t > EPS ) {
			tOut = t;
		} 	
	}
	return tOut;
}

Vec Cyl::getNorm (Vec isect) {
	Vec N = ((isect - center) * (1.0/radius));
	N.unitize();
	return N;
}


// Textured cylinders not yet supported.
double Cyl::getU (Vec isect) {
	return 0;
}
double Cyl::getV (Vec isect) {
	return 0;
}

void Cyl::print() {
	Object::print();
	switch(axis) {
		case 1: cout << "X axis\n";
		case 2: cout << "Y axis\n";
		case 3: cout << "Z axis\n";
		default: cout << "Undefined axis\n";
	}
}
