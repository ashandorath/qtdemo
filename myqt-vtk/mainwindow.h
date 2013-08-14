

 #ifndef MAINWINDOW_H
 #define MAINWINDOW_H

 #include <QList>
 #include <QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QComboBox>
#include "point.h"
#include "vtkQTWindow.h"

//#include "vtkstuff.h"

//class VtkInterface;

 class DrawArea;

 class vtkQTWindow;

 class PolygonComboBox;




 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();
 
 PolygonComboBox *polygonList;
  DrawArea *drawArea;

  vtkQTWindow *vtkWindow;

QPushButton *apply;
QPushButton *setOpacity;
QPushButton *newPolygon;
QPushButton *renderButton;


QLineEdit *setMinGradient;
QLineEdit *setMaxGradient;
QLineEdit *setMinValue;
QLineEdit *setMaxValue;

QLabel *labelSetMinGradient;
QLabel *labelSetMaxGradient;
QLabel *labelSetMinValue;
QLabel *labelSetMaxValue;


QLabel *displayMinGradient;
QLabel *displayMaxGradient;
QLabel *displayMinValue;
QLabel *displayMaxValue;

QLineEdit *opacityValue;






//QLabel *errorMessages;

 protected:


 private slots:
 void setValues();
 void applyOpacity();
 void createNewPolygon();
 void handleSelectionChanged(int index);
 void render();
 void showPQ2DTFDialog();

 private:
void setupWindow();

 };

 #endif
