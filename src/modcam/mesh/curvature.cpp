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

#include "modcam/mesh/curvature.h"

#include "modcam/mesh/per_vertex_basis.h"
#include "modcam/mesh/per_vertex_normals.h"

#include <Eigen/Eigenvalues>
#include <igl/local_basis.h>

namespace modcam::mesh {
Curvature curvature_rus2004(const Eigen::MatrixX3d &vertices,
                            const Eigen::MatrixX3i &faces) {
	Eigen::MatrixX3d vertex_normals = mesh::per_vertex_normals(vertices, faces);
	std::tuple<Eigen::MatrixX3d, Eigen::MatrixX3d, Eigen::MatrixX3d> basis =
		mesh::per_vertex_basis(vertex_normals);
}
} // namespace modcam::mesh
