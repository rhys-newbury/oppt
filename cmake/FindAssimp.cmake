#
# Try to find ASSIMP library and include path. Once done this will define
#
# ASSIMP_FOUND ASSIMP_INCLUDE_PATH ASSIMP_LIBRARY
#

if(WIN32)
  find_path(ASSIMP_INCLUDE_PATH assimp/scene.h ${ASSIMP_ROOT_DIR}/include
            DOC "The directory where assimp/scene.h resides")

  find_library(
    ASSIMP_LIBRARY
    NAMES assimp ASSIMP assimp
    PATHS ${ASSIMP_ROOT_DIR}/lib
    DOC "The ASSIMP library")
else(WIN32)
  find_path(
    ASSIMP_INCLUDE_PATH
    assimp/scene.h
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include
    ${ASSIMP_ROOT_DIR}/include
    DOC "The directory where assimp/scene.h resides")

  find_library(
    ASSIMP_LIBRARY
    NAMES ASSIMP assimp
    PATHS /usr/lib64
          /usr/lib
          /usr/local/lib64
          /usr/local/lib
          /sw/lib
          /opt/local/lib
          ${ASSIMP_ROOT_DIR}/lib
    DOC "The ASSIMP library")
endif(WIN32)

set(ASSIMP_FOUND "NO")
if(ASSIMP_INCLUDE_PATH AND ASSIMP_LIBRARY)
  set(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})
  set(ASSIMP_FOUND "YES")
  message(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
endif(ASSIMP_INCLUDE_PATH AND ASSIMP_LIBRARY)
