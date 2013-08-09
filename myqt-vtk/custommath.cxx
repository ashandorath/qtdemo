#include "custommath.h"

float cotangent(twoDOpacityFloatPoint a, twoDOpacityFloatPoint b, twoDOpacityFloatPoint c) {
	twoDOpacityFloatPoint ba(a.x - b.x, a.y - b.y);
	twoDOpacityFloatPoint bc(c.x - b.x, c.y - b.y);
	return ((bc.x * ba.x + bc.y * ba.y) / fabs(bc.x * ba.y - ba.y * bc.x));
}

/*
 * cotangent(vector2d a, vector2d b, vector2d c)
 {
 vector2d ba = a-b
 vector2d bc = c-b
 return ( dot(bc, ba)/cross(bc, ba))

 }
 */

 void computeBarycentricCoordinates(twoDOpacityFloatPoint p,
		const std::vector<twoDOpacityFloatPoint> &polygon, float* w) {
	unsigned int size = polygon.size();
	float weightSum = 0;
	int prev, next;
	for (int i = 0; i < size; i++) {
		prev = (i + size - 1) % size;
		next = (i + 1) % size;
		w[i] = (cotangent(p, polygon[i], polygon[prev])
				+ cotangent(p, polygon[i], polygon[next]))
				/ sqrt(pow(p.x - polygon[i].x + p.y - polygon[i].y, 2));
		weightSum += w[i];
	}

	for (int i = 0; i < size; i++) {
		w[i] /= weightSum;
	}

}

 bool insidePolygon(twoDOpacityFloatPoint p,
		std::vector<twoDOpacityFloatPoint> polygon){

}
