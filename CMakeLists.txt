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

cmake_minimum_required(VERSION 3.23)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(modcam_version)

project(
    modCAM
    DESCRIPTION "Open source software for Computer Aided Manufacturing (CAM) research"
	VERSION ${modCAM_VER}
    LANGUAGES CXX
)

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(PROJECT_IS_TOP_LEVEL AND EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build directory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

configure_file("${modCAM_SOURCE_DIR}/src/modcam/modcam_version.cpp.in" "${modCAM_SOURCE_DIR}/src/modcam/modcam_version.cpp" @ONLY)

# Helpful CMake modules
include(GNUInstallDirs)
include(GenerateExportHeader)

# Symbols are hidden by default so that we explicitly define which symbols to 
# expose.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# rpath
if(APPLE)
	set(MODCAM_RPATH_BASE @loader_path)
else()
	set(MODCAM_RPATH_BASE $ORIGIN)
endif()
file(RELATIVE_PATH relDir
	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)
set(CMAKE_INSTALL_RPATH ${MODCAM_RPATH_BASE} ${MODCAM_RPATH_BASE}/${relDir})

# Require C++20, but let a parent project ask for something higher
if(DEFINED CMAKE_CXX_STANDARD)
	if(CMAKE_CXX_STANDARD EQUAL 98 OR CMAKE_CXX_STANDARD LESS 20)
		message(FATAL_ERROR "modCAM requires at least C++20")
	endif()
else()
	set(CMAKE_CXX_STANDARD 20)
endif()

# Always enforce the language constraint
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# We don't need compiler extensions, but let a parent ask for them
if(NOT DEFINED CMAKE_CXX_EXTENSIONS)
	set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Target output locations
set(MODCAM_STAGE_DIR ${CMAKE_CURRENT_BINARY_DIR}/staging)
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MODCAM_STAGE_DIR}/${CMAKE_INSTALL_BINDIR})
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MODCAM_STAGE_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MODCAM_STAGE_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()

# Install system runtime libraries
if(WIN32)
	set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR})
else()
	set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
set(CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT modCAM_Runtime)
include(InstallRequiredSystemLibraries)

# All dependencies here
include(modcam_dependencies)

# Project files
add_subdirectory(src)

# Documentation
option(MODCAM_BUILD_DOC "Build documentation" ON)
if(MODCAM_BUILD_DOC)
    add_subdirectory(docs)
endif()

# Tests
option(MODCAM_ENABLE_TESTING "Build tests" ON)
if(MODCAM_ENABLE_TESTING)
    add_subdirectory(tests)
endif()

# Packaging
# Allow package maintainers to freely override the path for the configs
set(MODCAM_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/modCAM"
    CACHE PATH "CMake package config location"
)
mark_as_advanced(MODCAM_INSTALL_CMAKEDIR)

if(PROJECT_IS_TOP_LEVEL)
	add_subdirectory(packaging)
endif()
