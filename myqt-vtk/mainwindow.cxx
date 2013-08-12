 #include <QtGui>

 #include "mainwindow.h"
 #include "drawarea.h" 
//#include "vtkstuff.h"
#include <iostream>
#include "vtkwindow.h"
#include "polygoncombobox.h"
#include "errorwindow.h"





MainWindow::MainWindow()
 {
     
	setupWindow();
//     createActions();
 //    createMenus();

//drawArea = new DrawArea;
  //   setCentralWidget(drawArea);
     setWindowTitle(tr("OpacitySetter"));
     resize(1280, 840);

     vtkWindow = new VtkWindow(this);

     vtkWindow->setWindowFlags(Qt::Window);
     vtkWindow->setupWindow();
     vtkWindow->show();



 }

void MainWindow::setupWindow(){




	drawArea = new DrawArea(this);
	//setCentralWidget(drawArea);

	drawArea->setGeometry(QRect(50, 50,400, 400));
	drawArea->resizeImage(&(drawArea->image), QSize(drawArea->geometry().width(), drawArea->geometry().height()));

	drawArea->initialize();



setMinGradient = new QLineEdit(this);
setMinGradient->setObjectName(QString::fromUtf8("setMinGradient"));
setMinGradient->setGeometry(QRect(480, 120, 100, 30));

setMaxGradient = new QLineEdit(this);
setMaxGradient->setObjectName(QString::fromUtf8("setMinGradient"));
setMaxGradient->setGeometry(QRect(480, 160, 100, 30));

setMinValue = new QLineEdit(this);
setMinValue->setObjectName(QString::fromUtf8("setMinGradient"));
setMinValue->setGeometry(QRect(480, 200, 100, 30));

setMaxValue = new QLineEdit(this);
setMaxValue->setObjectName(QString::fromUtf8("setMinGradient"));
setMaxValue->setGeometry(QRect(480, 240, 100, 30));



labelSetMinGradient = new QLabel(this);
labelSetMinGradient->setObjectName(QString::fromUtf8("labelSetMinGradient"));
labelSetMinGradient->setGeometry(QRect(setMaxGradient->geometry().topLeft().x()+100, setMaxGradient->geometry().topLeft().y(), 200, 17));
labelSetMinGradient->setText(QApplication::translate("MainWindow", "set min Gradient", 0, QApplication::UnicodeUTF8));

labelSetMaxGradient = new QLabel(this);
labelSetMaxGradient->setObjectName(QString::fromUtf8("labelSetMaxGradient"));
labelSetMaxGradient->setGeometry(QRect(setMinGradient->geometry().topLeft().x()+100, setMinGradient->geometry().topLeft().y(), 200, 17));
labelSetMaxGradient->setText(QApplication::translate("MainWindow", "set max Gradient", 0, QApplication::UnicodeUTF8));

labelSetMinValue = new QLabel(this);
labelSetMinValue->setObjectName(QString::fromUtf8("labelSetMinValue"));
labelSetMinValue->setGeometry(QRect(setMinValue->geometry().topLeft().x()+100, setMinValue->geometry().topLeft().y(), 200, 17));
labelSetMinValue->setText(QApplication::translate("MainWindow", "set min value", 0, QApplication::UnicodeUTF8));

//drawArea->geometry().bottomRight();

labelSetMaxValue = new QLabel(this);
labelSetMaxValue->setObjectName(QString::fromUtf8("labelSetMaxValue"));
labelSetMaxValue->setGeometry(QRect(setMaxValue->geometry().topLeft().x()+100, setMaxValue->geometry().topLeft().y(), 200, 17));
labelSetMaxValue->setText(QApplication::translate("MainWindow", "set max value", 0, QApplication::UnicodeUTF8));












displayMinGradient = new QLabel(this);

displayMinGradient->setObjectName(QString::fromUtf8("displayMinGradient"));

displayMinGradient->setGeometry(QRect(drawArea->geometry().bottomRight().x()+50, drawArea->geometry().bottomRight().y(), 100, 30));

displayMinGradient->setText(QApplication::translate("MainWindow", "minGradient", 0, QApplication::UnicodeUTF8));



displayMaxGradient = new QLabel(this);
displayMaxGradient->setObjectName(QString::fromUtf8("displayMaxGradient"));
displayMaxGradient->setGeometry(QRect(drawArea->geometry().topRight().x()+50, drawArea->geometry().topRight().y(), 100, 30));
displayMaxGradient->setText(QApplication::translate("MainWindow", "maxGradient", 0, QApplication::UnicodeUTF8));



displayMinValue = new QLabel(this);
displayMinValue->setObjectName(QString::fromUtf8("displayMinValue"));
displayMinValue->setGeometry(QRect(drawArea->geometry().bottomLeft().x(), drawArea->geometry().bottomLeft().y()+30, 100, 30));
displayMinValue->setText(QApplication::translate("MainWindow", "minvalue", 0, QApplication::UnicodeUTF8));


//drawArea->geometry().bottomRight();

displayMaxValue = new QLabel(this);
displayMaxValue->setObjectName(QString::fromUtf8("displayMaxValue"));
displayMaxValue->setGeometry(QRect(drawArea->geometry().bottomRight().x()-50, drawArea->geometry().bottomRight().y()+30, 100, 30));
displayMaxValue->setText(QApplication::translate("MainWindow", "maxvalue", 0, QApplication::UnicodeUTF8));




apply = new QPushButton(this);
apply->setObjectName(QString::fromUtf8("Apply"));
apply->setGeometry(QRect(480, 280, 113, 27));
apply->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));



