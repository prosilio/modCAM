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

#include "modcam/mesh/principal_curvature.h"

#include <Eigen/Core>
#include <cmrc/cmrc.hpp>
#include <doctest/doctest.h>
#include <igl/readSTL.h>
#include <igl/remove_duplicate_vertices.h>

#include <cmath>
#include <cstddef>
#include <numbers>
#include <strstream>

CMRC_DECLARE(modcam);

namespace modcam {
TEST_CASE("Test curvature function") {
	SUBCASE("Sphere") {
		auto fs = cmrc::modcam::get_filesystem();
		std::string sphere_path{"data/mesh/sphere.stl"};
		REQUIRE(fs.is_file(sphere_path));
		auto sphere_rc = fs.open(sphere_path);
		std::istrstream sphere_stl(
			sphere_rc.begin(),
			sphere_rc.size()); // TODO: Change this to spanstream when I switch
		                       // to C++23.
		Eigen::MatrixX3d tmp_vertices;
		Eigen::MatrixX3i tmp_faces;
		Eigen::MatrixX3d tmp_normals;
		igl::readSTL(sphere_stl, tmp_vertices, tmp_faces, tmp_normals);
		Eigen::MatrixX3d vertices;
		Eigen::MatrixX3i faces;
		Eigen::VectorXi tmpi;
		Eigen::VectorXi tmpj;
		igl::remove_duplicate_vertices(tmp_vertices, tmp_faces, 1.0e-7,
		                               vertices, tmpi, tmpj, faces);
		Eigen::RowVector3d centers{
			(vertices.colwise().maxCoeff() - vertices.colwise().minCoeff()) /
			2.0};
		for (int i = 0; i < 3; i++) {
			vertices.col(i).array() -=
				centers(i); // Center the sphere on the origin
		}
		vertices.rowwise().normalize(); // Set radius to 1.0
		double radius = 11.37;
		vertices *= radius; // Make the sphere radius variable
		mesh::Curvature principal_curvature =
			mesh::principal_curvature_rus2004(vertices, faces);
		auto &pv1 = std::get<0>(principal_curvature);
		auto &pv2 = std::get<1>(principal_curvature);
		auto &pd1 = std::get<2>(principal_curvature);
		auto &pd2 = std::get<3>(principal_curvature);

		Eigen::Index num_vertices{vertices.rows()};
		CHECK(pv1.rows() == num_vertices);
		CHECK(pv1.cols() == 1);
		CHECK(pv2.rows() == num_vertices);
		CHECK(pv2.cols() == 1);
		CHECK(pd1.rows() == num_vertices);
		CHECK(pd1.cols() == 2);
		CHECK(pd2.rows() == num_vertices);
		CHECK(pd2.cols() == 2);

		double tolerance = 1.0e-6;
		CHECK(((pv1.array() - 1.0 / radius).abs() < tolerance).all());
		CHECK(((pv2.array() - 1.0 / radius).abs() < tolerance).all());
	}
	SUBCASE("Empty face array") {
		const Eigen::MatrixX3d vertices{
			{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.5, 0.0, 0.0}};
		const Eigen::MatrixX3i faces(0, 3);
		mesh::Curvature principal_curvature =
			mesh::principal_curvature_rus2004(vertices, faces);
		auto &pv1 = std::get<0>(principal_curvature);
		CHECK(pv1.size() == 0);
		auto &pv2 = std::get<1>(principal_curvature);
		CHECK(pv2.size() == 0);
		auto &pd1 = std::get<2>(principal_curvature);
		CHECK(pd1.size() == 0);
		auto &pd2 = std::get<3>(principal_curvature);
		CHECK(pd2.size() == 0);
	}
	SUBCASE("Empty vertex array") {
		const Eigen::MatrixX3d vertices(0, 3);
		const Eigen::MatrixX3i faces{{0, 1, 2}};
		mesh::Curvature principal_curvature =
			mesh::principal_curvature_rus2004(vertices, faces);
		auto &pv1 = std::get<0>(principal_curvature);
		CHECK(pv1.size() == 0);
		auto &pv2 = std::get<1>(principal_curvature);
		CHECK(pv2.size() == 0);
		auto &pd1 = std::get<2>(principal_curvature);
		CHECK(pd1.size() == 0);
		auto &pd2 = std::get<3>(principal_curvature);
		CHECK(pd2.size() == 0);
	}
	// SUBCASE("Icosahedron") {
	// 	double phi = (1.0 + std::sqrt(5.0)) / 2.0;
	// 	Eigen::MatrixX3d vertices{
	// 		{phi, 1.0, 0.0},   {phi, -1.0, 0.0},  {-phi, -1.0, 0.0},
	// 		{-phi, 1.0, 0.0},  {1.0, 0.0, phi},   {-1.0, 0.0, phi},
	// 		{-1.0, 0.0, -phi}, {1.0, 0.0, -phi},  {0.0, phi, 1.0},
	// 		{0.0, phi, -1.0},  {0.0, -phi, -1.0}, {0.0, -phi, 1.0}};
	// 	vertices.rowwise().normalize(); // Set radius to 1.0
	// 	Eigen::MatrixX3i faces{{5, 4, 8},  {4, 5, 11},  {8, 4, 0},   {4, 1, 0},
	// 	                       {4, 11, 1}, {11, 10, 1}, {11, 2, 10}, {5, 2, 11},
	// 	                       {1, 10, 7}, {0, 1, 7},   {5, 8, 3},   {2, 5, 3},
	// 	                       {0, 7, 9},  {10, 2, 6}};
	// 	mesh::Curvature principal_curvature =
	// 		mesh::principal_curvature_rus2004(vertices, faces);
	// 	auto &pv1 = std::get<0>(principal_curvature);
	// 	auto &pv2 = std::get<1>(principal_curvature);
	// 	auto &pd1 = std::get<2>(principal_curvature);
	// 	auto &pd2 = std::get<3>(principal_curvature);
	// 	Eigen::Index num_vertices{vertices.rows()};
	// 	CHECK(pv1.rows() == num_vertices);
	// 	CHECK(pv1.cols() == 1);
	// 	CHECK(pv2.rows() == num_vertices);
	// 	CHECK(pv2.cols() == 1);
	// 	CHECK(pd1.rows() == num_vertices);
	// 	CHECK(pd1.cols() == 2);
	// 	CHECK(pd2.rows() == num_vertices);
	// 	CHECK(pd2.cols() == 2);
	// 	const double radius = 1.0;
	// 	int inner_vertices[3] = {1, 4, 11};
	// 	for (int i = 0; i < 3; i++) {
	// 		CHECK(pv1(inner_vertices[i]) == doctest::Approx(1.0 / radius));
	// 		CHECK(pv2(inner_vertices[i]) == doctest::Approx(1.0 / radius));
	// 	}
	// 	int excluded_vertices[3] = {3, 6, 9};
	// 	for (int i = 0; i < 3; i++) {
	// 		CHECK(pd1.row(excluded_vertices[i]).array().isNaN().all());
	// 	}
	// }
	// SUBCASE("Cylinder") {
	// 	const double radius = 0.5;
	// 	const double x0 = radius;
	// 	const double x1 = radius * std::cos(1.0 * 2.0 * std::numbers::pi / 6.0);
	// 	const double x2 = radius * std::cos(2.0 * 2.0 * std::numbers::pi / 6.0);
	// 	const double x3 = radius * std::cos(3.0 * 2.0 * std::numbers::pi / 6.0);
	// 	const double x4 = radius * std::cos(4.0 * 2.0 * std::numbers::pi / 6.0);
	// 	const double x5 = radius * std::cos(5.0 * 2.0 * std::numbers::pi / 6.0);
	// 	const double y0 = 0.0;
	// 	const double y1 = radius * std::sin(1.0 * 2.0 * std::numbers::pi / 6.0);
	// 	const double y2 = radius * std::sin(2.0 * 2.0 * std::numbers::pi / 6.0);
	// 	const double y3 = radius * std::sin(3.0 * 2.0 * std::numbers::pi / 6.0);
	// 	const double y4 = radius * std::sin(4.0 * 2.0 * std::numbers::pi / 6.0);
	// 	const double y5 = radius * std::sin(5.0 * 2.0 * std::numbers::pi / 6.0);
	// 	Eigen::MatrixX3d vertices{{x0, y0, 0.0}, {x0, y0, 1.0}, {x1, y1, 0.0},
	// 	                          {x1, y1, 1.0}, {x2, y2, 0.0}, {x2, y2, 1.0},
	// 	                          {x3, y3, 0.0}, {x3, y3, 1.0}, {x4, y4, 0.0},
	// 	                          {x4, y4, 1.0}, {x5, y5, 0.0}, {x5, y5, 1.0}};
	// 	Eigen::MatrixX3i faces{{1, 0, 2},   {2, 3, 1},   {3, 2, 4},
	// 	                       {4, 5, 3},   {5, 4, 6},   {6, 7, 5},
	// 	                       {7, 6, 8},   {8, 9, 7},   {9, 8, 10},
	// 	                       {10, 11, 9}, {11, 10, 0}, {0, 1, 11}};
	// 	mesh::Curvature principal_curvature =
	// 		mesh::principal_curvature_rus2004(vertices, faces);
	// 	auto &pv1 = std::get<0>(principal_curvature);
	// 	auto &pv2 = std::get<1>(principal_curvature);
	// 	auto &pd1 = std::get<2>(principal_curvature);
	// 	auto &pd2 = std::get<3>(principal_curvature);
	// 	Eigen::Index num_vertices{vertices.rows()};
	// 	CHECK(pv1.rows() == num_vertices);
	// 	CHECK(pv1.cols() == 1);
	// 	CHECK(pv2.rows() == num_vertices);
	// 	CHECK(pv2.cols() == 1);
	// 	CHECK(pd1.rows() == num_vertices);
	// 	CHECK(pd1.cols() == 2);
	// 	CHECK(pd2.rows() == num_vertices);
	// 	CHECK(pd2.cols() == 2);
	// 	for (int i = 0; i < vertices.cols(); i++) {
	// 		CHECK(pv1(i) == doctest::Approx(0.0));
	// 		CHECK(pv2(i) == doctest::Approx(1.0 / radius));
	// 	}
	// }
}
} // namespace modcam
