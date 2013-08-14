/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: pqTransferFunctionEditor.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME pqTransferFunctionEditor
// .SECTION Thanks
// <verbatim>
//
//  This file is part of the PointSprites plugin developed and contributed by
//
//  Copyright (c) CSCS - Swiss National Supercomputing Centre
//
//  John Biddiscombe
//
// </verbatim>

#include "pqTransferFunctionEditor.h"
#include "ui_pqTransferFunctionEditor.h"

#include <QDoubleValidator>
#include <QTimer>
#include <QChar>

#include <iostream>
using namespace std;

// Qvis includes
#include <Qvis2DTransferFunctionWidget.h>

// Paraview includes
#include "pqPipelineRepresentation.h"
#include "pqPropertyLinks.h"
#include "pqScalarsToColors.h"
#include "pqSMAdaptor.h"
#include "vtkSMProxy.h"
#include "vtkSMProperty.h"
#include "vtkSMProxyProperty.h"
#include "vtkSMIntVectorProperty.h"
#include "vtkSMStringVectorProperty.h"
//
#include "vtkPVDataInformation.h"

// vtk includes
#include "vtkSmartPointer.h"
#include "vtkEventQtSlotConnect.h"
//-----------------------------------------------------------------------------
class pqTransferFunctionEditor::pqInternals: public Ui::pqTransferFunctionEditor
{
public:
  pqPipelineRepresentation* Representation;
  vtkSmartPointer<vtkEventQtSlotConnect> VTKConnect;
  pqPropertyLinks Links;
  int BlockSignals;
  int Updating;

