#include "Color.h"

// Color objects contain 3 doubles within the range [0-1].
// okay() method validates this property whenever colors are created or updated.
Color::Color (double R, double G, double B)
: R(R), G(G), B(B)
{
	okay();
}

Color::Color (const Color& c) {
	R = c.R;
	G = c.G;
	B = c.B;
	okay();
}

void Color::set (Color c) {
	R = c.R;
	G = c.G;
	B = c.B;
	okay();
}
void Color::set (double a, double b, double c) {
	R = a;
	G = b;
	B = c;
	okay();
}
void Color::setR (double in) {
	R = in;
	okay();
}	
void Color::setG (double in) {
	G = in;
	okay();
}	
void Color::setB (double in) {
	B = in;
	okay();
}

double Color::getR () {
	return R;
}
double Color::getG () {
	return G;
}	
double Color::getB () {
	return B;
}

void Color::okay() {
	if ( (R < (-1*EPS)) || ((1 - R) <  (-1*EPS)))  {
		throw "Error, Invalid Red channel. Values must be between 0.0 and 1.0\n";
	}
	else if ( (G < (-1*EPS)) || ((1 - G) <  (-1*EPS)))  {
		throw "Error, Invalid Green channel. Values must be between 0.0 and 1.0\n";
	} 
	else if ( (B < (-1*EPS)) || ((1 - B) <  (-1*EPS)))  {
		throw "Error, Invalid Blue channel. Values must be between 0.0 and 1.0\n";
	}
}

Color Color::operator* (double c) {
	if (c < EPS) {
		c = 0;
	}
	if ((1 - c) < (-1*EPS)) {
		printf( "Error, invalid color scalar: %f.\n", c);
	}
	Color out ((R*c), (G*c), (B*c));
	return out;
}

Color Color::operator* (Color c) {
	Color out (R * c.getR(), G * c.getG(), B * c.getB());
	return out;
}
	
	
Color Color::operator+ (Color c) {
	Color out;
	double r = R + c.getR();
	double g = G + c.getG();
	double b = B + c.getB();
 
	if (r - 1 < EPS) {
		out.setR(r);
	}
	else {
		out.setR(1.0);
		//printf("Red Overflow.\n");
	}
	if (g - 1 < EPS) {
		out.setG(g);
	}
	else {
		out.setG(1.0);		
		//printf("Green Overflow.\n");
	}
	if (b - 1 < EPS) {
		out.setB(b);
	}
	else {
		out.setB(1.0);		
		//printf("Blue Overflow.\n");
	}
	
	return out;
}

void Color::print() {
	printf ("R: %f, G: %f, B: %f.\n", R, G, B);
}
