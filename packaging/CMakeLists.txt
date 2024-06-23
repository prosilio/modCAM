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

install(
	FILES modCAMConfig.cmake
	DESTINATION "${MODCAM_INSTALL_CMAKEDIR}"
	COMPONENT modCAM_Development
)

install(
    EXPORT modCAM_Targets
    DESTINATION "${MODCAM_INSTALL_CMAKEDIR}"
    NAMESPACE modCAM::
    FILE modCAM-Targets.cmake
    COMPONENT modCAM_Development
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	modCAMConfigVersion.cmake
	COMPATIBILITY AnyNewerVersion
)

set(CPACK_PACKAGE_NAME modCAM)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Free and open source CAM software")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_VERBATIM_VARIABLES YES)

if(WIN32)
	set(CPACK_GENERATOR ZIP)
else()
	set(CPACK_GENERATOR TGZ)
endif()

set(CPACK_SOURCE_IGNORE_FILES
	/\\.git/
	\\.swp
	\\.orig
	/CMakeLists\\.txt\\.user
)

include(CPack)

cpack_add_component(modCAM_Runtime
	DISPLAY_NAME Runtime
	DESCRIPTION "Shared libraries and executables"
	REQUIRED
	INSTALL_TYPES Full Developer Minimal
)
cpack_add_component(modCAM_Development
	DISPLAY_NAME "Developer pre-requisites"
	DESCRIPTION "Headers/static libs needed for building"
	DEPENDS modCAM_Runtime
	INSTALL_TYPES Full Developer
)
