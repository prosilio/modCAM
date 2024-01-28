# Copyright 2024 prosilio
#
# This file is part of modCAM, open source software for Computer Aided
# Manufacturing research.
#
# modCAM is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# modCAM is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# modCAM. If not, see <https://www.gnu.org/licenses/>.

import numpy as np
import modcam.mesh
import pytest


@pytest.fixture
def partial_icosahedron():
    phi = (1.0 + np.sqrt(5.0)) / 2.0
    vertices = np.array(
        [
            [phi, 1.0, 0.0],
            [phi, -1.0, 0.0],
            [-phi, -1.0, 0.0],
            [-phi, 1.0, 0.0],
            [1.0, 0.0, phi],
            [-1.0, 0.0, phi],
            [-1.0, 0.0, -phi],
            [1.0, 0.0, -phi],
            [0.0, phi, 1.0],
            [0.0, phi, -1.0],
            [0.0, -phi, -1.0],
            [0.0, -phi, 1.0],
        ]
    )
    vertices = vertices / np.linalg.norm(vertices, axis=1, ord=2).reshape(
        vertices.shape[0], 1
    )
    faces = np.array(
        [
            [5, 4, 8],
            [4, 5, 11],
            [8, 4, 0],
            [4, 1, 0],
            [4, 11, 1],
            [11, 10, 1],
            [11, 2, 10],
            [5, 2, 11],
            [1, 10, 7],
            [0, 1, 7],
        ]
    )
    return (vertices, faces)


@pytest.fixture
def vertex_normals(partial_icosahedron):
    vertices = partial_icosahedron[0]
    faces = partial_icosahedron[1]
    return modcam.mesh.per_vertex_normals(vertices, faces)


@pytest.mark.parametrize("dim", [(0), (1)])
def test_shape(partial_icosahedron, vertex_normals, dim):
    vertices = partial_icosahedron[0]
    assert vertex_normals.shape[dim] == vertices.shape[dim]


@pytest.mark.parametrize("row", [(1), (4), (11)])
def test_normals(partial_icosahedron, vertex_normals, row):
    vertices = partial_icosahedron[0]
    assert vertex_normals[row, :] == pytest.approx(vertices[row, :])


@pytest.mark.parametrize("row", [(3), (6), (9)])
def test_normals(vertex_normals, row):
    assert np.isnan(vertex_normals[row, :]).all()
