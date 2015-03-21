PROJECT(helloworld)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Add include directory so include files are found
include_directories(../../include)

#
# helloworld module
#

ADD_LIBRARY(helloworld MODULE helloworld.c)

# Remove the "lib" from the .so target
SET_TARGET_PROPERTIES(helloworld PROPERTIES PREFIX "")
