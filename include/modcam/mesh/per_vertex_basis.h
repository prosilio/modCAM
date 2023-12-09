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

#ifndef PER_VERTEX_BASIS_H
#define PER_VERTEX_BASIS_H

#include <Eigen/Core>

namespace modcam::mesh {

/**
 * Compute an orthonormal set of basis vectors where the z-axis is the vertex
 * normal.
 */

void per_vertex_basis(const Eigen::MatrixXd &vertices,
                      const Eigen::MatrixXi &faces);

} // namespace modcam::mesh

#endif
