project(pre_prey)
 
cmake_minimum_required(VERSION 2.8.0)

#SET(CMAKE_BUILD_TYPE RELEASE)
SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -O0 -Wall -mtune=native") # 
 
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenCV REQUIRED)
 
include_directories(${Qt5Widgets_INCLUDES})
#include_directories( ${OpenCV_INCLUDE_DIRS} )
 
 add_definitions(${Qt5Widgets_DEFINITIONS})
 #set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
 
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
#  ${CMAKE_CURRENT_SOURCE_DIR}/src/core
)
                        

#find_package(PCL 1.8 REQUIRED)
#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

#find_package(VTK 9 REQUIRED)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(MOC_PRED_PREY src/gui/MainWindow.h 
                src/PredPray.h
                src/gui/ViewerWorld.h
#                src/gui/WidgetImage.h
#              src/core/QtExpl.h
#              src/gui/IWidgetMap.h
#              src/gui/WidgetMapSizeRegion.h
#              src/gui/WidgetMapChangedRegions.h
#              src/gui/WidgetConfig.h
#              src/gui/WidgetSegment.h
              )

#set(UI_QT_EXPL src/gui/main_window.ui
#               src/gui/config.ui
#               src/gui/segment.ui)

qt5_wrap_cpp(MOC_GENERATED_PRED_PREY ${MOC_PRED_PREY})

#qt5_wrap_ui(UI_GENERATED_QTREE ${UI_QT_EXPL})
 
link_directories(/usr/local/lib)

add_executable(pred_prey 
src/main.cpp
src/PredPray.cpp
#src/Map.cpp
src/Prey.cpp 
src/Food.cpp
src/ObjectMap.cpp
src/gui/MainWindow.cpp
src/gui/ViewerWorld.cpp
#                       src/gui/MainWindow.cpp
#                       src/gui/WidgetImage.cpp
#                       src/gui/WidgetMapSizeRegion.cpp
#                       src/gui/WidgetMapChangedRegions.cpp
#                       src/core/DataObjectQPoint.cpp
#                       src/utils/utils.cpp
#                       src/gui/WidgetConfig.cpp
#                       src/gui/WidgetSegment.cpp
                       ${MOC_GENERATED_PRED_PREY}
#                       ${UI_GENERATED_QTREE}
)
    
#add_executable(load_expl src/load_expl.cpp src/core/DataObjectQPoint.cpp)

#add_executable(fw_bw_cp src/fw_bw_cp.cpp src/core/DataObjectQPoint.cpp src/utils/utils.cpp)


target_link_libraries(pred_prey
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  pr_tree
  phillib_utils
  phillib_qt
  tinyxml2
#  VTK::CommonCore
#  VTK::CommonColor 
#  VTK::ViewsQt 
#  ${PCL_LIBRARIES}
#  ${VTK_LIBRARIES}
#  ${OpenCV_LIBRARIES}
)
