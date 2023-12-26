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

#include <Eigen/Core>
#include <doctest/doctest.h>

#include <cmath>

namespace modcam {
TEST_CASE("Test per-vertex normals function") {
	SUBCASE("Partial icosahedron") {
		double phi = (1.0 + std::sqrt(5.0)) / 2.0;
		Eigen::MatrixX3d vertices{
			{phi, 1.0, 0.0},   {phi, -1.0, 0.0},  {-phi, -1.0, 0.0},
			{-phi, 1.0, 0.0},  {1.0, 0.0, phi},   {-1.0, 0.0, phi},
			{-1.0, 0.0, -phi}, {1.0, 0.0, -phi},  {0.0, phi, 1.0},
			{0.0, phi, -1.0},  {0.0, -phi, -1.0}, {0.0, -phi, 1.0}};
		vertices.rowwise()
			.normalize(); // This will make it easier to compare calculated
		                  // vertex normals to the "true" normals.
		Eigen::MatrixX3i faces{{5, 4, 8},  {4, 5, 11},  {8, 4, 0},   {4, 1, 0},
		                       {4, 11, 1}, {11, 10, 1}, {11, 2, 10}, {5, 2, 11},
		                       {1, 10, 7}, {0, 1, 7}};
		Eigen::MatrixX3d vertex_normals =
			mesh::per_vertex_normals(vertices, faces);
		CHECK(vertex_normals.rows() == vertices.rows());
		CHECK(vertex_normals.cols() == vertices.cols());
		CHECK((vertex_normals.row(4).array() == vertices.row(4).array()).all());
		CHECK(
			(vertex_normals.row(11).array() == vertices.row(11).array()).all());
		CHECK((vertex_normals.row(1).array() == vertices.row(1).array()).all());
		CHECK(vertex_normals.row(3).array().isNaN().all());
		CHECK(vertex_normals.row(6).array().isNaN().all());
		CHECK(vertex_normals.row(9).array().isNaN().all());
	}

	SUBCASE("Empty face array") {
		double phi = (1.0 + std::sqrt(5.0)) / 2.0;
		Eigen::MatrixX3d vertices{
			{phi, 1.0, 0.0},   {phi, -1.0, 0.0},  {-phi, -1.0, 0.0},
			{-phi, 1.0, 0.0},  {1.0, 0.0, phi},   {-1.0, 0.0, phi},
			{-1.0, 0.0, -phi}, {1.0, 0.0, -phi},  {0.0, phi, 1.0},
			{0.0, phi, -1.0},  {0.0, -phi, -1.0}, {0.0, -phi, 1.0}};
		Eigen::MatrixXi faces(0, 0);
		Eigen::MatrixXd vertex_normals =
			mesh::per_vertex_normals(vertices, faces);
		CHECK(vertex_normals.size() == 0);
	}

	SUBCASE("Empty vertex array") {
		const Eigen::MatrixXd vertices(0, 0);
		Eigen::MatrixX3i faces{{0, 1, 2}, {0, 2, 3}, {0, 3, 4},
		                       {0, 4, 5}, {0, 5, 6}, {0, 6, 1}};
		Eigen::MatrixXd vertex_normals =
			mesh::per_vertex_normals(vertices, faces);
		CHECK(vertex_normals.size() == 0);
	}

	SUBCASE("2D vertex array") {
		Eigen::MatrixXd vertices{{0.0, 0.0},
		                         {1.0, 0.0},
		                         {0.5, std::sqrt(3.0) / 2.0},
		                         {-0.5, std::sqrt(3.0) / 2.0},
		                         {-1.0, 0.0},
		                         {-0.5, -std::sqrt(3.0) / 2.0},
		                         {0.5, -std::sqrt(3.0) / 2.0}};
		Eigen::MatrixX3i faces{{0, 1, 2}, {0, 2, 3}, {0, 3, 4},
		                       {0, 4, 5}, {0, 5, 6}, {0, 6, 1}};
		CHECK_THROWS_AS(mesh::per_vertex_normals(vertices, faces),
		                std::invalid_argument);
	}

	SUBCASE("Improperly sized face array") {
		double phi = (1.0 + std::sqrt(5.0)) / 2.0;
		Eigen::MatrixX3d vertices{
			{phi, 1.0, 0.0},   {phi, -1.0, 0.0},  {-phi, -1.0, 0.0},
			{-phi, 1.0, 0.0},  {1.0, 0.0, phi},   {-1.0, 0.0, phi},
			{-1.0, 0.0, -phi}, {1.0, 0.0, -phi},  {0.0, phi, 1.0},
			{0.0, phi, -1.0},  {0.0, -phi, -1.0}, {0.0, -phi, 1.0}};
		vertices.rowwise()
			.normalize(); // This will make it easier to compare calculated
		                  // vertex normals to the "true" normals.
		Eigen::MatrixXi faces{{5, 4},   {4, 5},  {8, 4}, {4, 1},  {4, 11},
		                      {11, 10}, {11, 2}, {5, 2}, {1, 10}, {0, 1}};
		CHECK_THROWS_AS(mesh::per_vertex_normals(vertices, faces),
		                std::invalid_argument);
	}
}
} // namespace modcam
