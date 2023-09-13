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
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
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