#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{
	TEST(TestDuale, TestCostruzioneDuale)
	{
		PolygonalMesh mesh;
		PolygonalMesh duale;
		PolygonalMesh duale_exp;
		
		//Costruisco il duale che mi aspetto, che dovrebbe essere il cubo
		
		//Cell0Ds
		duale_exp.NumCell0Ds=8;
		for (unsigned int i=0; i<8; i++){
			duale_exp.Cell0DsId.push_back(i);
		}
		duale_exp.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, duale_exp.NumCell0Ds);
		duale_exp.Cell0DsCoordinates.col(0) << 1/3.0, 1/3.0, 1/3.0;
		duale_exp.Cell0DsCoordinates.col(1) << -1/3.0, 1/3.0, 1/3.0;
		duale_exp.Cell0DsCoordinates.col(2) << -1/3.0, -1/3.0, 1/3.0;
		duale_exp.Cell0DsCoordinates.col(3) << 1/3.0, -1/3.0, 1/3.0;
		duale_exp.Cell0DsCoordinates.col(4) << 1/3.0, -1/3.0, -1/3.0;
		duale_exp.Cell0DsCoordinates.col(5) << -1/3.0, -1/3.0, -1/3.0;
		duale_exp.Cell0DsCoordinates.col(6) << -1/3.0, 1/3.0, -1/3.0;
		duale_exp.Cell0DsCoordinates.col(7) << 1/3.0, 1/3.0, -1/3.0;
		
		//Cell1Ds
		duale_exp.NumCell1Ds=12;
		for (unsigned int i=0; i<12; i++){
			duale_exp.Cell1DsId.push_back(i);
		}
		duale_exp.Cell1DsExtrema = Eigen::MatrixXi(2, duale_exp.NumCell1Ds);
		duale_exp.Cell1DsExtrema.col(0) << 0, 3;
		duale_exp.Cell1DsExtrema.col(1) << 4, 7;
		duale_exp.Cell1DsExtrema.col(2) << 0, 7;
		duale_exp.Cell1DsExtrema.col(3) << 3, 4;
		duale_exp.Cell1DsExtrema.col(4) << 1, 2;
		duale_exp.Cell1DsExtrema.col(5) << 5, 6;
		duale_exp.Cell1DsExtrema.col(6) << 1, 6;
		duale_exp.Cell1DsExtrema.col(7) << 2, 5;
		duale_exp.Cell1DsExtrema.col(8) << 0, 1;
		duale_exp.Cell1DsExtrema.col(9) << 2, 3;
		duale_exp.Cell1DsExtrema.col(10) << 6, 7;
		duale_exp.Cell1DsExtrema.col(11) << 4, 5;
		
		//Cell2Ds
		duale_exp.NumCell2Ds=6;
		for (unsigned int i=0;i<6;i++){
			duale_exp.Cell2DsId.push_back(i);
			duale_exp.Cell2DsNumVert.push_back(4);
			duale_exp.Cell2DsNumEdg.push_back(4);
		}
		
		duale_exp.Cell2DsVertices.reserve(duale_exp.NumCell2Ds);
		
		vector<unsigned int> v1 = {0,3,4,7};
		vector<unsigned int> v2 = {1,2,5,6};
		vector<unsigned int> v3 = {0,3,2,1};
		vector<unsigned int> v4 = {4,7,6,5};
		vector<unsigned int> v5 = {0,1,6,7};
		vector<unsigned int> v6 = {2,3,4,5};
		
		duale_exp.Cell2DsVertices= {v1, v2, v3, v4, v5, v6};
		
		duale_exp.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,3,1,2};
		vector<unsigned int> e2 = {4,7,5,6};
		vector<unsigned int> e3 = {0,9,4,8};
		vector<unsigned int> e4 = {1,10,5,11};
		vector<unsigned int> e5 = {8,6,10,2};
		vector<unsigned int> e6 = {9,3,11,7};
		
		duale_exp.Cell2DsEdges = {e1, e2, e3, e4, e5, e6};
		if (costruzione_poliedro(4,mesh)){
			duale=costruzione_duale(mesh,0,0);
		
		}
		double tol=1e-10;
		EXPECT_EQ(duale.NumCell0Ds,8);
		for (unsigned int i=0; i< 8;i++){
			EXPECT_TRUE((duale.Cell0DsCoordinates.col(i)-duale_exp.Cell0DsCoordinates.col(i)).norm()<tol);
			EXPECT_EQ(duale.Cell0DsId[i],duale_exp.Cell0DsId[i]);
		}
		
		EXPECT_EQ(duale.NumCell1Ds,12);
		for (unsigned int i=0; i< 12;i++){
			EXPECT_EQ(duale.Cell1DsExtrema.col(i),duale_exp.Cell1DsExtrema.col(i));
			EXPECT_EQ(duale.Cell1DsId[i],duale_exp.Cell1DsId[i]);
		}
		
		EXPECT_EQ(duale.NumCell2Ds,6);
		for (unsigned int i=0; i< 6;i++){
			EXPECT_EQ(duale.Cell2DsVertices[i],duale_exp.Cell2DsVertices[i]);
			EXPECT_EQ(duale.Cell2DsEdges[i],duale_exp.Cell2DsEdges[i]);
			EXPECT_EQ(duale.Cell2DsId[i],duale_exp.Cell2DsId[i]);
		}	
		
		
	}
	
	
	
}