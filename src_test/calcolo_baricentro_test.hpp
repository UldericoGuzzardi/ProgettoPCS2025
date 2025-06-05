#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestPolygons, TestBaricentro)
{
    PolygonalMesh mesh;

	mesh.NumCell0Ds=6;
	mesh.Cell0DsId = {0,1,2,3,4,5}; 
	mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
			
	mesh.Cell0DsCoordinates.col(0) << 1.0, 0.0, 0.0;
	mesh.Cell0DsCoordinates.col(1) << -1.0, 0.0, 0.0;
	mesh.Cell0DsCoordinates.col(2) << 0.0, 0.0, 1.0;
	mesh.Cell0DsCoordinates.col(3) << 0.0, 0.0, -1.0;
	mesh.Cell0DsCoordinates.col(4) << 0.0, 1.0, 0.0;
	mesh.Cell0DsCoordinates.col(5) << 0.0, -1.0, 0.0;
	
	vector<unsigned int> verts={0,1,2};
	Eigen::Vector3d baricentro = calcolo_baricentro(mesh, verts);
	Eigen::Vector3d baricentro_exp= {0,0,1.0/3.0};
	double tol =1e-10;
	EXPECT_TRUE((baricentro-baricentro_exp).norm()<tol);
}

}