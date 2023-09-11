cmake_minimum_required(VERSION 3.21...3.27)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

project(
	modcam
	DESCRIPTION "Open source software for Computer Aided Manufacturing (CAM) research"
	LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_STANDARD 17)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	include(CTest)
endif()

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# External libraries
find_package(Eigen3 REQUIRED NO_MODULE)
add_subdirectory(external/pybind11)

# Project files
add_subdirectory(src)

# Tests
# MODCAM_BUILD_TESTING override is provided in case this project is included in 
# another project.
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODCAM_BUILD_TESTING)
   AND BUILD_TESTING)
	add_subdirectory(tests)
endif()
