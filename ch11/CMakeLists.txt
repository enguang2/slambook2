cmake_minimum_required( VERSION 2.8 )
project( loop_closure )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# opencv 
set(OpenCV_DIR "/root/opencv/opencv-3.4.8/build")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# dbow3 
# dbow3 is a simple lib so I assume you installed it in default directory 
set( DBoW3_INCLUDE_DIRS "/usr/local/include" )
set( DBoW3_LIBS "/usr/local/lib/libDBoW3.so" )

add_executable( feature_training feature_training.cpp )
target_link_libraries( feature_training ${OpenCV_LIBS} ${DBoW3_LIBS} )

add_executable( loop_closure loop_closure.cpp )
target_link_libraries( loop_closure ${OpenCV_LIBS} ${DBoW3_LIBS} )

add_executable( gen_vocab gen_vocab_large.cpp )
target_link_libraries( gen_vocab ${OpenCV_LIBS} ${DBoW3_LIBS} )

#I add this 
add_executable( large_loop_closure large_loop_closure.cpp )
target_link_libraries( large_loop_closure ${OpenCV_LIBS} ${DBoW3_LIBS} )

add_executable( siebel_first_vocab siebel_first_vocab.cpp )
target_link_libraries( siebel_first_vocab ${OpenCV_LIBS} ${DBoW3_LIBS} )

add_executable( siebel_first_loop_closure siebel_first_loop_closure.cpp )
target_link_libraries( siebel_first_loop_closure ${OpenCV_LIBS} ${DBoW3_LIBS} )

add_executable( siebel_checkboard siebel_checkboard.cpp )
target_link_libraries( siebel_checkboard ${OpenCV_LIBS} ${DBoW3_LIBS} )
