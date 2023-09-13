#include <pybind11/pybind11.h>

namespace py = pybind11;

void bind_mesh(py::module &);

PYBIND11_MODULE(modcam, m) {
	m.doc() =
		"Open source software for Computer Aided Manufacturing (CAM) research";

	py::module mesh_m =
		m.def_submodule("mesh", "Tools for working with triangle mesh data");
	bind_mesh(mesh_m);
}