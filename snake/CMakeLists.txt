project(qt_snake)
 
cmake_minimum_required(VERSION 2.8.0)

SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -O2 -Wall -mtune=native") 
 
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
#find_package (Eigen3 3.3 REQUIRED NO_MODULE)
#find_package(OpenCV REQUIRED)
 
include_directories(${Qt5Widgets_INCLUDES})
include_directories(/usr/local/include)
 
 add_definitions(${Qt5Widgets_DEFINITIONS})
 #set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
 
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
)
                      
set(MOC_SNAKE src/gui/GraphicsView.h
              src/Snake.h                
              src/gui/SnakeGui.h                  
              )

qt5_wrap_cpp(MOC_GENERATED_SNAKE ${MOC_SNAKE})

qt5_wrap_ui(UI_GENERATED_SNAKE src/gui/snake.ui)
 
#link_directories(/usr/local/lib)

add_executable(snake
  src/snake_main.cpp
  
  src/gui/GraphicsView.cpp
  src/gui/SnakeGui.cpp
  src/Snake.cpp
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
                       ${MOC_GENERATED_SNAKE}
                       ${UI_GENERATED_SNAKE}
)
    
#add_executable(load_expl src/load_expl.cpp src/core/DataObjectQPoint.cpp)

#add_executable(fw_bw_cp src/fw_bw_cp.cpp src/core/DataObjectQPoint.cpp src/utils/utils.cpp)


target_link_libraries(snake
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  #Eigen3::Eigen
#  #pr_tree
#  phillib_utils
#  #phillib_qt
#  tinyxml2
#  VTK::CommonCore
#  VTK::CommonColor 
#  VTK::ViewsQt 
#  ${PCL_LIBRARIES}
#  ${VTK_LIBRARIES}
#  ${OpenCV_LIBRARIES}
)
