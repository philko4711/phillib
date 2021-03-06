project(cpp_helper)
 
cmake_minimum_required(VERSION 2.8.0)

SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -O2 -Wall  -mtune=native") # 

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
 
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})

set(MOC_CPP_HELPER 
                src/CppHelper.h
                src/gui/MainWindow.h
              )

set(UI src/gui/main_window.ui)

qt5_wrap_cpp(MOC_GENERATED_CPP_HELPER ${MOC_CPP_HELPER})
qt5_wrap_ui(UI_GENERATED ${UI})

add_executable(cpp_helper 
  src/CppHelper.cpp 
  src/cpp_helper.cpp
  src/gui/MainWindow.cpp 
  ${MOC_GENERATED_CPP_HELPER} 
  ${UI_GENERATED})

target_link_libraries(cpp_helper
    PUBLIC
  Qt5::Core
  Qt5::Gui 
  Qt5::Widgets
    )

#set(HEADER datatypes.h WidgetImage.h)
                                    
                          
install(TARGETS cpp_helper RUNTIME DESTINATION)
#install(FILES ${HEADER} DESTINATION include/phillib_qt)