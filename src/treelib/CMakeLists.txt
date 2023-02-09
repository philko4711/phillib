project(treelib)
 
cmake_minimum_required(VERSION 2.8.0)

#SET(CMAKE_BUILD_TYPE RELEASE)
SET(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -O0 -Wall  -mtune=native")

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
 




INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)


add_executable(test_tree_prq 
  src/prq/test_tree_prq.cpp 
  #src/prq/DataObjectBase.cpp 
  src/prq/DataObjectPoint.cpp 
#  src/prq/Index.cpp 
#  src/prq/Leaf.cpp 
#  src/prq/Node.cpp 
 src/prq/Point.cpp 
#  src/prq/RegionQ.cpp 
#  src/prq/TreeObjectBase.cpp 
#  src/prq/TreePrq.cpp 
)

add_library(lib_prq SHARED
src/prq/DataObjectBase.cpp 
  src/prq/Index.cpp 
  src/prq/Leaf.cpp 
  src/prq/Node.cpp 
  
  src/prq/RegionQ.cpp 
  src/prq/TreeObjectBase.cpp 
  src/prq/TreePrq.cpp
)

set(HEADER src/prq/DataObjectBase.h 
           src/prq/ITreeObject.h
           src/prq/IDataObject.h
           src/prq/Index.h
           src/prq/Leaf.h
           src/prq/Node.h
           src/prq/TreePrq.h
           src/prq/RegionQ.h
           src/prq/TreeObjectBase.h)


target_link_libraries(test_tree_prq lib_prq)

install(TARGETS lib_prq DESTINATION lib)
install(FILES ${HEADER} DESTINATION include/treelib/prq)