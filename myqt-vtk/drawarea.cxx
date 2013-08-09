#include "drawarea.h"
#include <QtGui>
#include <iostream>
#include "polygoncombobox.h"


DrawArea::DrawArea(QWidget *parent) :
		QWidget(parent) {
	setAttribute(Qt::WA_StaticContents);

}

void DrawArea::initialize(){
	circleRadius = 10;
	clearImage();
	maximumDistanceFromLine = 6;
	opacityPolygon first;
	polygons.push_back(first);
	currentPolygon = 0;
}


void DrawArea::resizeImage(QImage *image, const QSize &newSize) {
	if (image->size() == newSize)
		return;
	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}

void DrawArea::clearImage() {
	image.fill(qRgb(255, 255, 255));
	modified = true;
	update();
}

void DrawArea::drawLine(const QPoint &start, const QPoint &end,
		QPainter &painter) {

	painter.drawLine(start, end);

//	int rad = (myPenWidth / 2) + 2;
	/*update(QRect(start, end).normalized()
	 .adjusted(-rad, -rad, +rad, +rad));*/
}

/*
 * Copyright (c) 1970-2003, Wm. Randolph Franklin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimers.
    Redistributions in binary form must reproduce the above copyright notice in the documentation and/or other materials provided with the distribution.
    The name of W. Randolph Franklin may not be used to endorse or promote products derived from this Software without specific prior written permission.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
     (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;
  }
  return c;
}
*/
bool DrawArea::insidePolygon(float px, float py, const opacityPolygon &polygon){

	int size = polygon.count();
	if (size < 3)
		return false;

	int i, j= 0;
	 bool inside = false;
	 float ix, iy, jx, jy; //floats for vertex x and y's and for point

	 for (i = 0, j=size-1; i<size; j= i ,i++){
		 ix = (float) polygon.point(i).position.x(); iy = (float) polygon.point(i).position.y();
		 jx = (float) polygon.point(j).position.x(); jy = (float) polygon.point(j).position.y();

		 if ( ((iy>py) != (jy>py)) &&
			     (px < (jx-ix) * (py-iy) / (jy-iy) + ix) )
			       inside = !inside;
	 }


	  return inside;

}

void DrawArea::colorOpacity(){

	unsigned int nPolygons = polygons.size();
	for (int i = 0; i< image.width(); i++){
		for (int j = 0; j < image.height(); j++){
			for (int l = 0; l<nPolygons; l++){

				if (insidePolygon((float)i, (float) j, polygons[l]) ){
					float average = 0.0f;
	//switch to general barycentric coordinates. see firefox tab
					int size = polygons[l].count();
					for ( int k = 0; k<size; k++){
						average += polygons[l].point(k).opacity* sqrt(
								pow(((float) polygons[l].point(k).position.x())-((float) i),2)+
								pow(((float) polygons[l].point(k).position.y())-((float) j),2) );
					}
					image.setPixel(i,j,qRgb(average*255,0,0));
				}
			}
		}
	}
	update();
}

void DrawArea::drawPolygon(const QColor &color, const opacityPolygon &polygon, QPainter &painter){

	int sizem1 = std::max(polygon.count() - 1, 0);
		for (int i = 0; i < sizem1; i++) {
			drawLine(polygon.point(i).position, polygon.point(i + 1).position,
					painter);

		}
		if (sizem1 > 0) {
			drawLine(polygon.point(0).position, polygon.point(sizem1).position,
					painter);
		}

}


void DrawArea::drawLines(QColor color) {
	QPainter painter(&image);
	painter.setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	unsigned int size = polygons.size();
	for (int i = 0; i<size; i++){
		drawPolygon(color, polygons[i], painter);
	}

	painter.setPen(
			QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
					Qt::RoundJoin));
}



void DrawArea::drawCircle(const QPoint &point) {
	QPainter painter(&image);
	painter.drawEllipse(point.x() - circleRadius, point.y() - circleRadius,
			2 * circleRadius, 2 * circleRadius);
	modified = true;
	//update();

}

void DrawArea::drawCircles() {
	unsigned int size = polygons.size();
	for (unsigned int i = 0; i < size; i++) {
		int npoints = polygons[i].count();
		for (int k = 0; k<npoints; k++){
			drawCircle(polygons[i].point(k).position);
		}
	}
}

