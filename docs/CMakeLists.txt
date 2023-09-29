find_package(Doxygen)
if (NOT DOXYGEN_FOUND)
	message("Doxygen needs to be installed to build the documentation.")
	return()
endif ()

doxygen_add_docs(
	modCAM_docs
	"${modCAM_SOURCE_DIR}/src"
	ALL
)
