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

#include "modcam/mesh/per_vertex_normals.h"

#include "modcam/utility/modulus.h"

#include <Eigen/Geometry>
#include <igl/edge_lengths.h>

#include <limits>

namespace modcam::mesh {
Eigen::MatrixX3d per_vertex_normals(const Eigen::MatrixX3d &vertices,
                                    const Eigen::MatrixX3i &faces) {

	if (faces.size() == 0 || vertices.size() == 0) {
		return Eigen::MatrixX3d(0, 3);
	}

	Eigen::MatrixXd edge_squared;
	igl::edge_lengths(vertices, faces, edge_squared);
	edge_squared = edge_squared.cwiseProduct(edge_squared);

	Eigen::Index num_vertices = vertices.rows();
	Eigen::Index vertex_dim = vertices.cols();
	Eigen::MatrixX3d normals = Eigen::MatrixX3d::Zero(num_vertices, vertex_dim);
	Eigen::Index num_faces = faces.rows();
	Eigen::Index vertices_per_face = faces.cols();
	for (Eigen::Index row = 0; row < num_faces; row++) {
		for (Eigen::Index col = 0; col < vertices_per_face; col++) {
			Eigen::Index i = utility::mod(col - 1, vertices_per_face);
			Eigen::Index j = utility::mod(col + 1, vertices_per_face);
			Eigen::RowVector3d edge_i = vertices.row(faces(row, j)).array() -
			                            vertices.row(faces(row, col)).array();
			Eigen::RowVector3d edge_j = vertices.row(faces(row, i)).array() -
			                            vertices.row(faces(row, col)).array();
			normals.row(faces(row, col)) +=
				edge_i.cross(edge_j) /
				(edge_squared(row, i) * edge_squared(row, j));
		}
	}
	for (Eigen::Index row = 0; row < num_vertices; row++) {
		if (normals.row(row).isZero()) {
			normals.row(row) = Eigen::RowVector3d::Constant(
				std::numeric_limits<double>::quiet_NaN());
		}
	}
	normals.rowwise().normalize();
	return normals;
}
} // namespace modcam::mesh
