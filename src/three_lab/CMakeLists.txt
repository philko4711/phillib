project(three_lab)
 
cmake_minimum_required(VERSION 2.8.0)

SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++17  -Wall -mtune=native")
 
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

find_package(PCL 1.8 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
 
include_directories(${Qt5Widgets_INCLUDES})
 
 add_definitions(${Qt5Widgets_DEFINITIONS})
 set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
 
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
)
                        
set(MOCV src/gui/QvtkWidget.h
         src/gui/MainWindowLab.h
         src/gui/DialogSlopedCloud.h)

set(UI src/gui/main_window.ui
       src/gui/dialog_sloped_cloud.ui)

qt5_wrap_cpp(MOC_GENERATEDV ${MOCV})
qt5_wrap_ui(UI_GENERATED ${UI})
 
add_executable(three_lab src/three_lab.cpp
         src/gui/QvtkWidget.cpp
         src/gui/MainWindowLab.cpp
         src/gui/DialogSlopedCloud.cpp
                          ${MOC_GENERATEDV}
                          ${UI_GENERATED}
                          )
                                                  
target_link_libraries(three_lab
    PUBLIC
Qt5::Core
Qt5::Gui 
Qt5::Widgets
${PCL_LIBRARIES}
    ${VTK_LIBRARIES}
    )