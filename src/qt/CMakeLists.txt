project(phillib_qt)
 
cmake_minimum_required(VERSION 2.8.0)

SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -O2 -Wall  -mtune=native") # 

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

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

#find_package(VTK 9 REQUIRED)
#set(VTK_LIBRARIES "")
find_package(VTK COMPONENTS
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersCore
    vtkFiltersGeometry
    vtkFiltersModeling
    vtkFiltersSources
    vtkFiltersTexture
    vtkIOGeometry
    vtkIOImage
    vtkIOLegacy
    vtkIOPLY
    vtkIOParallel
    vtkIOXML
    vtkImagingHybrid
    vtkInteractionStyle
    vtkRenderingContextOpenGL2
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingGL2PSOpenGL2
    vtkRenderingOpenGL2
    OPTIONAL_COMPONENTS
    vtkTestingRendering
    QUIET
    )

#find_package(VTK COMPONENTS
#
#  CommonColor
#  CommonCore
#  IOImage
#  InteractionImage
#  InteractionStyle
#  FiltersSources
#  InteractionStyle
#  InteractionWidgets
#  RenderingContextOpenGL2
#  RenderingCore
#  RenderingFreeType
#  RenderingGL2PSOpenGL2
#  RenderingOpenGL2
#  #QUIET
#)

# find_package(VTK COMPONENTS 
#   vtkCommonColor
#   vtkCommonCore
  

#   vtkRenderingContextOpenGL2
#   vtkRenderingCore
#   vtkRenderingFreeType
#   vtkRenderingGL2PSOpenGL2
#   vtkRenderingOpenGL2
#   QUIET
# )

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
#include(${VTK_USE_FILE})
find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

link_directories(/usr/local/lib)


set(MOC_PHILLIB_QT 
                WidgetImage.h
              )

              set(MOC_TEST_QVTK 
                TestQvtk.h
                WidgetNewQvtk.h
              )


qt5_wrap_cpp(MOC_GENERATED_PHILLIB_QT ${MOC_PHILLIB_QT})
qt5_wrap_cpp(MOC_GENERATED_TEST_QVTK ${MOC_TEST_QVTK})

add_executable(test_vtk test_qvtk.cpp TestQvtk.cpp WidgetNewQvtk.cpp ${MOC_GENERATED_TEST_QVTK})# WidgetQvtk.cpp)
add_executable(test_scroll test_scroll.cpp WidgetDisplay.cpp)
add_executable(image_magic image_magic.cpp ImageMagic.cpp WidgetNewQvtk.cpp)

add_library(phillib_qt SHARED WidgetImage.cpp ${MOC_GENERATED_PHILLIB_QT})

target_link_libraries(phillib_qt
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
    )

    target_link_libraries(test_vtk
    PUBLIC
    VTK::ViewsQt
    VTK::CommonColor
    VTK::CommonCore
    VTK::IOImage
    VTK::InteractionImage
    VTK::InteractionStyle
    VTK::FiltersSources
    VTK::InteractionStyle
    VTK::InteractionWidgets
    VTK::RenderingContextOpenGL2
    VTK::RenderingCore
    VTK::RenderingFreeType
    VTK::RenderingGL2PSOpenGL2
    VTK::RenderingOpenGL2
    VTK::CommonColor
    VTK::CommonCore
    VTK::CommonDataModel
    VTK::FiltersCore
    VTK::FiltersGeometry
    VTK::FiltersModeling
    VTK::FiltersSources
    VTK::FiltersTexture
    VTK::IOGeometry
    VTK::IOImage
    VTK::IOLegacy
    VTK::IOPLY
    VTK::IOParallel
    VTK::IOXML
    VTK::ImagingHybrid
    VTK::InteractionStyle
    VTK::RenderingContextOpenGL2
    VTK::RenderingCore
    VTK::RenderingFreeType
    VTK::RenderingGL2PSOpenGL2
    VTK::RenderingOpenGL2
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  Qt5::OpenGL
  ${VTK_LIBRARIES}
  ${PCL_LIBRARIES}
  phillib_utils
  tinyxml2
    )

    target_link_libraries(test_scroll
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  
  phillib_qt
  
    )

    vtk_module_autoinit(
      TARGETS image_magic
      MODULES ${VTK_LIBRARIES})

    target_link_libraries(image_magic
    PUBLIC
    VTK::ViewsQt
    VTK::CommonColor
    VTK::CommonCore
    VTK::IOImage
    VTK::InteractionImage
    VTK::InteractionStyle
    VTK::FiltersSources
    VTK::InteractionStyle
    VTK::InteractionWidgets
    VTK::RenderingContextOpenGL2
    VTK::RenderingCore
    VTK::RenderingFreeType
    VTK::RenderingGL2PSOpenGL2
    VTK::RenderingOpenGL2
    VTK::CommonColor
    VTK::CommonCore
    VTK::CommonDataModel
    VTK::FiltersCore
    VTK::FiltersGeometry
    VTK::FiltersModeling
    VTK::FiltersSources
    VTK::FiltersTexture
    VTK::IOGeometry
    VTK::IOImage
    VTK::IOLegacy
    VTK::IOPLY
    VTK::IOParallel
    VTK::IOXML
    VTK::ImagingHybrid
    VTK::InteractionStyle
    VTK::RenderingContextOpenGL2
    VTK::RenderingCore
    VTK::RenderingFreeType
    VTK::RenderingGL2PSOpenGL2
    VTK::RenderingOpenGL2
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  Qt5::OpenGL
  ${VTK_LIBRARIES}
  ${PCL_LIBRARIES}
  phillib_utils
  tinyxml2
    )

    vtk_module_autoinit(
      TARGETS test_vtk 
      MODULES ${VTK_LIBRARIES})



set(HEADER datatypes.h WidgetImage.h)
                                    
                          
 install(TARGETS phillib_qt DESTINATION lib)
install(FILES ${HEADER} DESTINATION include/phillib_qt)