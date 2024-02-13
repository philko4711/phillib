project(balls)
 
cmake_minimum_required(VERSION 2.8.0)

SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -O2 -Wall -mtune=native") # 
 
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
 
include_directories(${Qt5Widgets_INCLUDES})
 
 add_definitions(${Qt5Widgets_DEFINITIONS})
 #set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
 
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
)
                      
set(MOC_BALLS src/gui/BallsMainWindow.h 
#                src/PredPray.h
#                src/gui/ViewerWorld.h
#                src/gui/WidgetImage.h
#              src/core/QtExpl.h
#              src/gui/IWidgetMap.h
#              src/gui/WidgetMapSizeRegion.h
#              src/gui/WidgetMapChangedRegions.h
#                            src/gui/WidgetConfig.h
#              src/gui/WidgetSegment.h
              )

qt5_wrap_cpp(MOC_GENERATED_BALLS ${MOC_BALLS})
#
qt5_wrap_ui(UI_GENERATED_BALLS src/gui/main_window_balls.ui)
 
link_directories(/usr/local/lib)

#add_executable(pred_prey 
#src/main.cpp
#src/PredPray.cpp
#src/Map.cpp
#src/Prey.cpp 
#src/Food.cpp
#src/ObjectMap.cpp
#src/gui/MainWindow.cpp
#src/gui/ViewerWorld.cpp
#                       src/gui/MainWindow.cpp
#                       src/gui/WidgetImage.cpp
#                       src/gui/WidgetMapSizeRegion.cpp
#                       src/gui/WidgetMapChangedRegions.cpp
#                       src/core/DataObjectQPoint.cpp
#                       src/utils/utils.cpp
#                       src/gui/WidgetConfig.cpp
#                       src/gui/WidgetSegment.cpp
#                       ${MOC_GENERATED_PRED_PREY}
#                       ${UI_GENERATED_PRED_PREY}
#                       ${UI_GENERATED_QTREE}
#)
    
add_executable(balls src/balls_main.cpp
                     src/gui/BallsMainWindow.cpp
                     ${MOC_GENERATED_BALLS}
                     ${UI_GENERATED_BALLS}
)

#add_executable(fw_bw_cp src/fw_bw_cp.cpp src/core/DataObjectQPoint.cpp src/utils/utils.cpp)


target_link_libraries(balls
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
#  #pr_tree
   phillib_utils
#  #phillib_qt
  tinyxml2
#  VTK::CommonCore
#  VTK::CommonColor 
#  VTK::ViewsQt 
#  ${PCL_LIBRARIES}
#  ${VTK_LIBRARIES}
#  ${OpenCV_LIBRARIES}
)
