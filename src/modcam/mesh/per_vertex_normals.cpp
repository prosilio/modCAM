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
Eigen::MatrixXd per_vertex_normals(const Eigen::MatrixXd &vertices,
                                   const Eigen::MatrixXi &faces) {

	int vertices_per_face = faces.cols();
	if (vertices_per_face != 3) {
		throw std::invalid_argument(
			"There should be three vertices per face, i.e. the faces array "
			"should have three columns.");
	}

	Eigen::MatrixXd edge_squared;
	igl::edge_lengths(vertices, faces, edge_squared);
	edge_squared = edge_squared.cwiseProduct(edge_squared);

	int num_vertices = vertices.rows();
	int vertex_dim = vertices.cols();
	Eigen::MatrixXd normals = Eigen::MatrixXd::Zero(num_vertices, vertex_dim);
	int num_faces = faces.rows();
	for (int row = 0; row < num_faces; row++) {
		for (int col = 0; col < vertices_per_face; col++) {
			int i = utility::mod(col - 1, vertices_per_face);
			int j = utility::mod(col + 1, vertices_per_face);
			Eigen::RowVector3d edge_i = vertices.row(faces(row, j)).array() -
			                            vertices.row(faces(row, col)).array();
			Eigen::RowVector3d edge_j = vertices.row(faces(row, i)).array() -
			                            vertices.row(faces(row, col)).array();
			normals.row(faces(row, col)) +=
				edge_i.cross(edge_j) /
				(edge_squared(row, i) * edge_squared(row, j));
		}
	}
	for (int row = 0; row < num_vertices; row++) {
		if (normals.row(row).isZero()) {
			normals.row(row) = Eigen::RowVector3d::Constant(
				std::numeric_limits<double>::quiet_NaN());
		}
	}
	normals.rowwise().normalize();
	return normals;
}
} // namespace modcam::mesh
