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

#include "modcam/utility/random_orthonormal.h"

#include <Eigen/Geometry>

#include <cmath>

namespace modcam::utility {
Eigen::RowVector3d random_orthonormal(const Eigen::RowVector3d &vector) {
	Eigen::RowVector3d perturb_vec = vector.normalized();
	double perturbation = 1.0;
	bool x_aligned = (1.0 - std::abs(perturb_vec(0))) < 1.0e-2;
	if (x_aligned) {
		perturb_vec(1) += perturbation;
	} else {
		perturb_vec(0) += perturbation;
	}
	Eigen::RowVector3d random_ortho_vector = vector.cross(perturb_vec);
	return random_ortho_vector;
}
} // namespace modcam::utility