newPolygon = new QPushButton(this);
newPolygon->setObjectName(QString::fromUtf8("newPolygon"));
newPolygon->setGeometry(QRect(480, 520, 100, 30));
newPolygon->setText(QApplication::translate("MainWindow", "newPolygon", 0, QApplication::UnicodeUTF8));

renderButton = new QPushButton(this);
renderButton->setObjectName(QString::fromUtf8("render"));
renderButton->setGeometry(QRect(480, 560, 100, 30));
renderButton->setText(QApplication::translate("MainWindow", "render", 0, QApplication::UnicodeUTF8));


polygonList = new PolygonComboBox(this);
polygonList->setGeometry(QRect(480, 400, 100, 30));
polygonList->addItem("1");



opacityValue = new QLineEdit(this);
opacityValue->setObjectName(QString::fromUtf8("setMinGradient"));
opacityValue->setGeometry(QRect(480, 360, 100, 30));


setOpacity = new QPushButton(this);
setOpacity->setObjectName(QString::fromUtf8("setOpacity"));
setOpacity->setGeometry(QRect(480, 480, 113, 27));
setOpacity->setText(QApplication::translate("MainWindow", "Apply Opacity", 0, QApplication::UnicodeUTF8));


std::cout <<"drawarea initialized" << std::endl;




connect(apply, SIGNAL(clicked()), this, SLOT(setValues()));

connect(setOpacity, SIGNAL(clicked()), this, SLOT(applyOpacity()));

connect(newPolygon, SIGNAL(clicked()), this, SLOT(createNewPolygon()));

connect(polygonList, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSelectionChanged(int)));


}



void MainWindow::applyOpacity(){
	bool success;
	float value = opacityValue -> text().toFloat(&success);
	if (success)
		drawArea->setOpacity(drawArea->getSelectedPolygon(), drawArea->getSelectedPoint(), value);
	else
		std::cout <<"opacity value could not be converted to float"<< std::endl;

}


void MainWindow::setValues(){

	double ming, maxg, minv, maxv ;
	bool succeed = true;
	bool ander;
	        ming = (setMinGradient -> text()).toDouble(&ander); succeed = succeed && ander;
	        maxg = (setMaxGradient -> text()).toDouble(&ander); succeed = succeed && ander;
	        minv = (setMinValue -> text()).toDouble(&ander); succeed = succeed && ander;
	        maxv = (setMaxValue -> text()).toDouble(&ander); succeed = succeed && ander;
	if (!succeed)
	{
		 //QString dialog();
		 displayErrorWindow("A value could not be converted to double. Please enter valid numbers");
		return;
	}
	drawArea ->setvalues(ming, maxg, minv, maxv);


}

void MainWindow::createNewPolygon(){
	polygonList->addItem(QString("%1").arg(drawArea->createNewPolygon()));
	polygonList->setCurrentIndex(drawArea->polygons.size()-1);

}




void MainWindow::handleSelectionChanged(int index){
		 drawArea->currentPolygon = polygonList->currentText().toInt()-1;
	 }


void MainWindow::render(){

}
