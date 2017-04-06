#include "Texture.h"

using std::vector;

Texture::Texture (int width, int height) {	
	setW(width);
	setH(height);
	texture = new Image (width, vector<Color> (height));
}

Texture::~Texture () {
	delete texture;
}

void Texture::setW(int w) {
	if (w <= 0) {
		throw "Error, invalid texture width.";
	}
	width = w;
}
int Texture::getW() {
	return width;
}

void Texture::setH(int h) {
	if (h <= 0) {
		throw "Error, invalid texture height.";
	}
	height = h;
}	
int Texture::getH() {
	return height;
}

void Texture::setXY(int x, int y, Color c) {
	if (x < 0 || x >= width) {
		printf ("x: %d ", x);
		throw " Error, invalid X\n";
	}
	if (y < 0 || y >= height) {
		printf ("y: %d ", y);
		throw "Error, invalid Y.\n";
	}
	(*texture)[x][y].set(c);
}

Color Texture::getXY(int x, int y) {
	if (x < 0 || x >= width) {
		printf ("x: %d ", x);
		throw " Error, invalid X\n";
	}
	if (y < 0 || y >= height) {
		printf ("y: %d ", y);
		throw "Error, invalid Y.\n";
	}
	return ((*texture)[x][y]);
}