/*
bool DrawArea::nearPoint(const QPoint &point) {
	bool near = false;
	unsigned int size = opacityPoints.size();
	for (unsigned int i = 0; i < size; i++) {
		if (sqrt(
				pow(opacityPoints[i].position.x() - point.x(), 2)
						+ pow(opacityPoints[i].position.y() - point.y(), 2))) {
			near = true;
			break;
		}
	}
	return near;
}
*/
bool DrawArea::nearPoint(unsigned int &polygonIndex, unsigned int &pointIndex, const QPoint &point) {
	bool near = false;
	unsigned int size = polygons.size();

	for (unsigned int i = 0; i < size; i++) {
		int npoints = polygons[i].count();
		for (int j = 0 ; j<npoints; j++){
			if (sqrt(
					pow(polygons[i].point(j).position.x() - point.x(), 2)
							+ pow(polygons[i].point(j).position.y() - point.y(), 2))
					< circleRadius) {
				near = true;
				polygonIndex = i;
				pointIndex = j;
				break;
			}
		}
	}
	return near;
}

float DrawArea::minimum_distance(QPoint start, QPoint end, QPoint point) {
	// Return minimum distance between line segment vw and point p

	const float l2 = (float) pow(start.x() - end.x(), 2)
			+ pow(start.y() - end.y(), 2);  // i.e. |w-v|^2 -  avoid a sqrt
	if (l2 == 0.0)
		return -1.0f;   // v == w case
	// Consider the line extending the segment, parameterized as v + t (w - v).
	// We find projection of point p onto the line.
	// It falls where t = [(p-v) . (w-v)] / |w-v|^2
	const float t = ((float) ((point.x() - start.x()) * (end.x() - start.x())
			+ (point.y() - start.y()) * (end.y() - start.y()))) / l2;
	if (t < 0.0)
		return -1;       // Beyond the 'v' end of the segment
	else if (t > 1.0)
		return -1;  // Beyond the 'w' end of the segment
	QPoint projection = start + t * (end - start); // Projection falls on the segment
	return sqrt((float) pow(projection.x() - point.x(), 2)
			+ pow(projection.y() - point.y(), 2));
}




bool DrawArea::nearLine(const QPoint &point, float maxdist,
		unsigned int &polygonIndex, unsigned int &pointIndex) {
	bool near = false;
	unsigned int npolygons = polygons.size();
	for (int k = 0; k<npolygons; k++){
		unsigned int size = polygons[k].count();

		for (unsigned int i = 0; i < size; i++) {
			float distance = minimum_distance(polygons[k].point(i).position,
					polygons[k].point((i + 1)%size).position, point);
			if (distance > 0 && distance < maxdist) {
				near = true;
				polygonIndex = k;
				pointIndex = (i+1)%size;
				return near;
			}
		}
	}
	return near;
}

void DrawArea::mousePressEvent(QMouseEvent *event) {
	if (event->pos().x() > image.width() || event->pos().y() > image.height() ||
			event->pos().x() < 0 || event->pos().y() < 0) {
		outofbounds = true;
		return;
	}

	//colorOpacity();

	unsigned int lineindex;
			unsigned int polygonIndex;
			unsigned int movingPointIndex;

	if (event->button() == Qt::LeftButton) {
		lastPoint = event->pos();

	//	 drawCircles();
	//	drawLines(Qt::white);



		leftMouseDown = true;

		if (movingCircle = nearPoint(polygonIndex, movingPointIndex, event->pos())) {
			drawLines(Qt::blue);

			drawCircles();

			selectedPoint = movingPointIndex;
			if (currentPolygon != polygonIndex)
							changeDisplayPolygonList(polygonIndex);
			currentPolygon = polygonIndex;

		}
		else if (nearLine(event->pos(), maximumDistanceFromLine, polygonIndex, lineindex)) {
			polygons[polygonIndex].points.insert(polygons[polygonIndex].points.begin() + lineindex, opacityPoint(event->pos()));
			drawLines(Qt::blue);
			drawCircles();
			movingCircle=true;
			movingPointIndex=lineindex;
			selectedPoint=lineindex;
			if (currentPolygon != polygonIndex)
				changeDisplayPolygonList(polygonIndex);
			currentPolygon = polygonIndex;


		}

		else {

			polygons[currentPolygon].points.push_back(opacityPoint(event->pos()));
			drawLines(Qt::blue);
			drawCircles();
			selectedPoint = polygons[currentPolygon].count()-1;

		}
	}

	else{
		if (nearPoint(polygonIndex, movingPointIndex, event->pos())){
			selectedPoint = movingPointIndex;
			currentPolygon = polygonIndex;
			deleteOpacityPoint(currentPolygon, selectedPoint);
		}

	}


}

