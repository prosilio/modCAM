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

import igl
import numpy as np
import modcam.mesh
import pytest


@pytest.fixture
def sphere_mesh():
    sphere_file = "data/mesh/sphere.stl"
    vertices, faces = igl.read_triangle_mesh(sphere_file)
    vertices, faces = igl.remove_duplicates(vertices, faces, 1.0e-7)
    for i in range(3):
        center = (vertices[:, i].max() - vertices[:, i].min()) / 2.0
        vertices[:, i] -= center
    vertices /= np.linalg.norm(vertices, ord=2, axis=1, keepdims=True)
    radius = 11.37
    vertices *= radius
    return vertices, faces, radius


def test_sphere_principal_curvature(sphere_mesh):
    vertices = sphere_mesh[0]
    faces = sphere_mesh[1]
    pv1, pv2, _, _ = modcam.mesh.principal_curvature(vertices, faces)
    radius = sphere_mesh[2]
    assert (pv1, pv2) == (pytest.approx(1.0 / radius), pytest.approx(1.0 / radius))


def test_empty_face_array():
    vertices = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 1.0, 0.0]])
    faces = np.empty((0, 3))
    pv1, pv2, pd1, pd2 = modcam.mesh.principal_curvature(vertices, faces)
    assert (pv1.size, pv2.size, pd1.size, pd2.size) == (0, 0, 0, 0)


def test_empty_vertex_array():
    vertices = np.empty((0, 3))
    faces = np.array([[0, 1, 2]])
    pv1, pv2, pd1, pd2 = modcam.mesh.principal_curvature(vertices, faces)
    assert (pv1.size, pv2.size, pd1.size, pd2.size) == (0, 0, 0, 0)
