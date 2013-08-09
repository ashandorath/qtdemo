#ifndef POINT_H
#define POINT_H

#include "point.h"

class twoDOpacityFunction {

//void gettable(double* table){

//}

//lookuptable  ---
	void getTable(const std::vector<std::vector<twoDFloatPoint> > &areas,
			double*table, double xStart, double xEnd, double yStart,
			double yEnd, int sizeX, int sizeY, int strideX, int strideY);

};

#endif
