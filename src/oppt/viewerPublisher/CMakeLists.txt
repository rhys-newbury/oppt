set(VIEWER_PUBLISHER_SRC "")
if(roscpp_FOUND)
  set(VIEWER_PUBLISHER_SRC ${CMAKE_CURRENT_LIST_DIR}/ViewerPublisher.cpp
                           ${CMAKE_CURRENT_LIST_DIR}/SDFParser.cpp)
  install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/oppt/
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hxx"
    PATTERN "*.hpp"
    PATTERN ".DS_Store" EXCLUDE)
endif()
