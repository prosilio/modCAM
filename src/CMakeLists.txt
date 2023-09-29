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

include(mesh/SourceList.cmake)

set(
	SRC
	bind_modcam.cpp
	"${MESH_SRC}"
)

set(
	HEADERS
	"${MESH_HEADERS}"
)

pybind11_add_module(modcam "${SRC}" "${HEADERS}")
target_link_libraries(modcam PRIVATE Eigen3::Eigen)
target_include_directories(
	modcam
	PUBLIC
		$<BUILD_INTERFACE:${modCAM_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)
target_compile_options(
	modcam
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
set_target_properties(
	modcam
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)