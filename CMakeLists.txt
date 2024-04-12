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

cmake_minimum_required(VERSION 3.23...3.27)

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

# Symbols are hidden by default so that we explicitly define which symbols to 
# expose.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
include(GenerateExportHeader)

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

# Target output locations
include(GNUInstallDirs)
set(MODCAM_STAGE_DIR ${CMAKE_CURRENT_BINARY_DIR}/staging)
include(GNUInstallDirs)
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MODCAM_STAGE_DIR}/${CMAKE_INSTALL_BINDIR})
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MODCAM_STAGE_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MODCAM_STAGE_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()

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
