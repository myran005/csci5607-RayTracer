/* Scott Myran
 * CSCI 5607
 * Assignment 1c
 * 10/15/2015
 */
#include <ctime>
#include <cstdlib>
 
#include "ReadInput.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::stack;

using std::rand;
using std::srand;
using std::time;


// Defined constants.
double const PI = 3.14159265;
double const EPS = .00000000125;
const int MAXDEPTH = 10;
const int MAXITERS = 50;
// Container for image.
// typedef vector < vector <Color> > Image; - Moved to texture class.

// Gloval Variables (bad idea?)

// Read from input file.
// Initialized to 0 by default. (Vectors and Colors too)
int width = 0;
int height = 0;
double fovh = 0;
Vec eye;
Vec viewDir;
Vec upDir;
Color bg;
bool parallel = false;
bool softShadows = false;

bool depthOfField = false;
double dist = 1.0;



// Lists to hold various objects
vector <Material> materialList; 
int matCount = -1;

vector <Light> lightList;
int lightCount = 0;

vector <Object*> objectList;  
int objCount = 0;

vector <Texture*> textureList;
int textureCount = -1;

// Vertex info
vector <Vec> vertexList;
int vertexCount = 0 ;

vector <Vec> textCoordList;
int textCoordCount = 0;

vector <Vec> normalList;
int normalCount = 0;

// Stack for refraction index of the material we're currently inside
stack <double> currentEta;


// Functions used in this file. This should move to a header.
Color rayTrace (Vec, Vec, int);
Color shadeRay (Object*, Vec, Vec, double, int);

int main(int argc, char *argv[]) {	
	string outName;

	try {
		// Make sure there is a command line argument fot input file.
		// TODO: Add debug flag (and debug code)
    	if (argc != 2) {
    		throw "Usage: ./assign1a *.txt\n";
    	}
    	string fileName = argv[1];
    	
    	// Read input file to global variables and get output filename.	
		outName = readInput(fileName); 

		// Make sure these fields were not ommited in the scene file.		
		if (viewDir.isZero() || upDir.isZero()) {
			throw "Error, input vectors undefined.\n";
		}
		if (width <= 0 || height <= 0 || fovh <=0 ) {
			throw "Error, image resolution undefined.\n";
		}
		
		// Check if angle between vectors is 0 or 180. 		
		if (viewDir.dot(upDir) == 1 || viewDir.dot(upDir) == -1 ) {
			throw "Error, input vectors are parallel.\n";
		}

 
	  	// Calculate stuff.
	   	double aspect = (double) width/height;
	   	double w = 2*dist*tan(fovh * PI / 360);
		double h = w/aspect;

		// Scale so parallel image doesn't look so far away.
		if (parallel) {
			w = (double) width / 10;
			h = (double) height / 10;
		}
	
	   	Vec u = ( viewDir.cross(upDir) );
	   	Vec v = ( u.cross(viewDir) );
		   
		Vec TL = eye + viewDir*dist - u*(w/2) + v*(h/2);

		Vec dH = u*(w/(width));					
		Vec dV = v*(-1*h/(height));	
	
		// Initalize dynamic matrix of Colors: image
		Image image (width, vector <Color> (height));
	
		double bgEta = 1;
		currentEta.push(bgEta);
	
		// For each pixel in the output image, trace a ray from the eye to the point in the world
		// and save the resulting color into the image.
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				if (parallel) {
					Vec curEye = TL + (dH*x) + (dV*y) ;
					image[x][y].set( rayTrace(curEye, viewDir, 0) );
				}
				else {
					if (!depthOfField) {
						Vec curDir = TL - eye + (dH*x) + (dV*y);      	    
						curDir.unitize();	
						image[x][y].set( rayTrace(eye, curDir, 0) );
					}
					// Depth of field
					else {
						Color depthAcc;
						time_t seconds;
						time(&seconds);
						srand((unsigned int) seconds);
						int MAXITERS = 50;

						for (int i = 0; i < MAXITERS; i++) {
							int randX = (rand() % 200001) - 100000;  
							double randXD = (double) randX / 100000; // values [-1:1]

							int randY = (rand() % 200001) - 100000; 
							double randYD = (double) randY / 100000; // values [-1:1]

							// Sample a 1x1 lens in the u-v plane.
							Vec randEye = eye + dH*randXD + dV*randYD;

							Vec curDir = TL - randEye + (dH*x) + (dV*y);      	    
							curDir.unitize();	
							Color temp = rayTrace( randEye, curDir, 0 );
	
							// Scale first to avoid overflow.
							temp = temp * (1.0/MAXITERS);
							depthAcc = depthAcc + temp;
						}
						image[x][y].set( depthAcc );
					}
				}	
			}
		}

		writeOutput ( outName, image ); 	
	
		
		// Delete items allocated on heap.
		for (int i = 0; i < objCount; i++) {
			delete objectList[i];
		} objectList.clear();
		
		for (int i = 0; i < textureCount; i++) {
			delete textureList[i];
		} textureList.clear();
    }
	catch (const char* err) {
		// Print error string and exit.
		cerr << err;
		return 1;
    }   
   	return 0;
}   


