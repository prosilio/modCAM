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

#include "modcam/mesh/curvature.h"

#include "modcam/mesh/per_vertex_basis.h"
#include "modcam/mesh/per_vertex_normals.h"
#include "modcam/mesh/voronoi_area.h"

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <igl/local_basis.h>

namespace modcam::mesh {
Curvature curvature_rus2004(const Eigen::MatrixX3d &vertices,
                            const Eigen::MatrixX3i &faces) {
	Eigen::MatrixX3d edge0 = vertices(faces.col(2).array(), Eigen::all) -
	                         vertices(faces.col(1).array(), Eigen::all);
	Eigen::MatrixX3d edge1 = vertices(faces.col(0).array(), Eigen::all) -
	                         vertices(faces.col(2).array(), Eigen::all);
	Eigen::MatrixX3d edge2 = vertices(faces.col(1).array(), Eigen::all) -
	                         vertices(faces.col(0).array(), Eigen::all);

	Eigen::MatrixX3d face_basis0;
	Eigen::MatrixX3d face_basis1;
	Eigen::MatrixX3d face_basis2;
	igl::local_basis(vertices, faces, face_basis0, face_basis1, face_basis2);

	Eigen::VectorXd e0_b0 = (edge0.cwiseProduct(face_basis0)).rowwise().sum();
	Eigen::VectorXd e0_b1 = (edge0.cwiseProduct(face_basis1)).rowwise().sum();
	Eigen::VectorXd e1_b0 = (edge1.cwiseProduct(face_basis0)).rowwise().sum();
	Eigen::VectorXd e1_b1 = (edge1.cwiseProduct(face_basis1)).rowwise().sum();
	Eigen::VectorXd e2_b0 = (edge2.cwiseProduct(face_basis0)).rowwise().sum();
	Eigen::VectorXd e2_b1 = (edge2.cwiseProduct(face_basis1)).rowwise().sum();

	Eigen::MatrixX3d vertex_normals = mesh::per_vertex_normals(vertices, faces);
	Eigen::MatrixX3d normal0 = vertex_normals(faces.col(0).array(), Eigen::all);
	Eigen::MatrixX3d normal1 = vertex_normals(faces.col(1).array(), Eigen::all);
	Eigen::MatrixX3d normal2 = vertex_normals(faces.col(2).array(), Eigen::all);

	// [a, b, c] where the second fundamental form is [[a, b],
	//                                                 [b, c]]
	Eigen::Index num_faces = faces.rows();
	Eigen::MatrixXd second_fundamental_fb(num_faces, faces.cols());
	Eigen::MatrixXd A(6, 3);
	Eigen::VectorXd b(6);
	for (Eigen::Index i = 0; i < num_faces; i++) {
		A = Eigen::MatrixXd{
			{e0_b0(i), e0_b1(i), 0.0}, {0.0, e0_b0(i), e0_b1(i)},
			{e1_b0(i), e1_b1(i), 0.0}, {0.0, e1_b0(i), e1_b1(i)},
			{e2_b0(i), e2_b1(i), 0.0}, {0.0, e2_b0(i), e2_b1(i)}};
		b = Eigen::VectorXd{
			{(normal2.row(i) - normal1.row(i)).dot(face_basis0.row(i)),
		     (normal2.row(i) - normal1.row(i)).dot(face_basis1.row(i)),
		     (normal0.row(i) - normal2.row(i)).dot(face_basis0.row(i)),
		     (normal0.row(i) - normal2.row(i)).dot(face_basis1.row(i)),
		     (normal1.row(i) - normal0.row(i)).dot(face_basis0.row(i)),
		     (normal1.row(i) - normal0.row(i)).dot(face_basis1.row(i))}};
		second_fundamental_fb.row(i) =
			(A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b))
				.transpose();
	}

	Eigen::Index num_vertices = vertices.rows();
	Eigen::MatrixX3d weights = voronoi_area(vertices, faces);
	Eigen::VectorXd sum_weights(num_vertices);
	Eigen::MatrixXd second_fundamental_vb(num_vertices, vertices.cols());
	for (Eigen::Index row = 0; row < num_vertices; row++) {
		for (Eigen::Index col = 0; col < 3; col++) {
			int v_idx = faces(row, col);
		}
	}

	std::tuple<Eigen::MatrixX3d, Eigen::MatrixX3d, Eigen::MatrixX3d>
		vertex_basis = mesh::per_vertex_basis(vertex_normals);
	auto &vertex_b0 = std::get<0>(vertex_basis);
	auto &vertex_b1 = std::get<1>(vertex_basis);
	auto &vertex_b2 = std::get<2>(vertex_basis);
}
} // namespace modcam::mesh
