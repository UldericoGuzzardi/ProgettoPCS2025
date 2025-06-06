#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{
	
	//La funzione triangola faccia dovrebbe funzionare anche nel caso di mesh vuota. Essa infatti utilizza le funzioni EsisteVertice ed EsisteLato
	//Per generare nuovi vertici e lati
	//Affinchè abbia senso, la faccia che passiamo alla funzione deve essere un triangolo equilatero.
	TEST(TestTriangolazionePoliedro,TestTriangolaFaccia)
	{
	
		PolygonalMesh mesh;
		unsigned int b=2;
		Eigen::Vector3d v_0={1,0,0};
		Eigen::Vector3d v_1={0,1,0};
		Eigen::Vector3d v_2={0,0,1};
		TriangolaFaccia(mesh,v_0,v_1,v_2,b);
		
		//Costruisco l'output che mi aspetto su un'altra mesh
		PolygonalMesh mesh_exp;
		
		//Cell0Ds
		mesh_exp.NumCell0Ds=6;
		for (unsigned int i=0; i<6; i++){
			mesh_exp.Cell0DsId.push_back(i);
		}
		mesh_exp.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh_exp.NumCell0Ds);
		mesh_exp.Cell0DsCoordinates.col(0) << 1, 0, 0;
		mesh_exp.Cell0DsCoordinates.col(1) << 1/2.0,1/2.0,0;
		mesh_exp.Cell0DsCoordinates.col(2) << 0, 1, 0;
		mesh_exp.Cell0DsCoordinates.col(3) << 1/2.0, 0, 1/2.0;
		mesh_exp.Cell0DsCoordinates.col(4) << 0,1/2.0,1/2.0;
		mesh_exp.Cell0DsCoordinates.col(5) << 0, 0, 1;
		
		//Cell1Ds
		mesh_exp.NumCell1Ds=9;
		for (unsigned int i=0;i<9;i++){
			mesh_exp.Cell1DsId.push_back(i);
		}
		mesh_exp.Cell1DsExtrema = Eigen::MatrixXi(2, mesh_exp.NumCell1Ds);
		
		mesh_exp.Cell1DsExtrema.col(0) << 0, 1;
		mesh_exp.Cell1DsExtrema.col(1) << 1, 3;
		mesh_exp.Cell1DsExtrema.col(2) << 0, 3;
		mesh_exp.Cell1DsExtrema.col(3) << 1, 4;
		mesh_exp.Cell1DsExtrema.col(4) << 3, 4;
		mesh_exp.Cell1DsExtrema.col(5) << 1, 2;
		mesh_exp.Cell1DsExtrema.col(6) << 2, 4;
		mesh_exp.Cell1DsExtrema.col(7) << 4, 5;
		mesh_exp.Cell1DsExtrema.col(8) << 3, 5;
		
		//Cell2Ds
		mesh_exp.NumCell2Ds=4;
		for (unsigned int i=0;i<4;i++){
			mesh_exp.Cell2DsId.push_back(i);
			mesh_exp.Cell2DsNumVert.push_back(3);
			mesh_exp.Cell2DsNumEdg.push_back(3);
		}
		
		mesh_exp.Cell2DsVertices.reserve(mesh_exp.NumCell2Ds); 
		
		vector<unsigned int> v1 = {0,1,3};
		vector<unsigned int> v2 = {1,4,3};
		vector<unsigned int> v3 = {1,2,4};
		vector<unsigned int> v4 = {3,4,5};
		
		mesh_exp.Cell2DsVertices= {v1, v2, v3, v4};
		
		mesh_exp.Cell2DsEdges.reserve(mesh_exp.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,1,2};
		vector<unsigned int> e2 = {3,4,1};
		vector<unsigned int> e3 = {5,6,3};
		vector<unsigned int> e4 = {4,7,8};
		
		mesh_exp.Cell2DsEdges = {e1, e2, e3, e4};
		
		double tol=1e-10;
		EXPECT_EQ(mesh.NumCell0Ds,6);
		for (unsigned int i=0; i< 6;i++){
			EXPECT_TRUE((mesh.Cell0DsCoordinates.col(i)-mesh_exp.Cell0DsCoordinates.col(i)).norm()<tol);
		}
		
		EXPECT_EQ(mesh.NumCell1Ds,9);
		for (unsigned int i=0; i< 9;i++){
			EXPECT_EQ(mesh.Cell1DsExtrema.col(i),mesh_exp.Cell1DsExtrema.col(i));
		}
		
		EXPECT_EQ(mesh.NumCell2Ds,4);
		for (unsigned int i=0; i< 4;i++){
			EXPECT_EQ(mesh.Cell2DsVertices[i],mesh_exp.Cell2DsVertices[i]);
			EXPECT_EQ(mesh.Cell2DsEdges[i],mesh_exp.Cell2DsEdges[i]);
		}
	
	}
	
}