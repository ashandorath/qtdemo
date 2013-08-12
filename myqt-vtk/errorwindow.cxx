#include "errorwindow.h"

void displayErrorWindow(QString dialog){
	QMessageBox msgBox;
	msgBox.setText(dialog);
	msgBox.exec();

}
