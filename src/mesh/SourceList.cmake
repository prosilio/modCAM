set(MESH_SRC_DIR "${CMAKE_SOURCE_DIR}/src/mesh")

set(
	MESH_SRC
	"${MESH_SRC_DIR}/bind_mesh.cpp"
	"${MESH_SRC_DIR}/voronoi_area.cpp"
)

set(MESH_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/mesh")

set(
	MESH_HEADERS
	"${MESH_INCLUDE_DIR}/voronoi_area.h"
)
