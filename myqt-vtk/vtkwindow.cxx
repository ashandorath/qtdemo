#include "vtkwindow.h"
#include "vtkstuff.h"


VtkWindow::VtkWindow(QWidget *parent) :
		QWidget(parent) {

}

void VtkWindow::setupWindow(){

	width = 600;
	height = 400;
	resize(600,400);

	vtkDisplay = new pqQVTKWidget(this);
	vtkDisplay->setObjectName(QString::fromUtf8("qvtkWidgetLeft"));
	vtkDisplay->setGeometry(QRect(0, 0, width, height));

	vtkInterface = new VtkInterface();
	std::string temp = "temp";

	vtkInterface->dostuff(0,(temp.c_str()));

	vtkDisplay->GetRenderWindow()->AddRenderer(vtkInterface->ren1);

}
