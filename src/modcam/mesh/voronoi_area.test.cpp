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
#include <doctest/doctest.h>

#include <cmath>

namespace modcam {
TEST_CASE("Test Voronoi area function") {
	SUBCASE("Equilateral triangle") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.5, std::sqrt(3.0) / 2.0, 0.0}};
		const Eigen::MatrixX3i faces{{0, 1, 2}};
		Eigen::MatrixX3d weights = mesh::voronoi_area_of(vertices, faces);
		CHECK(weights(0) == doctest::Approx(0.14433757));
		CHECK(weights(1) == doctest::Approx(0.14433757));
		CHECK(weights(2) == doctest::Approx(0.14433757));
	}

	SUBCASE("Obtuse triangle") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.5, 0.1, 0.0}};
		const Eigen::MatrixX3i faces{{0, 1, 2}};
		Eigen::MatrixX3d weights = mesh::voronoi_area_of(vertices, faces);
		CHECK(weights(0) == 0.0125);
		CHECK(weights(1) == 0.0125);
		CHECK(weights(2) == 0.025);
	}
}
} // namespace modcam
