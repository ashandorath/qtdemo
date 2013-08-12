#ifndef TWOD_OPACITY_FUNCTION_H
#define TWOD_OPACITY_FUNCTION_H

#include "custommath.h"
#include <vector>

class twoDOpacityFunction {

//void gettable(double* table){

//}

	//void computeBarycentricCoordinates(twoDOpacityPoint p, std::vector<twoDOpacityPoint> polygon, float* w);
	void addPolygonToTable(const opacityPolygon &polygon,
			double* table, float xStart, float xEnd, float yStart, float yEnd,
			int sizeX, int sizeY, int strideX, int strideY);

//lookuptable  ---
	void getTable(const std::vector<std::vector<twoDOpacityPoint> > &areas,
			double*table, double xStart, double xEnd, double yStart,
			double yEnd, int sizeX, int sizeY, int strideX, int strideY);

};

#endif
