#include "ReadInput.h"
/* For debug. gotta add ifdefs.
using std::cout;
using std::endl;
*/
using std::ifstream;
using std::ofstream;
using std::stringstream;


ifstream inputFile;
	
		
string readInput(string fileName) {
	// Find the file extension and check it.
	int dotPos = fileName.find_last_of(".");	
	string ext = fileName.substr(dotPos);
	if (ext != ".txt")
	{
		throw ("Error, input file extension must be .txt, not " + ext + ".\n").c_str();		
	}
	
	// Try to open the file.
	inputFile.open(fileName.c_str());
	if  ( !inputFile.is_open() )
	{
	    throw ("Error, could not open specified file '" + fileName + "'\n").c_str();
	}

	// Reading keywords from file. Basic error checking on input values.	
	while (! inputFile.eof() ) {	
		string word = "";		//Prevent saving previous word on last pass bug.	
		inputFile >> word;
		// Image setup variables.
		if (word[0] == '#') {
			getline(inputFile, word);
			continue;
			
		}
		if ( word == "eye" ) {
			// Point, not a vector. Do not unitize!
			eye.set( readVec() );
		}
		else if ( word == "viewdir" ) {
			viewDir.set( readVec() );
			if ( viewDir.isZero() ) {
				throw "Error, view direction input cannot be the zero vector.\n";
			}
			viewDir.unitize();
		}
		else if ( word == "updir" ) {
			upDir.set( readVec() );
			if ( upDir.isZero() ) {
				throw "Error, up direction input cannot be the zero vector.\n";
			}
			upDir.unitize();
		}
		else if ( word == "fovh" ) {
			inputFile >> fovh;
			if (fovh <= 0 || fovh > 180) {
				throw "Error, invalid Horizontal FOV (degrees).\n";
			}
		}

		else if ( word == "imsize" ) {
			inputFile >> width >> height;
			if (width <= 0 || height <= 0) {
				throw "Error, Invalid height or width.\n";
			}
		}
		else if ( word == "bkgcolor" ) {
			bg.set( readCol() );
		}	
		
		// Non object elements
		else if (word == "light") {			
			lightList.push_back( readLight() );
			lightCount++;
		}
		else if (word == "mtlcolor") {
			matCount++;
			materialList.push_back( readMat() );
		}
		else if (word == "texture") {		
			textureCount++;
			textureList.push_back( readTexture() );			
		}
		

		// Objects
		else if (word == "sphere") {			
			objectList.push_back( readSphere() );
			objCount++;
		}
		else if (word == "cylx") {			
			objectList.push_back( readCylX() );
			objCount++;
		}
		else if (word == "cyly") {			
			objectList.push_back( readCylY() );
			objCount++;
		}
		else if (word == "cylz") {			
			objectList.push_back( readCylZ() );
			objCount++;
		}
		else if (word == "cylz") {			
			objectList.push_back( readCylZ() );
			objCount++;
		}
		
		// Triangle stuff
		
		else if (word == "v") {
			if (vertexCount == 0) {
				vertexList.push_back( Vec (0, 0, 0) );
				vertexCount++;
			}				
			vertexList.push_back( readVec() );
			vertexCount++;
		}
		else if (word == "vt") {
			if (textCoordCount == 0) {
				textCoordList.push_back( Vec (0, 0, 0) );
				textCoordCount++;
			}				
			textCoordList.push_back( readVec2() );
			textCoordCount++;
		}
		else if (word == "vn") {
			if (normalCount == 0) {
				normalList.push_back( Vec (0, 0, 0) );
				normalCount++;
			}				
			normalList.push_back( readVec() );
			normalCount++;
		}
		else if (word == "f") {			
			objectList.push_back( readFace() );
			objCount++;
		}
		
		
  		// Flags
   		else if (word == "parallel") {
   			parallel = true;
   			dist = 0;
   		}
   		else if (word == "softshadows") {
   			softShadows = true;
   		}
   		else if (word == "viewdist" ) {
			inputFile >> dist;
			if (dist < EPS) {
				throw "Error, invalid FOV distance.\n";
			}
			depthOfField = true;
		}
		else if ( word == "\0" ) {
			break;	
		}
		else {
			throw ("Error, Invalid keyword: " + word + "\n").c_str();
		}
	}

	// Done with input file, return output file name.
	inputFile.close();
	string outFile = fileName.substr(0, dotPos) + ".ppm";
	return outFile;   	
}

