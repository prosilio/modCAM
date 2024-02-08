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

add_library(
	${PROJECT_NAME} 
	"${MODCAM_SRC}" "${MODCAM_HEADERS}" 
	"${UTILITY_SRC}" "${UTILITY_HEADERS}"
)
target_link_libraries(
	${PROJECT_NAME} 
	PUBLIC
		Eigen3::Eigen
	PRIVATE
		doctest
		igl::core
)
target_include_directories(
	${PROJECT_NAME} 
	PUBLIC
		$<BUILD_INTERFACE:${MODCAM_PROJECT_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		${MODCAM_PROJECT_DIR}/src
)
target_compile_options(
	${PROJECT_NAME} 
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
set_target_properties(
	${PROJECT_NAME} 
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)
