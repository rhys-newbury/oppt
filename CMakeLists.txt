cmake_minimum_required(VERSION 3.15)
project(oppt)

cmake_policy(SET CMP0012 NEW)

# Default to RelWithDebInfo build if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
if(NOT CMAKE_BUILD_TYPE MATCHES RELWITHDEBINFO
   AND NOT CMAKE_BUILD_TYPE MATCHES DEBUG
   AND NOT CMAKE_BUILD_TYPE MATCHES RELEASE)
  message(
    FATAL_ERROR
      "${CMAKE_BUILD_TYPE} is not a valid build type. Use Debug, Release, or RelWithDebInfo."
  )
endif()

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
    "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DEIGEN_NO_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DEIGEN_NO_DEBUG")

# Build flags
option(BUILD_PLUGINS "Build the POMDP model plugins" ON)
option(BUILD_SOLVERS "Build the POMDP solvers" ON)
option(BUILD_VIEWER "Build the viewer" ON)

add_definitions(-DUSE_DOUBLE_PRECISION=true)

# Setup paths
set(ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_definitions(-DROOT_PATH=${ROOT_PATH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ROOT_PATH}/../bin")
set(OPPT_CMAKE_DIR ${ROOT_PATH}/../cmake)
include(${OPPT_CMAKE_DIR}/CPM.cmake)

# Include macros and search
include(${OPPT_CMAKE_DIR}/SearchForStuff.cmake)


include(${OPPT_CMAKE_DIR}/FindGazebo.cmake)
set(GZ_INCLUDE_DIRS ${GAZEBO_INCLUDE_DIRS})
list(APPEND oppt_INCLUDE_TARGETS "${GAZEBO_INCLUDE_DIRS}")

CPMAddPackage(
  NAME spatialindex
  GITHUB_REPOSITORY libspatialindex/libspatialindex
  GIT_TAG 1.8.5
  OPTIONS
    "BUILD_TESTING OFF"
    "BUILD_TOOLS OFF"
)

add_library(spatialindex_iface INTERFACE)
target_link_libraries(spatialindex_iface INTERFACE spatialindex)
target_include_directories(spatialindex_iface INTERFACE ${spatialindex_SOURCE_DIR}/include)

set(SPATIALINDEX_INCLUDE_DIRS ${spatialindex_SOURCE_DIR})
list(APPEND oppt_INCLUDE_TARGETS ${SPATIALINDEX_INCLUDE_DIRS})

CPMAddPackage(
  NAME Eigen
  VERSION 3.2.8
  URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
  # Eigen's CMakelists are not intended for library use
  DOWNLOAD_ONLY YES 
)

if(Eigen_ADDED)
  add_library(Eigen INTERFACE IMPORTED)
  target_include_directories(Eigen INTERFACE ${Eigen_SOURCE_DIR})
endif()


CPMAddPackage(
  NAME
  boost_pfr
  GITHUB_REPOSITORY
  boostorg/pfr
  GIT_TAG
  2.2.0
)

find_package(Boost REQUIRED COMPONENTS system thread filesystem serialization)

CPMAddPackage(
  NAME tinyxml
  GITHUB_REPOSITORY jslee02/tinyxml
  GIT_TAG main
)

find_package(assimp QUIET)

if (NOT assimp_FOUND)
  CPMAddPackage(
    NAME assimp
    GITHUB_REPOSITORY assimp/assimp
    GIT_TAG v5.0.0 
    OPTIONS
      "ASSIMP_BUILD_TESTS OFF"
      "ASSIMP_NO_EXPORT ON"
      "BUILD_SHARED_LIBS OFF"
  )
endif()

CPMAddPackage(
  NAME fcl
  GITHUB_REPOSITORY flexible-collision-library/fcl
  GIT_TAG fcl-0.5  # Specify the version you want to use
)

if(GZ_GT_10)
  set(REQUIRED_CXX_STANDARD 17)
else()
  set(REQUIRED_CXX_STANDARD 11)
endif()

# Include macro template
configure_package_config_file(
  "${OPPT_CMAKE_DIR}/opptMacros.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/opptMacros.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/oppt")

include(${CMAKE_CURRENT_BINARY_DIR}/opptMacros.cmake)

# Include OPPT modules
include(${ROOT_PATH}/oppt/options/CMakeLists.txt)
include(${ROOT_PATH}/oppt/opptCore/CMakeLists.txt)
include(${ROOT_PATH}/oppt/plugin/CMakeLists.txt)
include(${ROOT_PATH}/oppt/robotEnvironment/CMakeLists.txt)
include(${ROOT_PATH}/oppt/robots/CMakeLists.txt)
include(${ROOT_PATH}/oppt/gazeboInterface/CMakeLists.txt)
include(${ROOT_PATH}/oppt/utils/CMakeLists.txt)
include(${ROOT_PATH}/oppt/filter/CMakeLists.txt)
include(${ROOT_PATH}/oppt/problemEnvironment/CMakeLists.txt)
include(${ROOT_PATH}/oppt/robotHeaders/CMakeLists.txt)
include(${ROOT_PATH}/oppt/solver/CMakeLists.txt)
include(${ROOT_PATH}/oppt/CMakeLists.txt)

if(USE_RVIZ AND BUILD_VIEWER)
  include(${ROOT_PATH}/oppt/viewerPublisher/CMakeLists.txt)
endif()

# Source and library setup
set(COMMON_SRCS ${THIRD_PARTY_SRC} ${CMAKE_CURRENT_LIST_DIR}/src/oppt/global.cpp)

set(OPPT_SRC
    ${COMMON_SRCS}
    ${OPTIONS_SRC}
    ${ROBOT_PROBLEM_SRC}
    ${ROBOT_ENVIRONMENT_SRC}
    ${GAZEBO_INTERFACE_SRC}
    ${ROBOTS_SRC}
    ${OPPT_UTILS_SRC}
    ${FILTER_SRC}
    ${VIEWER_PUBLISHER_SRC}
    ${CHANGES_PARSER_SRC})

# OPPT shared library
add_library(oppt SHARED ${OPPT_SRC})

find_package(ignition-math4 REQUIRED)
get_target_property(IGN_MATH4_INCLUDE_DIR ignition-math4::ignition-math4 INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(oppt
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    ${GAZEBO_INCLUDE_DIRS}
    ${IGN_MATH4_INCLUDE_DIR}
)
target_link_libraries(oppt
  PUBLIC
    Eigen
    ignition-math4::ignition-math4
    ${Boost_LIBRARIES}
    ${GAZEBO_LIBRARIES}
    ${SDF_LIBRARIES}
    ${catkin_LIBRARIES}
    ${TCLAP_LIBRARIES}
    ${URDFDOM_LIBRARIES}
    fcl
    ${kdl_parser_LIBRARIES}
    ${trac_ik_lib_LIBRARIES}
    ${TINYXML_LIBRARIES}
    ${ASSIMP_LIBRARIES}
    ${CMAKE_DL_LIBS}
    ${roscpp_LIBRARIES}
  PRIVATE
    spatialindex_iface

)

set_target_properties(oppt PROPERTIES CXX_STANDARD ${REQUIRED_CXX_STANDARD}
                                      CXX_STANDARD_REQUIRED YES)

install(
  TARGETS oppt
  EXPORT "opptTargets"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(TARGETS oppt
        LIBRARY DESTINATION oppt_py)  # ← install next to oppt_py.so

# Plugins and solvers
if(BUILD_PLUGINS)
  message(STATUS "Compiling OPPT plugins")
  add_subdirectory(${ROOT_PATH}/plugins/)
endif()

if(BUILD_SOLVERS)
  message(STATUS "Compiling solvers")
  add_subdirectory(${ROOT_PATH}/solvers/)
endif()

if(USE_RVIZ AND BUILD_VIEWER)
  message(STATUS "Compiling OPPT viewer")
  add_subdirectory(${ROOT_PATH}/viewer/)
endif()

# Install OPPT configuration
configure_package_config_file(
  "${OPPT_CMAKE_DIR}/opptConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/opptConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/oppt"
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR)

install(
  EXPORT opptTargets
  FILE "opptTargets.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/oppt")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/opptConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/opptMacros.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/oppt")

install(FILES ${ROOT_PATH}/../setup.sh
        DESTINATION ${CMAKE_INSTALL_DATADIR}/oppt/)
install(DIRECTORY ${ROOT_PATH}/../models
        DESTINATION ${CMAKE_INSTALL_DATADIR}/oppt/)

# Optional: Doxygen documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  add_custom_target(
    doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)
endif()

# Python bindings

cpmaddpackage(NAME pybind11 GITHUB_REPOSITORY pybind/pybind11 VERSION 2.12.0)

pybind11_add_module(_oppt_py src/bindings.cpp)

target_include_directories(_oppt_py PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(_oppt_py
  PRIVATE
    oppt
    abt_solver
    ${GAZEBO_LIBRARIES}
    ${Boost_LIBRARIES}
    fcl
    Eigen
    spatialindex_iface
)

target_link_options(_oppt_py PRIVATE
  "-Wl,--no-as-needed"
  "-Wl,--export-dynamic"
)

set_target_properties(_oppt_py PROPERTIES
  ENABLE_EXPORTS ON
  CXX_STANDARD ${REQUIRED_CXX_STANDARD}
  INSTALL_RPATH "$ORIGIN"
  BUILD_RPATH "$ORIGIN"  
)

install(TARGETS _oppt_py
    LIBRARY DESTINATION oppt_py  
)

install(FILES
  ${spatialindex_BINARY_DIR}/bin/libspatialindex.so.4
  DESTINATION oppt_py
)
