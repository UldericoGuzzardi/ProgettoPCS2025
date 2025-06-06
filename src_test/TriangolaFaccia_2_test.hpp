#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{
	
	
	TEST(TestTriangolazionePoliedro,TestTriangolaFaccia_2)
	{
	
		PolygonalMesh mesh;
		unsigned int b=2;
		
		Eigen::Vector3d v_0={1,0,0};
		Eigen::Vector3d v_1={0,1,0};
		Eigen::Vector3d v_2={0,0,1};
		TriangolaFaccia_2(mesh,v_0,v_1,v_2,b,0);
	
		//Costruisco l'output che mi aspetto su un'altra mesh
		PolygonalMesh mesh_exp;
		
		//Cell0Ds
		mesh_exp.NumCell0Ds=16;
		for (unsigned int i=0; i<16; i++){
			mesh_exp.Cell0DsId.push_back(i);
		}
		mesh_exp.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh_exp.NumCell0Ds);
		mesh_exp.Cell0DsCoordinates.col(0) << 1, 0, 0;
		mesh_exp.Cell0DsCoordinates.col(1) << 1/2.0, 1/2.0, 0;
		mesh_exp.Cell0DsCoordinates.col(2) << 0, 1, 0;
		mesh_exp.Cell0DsCoordinates.col(3) << 1/2.0, 0, 1/2.0;
		mesh_exp.Cell0DsCoordinates.col(4) << 0, 1/2.0, 1/2.0;
		mesh_exp.Cell0DsCoordinates.col(5) << 0, 0, 1;
		mesh_exp.Cell0DsCoordinates.col(6) << 2/3.0, 1/6.0, 1/6.0;
		mesh_exp.Cell0DsCoordinates.col(7) << 1/3.0, 1/3.0, 1/3.0;
		mesh_exp.Cell0DsCoordinates.col(8) << 1/6.0, 2/3.0, 1/6.0;
		mesh_exp.Cell0DsCoordinates.col(9) << 1/6.0, 1/6.0, 2/3.0;
		mesh_exp.Cell0DsCoordinates.col(10) << 3/4.0, 1/4.0, 0;
		mesh_exp.Cell0DsCoordinates.col(11) << 1/4.0, 3/4.0, 0;
		mesh_exp.Cell0DsCoordinates.col(12) << 3/4.0, 0, 1/4.0;
		mesh_exp.Cell0DsCoordinates.col(13) << 0, 3/4.0, 1/4.0;
		mesh_exp.Cell0DsCoordinates.col(14) << 1/4.0, 0, 3/4.0;
		mesh_exp.Cell0DsCoordinates.col(15) << 0, 1/4.0, 3/4.0;
		
		//Cell1Ds
		mesh_exp.NumCell1Ds=33;
		for (unsigned int i=0;i<33;i++){
			mesh_exp.Cell1DsId.push_back(i);
		}
		mesh_exp.Cell1DsExtrema = Eigen::MatrixXi(2, mesh_exp.NumCell1Ds);
		
		mesh_exp.Cell1DsExtrema.col(0) << 0, 6;
		mesh_exp.Cell1DsExtrema.col(1) << 0, 10;
		mesh_exp.Cell1DsExtrema.col(2) << 6, 10;
		mesh_exp.Cell1DsExtrema.col(3) << 0, 12;
		mesh_exp.Cell1DsExtrema.col(4) << 6, 12;
		mesh_exp.Cell1DsExtrema.col(5) << 1, 6;
		mesh_exp.Cell1DsExtrema.col(6) << 1, 10;
		mesh_exp.Cell1DsExtrema.col(7) << 3, 6;
		mesh_exp.Cell1DsExtrema.col(8) << 3, 12;
		mesh_exp.Cell1DsExtrema.col(9) << 3, 7;
		mesh_exp.Cell1DsExtrema.col(10) << 6, 7;
		mesh_exp.Cell1DsExtrema.col(11) << 1, 7;
		mesh_exp.Cell1DsExtrema.col(12) << 3, 9;
		mesh_exp.Cell1DsExtrema.col(13) << 7, 9;
		mesh_exp.Cell1DsExtrema.col(14) << 4, 7;
		mesh_exp.Cell1DsExtrema.col(15) << 4, 9;
		mesh_exp.Cell1DsExtrema.col(16) << 1, 8;
		mesh_exp.Cell1DsExtrema.col(17) << 7, 8;
		mesh_exp.Cell1DsExtrema.col(18) << 4, 8;
		mesh_exp.Cell1DsExtrema.col(19) << 2, 8;
		mesh_exp.Cell1DsExtrema.col(20) << 2, 11;
		mesh_exp.Cell1DsExtrema.col(21) << 8, 11;
		mesh_exp.Cell1DsExtrema.col(22) << 2, 13;
		mesh_exp.Cell1DsExtrema.col(23) << 8, 13;
		mesh_exp.Cell1DsExtrema.col(24) << 1, 11;
		mesh_exp.Cell1DsExtrema.col(25) << 4, 13;
		mesh_exp.Cell1DsExtrema.col(26) << 3, 14;
		mesh_exp.Cell1DsExtrema.col(27) << 9, 14;
		mesh_exp.Cell1DsExtrema.col(28) << 5, 9;
		mesh_exp.Cell1DsExtrema.col(29) << 5, 14;
		mesh_exp.Cell1DsExtrema.col(30) << 4, 15;
		mesh_exp.Cell1DsExtrema.col(31) << 9, 15;
		mesh_exp.Cell1DsExtrema.col(32) << 5, 15;
		
		//Cell2Ds
		mesh_exp.NumCell2Ds=18;
		for (unsigned int i=0;i<18;i++){
			mesh_exp.Cell2DsId.push_back(i);
			mesh_exp.Cell2DsNumVert.push_back(3);
			mesh_exp.Cell2DsNumEdg.push_back(3);
		}
		
