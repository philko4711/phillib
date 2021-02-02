project(phillib_utils)
 
cmake_minimum_required(VERSION 2.8.0)

SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17  -O2 -Wall  -mtune=native") #   ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}
 
 
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(phillib_utils SHARED random.cpp MutexSingleton.cpp)

set(HEADER random.h MutexSingleton.h)
                                    
                          
 install(TARGETS phillib_utils DESTINATION lib)
install(FILES ${HEADER} DESTINATION include/phillib_utils)