# Find Spatialindex
# ~~~
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
# Once run this will define:
#
# SPATIALINDEX_FOUND       = system has Spatialindex lib
# SPATIALINDEX_LIBRARIES     = full path to the Spatialindex library
# SPATIALINDEX_LIBRARY_DIRS     = path to the Spatialindex library
# SPATIALINDEX_INCLUDE_DIRS = where to find headers
#

find_path(
  SPATIALINDEX_INCLUDE_DIRS
  NAMES SpatialIndex.h
  PATHS /usr/include /usr/local/include "$ENV{LIB_DIR}/include" "$ENV{INCLUDE}"
        "$ENV{OSGEO4W_ROOT}/include"
  PATH_SUFFIXES spatialindex)

find_path(
  SPATIALINDEX_LIBRARY_DIRS
  NAMES libspatialindex.so
  PATHS /usr/lib /usr/local/lib "$ENV{LIB_DIR}/lib" "$ENV{LIB}/lib"
        "$ENV{OSGEO4W_ROOT}/lib")

find_library(
  SPATIALINDEX_LIBRARIES
  NAMES spatialindex_i spatialindex
  PATHS /usr/lib /usr/local/lib "$ENV{LIB_DIR}/lib" "$ENV{LIB}/lib"
        "$ENV{OSGEO4W_ROOT}/lib")

if(SPATIALINDEX_INCLUDE_DIRS AND SPATIALINDEX_LIBRARIES)
  set(SPATIALINDEX_FOUND TRUE)
endif(SPATIALINDEX_INCLUDE_DIRS AND SPATIALINDEX_LIBRARIES)

if(SPATIALINDEX_FOUND)
  if(NOT SPATIALINDEX_FIND_QUIETLY)
    message(STATUS "Found libSpatialIndex: ${SPATIALINDEX_LIBRARY}")
  endif(NOT SPATIALINDEX_FIND_QUIETLY)
else(SPATIALINDEX_FOUND)
  if(SPATIALINDEX_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find libSpatialIndex")
  endif(SPATIALINDEX_FIND_REQUIRED)
endif(SPATIALINDEX_FOUND)