mesh_exp.Cell2DsVertices.reserve(mesh_exp.NumCell2Ds);
		
		vector<unsigned int> v1 = {6,0,10};
		vector<unsigned int> v2 = {6,0,12};
		vector<unsigned int> v3 = {6,1,10};
		vector<unsigned int> v4 = {6,3,12};
		vector<unsigned int> v5 = {6,3,7};
		vector<unsigned int> v6 = {6,1,7};
		vector<unsigned int> v7 = {7,3,9};
		vector<unsigned int> v8 = {7,4,9};
		vector<unsigned int> v9 = {7,1,8};
		vector<unsigned int> v10 = {7,4,8};
		vector<unsigned int> v11 = {8,2,11};
		vector<unsigned int> v12 = {8,2,13};
		vector<unsigned int> v13 = {8,1,11};
		vector<unsigned int> v14 = {8,4,13};
		vector<unsigned int> v15 = {9,3,14};
		vector<unsigned int> v16 = {9,5,14};
		vector<unsigned int> v17 = {9,4,15};
		vector<unsigned int> v18 = {9,5,15};

		
		mesh_exp.Cell2DsVertices= {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17,v18};
		
		mesh_exp.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,1,2};
		vector<unsigned int> e2 = {0,3,4};
		vector<unsigned int> e3 = {5,6,2};
		vector<unsigned int> e4 = {7,8,4};
		vector<unsigned int> e5 = {7,9,10};
		vector<unsigned int> e6 = {5,11,10};
		vector<unsigned int> e7 = {9,12,13};
		vector<unsigned int> e8 = {14,15,13};
		vector<unsigned int> e9 = {11,16,17};
		vector<unsigned int> e10 = {14,18,17};
		vector<unsigned int> e11 = {19,20,21};
		vector<unsigned int> e12 = {19,22,23};
		vector<unsigned int> e13 = {16,24,21};
		vector<unsigned int> e14 = {18,25,23};
		vector<unsigned int> e15 = {12,26,27};
		vector<unsigned int> e16 = {28,29,27};
		vector<unsigned int> e17 = {15,30,31};
		vector<unsigned int> e18 = {28,32,31};
		
		
		mesh_exp.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17,e18};
		
		double tol=1e-10;
		EXPECT_EQ(mesh.NumCell0Ds,16);
		for (unsigned int i=0; i< 16;i++){
			EXPECT_TRUE((mesh.Cell0DsCoordinates.col(i)-mesh_exp.Cell0DsCoordinates.col(i)).norm()<tol);
		}
		
		EXPECT_EQ(mesh.NumCell1Ds,33);
		for (unsigned int i=0; i< 33;i++){
			EXPECT_EQ(mesh.Cell1DsExtrema.col(i),mesh_exp.Cell1DsExtrema.col(i));
		}
		
		EXPECT_EQ(mesh.NumCell2Ds,18);
		for (unsigned int i=0; i< 18;i++){
			EXPECT_EQ(mesh.Cell2DsVertices[i],mesh_exp.Cell2DsVertices[i]);
			EXPECT_EQ(mesh.Cell2DsEdges[i],mesh_exp.Cell2DsEdges[i]);
		}
	
	}
	
}