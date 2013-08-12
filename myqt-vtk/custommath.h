 #ifndef CUSTOMMATH_H
 #define CUSTOMMATH_H
#include <math.h>
#include <vector>
 #include <QPoint>


struct twoDOpacityPoint{
	float fx;
	float fy;
	QPoint position;
	float opacity;
	twoDOpacityPoint(float a, float b){
		fx = a;
		fy = b;
		position = QPoint((int)a, (int) b);
		opacity = 1;
	}
	twoDOpacityPoint(QPoint pos){
			position = pos;
			fx = pos.x();
			fy = pos.y();
			opacity = 1;
		}

	twoDOpacityPoint(float a, float b, float o){
		fx = a;
		fy = b;
		opacity = o;
	}
};

struct opacityPolygon{
	opacityPolygon(){

	}
	std::vector<twoDOpacityPoint> points;
	twoDOpacityPoint point(int i) const{
		return points[i];
	}
	int count() const{
		return points.size();
	}

};




float cotangent(twoDOpacityPoint a, twoDOpacityPoint b, twoDOpacityPoint c);

/*
 * cotangent(vector2d a, vector2d b, vector2d c)
 {
 vector2d ba = a-b
 vector2d bc = c-b
 return ( dot(bc, ba)/cross(bc, ba))

 }
 */

void computeBarycentricCoordinates(twoDOpacityPoint p,
		const opacityPolygon &polygon, float* w);

bool insidePolygon(twoDOpacityPoint p,
		opacityPolygon polygon);


#endif
