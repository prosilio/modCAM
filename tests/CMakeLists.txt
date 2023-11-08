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

find_package(Eigen3 REQUIRED NO_MODULE)

add_executable(
	test_modcam 
	$<TARGET_OBJECTS:modcam_objlib> 
	"${MODCAM_TEST_SRC}"
	"${MODCAM_PROJECT_DIR}/tests/run_tests.cpp"
)
target_link_libraries(
	test_modcam
	PRIVATE
		doctest
		Eigen3::Eigen
)
target_include_directories(
	test_modcam
	PUBLIC
		$<BUILD_INTERFACE:${MODCAM_PROJECT_DIR}/include>
		$<INSTALL_INTERFACE:include>
)
set_target_properties(
	test_modcam
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)
