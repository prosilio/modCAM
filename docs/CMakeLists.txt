find_package(Doxygen)
if (NOT DOXYGEN_FOUND)
	message("Doxygen needs to be installed to build the documentation.")
	return()
endif ()

set(DOXYGEN_EXCLUDE_PATTERNS "*.test.cpp")
set(DOXYGEN_CITE_BIB_FILES "${MODCAM_PROJECT_DIR}/docs/modCAM.bib")

doxygen_add_docs(
	modCAM_docs
	"${MODCAM_PROJECT_DIR}/include"
	"${MODCAM_PROJECT_DIR}/src/modcam"
	ALL
)
