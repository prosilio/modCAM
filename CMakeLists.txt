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

# Symbols are hidden by default so that we explicitly define which symbols to 
# expose.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
include(GenerateExportHeader)

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(MODCAM_PROJECT_DIR "${PROJECT_SOURCE_DIR}")

include(GNUInstallDirs)

# Dependencies
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(libigl REQUIRED)

# Project files
include("src/modcam/SourceList.cmake")
add_subdirectory(src)

# Tests
option(MODCAM_BUILD_TESTS "Build tests" ON)
if(MODCAM_BUILD_TESTS)
    find_package(doctest REQUIRED)
    
    # Resource files
    include(CMakeRC)
    include("data/SourceList.cmake")
    cmrc_add_resource_library(
        modcam-data 
        ALIAS modcam::data 
        NAMESPACE modcam 
        WHENCE "${MODCAM_PROJECT_DIR}"
        ${MODCAM_DATA}
    )

    add_subdirectory(tests)
endif()

# Documentation
option(MODCAM_BUILD_DOC "Build documentation" ON)
if(MODCAM_BUILD_DOC)
    add_subdirectory(docs)
endif()
