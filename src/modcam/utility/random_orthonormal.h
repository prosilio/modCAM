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

#ifndef RANDOM_ORTHONORMAL_H
#define RANDOM_ORTHONORMAL_H

#include <Eigen/Core>

namespace modcam::utility {
// Create a random normalized 3D vector orthogonal to the input vector.
Eigen::RowVector3d random_orthonormal(const Eigen::RowVector3d &vector);
} // namespace modcam::utility

#endif
