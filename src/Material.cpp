#include <iostream>
#include "Material.h"

using std::cout;
using std::endl;

Material::Material (Color d, Color s, Vec coeffs, int exp, double a, double e)
: diffuse(d), spectral(s), 
  ka(coeffs.getx()), kd(coeffs.gety()), ks(coeffs.getz()), 
  n(exp), alpha (a), eta(e) {
}

Material::Material (const Material& in)
: diffuse(in.diffuse), spectral(in.spectral), 
  ka(in.ka), kd(in.kd), ks(in.ks), 
  n(in.n), alpha (in.alpha), eta(in.eta) {
}

/*
void Material::setDiff (Color in) {
	diffuse.set (in);
}
void Material::setSpect (Color in) {
	spectral.set(in);
}
void Material::setCoeffs (Vec in) {
	ka = in.getx();
	kd = in.gety();
	ks = in.getz();
}
void Material::setKa (double in) {
	ka = in;
}
void Material::setKd (double in) {
	kd = in;
}
void Material::setKs (double in) {
	ks = in;
}
void Material::setn (int in) {
	n = in;
}
void Material::set (Color d, Color s, Vec c, int e) {
	diffuse.set(d);
	spectral.set(s);
	setCoeffs(c);
	n = e;
}
*/
Color Material::getDiff() {
	return diffuse;
}
Color Material::getSpect() {
	return spectral;
}
double Material::getKa() {
	return ka;
}
double Material::getKd() {
	return kd;
}
double Material::getKs() {
	return ks;
}
int Material::getN() {
	return n;
}

double Material::getAlpha() {
	return alpha;
}
double Material::getEta() {
	return eta;
}



void Material::print() {
	diffuse.print();
	spectral.print();
	cout << "ka: " << ka << " kd: "<< kd << "ks: " << ks << " n: " << n << endl;
}

	
