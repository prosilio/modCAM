# Copyright 2023 prosilio
# 
# This file is part of modCAM, open source software for Computer Aided
# Manufacturing research.
# 
# modCAM is free software: you can redistribute it and/or modify it under the 
# terms of the GNU General Public License as published by the Free Software 
# Foundation, either version 3 of the License, or (at your option) any later 
# version.
# 
# modCAM is distributed in the hope that it will be useful, but WITHOUT ANY 
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR 
# A PARTICULAR PURPOSE. See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with 
# modCAM. If not, see <https://www.gnu.org/licenses/>. 

cmake_minimum_required(VERSION 3.21...3.27)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
	message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build directory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

project(
	modCAM
	DESCRIPTION "Open source software for Computer Aided Manufacturing (CAM) research"
	LANGUAGES CXX
)

set(MODCAM_PROJECT_DIR "${PROJECT_SOURCE_DIR}")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_STANDARD 17)
	include(CTest)
endif()

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(
		CMAKE_BUILD_TYPE "${default_build_type}" CACHE
	    STRING "Choose the type of build." FORCE
	)
	# Set the possible values of build type for cmake-gui
	set_property(
		CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
		"Debug" "Release" "MinSizeRel" "RelWithDebInfo"
	)
endif()

# Build options
option(MODCAM_BUILD_CPP "Build C++ shared library" ON)
option(MODCAM_BUILD_PYTHON "Build Python bindings" ON)

if(MODCAM_BUILD_PYTHON)
	add_subdirectory("${MODCAM_PROJECT_DIR}/external/pybind11")
endif()

# Project files
add_subdirectory(src)

# Tests
add_subdirectory("${MODCAM_PROJECT_DIR}/external/doctest")
# add_subdirectory(tests)
set(DOCTEST_CONFIG_FILE "tests/doctest_config.h")
configure_file(
	"${DOCTEST_CONFIG_FILE}.in"
	"${DOCTEST_CONFIG_FILE}"
)
include_directories("${DOCTEST_CONFIG_FILE}")

# Documentation
# MODCAM_BUILD_DOC override is provided in case this project is included in 
# another project. Set it to TRUE to build this project's documentation.
option(BUILD_DOC "Build documentation" ON)
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODCAM_BUILD_DOC)
   AND BUILD_DOC)
	add_subdirectory(docs)
endif()
