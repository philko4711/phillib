project(phillib_qt)
 
cmake_minimum_required(VERSION 2.8.0)

SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -O2 -Wall  -mtune=native")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
 
#find_package(PCL  REQUIRED)
#include_directories(${PCL_INCLUDE_DIRS})


INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})

find_package(VTK 9 REQUIRED)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

link_directories(/usr/local/lib)


set(MOC_PHILLIB_QT 
  WidgetImage.h
  )

  set(MOC_PHILLIB_QT_3D 
  WidgetNewQvtk.h)

set(MOC_TEST_QVTK 
  TestQvtk.h
  WidgetNewQvtk.h
  WidgetNewQvtk.h
)

set(MOC_IMG_MAGIC
  WidgetNewQvtk.h
  ImageMagic.h
  MenuTransform.h
)

set(MOC_GRPH 
  grview/GraphScExample.h
  grview/MainWindow.h
  grview/GrView.h)

SET(FORMS_IMG_MAGIC menuTransform.ui
                  )
qt5_wrap_ui(FORMS_IMG_MAGIC_HEADER ${FORMS_IMG_MAGIC})


qt5_wrap_cpp(MOC_GENERATED_PHILLIB_QT ${MOC_PHILLIB_QT})
qt5_wrap_cpp(MOC_GENERATED_PHILLIB_QT_3D ${MOC_PHILLIB_QT_3D})
qt5_wrap_cpp(MOC_GENERATED_TEST_QVTK ${MOC_TEST_QVTK})
qt5_wrap_cpp(MOC_GENERATED_IMG_MAGIC ${MOC_IMG_MAGIC})
qt5_wrap_cpp(MOC_GENERATED_GRPH ${MOC_GRPH})

add_executable(test_vtk test_qvtk.cpp TestQvtk.cpp WidgetNewQvtk.cpp ${MOC_GENERATED_TEST_QVTK})# WidgetQvtk.cpp WidgetNewQvtk.cpp)
add_executable(test_scroll test_scroll.cpp WidgetDisplay.cpp)
add_executable(image_magic image_magic.cpp ImageMagic.cpp WidgetNewQvtk.cpp MenuTransform.cpp ${MOC_GENERATED_IMG_MAGIC} ${FORMS_IMG_MAGIC_HEADER})
add_executable(grph grview/graph_sc_example.cpp grview/MainWindow.cpp grview/GraphScExample.cpp grview/GrView.cpp ${MOC_GENERATED_GRPH})

add_library(phillib_qt SHARED WidgetImage.cpp  ${MOC_GENERATED_PHILLIB_QT}) 
add_library(phillib_qt_3d SHARED  WidgetNewQvtk.cpp ${MOC_GENERATED_PHILLIB_QT_3D})  #

target_link_libraries(phillib_qt
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  phillib_utils
  tinyxml2
    )

    target_link_libraries(grph
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  Qt5::Multimedia
  Qt5::MultimediaWidgets
  phillib_utils
  tinyxml2
    )

    target_link_libraries(phillib_qt_3d
    PUBLIC
    VTK::CommonCore
    VTK::ViewsQt
    VTK::CommonColor 
    Qt5::Core
    Qt5::Gui 
    Qt5::Widgets
    Qt5::OpenGL
  ${VTK_LIBRARIES}
  ${PCL_LIBRARIES}
  phillib_utils
  #phillib_qt
  tinyxml2)

    target_link_libraries(test_vtk
    PUBLIC
    VTK::CommonCore
    VTK::ViewsQt
    VTK::CommonColor 
    Qt5::Core
    Qt5::Gui 
    Qt5::Widgets
    Qt5::OpenGL
  ${VTK_LIBRARIES}
  ${PCL_LIBRARIES}
  phillib_utils
  #phillib_qt
  tinyxml2
    )

    target_link_libraries(test_scroll
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  
  phillib_qt
  
    )

  
    target_link_libraries(image_magic
    PUBLIC
    VTK::CommonCore
#VTK::GUISupportQt
VTK::ViewsQt
VTK::CommonColor 
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  Qt5::OpenGL
  ${VTK_LIBRARIES}
  ${PCL_LIBRARIES}
  phillib_utils
  tinyxml2
    )

    

set(HEADER datatypes.h WidgetImage.h WidgetNewQvtk.h)
                                    
                          
 install(TARGETS phillib_qt phillib_qt_3d DESTINATION lib)
install(FILES ${HEADER} DESTINATION include/phillib_qt)