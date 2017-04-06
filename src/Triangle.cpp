#include "Triangle.h"

using std::cout;
using std::endl;
//extern const double EPS;

// Triangle object class. 

Triangle::Triangle( int m, int t, VecI v, VecI c, VecI n) : Object(m, t) {
	setVerts (v);
	setTextCoords(c);
	setNormInds(n);
}

Triangle::Triangle (const Triangle& in) : Object ( in.matIndex, in.textureIndex ) {
	setVerts(in.verts);
	setTextCoords(in.textCoords);
	setNormInds(in.norms);
}
void Triangle::setVerts (VecI c) {
	verts.set(c);
}
VecI Triangle::getVerts() {
	return verts;
}

void Triangle::setTextCoords (VecI c) {
	textCoords.set(c);
}
VecI Triangle::getTextCoords() {
	return textCoords;
}
void Triangle::setNormInds (VecI c) {
	norms.set(c);
}
VecI Triangle::getNormInds() {
	return norms;
}

double Triangle::getIsecT(Vec origin, Vec dir)
{
	Vec p1 = vertexList[ verts.geta() ];
	Vec p2 = vertexList[ verts.getb() ];
	Vec p3 = vertexList[ verts.getc() ];
/*
Figure out longest side and take that one as e1.
	Vec e1 = p2 - p1; 
	Vec e2 = p3 - p1;
	Vec e3 = p3 - p2;		
*/
	//Möller–Trumbore algorithm

	Vec e1 = p2 - p1; 
	Vec e2 = p3 - p1;
	Vec P = dir.cross ( e2 );
	double det = e1.dot(P);
	if (det < EPS) {
		return -1;
	}
	double inv_det = 1.0 / det;
	
	Vec T = origin - p1;
	// If gamma isn't between 0 and 1 we missed the triangle.
	beta = T.dot( P ) * inv_det;
	if (beta < -1*EPS || (beta - 1) > EPS ) {
		return -1;
	}
	
	Vec Q = T.cross (e1);
	
	gamma = dir.dot(Q) * inv_det;
	if (gamma < -1*EPS || (1 - (beta + gamma)) < -1*EPS ) {
		return -1;
	}
	
	double t = e2.dot(Q) * inv_det;
	alpha = 1 - (beta + gamma);
	return t;
}

// Take average 
Vec Triangle::getNorm (Vec isect) {
	
	Vec out;
	// Flat shading
	if ( norms.geta() == -1 ) {
		Vec p1 = vertexList[ verts.geta() ];
		Vec p2 = vertexList[ verts.getb() ];
		Vec p3 = vertexList[ verts.getc() ];
		Vec e1 = p2 - p1; 
		Vec e2 = p3 - p1;	
		out = ( e1.cross( e2 ) );
	}
	// Smooth shading, take average of 3 normals.
	else { 
		Vec n1 = normalList[ norms.geta() ];
		Vec n2 = normalList[ norms.getb() ];
		Vec n3 = normalList[ norms.getc() ];
		
		// cout << alpha << beta << gamma << endl;
		n1 = n1 * alpha;
		n2 = n2 * beta;
		n3 = n3 * gamma;
		out = ( (n1) + (n2) + (n3) );
	}
//	out.print();
	out.unitize();
	
	return out;
}

double Triangle::getU (Vec) {
	Vec a = textCoordList[ textCoords.geta() ];
	double u1 = a.getx();
	Vec b = textCoordList[ textCoords.getb() ];
	double u2 = b.getx();
	Vec c = textCoordList[ textCoords.getc() ];
	double u3 = c.getx();

	//cout << u1 << ' ' << u2 << " " << u3 << endl;
	double out = ( ( u1 * alpha ) + ( u2 * beta ) + ( u3 * gamma ) );
	//cout << out << endl;
	if (out < EPS) {
		out = 0;
	}
	if (1 - out < -1*EPS) {
		out = 1;
	}
	return out;
}
double Triangle::getV (Vec) {
	double v1 = textCoordList[ textCoords.geta() ].gety();
	double v2 = textCoordList[ textCoords.getb() ].gety();
	double v3 = textCoordList[ textCoords.getc() ].gety();
	
	double out = ( v1 * alpha ) + ( v2 * beta ) + ( v3 * gamma );
	if (out < EPS) {
		out = 0;
	}
	if (1 - out < -1*EPS) {
		out = 1;
	}
	return out;
}
