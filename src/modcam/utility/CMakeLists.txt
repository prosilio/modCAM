# Copyright 2024 prosilio
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

# The utility library MUST be linked privately by other libraries.
# 
# These are small helper functions that are not intended to be used outside 
# this project.
add_library(modCAM_utility STATIC)
add_library(modCAM::utility ALIAS modCAM_utility)
target_link_libraries(
    modCAM_utility 
    PUBLIC
        Eigen3::Eigen
)
if(BUILD_SHARED_LIBS)
	set_target_properties(
		modCAM_utility 
		PROPERTIES 
			POSITION_INDEPENDENT_CODE ON
	)
endif()
target_sources(
	modCAM_utility
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS "${modCAM_SOURCE_DIR}/src"
		FILES
			"${modCAM_SOURCE_DIR}/src/modcam/utility/modulus.h"
			"${modCAM_SOURCE_DIR}/src/modcam/utility/random_orthonormal.h"
)
target_sources(
	modCAM_utility
	PRIVATE
		random_orthonormal.cpp
)
