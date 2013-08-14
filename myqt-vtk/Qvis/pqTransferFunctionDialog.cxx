/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: pqTransferFunctionDialog.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME pqTransferFunctionDialog
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

#include "pqTransferFunctionDialog.h"
#include "ui_pqTransferFunctionDialog.h"

#include "pqTransferFunctionEditor.h"

class pqTransferFunctionDialog::pqInternals: public Ui::pqTransferFunctionDialog
{

};

pqTransferFunctionDialog::pqTransferFunctionDialog(QWidget* parentObject) : QDialog(parentObject)
{
  this->Internals = new pqTransferFunctionDialog::pqInternals();
  this->Internals->setupUi(this);
}

pqTransferFunctionDialog::~pqTransferFunctionDialog()
{
}

pqTransferFunctionEditor* pqTransferFunctionDialog::Editor()
{
  return this->Internals->TransferFunction;
}

void  pqTransferFunctionDialog::setRepresentation(pqPipelineRepresentation* repr)
{
  this->Internals->TransferFunction->setRepresentation(repr);
}



