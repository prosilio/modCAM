/*
 * Copyright 2023 prosilio
 *
 * This file is part of modCAM, open source software for Computer Aided
 * Manufacturing research.
 *
 * modCAM is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * modCAM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * modCAM. If not, see <https://www.gnu.org/licenses/>.
 */

#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>

#include "modcam/mesh/voronoi_area.h"

namespace py = pybind11;

void bind_mesh(py::module &m) {
	m.def("voronoi_area_of", &modcam::mesh::voronoi_area_of,
	      py::arg_v("vertices", "V-by-3 array of floats"),
	      py::arg_v("faces", "F-by-3 array of ints"),
	      "Compute the Voronoi cell areas for the triangles in a mesh. Returns "
	      "F-by-3 array of floats.");
}
