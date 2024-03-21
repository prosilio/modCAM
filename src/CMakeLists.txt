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
    modCAM_mesh 
    "${MODCAM_SRC}" "${MODCAM_HEADERS}" 
    "${UTILITY_SRC}" "${UTILITY_HEADERS}"
)
add_library(modCAM::mesh ALIAS modCAM_mesh)
target_link_libraries(
    modCAM_mesh 
    PUBLIC
        Eigen3::Eigen
    PRIVATE
        igl::igl_core
)
target_include_directories(
    modCAM_mesh 
    PUBLIC
        $<BUILD_INTERFACE:${modCAM_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
        ${modCAM_SOURCE_DIR}/src
)
set_target_properties(
	modCAM_mesh PROPERTIES
	EXPORT_NAME mesh
)

generate_export_header(
	modCAM_mesh
	BASE_NAME ${PROJECT_NAME}
)

install(
    TARGETS modCAM_mesh 
    EXPORT modCAM_Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT "modCAM_Runtime"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT "modCAM_Runtime"
            NAMELINK_COMPONENT "modCAM_Development"
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT "modCAM_Development"
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    EXPORT      modCAM_Targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/modCAM 
    NAMESPACE   modCAM::
    FILE        "modCAM-Targets.cmake"
    COMPONENT   "modCAM_Development"
)
