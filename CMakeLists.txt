cmake_minimum_required(VERSION 3.29)
project(algoritmoDDA)

set(CMAKE_CXX_STANDARD 20)

find_package(GLUT REQUIRED)
add_executable(algoritmoDDA main.cpp)
target_link_libraries(algoritmoDDA ${GLUT_LIBRARIES} GLU GL)
