PROJECT(exif)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb  -O0 -D__DEBUG")

# Add include directory so include files are found
include_directories(../../include)

#
# Exif module
#

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(PC_LIBEXIF REQUIRED libexif)
INCLUDE_DIRECTORIES(${PC_LIBEXIF_INCLUDE_DIRS})
LIST(APPEND 3rdparty_libs ${PC_LIBEXIF_LIBRARIES})

# We must use modexif instead of exif, as the exif library is called 'exif' too.
ADD_LIBRARY(modexif MODULE exif.c)

TARGET_LINK_LIBRARIES(modexif ${3rdparty_libs})

SET_TARGET_PROPERTIES(modexif PROPERTIES PREFIX "")

# We override modexif.so to be called exif.so as output
SET_TARGET_PROPERTIES(modexif PROPERTIES OUTPUT_NAME "exif")
