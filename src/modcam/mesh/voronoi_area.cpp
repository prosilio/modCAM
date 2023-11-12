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

#include "modcam/mesh/voronoi_area.h"

#include <igl/cotmatrix_entries.h>
#include <igl/doublearea.h>
#include <igl/edge_lengths.h>
#include <igl/internal_angles.h>

#include <numbers>

namespace {
// Modulo function for looping backward
// For example, mod(-1, 3) == 2, whereas -1 % 3 == -1
int mod(int k, int n) { return ((k %= n) < 0) ? k + n : k; }
} // namespace

namespace mesh {
Eigen::MatrixXd voronoi_area_of(const Eigen::MatrixXd &vertices,
                                const Eigen::MatrixXi &faces) {

	Eigen::VectorXd area;
	igl::doublearea(vertices, faces, area);
	area.array() /= 2.0;

	Eigen::MatrixXd angles;
	igl::internal_angles(vertices, faces, angles);

	Eigen::MatrixXd half_cot;
	igl::cotmatrix_entries(vertices, faces, half_cot);

	Eigen::MatrixXd edge_squared;
	igl::edge_lengths(vertices, faces, edge_squared);
	edge_squared = edge_squared.cwiseProduct(edge_squared);

	double right_angle = std::numbers::pi / 2.0;
	Eigen::Array<bool, Eigen::Dynamic, 1> nonobtuse =
		(angles.array() <= right_angle).rowwise().all();

	int num_faces = faces.rows();
	Eigen::MatrixXd v_area(num_faces, 3);

	for (int row = 0; row < num_faces; row++) {
		for (int col = 0; col < faces.cols(); col++) {
			if (nonobtuse(row)) {
				int i = mod(col - 1, 3);
				int j = mod(col + 1, 3);
				v_area(row, col) =
					0.25 * (edge_squared(row, i) * half_cot(row, i) +
				            edge_squared(row, j) * half_cot(row, j));
			} else {
				if (angles(row, col) > right_angle) {
					v_area(row, col) = area(row) / 2.0;
				} else {
					v_area(row, col) = area(row) / 4.0;
				}
			}
		}
	}

	return v_area;
}
} // namespace mesh
