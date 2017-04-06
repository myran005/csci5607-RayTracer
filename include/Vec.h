#ifndef VEC_H
#define VEC_H

#include <stdio.h>
#include <math.h>
extern const double EPS;

class Vec {
private:	
	double x, y, z;	
	void vScale(double);

public:		
	Vec (double x=0, double y=0, double z=0);
	Vec (const Vec&);
	
	void set(Vec);
	void set(double, double, double);

	void setx(double);
	double getx();
	
	void sety(double);
	double gety();
	
	void setz(double);	
	double getz();
	
	Vec operator* (double);
	Vec operator+ (Vec);
	Vec operator- (Vec);	
	Vec operator+= (Vec);
	bool operator== (Vec);

	bool isZero();		
	double vLen();	
	
	void unitize();
	
	double dot(Vec);
	Vec cross(Vec);
	
	void print();	
};

#endif
