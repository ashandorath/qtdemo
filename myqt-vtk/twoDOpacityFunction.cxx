#include "twoDOpacityFunction.h"




/*
 * computeBarycentric(vector2d p, polygon Q, int n, real w[])
 {
 weightSum = 0;
 foreach vertex q_j of Q
 prev = (j+n -1)mod n
 next = (j+1) mod n
 w_j =( cotangent(p,q_j, qprev)+cotangent(p,q_j, qnext))/||p-q_j||²
 weightSum += w_j

 foreach weight w_j
 w_j /= weightSum

 }



 */

void twoDOpacityFunction::addPolygonToTable(const opacityPolygon &polygon,
		double* table, float xStart, float xEnd, float yStart, float yEnd,
		int sizeX, int sizeY, int strideX, int strideY) {

	for (int i = 0; i< sizeX*sizeY; i++){
		table[i]=0; //clear the table, we fill in the non zero values below
	}


//find starting and end polygon on the table
	float maxX = 0, maxY = 0, minY, minX;
	maxX = polygon.point(0).fx;
	minX = polygon.point(0).fx;
	maxY = polygon.point(0).fy;
	minY = polygon.point(0).fy;
	for (int i = 1; i < polygon.count(); i++) {
		maxX = polygon.point(i).fx > maxX ? polygon.point(i).fx : maxX;
		minX = polygon.point(i).fx < maxX ? polygon.point(i).fx : minX;
		maxY = polygon.point(i).fy > maxY ? polygon.point(i).fy : maxY;
		minY = polygon.point(i).fy < minY ? polygon.point(i).fy : minY;
	}

	int xTableStart, xTableEnd, yTableStart, yTableEnd;

	xTableStart = (int) floor((minX - xStart) / ((double) sizeX));
	xTableEnd = (int) ceil((maxX - xStart) / ((double) sizeX));
	yTableStart = (int) floor((minY - yStart) / ((double) sizeY));
	yTableEnd =  (int) ceil((maxY - yStart) / ((double) sizeY));

//x is accross on the field, y is up down ->
	float xpoint, ypoint;
	float * weights = new float[polygon.count()];
	for (int i = yTableStart; i < yTableEnd; i++) {
		for (int j = xTableStart; j < xTableEnd; j++) {
			xpoint = ((float)j)*((float)sizeX)/(minX - xStart);
			ypoint = ((float)i)*((float)sizeY)/(minY-yStart);
			if(insidePolygon(twoDOpacityPoint(xpoint,ypoint),polygon))
			{
				computeBarycentricCoordinates(twoDOpacityPoint(xpoint,ypoint,0), polygon, weights);
				double opacity = 0;
				for (int k = 0; k< polygon.count(); k++){
					opacity += weights[k]*polygon.point(k).opacity;
				}
				table[i*sizeY + j] = opacity;

			}


		}
	}

}

void twoDOpacityFunction::getTable(
		const std::vector<std::vector<twoDOpacityPoint> > &areas, double* table,
		double xStart, double xEnd, double yStart, double yEnd, int sizeX,
		int sizeY, int strideX, int strideY) {

	//add each polygon to the table

}
