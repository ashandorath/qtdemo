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


find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES *.ui)
file(GLOB QT_WRAP *.h)
file(GLOB CXX_FILES *.cxx)

QT4_WRAP_UI (UISrcs ${UI_FILES})
QT4_WRAP_CPP (MOCSrcs ${QT_WRAP})

add_executable(myqtvtk MACOSX_BUNDLE ${CXX_FILES} ${UISrcs} ${MOCSrcs})

if (VTK_LIBRARIES)
	if(${VTK_VERSION} VERSION_LESS "6")
		target_link_libraries(myqtvtk ${VTK_LIBRARIES} QVTK)
	else()	
		target_link_libraries(myqtvtk ${VTK_LIBRARIES})
	endif()
else()
	target_link_libraries(myqtvtk vtkHybrid QVTK vtkViews ${QT_LIBRARIES})
endif()





