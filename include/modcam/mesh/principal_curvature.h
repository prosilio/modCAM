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

#ifndef CURVATURE_H
#define CURVATURE_H

#include <Eigen/Core>

#include <tuple>
#include <vector>

namespace modcam::mesh {

using Curvature = std::tuple<Eigen::VectorXd, Eigen::VectorXd, Eigen::MatrixXd,
                             Eigen::MatrixXd>;

/**
 * Compute the (vertex) principal curvature using the algorithm described in
 * @cite Rusinkiewicz2004.
 */
Curvature principal_curvature_rus2004(const Eigen::MatrixX3d &vertices,
                                      const Eigen::MatrixX3i &faces);

} // namespace modcam::mesh

#endif
