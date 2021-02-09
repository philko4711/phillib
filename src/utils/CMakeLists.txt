project(phillib_utils)
 
cmake_minimum_required(VERSION 2.8.0)

SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17  -O2 -Wall  -mtune=native") #   ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}
 
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
 
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(phillib_utils SHARED random.cpp MutexSingleton.cpp utilsmath.cpp)

set(HEADER random.h MutexSingleton.h Fifo.h utilsmath.h typedefs_eigen.h)

target_link_libraries(phillib_utils Eigen3::Eigen)
                          
 install(TARGETS phillib_utils DESTINATION lib)
install(FILES ${HEADER} DESTINATION include/phillib_utils)