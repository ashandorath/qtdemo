/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: pqTransferFunctionEditor.h,v $

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

#ifndef __pqTransferFunctionEditor_h
#define __pqTransferFunctionEditor_h

#include <QWidget>
#include <QDialog>

class pqPipelineRepresentation;

class pqTransferFunctionEditor: public QWidget
{
  Q_OBJECT
  typedef QWidget Superclass;
public:
   pqTransferFunctionEditor(QDialog *parent = 0, Qt::WindowFlags f=0);
  ~pqTransferFunctionEditor();

  void setRepresentation(pqPipelineRepresentation* repr);
  //

public slots :
  void  needReloadGUI();

protected slots :
  void reloadGUI();

  void onAutoXRange(bool);
  //void onAutoYRange(bool);

  void onXRangeModified();
  void onYRangeModified();
  void onTFModeChanged(int index);
  void onOpacityLevelChanged(int value);
  void onApplyClicked();
  void onActiveRegionChanged(int region);
  void onRegionValuesModified();

  void updateAllViews();

protected:
  QList<QVariant> regionControlPoints();

  void setRegionControlPoints(const QList<QVariant>&);

  QList<QVariant> GetProxyValueList(const char *name);
  void SetProxyValue(const char *name, QList<QVariant> val, bool update = true);

  //void  initialize();

private:
  class pqInternals;
  pqInternals* Internals;

  pqTransferFunctionEditor(const pqTransferFunctionEditor&); // Not implemented.
  void operator=(const pqTransferFunctionEditor&); // Not implemented.
};

#endif

