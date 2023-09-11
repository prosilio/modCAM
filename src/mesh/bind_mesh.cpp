#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "mesh/voronoi_area.h"

namespace py = pybind11;

void bind_mesh(py::module &m)
{
	m.def("voronoi_area", &Mesh::voronoi_area);
}
