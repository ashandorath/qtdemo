#ifndef POLYGONCOMBOBOX_H
#define POLYGONCOMOBOX_H

#include <QtGui>

class PolygonComboBox: public QComboBox
 {
	 Q_OBJECT
 public:


	 PolygonComboBox(QWidget* parent):QComboBox(parent)
	 {
		 this->setParent(parent);

	 };
	 ~ PolygonComboBox(){};

	 void polygonChangedThroughDrawer(int index){
	 setCurrentIndex(index);

	 };


 };
#endif
