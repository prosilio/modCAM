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

set(MESH_SRC_DIR "${MODCAM_SRC_DIR}/mesh")
set(
	MESH_SRC
	"${MESH_SRC_DIR}/per_vertex_basis.cpp"
	"${MESH_SRC_DIR}/per_vertex_normals.cpp"
	"${MESH_SRC_DIR}/principal_curvature.cpp"
	"${MESH_SRC_DIR}/voronoi_area.cpp"
)

set(MESH_INCLUDE_DIR "${MODCAM_INCLUDE_DIR}/mesh")
set(
	MESH_HEADERS
	"${MESH_INCLUDE_DIR}/per_vertex_basis.h"
	"${MESH_INCLUDE_DIR}/per_vertex_normals.h"
	"${MESH_INCLUDE_DIR}/principal_curvature.h"
	"${MESH_INCLUDE_DIR}/voronoi_area.h"
)

set(
	MESH_TEST_SRC
	"${MESH_SRC_DIR}/per_vertex_basis.test.cpp"
	"${MESH_SRC_DIR}/per_vertex_normals.test.cpp"
	"${MESH_SRC_DIR}/principal_curvature.test.cpp"
	"${MESH_SRC_DIR}/voronoi_area.test.cpp"
)
