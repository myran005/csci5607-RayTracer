#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec.h"
#include "Color.h"

class Material {

public:
	Color diffuse;
	Color spectral;
	double ka, kd, ks; 
	int n;	
	double alpha, eta;
	
	Material (Color d, Color s, Vec coeffs, int n, double a, double e);
	Material (const Material&);
	/*
	void setDiff (Color);
	void setSpect (Color);
	void setCoeffs (Vec);
	void setKa (double);
	void setKd (double);
	void setKs (double);
	void setn (int);
	void set (Color, Color, Vec, int);
	void set (Material);
	*/	
	Color getDiff();
	Color getSpect();
	double getKa();
	double getKd();
	double getKs();
	int getN();
	
	double getAlpha();
	double getEta();
	
	void print(); 	
};	
	
#endif
