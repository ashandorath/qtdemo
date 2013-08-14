

#include "pqQVTKWidget.h"


class VtkInterface;

class vtkQTWindow : public QWidget{


public :
	vtkQTWindow(QWidget *parent);
	pqQVTKWidget *vtkDisplay;

	void setupWindow();
	int width, height;

	VtkInterface *vtkInterface;


};