Color rayTrace (Vec orig, Vec dir, int depth) {
	if (depth >= MAXDEPTH) {
		return Color(0, 0, 0);
	}

	double tMin = 1.0/0.0;		//Infinity.
	int minObj = -1;

	// For each object, look for an intersection with the input ray. 
	for (int i = 0; i < objCount; i++) {
		Object* obj = ( objectList[i] );			
		double tCur = obj->getIsecT(orig, dir);
	
		// Keep track of the closest object found	
		
		if ( (tMin - tCur) > EPS && tCur > EPS) {
			tMin = tCur;
			minObj = i;
		}
	}	

	// hit either points to the closest object hit or NULL.
	Object* hit = NULL;
	if (minObj != -1) {
		hit = objectList[minObj];
	}

	return shadeRay (hit, orig, dir, tMin, depth);
}



// Just return the color.
Color shadeRay (Object* hit, Vec origin, Vec dir, double tMin, int depth) {
	
	// If we miss all objects just return background color.
	if (!hit) {		
		return bg;
	}

	// If we hit an object, calculate the intersection point and ask for surface normal.
	Vec isect = (origin + dir*(tMin));
	Vec	normal = hit->getNorm(isect);
	
	
	
	// Get material we're working with		
	int mat = hit->getMatIndex();
	Material m = materialList[mat];


			
	Color Od = m.getDiff();
	Color Os = m.getSpect();
	
	// If the image is textured, get the Od color from the texture.
	int tex = hit->getTextureIndex();
	
	if (tex != -1) {
		Texture* t = (textureList[tex]);

		double u = hit->getU(isect);
		double v = hit->getV(isect);
		double tw = t->getW() - 1;
		double th = t->getH() - 1;
		
		int i = (int) ((u * tw ) + 0.5);
		int j = (int) ((v * th ) + 0.5);

		if (i < 0 || j < 0) {
			printf ("u: %f, v: %f, i: %d, j: %d", u, v, i, j);
		}
		Od.set (t->getXY(i,j));
	}
		
	// Only calculate ambient color once
	Color ambient = Od * m.getKa();		
	Color lights;

	double notShadow = 1.0;
	
	Vec L;
			
	// For each light in the scene, check to see if an object is casting a shadow.
	for (int i = 0; i < lightCount; i++) {		
		// Get current light
		Light l = ( lightList[i] );
		
		// Point lights
		if (l.getIsPoint()) {
			if (!softShadows) {

				L = l.getVec() - isect;
				// Find magnitude of light vector before unitizing.
				double lenL = L.vLen();
				if (lenL < EPS) {
					continue;
				}
				L.unitize();
				// Look for shadows
				for (int i = 0; i < objCount; i++) {
					Object* obj = ( objectList[i] );
					double tCur = obj->getIsecT((isect), L);
					
					Vec curIsect = isect + dir*(tCur);
					double curLen = curIsect.vLen();
					// Set flag and quit if shadow detected.
					if ( ((lenL - curLen) > EPS) && (tCur > EPS) ) {
						notShadow *= (1 - materialList[obj->getMatIndex()].getAlpha());
					}
				}                
			}
			// Soft Shadows.
			
			else {			
				double shadowAcc = 0.0;
				time_t seconds;
				time(&seconds);
				srand((unsigned int) seconds);

				for (int j = 0; j < MAXITERS; j++) {
					double temp = notShadow;
				
					// Randomly jitter lights by +/- .1 in all directions.
					int randX = (rand() % 2001) - 1000; 	// values -1000-1000
					double randXD = (double) randX / 10000; // values -.1 -.1

					int randY = (rand() % 2001) - 1000;  	// values -1000-1000
					double randYD = (double) randY / 10000; // values -.1 -.1

					int randZ = (rand() % 2001) - 1000;  	// values -1000-1000
					double randZD = (double) randZ / 10000; // values -.1 -.1
					
					Vec rand (randXD, randYD, randZD);
					
					L = l.getVec() - isect + rand;
					// Make sure we don't try to divide by 0.
					double lenL = L.vLen();
					if (lenL < EPS) {
						continue;
					}
					L.unitize();
					// Look for shadows
					for (int k = 0; k < objCount; k++) {
						Object* obj = ( objectList[k] );
						double tCur = obj->getIsecT((isect), L);
						
						Vec curIsect = isect + dir*(tCur);
						double curLen = curIsect.vLen();
						// Set flag and quit if shadow detected.
						if ( ((lenL - curLen) > EPS) && (tCur > EPS) ) {
							temp *= (1 - materialList[obj->getMatIndex()].getAlpha());
						}                
					}
					temp /= MAXITERS;
					shadowAcc += temp;

				}

				notShadow *= shadowAcc;
			}
		}
		// Directional lights
		else {
			L = l.getVec()*-1;
			L.unitize();
			for (int i = 0; i < objCount; i++) {
				Object* obj = ( objectList[i] );
				double tCur = obj->getIsecT(isect, L);					 
				if (tCur > EPS) {
					notShadow *= (1 - materialList[obj->getMatIndex()].getAlpha());
				}
			}				
		}

		Vec H = (L - dir);
		if (H.vLen() > EPS) {		
			H.unitize();	
		}
		// Clamp dot products to 0.
		double nDotL = normal.dot(L);
		if (nDotL < EPS) {
			nDotL = 0;
		}		
		double nDotH = normal.dot(H);
		if (nDotH < EPS) {
			nDotH = 0;
		}
		nDotH = pow (nDotH, m.getN());
		// Calculate remaining components.
		Color diff = Od * (m.getKd() * nDotL);
		Color spec = Os * (m.getKs() * nDotH);
		
		// Scale contribution if in shadow
		Color sum = (diff + spec) * notShadow;
		// Scale by light intensity and add to accumulator.
		lights = lights + sum*l.getCol();
	}


	
	// Calcuate relfection direction R.
	Vec I = dir*(-1);					//origin - isect;
	I.unitize();	
	double cosThetaI = normal.dot(I); 	// cos(theta_i), lets just call it that instead.

	// TODO: add pushes and pops to support objects inside other objects.	
	// Get previous and current material.
	double etaT = m.getEta();
	double etaI = currentEta.top();
	
	// Reverse normal direction if inside object, recaculate N dot I.
	if (cosThetaI < EPS) {	
		normal = normal * -1;
		cosThetaI = normal.dot(I);	
	}

	Vec R = (normal * (2 * cosThetaI)) - I;
	
	// Get the reflected color	
	Color reflected = rayTrace (isect, R, depth+1);
	
 	
	// Fr with Schlick's approx.
	double f0 = pow( (( etaT - etaI) / (etaT + etaI)), 2 );
	double Fr = f0 + (1 - f0) * pow( (1 - cosThetaI), 5 );
	
	reflected = reflected * Fr;

	double etaRatio = etaI / etaT;
	double sinThetaI = 1 - pow(cosThetaI, 2);

	Color refracted;
	
	// If there's not total internal reflection, find the refracted color.
	if ((etaT/etaI) - sinThetaI > -1*EPS) {
	
		double cosThetaT = sqrt(1 - pow(etaRatio, 2)*sinThetaI);
	
		Vec T = (normal * (-1.0* cosThetaT)) + ((normal*cosThetaI) - I)*etaRatio;
	
		refracted = rayTrace (isect, T, depth+1);		
			
		refracted = refracted * ( (1 - Fr) * ( 1 - (m.getAlpha()) ) );
	}
	// Total internal reflection, set the refracted color to the reflected color
	else {
		refracted = reflected;
	}
	// Ambient color plus contribution of all light sources.
	// And reflected and refracted components.
	return (ambient + lights + reflected + refracted);	
}
