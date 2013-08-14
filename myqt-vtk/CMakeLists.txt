cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)

PROJECT (myqtvtk)

if(NOT VTK_BINARY_DIR)
  find_package(VTK COMPONENTS

vtkCommonCore
    vtkCommonDataModel
    vtkIOImage 
    vtkIOGeometry
    vtkIOXML
    vtkImagingCore
    vtkInteractionWidgets
    vtkRenderingCore
    vtkRenderingOpenGL
    vtkRenderingVolume
    vtkRenderingVolumeOpenGL
    vtkCommonExecutionModel
    vtkCommonSystem
    vtkCommonMath
    vtkCommonMisc
    vtkCommonTransforms
    vtkIOCore
    vtkMetaIO
    vtkDICOMParser
    vtkexpat
    vtkIOXML

    pqWidgets
    pqCore
    pqComponents
    pqApplicationComponents
  )
  include(${VTK_USE_FILE})
endif()

#--------------------------------------------------
# Qt
#--------------------------------------------------
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR} 
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Qvis
)

  set(UI_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/pqTransferFunctionDialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/pqTransferFunctionEditor.ui
  )

  set(CXX_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/twoDOpacityFunction.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtktestquadric.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/custommath.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/errorwindow.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cxx
  )

  set(QVIS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/QvisAbstractOpacityBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/Qvis2DTransferFunctionWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/QvisColourBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/pqTransferFunctionDialog.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/pqTransferFunctionEditor.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/pqDoubleEdit.cxx
    #
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/drawarea.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkQTWindow.cxx
  )
 
  qt4_wrap_cpp(QVIS_MOC_SRCS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/QvisAbstractOpacityBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/Qvis2DTransferFunctionWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/QvisColourBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/pqTransferFunctionDialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/pqTransferFunctionEditor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Qvis/pqDoubleEdit.h
    #
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/drawarea.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkQTWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/polygoncombobox.h
  )

QT4_WRAP_UI (UISrcs ${UI_FILES})


add_executable(myqtvtk MACOSX_BUNDLE ${CXX_FILES} ${UISrcs} ${MOCSrcs} ${QVIS_SRCS} ${QVIS_MOC_SRCS} )

if (VTK_LIBRARIES)
	if(${VTK_VERSION} VERSION_LESS "6")
		target_link_libraries(myqtvtk ${VTK_LIBRARIES} QVTK)
	else()	
		target_link_libraries(myqtvtk ${VTK_LIBRARIES})
	endif()
else()
	target_link_libraries(myqtvtk vtkHybrid QVTK vtkViews ${QT_LIBRARIES})
endif()





