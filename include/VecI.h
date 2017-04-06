#ifndef VECI_H
#define VECI_H

#include <stdio.h>

class VecI {
private:	
	int a, b, c;
public:		
	VecI (int a=-1, int b=-1, int c=-1);
	VecI (const VecI&);
	
	void set(int, int, int);
	void set(VecI);
	
	void seta(int);
	int geta();
	
	void setb(int);
	int getb();

	void setc(int);
	int getc();
	
	void print();	
};	

#endif
