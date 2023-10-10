find_package(Doxygen)
if (NOT DOXYGEN_FOUND)
	message("Doxygen needs to be installed to build the documentation.")
	return()
endif ()

set(DOXYGEN_CITE_BIB_FILES "${modCAM_SOURCE_DIR}/docs/modCAM.bib")

doxygen_add_docs(
	modCAM_docs
	"${modCAM_SOURCE_DIR}/include"
	"${modCAM_SOURCE_DIR}/src"
	ALL
)
