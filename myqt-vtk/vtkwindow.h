

#include "pqQVTKWidget.h"


class VtkInterface;

class VtkWindow : public QWidget{


public :
	VtkWindow(QWidget *parent);
	pqQVTKWidget *vtkDisplay;

	void setupWindow();
	int width, height;

	VtkInterface *vtkInterface;


};
