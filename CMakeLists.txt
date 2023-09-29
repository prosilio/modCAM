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

set(modCAM_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

project(
	modCAM
	DESCRIPTION "Open source software for Computer Aided Manufacturing (CAM) research"
	LANGUAGES CXX
)

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

# External libraries
find_package(Eigen3 REQUIRED NO_MODULE)
add_subdirectory(external/pybind11)

# Project files
add_subdirectory(src)

# Tests
# MODCAM_BUILD_TEST override is provided in case this project is included in 
# another project. Set it to TRUE to build this project's tests.
option(BUILD_TEST "Build tests" ON)
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODCAM_BUILD_TEST)
   AND BUILD_TEST)
	add_subdirectory(tests)
endif()

# Documentation
# MODCAM_BUILD_DOC override is provided in case this project is included in 
# another project. Set it to TRUE to build this project's documentation.
option(BUILD_DOC "Build documentation" ON)
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODCAM_BUILD_DOC)
   AND BUILD_DOC)
	add_subdirectory(docs)
endif()