Vec readVec () {
	double a, b, c;
	inputFile >> a >> b >> c;
	return Vec(a, b, c);
} 
 
// Only reads 2 numbers. Z set to 0.
Vec readVec2 () {
	double a, b;
	inputFile >> a >> b;
	// Fix it instead of throwing an error.
	// throw "Error, texture coords must be between 0 and 1.\n";
	if (a - 1 > EPS ) {
		a = 1;
	}
	else if (a < EPS ) {
		a = 0;
	}
	if (b - 1 > EPS ) {
		b = 1;
	}
	else if ( b < EPS )  {
		b = 0;
	}
	return Vec (a, b, 0);
} 
Color readCol () {
	double a, b, c;
	inputFile >> a >> b >> c;

	return Color (a, b, c);
}

Material readMat () {
	Color objDiff = readCol();
	Color objSpect = readCol();
	Vec coeffs = readVec();
	if (coeffs.getx() > 1 || coeffs.getx() < 0) {
		throw "Error, invalid ka.\n";
	}
	if (coeffs.gety() > 1 || coeffs.gety() < 0) {
		throw "Error, invalid kd.\n";
	}
	if (coeffs.getz() > 1 || coeffs.getz() < 0) {
		throw "Error, invalid ks.\n";
	}
	double alpha, eta;
	int n;
	inputFile >> n >> alpha >> eta;
	if (n < 1) {
		throw "Error, invalid exponent n.\n";
	}
	if ((alpha - 1) > EPS || alpha < EPS*-1) {
		throw "Error, invalid alpha.\n";
	}
	return Material(objDiff, objSpect, coeffs, n, alpha, eta);
}
Light readLight () {
	Vec vec ( readVec() );
	int pt;
	inputFile >> pt;
	Color lCol = readCol() ;
	bool isPt = false;
	if (pt == 1) {
		isPt = true;
	}	
	
	Light l (vec, isPt, lCol) ;
	return l;	
}		
Texture* readTexture () {
	ifstream textureFile;
	string textureName;
	inputFile >> textureName;
	// Find the file extension and check it.
	int dotPos = textureName.find_last_of(".");	
	string ext = textureName.substr(dotPos);
	if (ext != ".ppm") {
		throw ("Error, texture file extension must be .ppm, not " + ext + "\n").c_str();		
	}

	// Try to open the file.
	textureFile.open(textureName.c_str());
	if  ( !textureFile.is_open() ) {
		throw ("Error, could not open specified texture file '" + textureName + "'\n").c_str();
	}

	string header;
	int w, h, c;
	textureFile >> header >> w >> h >> c;
	if (header != "P3") {
		throw ("Error, invalid texture header.\n");
	}
	Texture* out = new Texture (w, h);
	int r, g, b;
	double R, G, B;
	double C = (double) c;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			textureFile >> r >> g >> b;
			R = (double) r / C;
			G = (double) g / C;
			B = (double) b / C;
			Color c (R, G, B);
			out->setXY(x, y, c);
		}
	}
	return out;
}


Object* readSphere () {
	Vec cent( readVec() );
	double r;
	inputFile >> r;

	Object* ptr = new Sphere (matCount, textureCount, cent, r);
	return ptr;		
}
Object* readCylZ () {
	double x, y, r;
	inputFile >> x >> y >> r;
	Vec cent (x, y, 0);
	int a = 3;	
	
	Object* ptr = new Cyl (matCount, textureCount, cent, r, a);
	return ptr;
}
Object* readCylY () {
	double x, z, r;
	inputFile >> x >> z >> r;
	Vec cent (x, 0, z);
	int a = 2;
	Object* ptr = new Cyl (matCount, textureCount, cent, r, a);
	return ptr;
}
Object* readCylX () {
	double y, z, r;
	inputFile >> y >> z >> r;
	Vec cent (0, y, z);
	int a = 1;
	Object* ptr = new Cyl (matCount, textureCount, cent, r, a);
	return ptr;
}


