#ifndef TWOD_OPACITY_FUNCTION_H
#define TWOD_OPACITY_FUNCTION_H

#include "point.h"
#include <vector>

class twoDOpacityFunction {

//void gettable(double* table){

//}

	void computeBarycentricCoordinates(twoDFloatPoint p, std::vector<twoDFloatPoint> polygon, float* w);
	void addPolygonToTable(std::vector<twoDFloatPoint> points, double* table, double xStart, double xEnd, double yStart,
			double yEnd, int sizeX, int sizeY, int strideX, int strideY);

//lookuptable  ---
	void getTable(const std::vector<std::vector<twoDFloatPoint> > &areas,
			double*table, double xStart, double xEnd, double yStart,
			double yEnd, int sizeX, int sizeY, int strideX, int strideY);

};

#endif
