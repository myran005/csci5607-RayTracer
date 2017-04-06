#include "Sphere.h"
using std::cout;

// Sphere object class. 

Sphere::Sphere( int m, int t, Vec coord, double r) : Object(m, t) {
	setCenter(coord);
	setRadius(r);
}

Sphere::Sphere (const Sphere& in) : Object ( in.matIndex, in.textureIndex ) {
	setCenter(in.center);
	setRadius(in.radius);
}
void Sphere::setCenter (Vec c) {
	center.set(c);
}
Vec Sphere::getCenter() {
	return center;
}

void Sphere::setRadius (double r) {
	radius = r;
	if (r < EPS) {
		throw "Error, sphere has invalid radius.\n";
	}
}
double Sphere::getRadius ()  {
	return radius;
}

// Return minimum positive t for ray-object intersection.
double Sphere::getIsecT(Vec origin, Vec dir) {
	double tOut = -1;
	Vec oms = origin - center;
	//double A = dir.dot(dir); // 1
	double B = dir.dot(oms) * 2;
	double C = oms.dot(oms) - pow(radius, 2);
	double discrim = pow (B, 2) - 4*C;
	if (discrim > EPS) {
		double t1 = ( (-1)*B + sqrt(discrim) )/(2);
		double t2 = ( (-1)*B - sqrt(discrim) )/(2);			
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

// Return normal vector.
Vec Sphere::getNorm (Vec isect) {
	Vec N = (isect - center) * (1.0/radius);
	N.unitize();
	return N;
}

/* This pair of functions maps the top of the image to the  
 * y axis so that a map displays as expected */
double Sphere::getU (Vec isect) {
	Vec N = getNorm(isect);	
	double theta = atan2(N.getx(), N.getz()); 
	if (theta < EPS) {
		theta += 2*PI;
	}
	return (theta / (2*PI));
	
}
double Sphere::getV (Vec isect) {
	Vec N = getNorm(isect);
	double y = N.gety();
	
	//Check the x is in the domain of acos [-1, 1] so we never return nan.
	if (y + 1 < EPS) {
		//printf("y: %f\n", y);
		y = -1;
	}
	if (y - 1 > -1*EPS) {
		//printf("y: %f\n", y);
		y = 1;
	}
	//printf("y: %f\n", y);
	
	double phi = acos (y);	
	return (phi / PI);	
}

void Sphere::print() {
	Object::print();
	cout << "Radius: " << radius << "\n";
}
