 #ifndef DRAWAREA_H
 #define DRAWAREA_H
 

#include <QColor>
 #include <QImage>
 #include <QPoint>
 #include <QWidget>
#include "point.h"




class PolygonComboBox;

struct opacityPoint{
	opacityPoint(QPoint pos){
		position = pos;
		opacity = 1;
	}
	QPoint position;
	float opacity;

};

struct opacityPolygon{
	opacityPolygon(){

	}
	std::vector<opacityPoint> points;
	opacityPoint point(int i) const{
		return points[i];
	}
	int count() const{
		return points.size();
	}

};


class DrawArea : public QWidget
 {
     Q_OBJECT


public:

     //getters and setters
     double getMinGradient();

     void setMinGradient(double newvalule);

     double getMaxGradient();

     void setMaxGradient(double newvalule);

     double getMinValue();

     void setMinValue(double newvalule);

     double getMaxValue();

     void setMaxValue(double newvalule);

     void setvalues(double minG, double maxG, double minV, double maxV);

     //end of getters and setters



     void changeDisplayPolygonList(int index);

     DrawArea(QWidget *parent = 0);

     PolygonComboBox *polygonComboBox;
   void resizeImage(QImage *image, const QSize &newSize);

   void initialize();

     bool isModified() const { return modified; }
     QColor penColor() const { return myPenColor; }
     int penWidth() const { return myPenWidth; }
     QImage image;

     int circleRadius;
    // std::vector<opacityPoint> opacityPoints;
     std::vector<opacityPolygon> polygons;
     unsigned int currentPolygon;




     double minGradient, maxGradient, minValue, maxValue;
     float maximumDistanceFromLine;
     void deleteOpacityPoint(int polygonIndex, int index);

     unsigned int getSelectedPoint();
     unsigned int getSelectedPolygon();

     void setOpacity(unsigned int polygonIndex, unsigned int pointIndex, float value);

     void clearImage();

     int createNewPolygon();

     void packUpAreas(std::vector<std::vector<twoDFloatPoint> > &areas);


 protected:

     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void paintEvent(QPaintEvent *event);
     void resizeEvent(QResizeEvent *event);

 private:
     twoDFloatPoint drawPointToRealPoint(QPoint position);

     void colorOpacity();
     bool insidePolygon(float px, float py, const opacityPolygon &polygon);

     void drawPolygon(const QColor &color, const opacityPolygon &polygon, QPainter &painter);

     unsigned int selectedPoint;
  //   bool nearPoint(unsigned int &polygonIndex, unsigned int &pointIndex, const QPoint &point);
 	 bool nearPoint(unsigned int &polygonIndex, unsigned int &pointIndex, const QPoint &point);

   	 bool nearLine(const QPoint &point, float maxdist, unsigned int &polygonIndex, unsigned int &pointIndex);
   	float minimum_distance(QPoint start, QPoint end, QPoint point);

     void drawLineTo(const QPoint &endPoint);

     void drawCircle(const QPoint &point);
     void drawCircles();

     bool modified;
     bool leftMouseDown;
     bool movingCircle;
     bool outofbounds;
     unsigned int movingPointIndex;
     int myPenWidth;
     QColor myPenColor;

     QPoint lastPoint;

	void drawLine(const QPoint &start, const QPoint &end, QPainter &painter);
     void drawLines(QColor color);



 public slots:

 protected:

 private:


};

 #endif