int strToI (const string &str) {
	int out;
	stringstream convert;
	convert << str;
	convert >> out;
	if (out != 0) {
		return out;
	}
	else {
		throw "Bad index.\n";
	}
}

Object* readFace () {
	int v1, v2, v3;
	int t1, t2, t3;
	int n1, n2, n3;
    string a, b, c;
    
    // Read all vertex data
	inputFile >> a >> b >> c;

	//cout << "raw: " << a << ' ' << b <<  ' ' << c << endl;
	int x = a.find("/");
	// Case: non-textured, flat shading (no text, normal)
	if (x == -1) {
		v1 = strToI (a);	
		v2 = strToI (b);
		v3 = strToI (c);	

		t1 = -1;
		t2 = -1;
		t3 = -1;
		n1 = -1;
		n2 = -1;
		n3 = -1;
	}
	else {
		// Find other two indicies. Assuming all vertex have same properties. 
		int y = b.find("/");
		int z = c.find("/");
		
		// Break off Vertex indicies
		string a1 = a.substr(0, x);		
		string b1 = b.substr(0, y);
		string c1 = c.substr(0, z);
		
		v1 = strToI(a1);
		v2 = strToI(b1);
		v3 = strToI(c1);	
		
		// The remaining string contains texture index, normal index, or both.
		string a2 = a.substr(x+1, a.length()-1-x);
		string b2 = b.substr(y+1, b.length()-1-y);
		string c2 = c.substr(z+1, c.length()-1-z);
		
//		cout << a2 << " " << b2 << " " << c2 << endl;
		// Case: Textured, flat shading (no normal)
		int x1 = a2.find("/");
		if (x1 == -1) {
			t1 = strToI(a2);
			t2 = strToI(b2);
			t3 = strToI(c2);
			
			//cout << t1 << " " << t2 << " " << t3 << endl;
			n1 = -1;
			n2 = -1;
			n3 = -1;
		}
		else {
			int y1 = b2.find("/");
			int z1 = c2.find("/");

			// If we made it this far there's a normal index so take it.
			string a4 = a2.substr(x1+1, a2.length()-1-x1);
			string b4 = b2.substr(y1+1, b2.length()-1-y1);
			string c4 = c2.substr(z1+1, c2.length()-1-z1);
			
			n1 = strToI(a4);
			n2 = strToI(b4);
			n3 = strToI(c4);
			
			// Case: Textured, smooth shading
			if (x1 != 0) {
				string a3 = a2.substr(0, x1);
				string b3 = b2.substr(0, y1);
				string c3 = c2.substr(0, z1);
				
				t1 = strToI(a3);
				t2 = strToI(b3);
				t3 = strToI(c3);
			}
			
			// Case: Untextured, smooth shading 
			else {
				t1 = -1;
				t2 = -1;
				t3 = -1;
			}
		}
	} 
	
	/*
	cout << v1 << ' ' << v2 <<  ' ' << v3 << endl;
	cout << t1 << ' ' << t2 <<  ' ' << t3 << endl;
	cout << n1 << ' ' << n2 <<  ' ' << n3 << endl;
	*/
	
	VecI v (v1, v2, v3);
	VecI t (t1, t2, t3);
	VecI n (n1, n2, n3);
	
	Object* out = new Triangle (matCount, textureCount, v, t, n);
	return out; 			
}



void writeOutput (string out, Image &image)
{
	int const MAX_COLORS = 255;
	// Open output file.
	ofstream outFile;
	outFile.open( out.c_str() );

	// .ppm Header.
	outFile << "P3\n";
	outFile << "#Scott Myran's Assignment 1d output file.\n";
	outFile << width << " " << height << "\n";
	outFile << MAX_COLORS << "\n";

	// Write image data.
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Round values to nearest int.
			outFile << (int) (0.5 + MAX_COLORS*image[x][y].getR()) << " ";
			outFile << (int) (0.5 + MAX_COLORS*image[x][y].getG()) << " ";
			outFile << (int) (0.5 + MAX_COLORS*image[x][y].getB()) << "\n";
		}
	}
	outFile.close();
}
