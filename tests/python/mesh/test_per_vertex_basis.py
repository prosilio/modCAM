import numpy as np
import modcam.mesh
import pytest


@pytest.mark.parametrize(
    "normal_vector",
    [
        (np.array([[1.0, 0.0, 0.0]])),
        (np.array([[0.0, 1.0, 0.0]])),
        (np.array([[0.0, 0.0, 1.0]])),
    ],
)
def test_axis_aligned_normal(normal_vector):
    (b0, b1, b2) = modcam.mesh.per_vertex_basis(normal_vector)
    assert (
        (b2 == normal_vector).all()
        and (np.cross(b0, b1) == b2).all()
        and (np.cross(b1, b2) == b0).all()
    )


def test_non_unit_normal():
    normal_vector = np.array([[1.0, 1.0, 1.0]])
    (b0, b1, b2) = modcam.mesh.per_vertex_basis(normal_vector)
    unit_normal = normal_vector / np.linalg.norm(normal_vector, axis=1, ord=2)
    assert (
        b2 == pytest.approx(unit_normal)
        and np.cross(b0, b1) == pytest.approx(b2)
        and np.cross(b1, b2) == pytest.approx(b0)
    )
