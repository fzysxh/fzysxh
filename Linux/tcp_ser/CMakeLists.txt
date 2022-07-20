cmake_minimum_required( VERSION 2.8 )
project( tcp_ser )
 
# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )
 
# 寻找OpenCV库
#set(OpenCV_DIR /usr/local/share/OpenCV)
set(OpenCV_DIR ros/kinetic/share/OpenCV-3.3.1-dev)
find_package( OpenCV REQUIRED )
# 添加头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )
 
add_executable( tcp_ser tcp_ser.cpp )
# 链接OpenCV库
target_link_libraries( tcp_ser ${OpenCV_LIBS} )
