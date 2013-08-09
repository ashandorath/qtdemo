#ifndef TWOD_OPACITY_FUNCTION_H
#define TWOD_OPACITY_FUNCTION_H

#include "custommath.h"
#include <vector>

class twoDOpacityFunction {

//void gettable(double* table){

//}

	//void computeBarycentricCoordinates(twoDOpacityFloatPoint p, std::vector<twoDOpacityFloatPoint> polygon, float* w);
	void addPolygonToTable(std::vector<twoDOpacityFloatPoint> points,
			double* table, float xStart, float xEnd, float yStart, float yEnd,
			int sizeX, int sizeY, int strideX, int strideY);

//lookuptable  ---
	void getTable(const std::vector<std::vector<twoDOpacityFloatPoint> > &areas,
			double*table, double xStart, double xEnd, double yStart,
			double yEnd, int sizeX, int sizeY, int strideX, int strideY);

};

#endif
