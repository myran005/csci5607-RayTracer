#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
extern const double EPS;

class Color {	
private:
	double R, G, B;
	
public:
	Color (double R = 0, double G = 0, double B = 0);
	Color (const Color&);
	void set (Color);
	void set (double, double, double);
	void setR (double);
	void setG (double);
	void setB (double);
	void okay();

	double getR ();
	double getG ();
	double getB ();
	
	Color operator* (double);
	Color operator* (Color);
	Color operator+ (Color);
	
	void print();
};	
	
#endif
