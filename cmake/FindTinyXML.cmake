# * Find TinyXML Find the native TinyXML includes and library
#
# TINYXML_FOUND       - True if TinyXML found. TINYXML_INCLUDE_DIR - where to
# find tinyxml.h, etc. TINYXML_LIBRARIES   - TinyXML library.
#

if(TINYXML_INCLUDE_DIR)
  # Already in cache, be silent
  set(TinyXML_FIND_QUIETLY TRUE)
endif(TINYXML_INCLUDE_DIR)

find_path(TINYXML_INCLUDE_DIR "tinyxml.h" PATH_SUFFIXES "tinyxml")

find_library(
  TINYXML_LIBRARIES
  NAMES "tinyxml"
  PATH_SUFFIXES "tinyxml")

set(TINYXML_FOUND "NO")
if(TINYXML_LIBRARIES AND TINYXML_INCLUDE_DIR)
  set(TINYXML_FOUND "YES")
endif(TINYXML_LIBRARIES AND TINYXML_INCLUDE_DIR)
