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


def test_equilateral_triangle():
    vertices = np.array(
        [[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, np.sqrt(3.0) / 2.0, 0.0]]
    )
    faces = np.array([[0, 1, 2]])
    weights = modcam.mesh.voronoi_area(vertices, faces)
    assert weights == pytest.approx(0.14433757)


def test_obtuse_triangle():
    vertices = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 0.1, 0.0]])
    faces = np.array([[0, 1, 2]])
    weights = modcam.mesh.voronoi_area(vertices, faces)
    assert (weights == np.array([[0.0125, 0.0125, 0.025]])).all()


def test_colocated_vertices():
    vertices = np.array([[0.0, 0.0, 0.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]])
    faces = np.array([[0, 1, 2]])
    weights = modcam.mesh.voronoi_area(vertices, faces)
    assert (weights == 0.0).all()


def test_face_singularity():
    vertices = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 0.1, 0.0]])
    faces = np.array([[0, 0, 0]])
    weights = modcam.mesh.voronoi_area(vertices, faces)
    assert (weights == 0.0).all()


def test_colinear_vertices():
    vertices = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 0.0, 0.0]])
    faces = np.array([[0, 1, 2]])
    weights = modcam.mesh.voronoi_area(vertices, faces)
    assert (weights == 0.0).all()


def test_empty_face_array():
    vertices = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 0.1, 0.0]])
    faces = np.array([[]])
    weights = modcam.mesh.voronoi_area(vertices, faces)
    assert (weights == 0.0).all()


def test_empty_vertex_array():
    vertices = np.array([[]])
    faces = np.array([[0, 1, 2]])
    weights = modcam.mesh.voronoi_area(vertices, faces)
    assert (weights == 0.0).all()


def test_2D_vertex_array():
    vertices = np.array([[0.0, 0.0], [1.0, 0.0], [0.5, 0.1]])
    faces = np.array([[0, 1, 2]])
    weights = modcam.mesh.voronoi_area(vertices, faces)
    assert (weights == np.array([[0.0125, 0.0125, 0.025]])).all()


@pytest.mark.xfail(reason="Invalid input", raises=ValueError, strict=True)
def test_improperly_sized_face_array():
    vertices = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 0.1, 0.0]])
    faces = np.array([[0, 1]])
    modcam.mesh.voronoi_area(vertices, faces)
    assert True
