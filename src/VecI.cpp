#include "VecI.h"

VecI::VecI(int x, int y, int z) {
	seta( x );
	setb( y );
	setc( z );
}

VecI::VecI (const VecI& v) : a(v.a), b(v.b), c(v.c) {
	seta( v.a );
	setb( v.b );
	setc( v.c );
}

void VecI::set(int x, int y, int z) {
	seta( x );
	setb( y );
	setc( z );
}

void VecI::set (VecI v) {
	seta ( v.a );
	setb ( v.b );
	setc ( v.c );
}

void VecI::seta (int in) {
	a = in;
}	
int VecI::geta () {
	return a;
}

void VecI::setb (int in) {
	b = in;
}
int VecI::getb () {
	return b;
}
	
void VecI::setc (int in) {
	c = in;
}
int VecI::getc () {
	return c;
}

void VecI::print() {
	printf ("<%d, %d, %d> \n", a, b, c);
} 
