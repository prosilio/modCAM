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

#include <Eigen/Core>
#include <doctest/doctest.h>

#include <cmath>
#include <numbers>

namespace modcam {
TEST_CASE("Test curvature function") {
	SUBCASE("Partial icosahedron") {
		double phi = (1.0 + std::sqrt(5.0)) / 2.0;
		Eigen::MatrixX3d vertices{
			{phi, 1.0, 0.0},   {phi, -1.0, 0.0},  {-phi, -1.0, 0.0},
			{-phi, 1.0, 0.0},  {1.0, 0.0, phi},   {-1.0, 0.0, phi},
			{-1.0, 0.0, -phi}, {1.0, 0.0, -phi},  {0.0, phi, 1.0},
			{0.0, phi, -1.0},  {0.0, -phi, -1.0}, {0.0, -phi, 1.0}};
		vertices.rowwise().normalize(); // Set radius to 1.0
		Eigen::MatrixX3i faces{{5, 4, 8},  {4, 5, 11},  {8, 4, 0},   {4, 1, 0},
		                       {4, 11, 1}, {11, 10, 1}, {11, 2, 10}, {5, 2, 11},
		                       {1, 10, 7}, {0, 1, 7}};
		mesh::Curvature curvature = mesh::curvature_rus2004(vertices, faces);
		CHECK(curvature.size() == vertices.rows());
		const double radius = 1.0;
		int inner_vertices[3] = {1, 4, 11};
		for (int i = 0; i < 3; i++) {
			CHECK(curvature[inner_vertices[i]].first(0) ==
			      doctest::Approx(1.0 / radius));
			CHECK(curvature[inner_vertices[i]].first(1) ==
			      doctest::Approx(1.0 / radius));
		}
		int excluded_vertices[3] = {3, 6, 9};
		for (int i = 0; i < 3; i++) {
			CHECK(curvature[excluded_vertices[i]].first.array().isNaN().all());
		}
	}
	SUBCASE("Cylinder") {
		const double radius = 0.5;
		const double x0 = radius;
		const double x1 = radius * std::cos(1.0 * 2.0 * std::numbers::pi / 6.0);
		const double x2 = radius * std::cos(2.0 * 2.0 * std::numbers::pi / 6.0);
		const double x3 = radius * std::cos(3.0 * 2.0 * std::numbers::pi / 6.0);
		const double x4 = radius * std::cos(4.0 * 2.0 * std::numbers::pi / 6.0);
		const double x5 = radius * std::cos(5.0 * 2.0 * std::numbers::pi / 6.0);
		const double y0 = 0.0;
		const double y1 = radius * std::sin(1.0 * 2.0 * std::numbers::pi / 6.0);
		const double y2 = radius * std::sin(2.0 * 2.0 * std::numbers::pi / 6.0);
		const double y3 = radius * std::sin(3.0 * 2.0 * std::numbers::pi / 6.0);
		const double y4 = radius * std::sin(4.0 * 2.0 * std::numbers::pi / 6.0);
		const double y5 = radius * std::sin(5.0 * 2.0 * std::numbers::pi / 6.0);
		Eigen::MatrixX3d vertices{{x0, y0, 0.0}, {x0, y0, 1.0}, {x1, y1, 0.0},
		                          {x1, y1, 1.0}, {x2, y2, 0.0}, {x2, y2, 1.0},
		                          {x3, y3, 0.0}, {x3, y3, 1.0}, {x4, y4, 0.0},
		                          {x4, y4, 1.0}, {x5, y5, 0.0}, {x5, y5, 1.0}};
		Eigen::MatrixX3i faces{{1, 0, 2},   {2, 3, 1},   {3, 2, 4},
		                       {4, 5, 3},   {5, 4, 6},   {6, 7, 5},
		                       {7, 6, 8},   {8, 9, 7},   {9, 8, 10},
		                       {10, 11, 9}, {11, 10, 0}, {0, 1, 11}};
		mesh::Curvature curvature = mesh::curvature_rus2004(vertices, faces);
		CHECK(curvature.size() == vertices.rows());
		const double radius = 1.0;
		for (int i = 0; i < vertices.cols(); i++) {
			CHECK(curvature[i].first(0) == doctest::Approx(0.0));
			CHECK(curvature[i].first(1) == doctest::Approx(1.0 / radius));
		}
	}
}
} // namespace modcam
