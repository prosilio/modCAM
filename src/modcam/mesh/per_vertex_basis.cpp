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

#include "modcam/mesh/per_vertex_basis.h"

#include "modcam/utility/random_orthonormal.h"

#include <Eigen/Geometry>

namespace modcam::mesh {
std::tuple<Eigen::MatrixX3d, Eigen::MatrixX3d, Eigen::MatrixX3d>
per_vertex_basis(const Eigen::MatrixX3d &vertex_normals) {
	std::tuple<Eigen::MatrixX3d, Eigen::MatrixX3d, Eigen::MatrixX3d> basis;
	auto &b0 = std::get<0>(basis);
	auto &b1 = std::get<1>(basis);
	auto &b2 = std::get<2>(basis);

	b2 = vertex_normals.rowwise().normalized();
	Eigen::Index num_vectors = b2.rows();
	Eigen::Index dim = b2.cols();
	b0.resize(num_vectors, dim);
	b1.resize(num_vectors, dim);
	for (Eigen::Index row = 0; row < num_vectors; row++) {
		b0.row(row) = utility::random_orthonormal(b2.row(row));
		b1.row(row) = b2.row(row).cross(b0.row(row));
	}

	return basis;
}
} // namespace modcam::mesh
