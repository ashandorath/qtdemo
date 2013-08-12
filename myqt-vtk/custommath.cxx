#include "custommath.h"
#include <iostream>

float cotangent(twoDOpacityPoint a, twoDOpacityPoint b, twoDOpacityPoint c) {
	twoDOpacityPoint ba(a.fx - b.fx, a.fy - b.fy);
	twoDOpacityPoint bc(c.fx - b.fx, c.fy - b.fy);
	return ((bc.fx * ba.fx + bc.fy * ba.fy) / fabs(bc.fx * ba.fy - ba.fx * bc.fy));
}

/*
 * cotangent(vector2d a, vector2d b, vector2d c)
 {
 vector2d ba = a-b
 vector2d bc = c-b
 return ( dot(bc, ba)/cross(bc, ba))

 }
 */

 void computeBarycentricCoordinates(twoDOpacityPoint p,
		const opacityPolygon &polygon, float* w) {
	unsigned int size = polygon.count();
	float weightSum = 0;
	int prev, next;
	for (int i = 0; i < size; i++) {
		prev = (i + size - 1) % size;
		next = (i + 1) % size;
		w[i] = (cotangent(p, polygon.point(i), polygon.point(prev))
				+ cotangent(p, polygon.point(i), polygon.point(next)))
				/ (pow(p.fx - polygon.point(i).fx,2.0f)+ pow(p.fy - polygon.point(i).fy, 2.0f));

		weightSum += w[i];
	}

	for (int i = 0; i < size; i++) {
		w[i] /= weightSum;

	}

}

 bool insidePolygon(twoDOpacityPoint p,
		 opacityPolygon polygon){

}