  pqInternals()
  {
    Representation = NULL;
    VTKConnect = vtkSmartPointer<vtkEventQtSlotConnect>::New();
    BlockSignals = 0;
    Updating = 0;
  }

};
//-----------------------------------------------------------------------------
pqTransferFunctionEditor::pqTransferFunctionEditor(QDialog *parent, Qt::WindowFlags f)
{
  QWidget::QWidget(parent,f);
  this->Internals = new pqTransferFunctionEditor::pqInternals();
  this->Internals->setupUi(this);

  //this->initialize();

  // We are usinging Queued slot execution where ever possible,
  // This ensures that the updateAllViews() slot is called
  // only after the vtkSMProperty has been changed by the pqPropertyLinks.


  //
  // Connect the transfer function widgets
  //

  connect(this->Internals->TransferFunction, SIGNAL(mouseReleased()), this,
      SLOT(onRegionValuesModified()), Qt::QueuedConnection);

  QDoubleValidator* validator;
  validator = new QDoubleValidator(this->Internals->YMin);
  validator->setBottom(0.0);
  this->Internals->YMin->setValidator(validator);

  validator = new QDoubleValidator(this->Internals->YMax);
  validator->setBottom(0.0);
  this->Internals->YMax->setValidator(validator);

  validator = new QDoubleValidator(this->Internals->XMin);
  this->Internals->XMin->setValidator(validator);

  validator = new QDoubleValidator(this->Internals->XMax);
  this->Internals->XMax->setValidator(validator);

  this->connect(this->Internals->XRangeAuto, SIGNAL(toggled(bool)), this,
      SLOT(onAutoXRange(bool)));

  this->connect(this->Internals->YMin, SIGNAL(valueChanged(double)), this,
      SLOT(onYRangeModified()), Qt::QueuedConnection);

  this->connect(this->Internals->YMax, SIGNAL(valueChanged(double)), this,
      SLOT(onYRangeModified()), Qt::QueuedConnection);

  this->connect(this->Internals->XMin, SIGNAL(valueChanged(double)), this,
      SLOT(onXRangeModified()), Qt::QueuedConnection);

  this->connect(this->Internals->XMax, SIGNAL(valueChanged(double)), this,
      SLOT(onXRangeModified()), Qt::QueuedConnection);

  this->connect(this->Internals->TransferFunctionMode, SIGNAL(currentIndexChanged(int)), this, 
    SLOT(onTFModeChanged(int)), Qt::QueuedConnection);

  this->connect(this->Internals->OpacityLevel, SIGNAL(valueChanged(int)), this, 
    SLOT(onOpacityLevelChanged(int)), Qt::QueuedConnection);

  this->connect(this->Internals->Apply, SIGNAL(clicked()), this, 
    SLOT(onApplyClicked()), Qt::QueuedConnection);

  this->connect(this->Internals->TransferFunction, SIGNAL(activeRegionChanged(int)), this, 
    SLOT(onActiveRegionChanged(int)), Qt::QueuedConnection);

}
//-----------------------------------------------------------------------------
pqTransferFunctionEditor::~pqTransferFunctionEditor()
{

}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::needReloadGUI()
{
  if (this->Internals->Updating)
    {
    return;
    }
  this->Internals->Updating = true;
  QTimer::singleShot(0, this, SLOT(reloadGUI()));
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::reloadGUI()
{
  this->Internals->Updating = false;
  vtkSMProxy *reprProxy = (this->Internals->Representation) ? 
    this->Internals->Representation->getProxy() : NULL;
  if (!reprProxy) return;
  //
  this->Internals->BlockSignals++;
  //

  reprProxy->UpdateVTKObjects();
  reprProxy->UpdatePropertyInformation(reprProxy->GetProperty("HistogramDimensions"));
  reprProxy->UpdatePropertyInformation(reprProxy->GetProperty("HistogramValues"));

  QList<QVariant> HistogramSize = pqSMAdaptor::getMultipleElementProperty(
      reprProxy->GetProperty("HistogramDimensions"));

  if (HistogramSize[0].toInt()>0 && HistogramSize[1].toInt()>0) {
    vtkSMIntVectorProperty *ivp = vtkSMIntVectorProperty::SafeDownCast(
      reprProxy->GetProperty("HistogramValues"));
    //
    int *values = ivp->GetElements();
    this->Internals->TransferFunction->setBackgroundGradientData(
      HistogramSize[0].toInt(), HistogramSize[1].toInt(), values);
  }

  vtkSMProxyProperty *lutp = vtkSMProxyProperty::SafeDownCast(
    reprProxy->GetProperty("LookupTable"));
  if (lutp && lutp->GetNumberOfProxies()>0) {
    vtkSMProxy *lut = lutp->GetProxy(0);
    vtkSMIntVectorProperty *ntv = vtkSMIntVectorProperty::SafeDownCast(
      lut->GetProperty("NumberOfTableValues"));
    int N = ntv->GetElement(0);
    if (N>0) {
      lut->UpdatePropertyInformation(lut->GetProperty("TableValues"));
      vtkSMIntVectorProperty *ivp = vtkSMIntVectorProperty::SafeDownCast(
        lut->GetProperty("TableValues"));
      //
      int *values = ivp->GetElements();
      this->Internals->ColorScale->setBackgroundColourData(N, values);
      this->Internals->TransferFunction->setBackgroundColourData(N, values);

      pqScalarsToColors* lut = this->Internals->Representation->getLookupTable();
        QPair<double,double> range = lut->getScalarRange();
        this->Internals->XMin->setValue(range.first);
        this->Internals->XMax->setValue(range.second);
    }
  }
  else {
    this->Internals->ColorScale->setBackgroundColourData(0, NULL);
  }

/*
  int XRangeAuto = pqSMAdaptor::getElementProperty(reprProxy->GetProperty(
      this->Internals->UseXRangeProperty)).toInt();
  QString transfertFunctionMode =
      pqSMAdaptor::getEnumerationProperty(reprProxy->GetProperty(
          this->Internals->TransferFunctionModeProperty)).toString();
  QList<QVariant> tableValues = pqSMAdaptor::getMultipleElementProperty(
      reprProxy->GetProperty(this->Internals->TableValuesProperty));
  QList<QVariant> regionValues = pqSMAdaptor::getMultipleElementProperty(
      reprProxy->GetProperty(this->Internals->RegionControlPointsProperty));
  QList<QVariant> scaleRange = pqSMAdaptor::getMultipleElementProperty(
      reprProxy->GetProperty(this->Internals->RangeProperty));
  QList<QVariant> scalarRange = pqSMAdaptor::getMultipleElementProperty(
      reprProxy->GetProperty(this->Internals->XRangeProperty));

  //bool setAutoXRange = false;
  if (XRangeAuto == 0)
    {
    this->Internals->XMin->setValue(scalarRange[0].toDouble());
    this->Internals->XMax->setValue(scalarRange[1].toDouble());
    }
  else
    {
    onAutoXRange(true);
    }

  // the opacity editor has no scale range property, so the returned list is empty
  if (scaleRange.size() == 2)
    {
    this->Internals->YMin->setValue(scaleRange[0].toDouble());
    this->Internals->YMax->setValue(scaleRange[1].toDouble());
    }

  this->setRegionControlPoints(regionValues);
*/
  this->Internals->BlockSignals--;
  if (this->Internals->TransferFunction->isVisible()) {
    this->Internals->TransferFunction->repaint();
  }
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::setRepresentation(pqPipelineRepresentation* repr)
{
  if (this->Internals->Representation == repr)
    {
    return;
    }

  this->Internals->Representation = repr;

  this->Internals->Links.removeAllPropertyLinks();
  this->Internals->VTKConnect->Disconnect();

  vtkSMProxy* reprProxy = (repr) ? repr->getProxy() : NULL;

  if (reprProxy)
    {
    vtkSMProperty* prop;
/*
    prop = reprProxy->GetProperty(this->Internals->UseXRangeProperty);
    if (prop)
      {
      this->Internals->Links.addPropertyLink(this->Internals->XRangeAuto,
          "checked", SIGNAL(toggled(bool)), reprProxy, prop);
      }
*/

    prop = reprProxy->GetProperty("Representation");
    if (prop)
      {
      this->Internals->VTKConnect->Connect(prop, vtkCommand::ModifiedEvent,
          this, SLOT(needReloadGUI()), NULL, 0.0, Qt::QueuedConnection);
      }

    // Every time the display updates, it is possible that the arrays available for 
    // coloring have changed, hence we reload the list.
    QObject::connect(this->Internals->Representation, SIGNAL(dataUpdated()),
      this, SLOT(needReloadGUI()));

    // If any of these properties change, we know that the coloring for the
    // representation has been affected.
    const char* properties[] = {
      "LookupTable",
      "ColorArrayName",
      "ColorAttributeType",
      0};

    for (int cc=0; properties[cc]; cc++)
      {
      this->Internals->VTKConnect->Connect(
        reprProxy->GetProperty(properties[cc]), vtkCommand::ModifiedEvent,
        this, SLOT(needReloadGUI()));
      }

    }
  needReloadGUI();
}
//-----------------------------------------------------------------------------
QList<QVariant> pqTransferFunctionEditor::regionControlPoints()
{
  QList<QVariant> list;
  for (int i = 0; i < this->Internals->TransferFunction->getNumberOfRegions(); ++i)
    {
    float g[REGION_VARS];
    this->Internals->TransferFunction->getRegion(i, &g[0], &g[1], &g[2], &g[3], &g[4], &g[5]);

    for (int j = 0; j < REGION_VARS; j++)
      {
      list.append(QVariant(static_cast<double> (g[j])));
      }
    }
  return list;
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::setRegionControlPoints(const QList<QVariant>& values)
{
  this->Internals->TransferFunction->blockSignals(true);
  //
  this->Internals->TransferFunction->setAllRegions(0, NULL);
  int n = values.size();
  if (n > 0)
    {
    float gcpts[1024];
    for (int i = 0; i < n; ++i)
      gcpts[i] = static_cast<float> (values[i].toDouble());
    // Set all of the regions into the widget.
    this->Internals->TransferFunction->setAllRegions(n / REGION_VARS, gcpts);
    }
  this->Internals->TransferFunction->blockSignals(false);
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::onRegionValuesModified()
{
  pqPipelineRepresentation* repr = this->Internals->Representation;
  vtkSMProxy* reprProxy = (repr) ? repr->getProxy() : NULL;
  if (!reprProxy)
    return;
/*
  this->SetProxyValue(this->Internals->RegionControlPointsProperty,
      this->regionControlPoints(), false);
*/
  if (this->Internals->BlockSignals)
    return;

  reprProxy->UpdateVTKObjects();
  this->updateAllViews();
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::onXRangeModified()
{
  QList<QVariant> range;
  range.append(this->Internals->XMin->value());
  range.append(this->Internals->XMax->value());
/*
  this->SetProxyValue(this->Internals->XRangeProperty, range);
*/
  pqPipelineRepresentation* repr = this->Internals->Representation;
  vtkSMProxy * reprProxy = (repr ? repr->getProxy() : NULL);
  if (!reprProxy)
    {
    return;
    }

}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::onYRangeModified()
{
  QList<QVariant> range;
  range.append(this->Internals->YMin->value());
  range.append(this->Internals->YMax->value());
/*
  this->SetProxyValue(this->Internals->RangeProperty, range);
*/
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::onAutoXRange(bool autoRange)
{
  if (autoRange)
    {
    pqPipelineRepresentation* repr = this->Internals->Representation;
    vtkSMProxy * reprProxy = (repr ? repr->getProxy() : NULL);
    if (!reprProxy)
      {
      return;
      }
/*
    const char* array =
        vtkSMStringVectorProperty::SafeDownCast(reprProxy->GetProperty(
            this->Internals->ArrayNameProperty))->GetElement(4);
    int comp = pqSMAdaptor::getElementProperty(reprProxy->GetProperty(
        this->Internals->ArrayComponentProperty)).toInt();

    if (strcmp(array, this->Internals->ConstantNameProperty) == 0 || strcmp(
        array, "") == 0)
      return;

    QPair<double, double> range = repr->getColorFieldRange(array, comp);

    this->Internals->XMin->setValue(range.first);
    this->Internals->XMax->setValue(range.second);
*/
    }
}
//----------------------------------------------------------------------------
// The routines below here should be in some generic proxy set/get class
//----------------------------------------------------------------------------
void pqTransferFunctionEditor::SetProxyValue(const char *name,
    QList<QVariant> val,
    bool updateFlag)
{
  vtkSMProxy
      *reprProxy =
          (this->Internals->Representation ? this->Internals->Representation->getProxy()
              : NULL);
  if (!reprProxy)
    {
    return;
    }

  vtkSMProperty* Property = reprProxy->GetProperty(name);
  pqSMAdaptor::setMultipleElementProperty(Property, val);
  if (updateFlag && !this->Internals->BlockSignals)
    {
    reprProxy->UpdateVTKObjects();
    this->updateAllViews();
    }
}
//----------------------------------------------------------------------------
QList<QVariant> pqTransferFunctionEditor::GetProxyValueList(const char *name)
{
  vtkSMProxy
      *proxy =
          (this->Internals->Representation ? this->Internals->Representation->getProxy()
              : NULL);
  if (!this->Internals->Representation || !proxy)
    {
    return QList<QVariant> ();
    }

  vtkSMProperty* Property = proxy->GetProperty(name);
  return pqSMAdaptor::getMultipleElementProperty(Property);
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::updateAllViews()
{
  if (this->Internals->Representation)
    {
    this->Internals->Representation->renderViewEventually();
    }
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::onTFModeChanged(int index)
{
  this->Internals->TransferFunction->setActiveRegionMode(index);
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::onOpacityLevelChanged(int value)
{
  double val = (double)value/4999.0;
  this->Internals->TransferFunction->setActiveRegionMaximum(val);
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::onApplyClicked()
{
  vtkSMProxy *reprProxy = (this->Internals->Representation) ? 
    this->Internals->Representation->getProxy() : NULL;
  if (!reprProxy) return;
  
  std::vector<unsigned char> data(256*256*4, 255);
  this->Internals->TransferFunction->createRGBAData(&data[0]);

  vtkSMIntVectorProperty *ctd = vtkSMIntVectorProperty::SafeDownCast(
    reprProxy->GetProperty("ColourTableValues"));
  int *ip = reinterpret_cast<int*>(&data[0]);
  ctd->SetElements(ip);
  reprProxy->UpdateVTKObjects();
}
//-----------------------------------------------------------------------------
void pqTransferFunctionEditor::onActiveRegionChanged(int region)
{
  pqPipelineRepresentation* repr = this->Internals->Representation;
  vtkSMProxy* reprProxy = (repr) ? repr->getProxy() : NULL;
  if (!reprProxy) return;
  if (this->Internals->BlockSignals) return;
  //
  if (this->Internals->TransferFunction->getActiveRegionMaximum()>-1) {
    float val = this->Internals->TransferFunction->getActiveRegionMaximum();
    int     m = this->Internals->TransferFunction->getActiveRegionMode();
    this->Internals->OpacityLevel->setValue(val*this->Internals->OpacityLevel->maximum());
    this->Internals->TransferFunctionMode->setCurrentIndex(m);
  }
  reprProxy->UpdateVTKObjects();
  this->updateAllViews();
}