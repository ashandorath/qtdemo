 #ifndef CUSTOMMATH_H
 #define CUSTOMMATH_H
#include <math.h>
#include <vector>


struct twoDOpacityFloatPoint{
	float x;
	float y;
	float opacity;
	twoDOpacityFloatPoint(float a, float b){
		x = a;
		y = b;
		opacity = -1;
	}
	twoDOpacityFloatPoint(float a, float b, float o){
		x = a;
		y = b;
		opacity = o;
	}
};




float cotangent(twoDOpacityFloatPoint a, twoDOpacityFloatPoint b, twoDOpacityFloatPoint c);

/*
 * cotangent(vector2d a, vector2d b, vector2d c)
 {
 vector2d ba = a-b
 vector2d bc = c-b
 return ( dot(bc, ba)/cross(bc, ba))

 }
 */

void computeBarycentricCoordinates(twoDOpacityFloatPoint p,
		const std::vector<twoDOpacityFloatPoint> &polygon, float* w);

bool insidePolygon(twoDOpacityFloatPoint p,
		std::vector<twoDOpacityFloatPoint> polygon);


#endif
