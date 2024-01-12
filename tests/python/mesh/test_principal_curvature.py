import igl
import numpy as np
import modcam.mesh
import pytest


@pytest.fixture
def sphere_mesh():
    sphere_file = "data/meshes/sphere.stl"
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
    radius = sphere_mesh[2]
    pv1, pv2, pd1, pd2 = modcam.mesh.principal_curvature(vertices, faces)
    assert (pv1 == pytest.approx(1.0 / radius)) and (pv2 == pytest.approx(1.0 / radius))


def test_empty_face_array():
    vertices = np.array([[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.5, 1.0, 0.0]])
    faces = np.empty((0, 3))
    pv1, pv2, pd1, pd2 = modcam.mesh.principal_curvature(vertices, faces)
    assert (pv1.size == 0) and (pv2.size == 0) and (pd1.size == 0) and (pd2.size == 0)


def test_empty_vertex_array():
    vertices = np.empty((0, 3))
    faces = np.array([[0, 1, 2]])
    pv1, pv2, pd1, pd2 = modcam.mesh.principal_curvature(vertices, faces)
    assert (pv1.size == 0) and (pv2.size == 0) and (pd1.size == 0) and (pd2.size == 0)
