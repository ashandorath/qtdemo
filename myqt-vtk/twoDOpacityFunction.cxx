#include "twoDOpacityFunction.h"
#include <math.h>



float cotangent(twoDFloatPoint a, twoDFloatPoint b, twoDFloatPoint c){
	twoDFloatPoint ba(a.x-b.x, a.y-b.y);
	twoDFloatPoint bc(c.x-b.x, c.y-b.y);
	return ((bc.x*ba.x+bc.y*ba.y)/fabs(bc.x*ba.y-ba.y*bc.x));
}

/*
 * cotangent(vector2d a, vector2d b, vector2d c)
{
vector2d ba = a-b
vector2d bc = c-b
return ( dot(bc, ba)/cross(bc, ba))

}
 */

void twoDOpacityFunction::computeBarycentricCoordinates(twoDFloatPoint p, std::vector<twoDFloatPoint> polygon, float* w)
{
	unsigned int size = polygon.size();
	float weightSum = 0;
	int prev, next;
	for (int i = 0; i< size; i++){
		prev = (i+size-1)%size;
		next = (i+1)%size;
		w[i] = (cotangent(p, polygon[i],polygon[prev])+cotangent(p,polygon[i],polygon[next]))/sqrt(pow(p.x-polygon[i].x+p.y-polygon[i].y,2));
		weightSum += w[i];
	}

	for (int i = 0; i<size; i++){
		w[i] /= weightSum;
	}

}

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





void twoDOpacityFunction::addPolygonToTable(std::vector<twoDFloatPoint> points, double* table, double xStart, double xEnd, double yStart,
		double yEnd, int sizeX, int sizeY, int strideX, int strideY){

//find starting and end points on the table
	double maxX=0, maxY=0, minY, minX;
	maxX = points[0].x;
	minX = points[0].x;
	maxY = points[0].y;
	minY = points[0].y;
	for (int i = 1; i< points.size(); i++){
		maxX = points[i].x>maxX ? points[i].x : maxX;
		minX = points[i].x<maxX ? points[i].x : minX;
		maxY = points[i].y>maxY ? points[i].y : maxY;
		minY = points[i].y<minY ? points[i].y : minY;
	}

	int xTableStart, xTableEnd, yTableStart, yTableEnd;

	xTableStart = floor((minX-xStart)/((double)sizeX));
	xTableEnd = ceil((maxX-xStart)/((double)sizeX));
	yTableStart = floor((minY-yStart)/((double)sizeY));
	yTableEnd = ceil((maxY-yStart)/((double)sizeY));

//x is accross on the field, y is up down ->
	for (int i = yTableStart; i<yTableEnd; i++){
		for (int j = xTableStart; j<xTableEnd; j++){
			//calculate value and insert

		}
	}

}



void twoDOpacityFunction::getTable(const std::vector<std::vector<twoDFloatPoint> > &areas,
		double* table, double xStart, double xEnd, double yStart,
		double yEnd, int sizeX, int sizeY, int strideX, int strideY){

	//add each polygon to the table


}
