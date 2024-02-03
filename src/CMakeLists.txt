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

add_library(modcam_objlib OBJECT "${MODCAM_SRC}" "${MODCAM_HEADERS}" "${UTILITY_SRC}" "${UTILITY_HEADERS}")
target_link_libraries(
	modcam_objlib
	PUBLIC
		Eigen3::Eigen
	PRIVATE
		doctest
		igl::core
)
target_include_directories(
	modcam_objlib
	PUBLIC
		$<BUILD_INTERFACE:${MODCAM_PROJECT_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		${MODCAM_PROJECT_DIR}/src
)
target_compile_options(
	modcam_objlib
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
set_target_properties(modcam_objlib PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(MODCAM_BUILD_CPP)
	add_library(modcam_cpp SHARED $<TARGET_OBJECTS:modcam_objlib>)
	target_include_directories(
		modcam_cpp
		PUBLIC
			$<TARGET_PROPERTY:modcam_objlib,INCLUDE_DIRECTORIES>
	)
	set_target_properties(
		modcam_cpp
		PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
	)
endif()

if(MODCAM_BUILD_PYTHON)
	include("py_modcam/SourceList.cmake")
	pybind11_add_module(py_modcam "${PY_MODCAM_SRC}")
	target_link_libraries(
		py_modcam
		PRIVATE
			modcam_objlib
			Eigen3::Eigen
	)
	set_target_properties(
		py_modcam
		PROPERTIES
			LIBRARY_OUTPUT_NAME "modcam"
			LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
	)
endif()
