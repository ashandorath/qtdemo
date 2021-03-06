#ifndef VTKINTERFACE
#define VTKINTERFACE
#include <vtkSmartPointer.h>
#include <vtkSphere.h>
#include <vtkSampleFunction.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolumeProperty.h>
#include <vtkCamera.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkXMLImageDataReader.h>
#include "vtkQuadric.h"


class VtkInterface {

public:

int dostuff(int argc, std::string filename);

vtkSmartPointer<vtkXMLImageDataReader> reader; 

vtkSmartPointer<vtkImageData> imageData;
vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity;
vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity;
vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper;
vtkSmartPointer<vtkVolumeProperty> volumeProperty;
vtkSmartPointer<vtkRenderWindow> renWin;
vtkSmartPointer<vtkRenderer> ren1;
vtkSmartPointer<vtkRenderWindowInteractor> iren;

void createImageData();
};




#endif
