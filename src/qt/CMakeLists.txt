project(phillib_qt)
 
cmake_minimum_required(VERSION 2.8.0)

SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -O2 -Wall  -mtune=native") # 

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
 
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})

find_package(VTK REQUIRED)
#find_package(VTK COMPONENTS
#  vtkCommonCore
#  vtkFiltersSources
#  vtkGUISupportQt
#  vtkIOImage
#  vtkInteractionImage
#  vtkFiltersCore
#  vtkInfovisCore
#  vtkInteractionStyle
#  vtkViewsQt
#)
#include(${VTK_USE_FILE})
include(${VTK_USE_FILE})
find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

set(MOC_PHILLIB_QT 
                WidgetImage.h
              )

qt5_wrap_cpp(MOC_GENERATED_PHILLIB_QT ${MOC_PHILLIB_QT})

add_executable(test_vtk test_qvtk.cpp WidgetQvtk.cpp)

add_library(phillib_qt SHARED WidgetImage.cpp ${MOC_GENERATED_PHILLIB_QT})

target_link_libraries(phillib_qt
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
    )

    target_link_libraries(test_vtk
    PUBLIC
    ${VTK_LIBRARIES}
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  
  ${PCL_LIBRARIES}
    )

set(HEADER datatypes.h WidgetImage.h)
                                    
                          
 install(TARGETS phillib_qt DESTINATION lib)
install(FILES ${HEADER} DESTINATION include/phillib_qt)