void DrawArea::mouseMoveEvent(QMouseEvent *event) {
	if (leftMouseDown && movingCircle
			&& !(event->pos().x() > image.width()
					|| event->pos().y() > image.height()||
					event->pos().x() < 0 || event->pos().y() < 0)) {
		image.fill(qRgb(255, 255, 255));
		polygons[currentPolygon].points[selectedPoint] = event->pos();
		drawCircles();
		drawLines(Qt::blue);
		//colorOpacity();
		update();
	}
}

void DrawArea::mouseReleaseEvent(QMouseEvent *event) {
	colorOpacity();
	update();
	outofbounds = false;

}

void DrawArea::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, image, dirtyRect);
}

void DrawArea::resizeEvent(QResizeEvent *event) {
	if (width() > image.width() || height() > image.height()) {
		int newWidth = width() / 2;
		int newHeight = height() / 2;
		resizeImage(&image, QSize(newWidth, newHeight));
		update();
	}
	QWidget::resizeEvent(event);
}

unsigned int DrawArea::getSelectedPoint(){
	return selectedPoint;
}

unsigned int DrawArea::getSelectedPolygon(){
	return currentPolygon;
}


void DrawArea::deleteOpacityPoint(int polygonIndex, int index){
	if (polygonIndex < polygons.size()){
		if (index < polygons[polygonIndex].count()){
			polygons[polygonIndex].points.erase(polygons[polygonIndex].points.begin() + index);
			clearImage();
			drawLines(Qt::blue);
			drawCircles();
			update();
			index = polygons[polygonIndex].count()+100;
		}
	}
}

void DrawArea::setOpacity(unsigned int polygonIndex, unsigned int pointIndex, float value){
	if(polygonIndex>polygons.size())
		return;
	if (pointIndex< polygons[polygonIndex].count())
		polygons[polygonIndex].points[pointIndex].opacity = value;
}




int DrawArea::createNewPolygon(){
	opacityPolygon polygon;
	polygons.push_back(polygon);
	currentPolygon = polygons.size()-1;
	return currentPolygon+1;
}

void DrawArea::changeDisplayPolygonList(int index){
	polygonComboBox->polygonChangedThroughDrawer(index);
}


twoDOpacityFloatPoint DrawArea::drawPointToRealPoint(QPoint position, float opacity){
	//tbd
	return twoDOpacityFloatPoint(position.x(),position.y(), opacity);
}

void DrawArea::packUpAreas(std::vector<std::vector<twoDOpacityFloatPoint> > &areas){
	float x,y;
	for (int i = 0; i<polygons.size(); i++){
		//std::vector<twoDOpacityFloatPoint> temp;
		areas.push_back(std::vector<twoDOpacityFloatPoint>());
		for (int j = 0; j< polygons[i].count(); j++){
				areas[i].push_back(drawPointToRealPoint(polygons[i].point(j).position, polygons[i].point(j).opacity));
		}
	}
}






//getters and setters


double DrawArea::getMinGradient(){
	return minGradient;
}

void DrawArea::setMinGradient(double newvalue){
	minGradient = newvalue;
}

double DrawArea::getMaxGradient(){
	return maxGradient;
}

void DrawArea::setMaxGradient(double newvalue){
	maxGradient = newvalue;
}

double DrawArea::getMinValue(){
	return minValue;
}

void DrawArea::setMinValue(double newvalue){
	minValue = newvalue;
}

double DrawArea::getMaxValue(){
	return minValue;
}

void DrawArea::setMaxValue(double newvalue){
	maxValue = newvalue;
}

void DrawArea::setvalues(double minG, double maxG, double minV, double maxV) {
	minGradient = minG;
	maxGradient = maxG;
	minValue = minV;
	maxValue = maxV;

}




