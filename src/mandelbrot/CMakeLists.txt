project(cpp_hemandelbrot)
 
cmake_minimum_required(VERSION 2.8.0)

#SET(CMAKE_BUILD_TYPE RELEASE)
SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -O0 -Wall  -mtune=native") # 

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
 
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})

set(MOC_MANDELBROT
                src/gui/MainWindow.h

              )
set(UI_MANDELBROT src/gui/main_window.ui)

qt5_wrap_cpp(MOC_GENERATED_CPP_MANDELBROT ${MOC_MANDELBROT})
qt5_wrap_ui(UI_GENERATED_MANDELBROT ${UI_MANDELBROT})

add_executable(mandelbrot
  src/mandelbrot.cpp 
  src/Mandelbrot.cpp
  src/gui/MainWindow.cpp
  #src/gui/MainWindow.cpp 
  ${MOC_GENERATED_CPP_MANDELBROT} 
  ${UI_GENERATED_MANDELBROT}
  )

target_link_libraries(mandelbrot
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
  phillib_utils
  phillib_qt
  tinyxml2
    )


                                    
                      