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

#ifndef PER_VERTEX_NORMALS_H
#define PER_VERTEX_NORMALS_H

#include "modcam_export.h"

#include <Eigen/Core>

namespace modcam::mesh {

/**
 * Compute the per-vertex normal vectors for a set of vertices and faces, as
 * described in @cite Max1999
 */

MODCAM_EXPORT Eigen::MatrixX3d
per_vertex_normals(const Eigen::MatrixX3d &vertices,
                   const Eigen::MatrixX3i &faces);

} // namespace modcam::mesh

#endif
