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

#include <Eigen/Core>
#include <doctest/doctest.h>

#include <cmath>

namespace modcam {
TEST_CASE("Test Voronoi area function") {
	SUBCASE("Equilateral triangle") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.5, std::sqrt(3.0) / 2.0, 0.0}};
		const Eigen::MatrixX3i faces{{0, 1, 2}};
		Eigen::MatrixX3d weights = mesh::voronoi_area(vertices, faces);
		const double one_third_area = std::sqrt(3.0) / 12.0;
		CHECK(weights(0) == doctest::Approx(one_third_area));
		CHECK(weights(1) == doctest::Approx(one_third_area));
		CHECK(weights(2) == doctest::Approx(one_third_area));
	}
	SUBCASE("Obtuse triangle") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.5, 0.1, 0.0}};
		const Eigen::MatrixX3i faces{{0, 1, 2}};
		Eigen::MatrixX3d weights = mesh::voronoi_area(vertices, faces);
		CHECK(weights(0) == 0.0125);
		CHECK(weights(1) == 0.0125);
		CHECK(weights(2) == 0.025);
	}
	SUBCASE("Multiple triangles") {
		const Eigen::MatrixX3d vertices{{0.0, 0.0, 0.0},
		                                {1.0, 0.0, 0.0},
		                                {0.5, std::sqrt(3.0) / 2.0, 0.0},
		                                {0.5, 0.1, 0.0}};
		const Eigen::MatrixX3i faces{{0, 1, 2}, {0, 1, 3}};
		Eigen::MatrixX3d weights = mesh::voronoi_area(vertices, faces);
		CHECK(weights.rows() == faces.rows());
		CHECK(weights.cols() == 3);
		const double one_third_area = std::sqrt(3.0) / 12.0;
		CHECK(weights(0, 0) == doctest::Approx(one_third_area));
		CHECK(weights(0, 1) == doctest::Approx(one_third_area));
		CHECK(weights(0, 2) == doctest::Approx(one_third_area));
		CHECK(weights(1, 0) == 0.0125);
		CHECK(weights(1, 1) == 0.0125);
		CHECK(weights(1, 2) == 0.025);
	}
	SUBCASE("Colocated vertices") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
		const Eigen::MatrixX3i faces{{0, 1, 2}};
		Eigen::MatrixX3d weights = mesh::voronoi_area(vertices, faces);
		CHECK(weights(0) == 0.0);
		CHECK(weights(1) == 0.0);
		CHECK(weights(2) == 0.0);
	}
	SUBCASE("Face singularity") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.5, 0.1, 0.0}};
		const Eigen::MatrixX3i faces{{0, 0, 0}};
		Eigen::MatrixX3d weights = mesh::voronoi_area(vertices, faces);
		CHECK(weights(0) == 0.0);
		CHECK(weights(1) == 0.0);
		CHECK(weights(2) == 0.0);
	}
	SUBCASE("Colinear vertices") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.5, 0.0, 0.0}};
		const Eigen::MatrixX3i faces{{0, 1, 2}};
		Eigen::MatrixX3d weights = mesh::voronoi_area(vertices, faces);
		CHECK(weights(0) == 0.0);
		CHECK(weights(1) == 0.0);
		CHECK(weights(2) == 0.0);
	}
	SUBCASE("Empty face array") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.5, 0.0, 0.0}};
		const Eigen::MatrixXi faces(0, 0);
		Eigen::MatrixXd weights = mesh::voronoi_area(vertices, faces);
		CHECK(weights.size() == 0);
	}
	SUBCASE("Empty vertex array") {
		const Eigen::MatrixXd vertices(0, 0);
		const Eigen::MatrixX3i faces{{0, 1, 2}};
		Eigen::MatrixXd weights = mesh::voronoi_area(vertices, faces);
		CHECK(weights(0) == 0.0);
		CHECK(weights(1) == 0.0);
		CHECK(weights(2) == 0.0);
	}
	SUBCASE("2D vertex array") {
		const Eigen::MatrixXd vertices{{0.0, 0.0}, {1.0, 0.0}, {0.5, 0.1}};
		const Eigen::MatrixX3i faces{{0, 1, 2}};
		Eigen::MatrixX3d weights = mesh::voronoi_area(vertices, faces);
		CHECK(weights(0) == 0.0125);
		CHECK(weights(1) == 0.0125);
		CHECK(weights(2) == 0.025);
	}
	SUBCASE("Improperly sized face array") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.5, 0.1, 0.0}};
		const Eigen::MatrixXi faces{{0, 1}};
		CHECK_THROWS_AS(mesh::voronoi_area(vertices, faces),
		                std::invalid_argument);
	}
}
} // namespace modcam
