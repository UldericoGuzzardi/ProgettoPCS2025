#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{
	
	//La funzione triangola faccia dovrebbe funzionare anche nel caso di mesh vuota. Essa infatti utilizza le funzioni EsisteVertice ed EsisteLato
	//Per generare nuovi vertici e lati
	//Affinchè abbia senso, la faccia che passiamo alla funzione deve essere un triangolo equilatero.
	TEST(TestPoliedri,TestTriangolaFaccia)
	{
	
		PolygonalMesh mesh;
		unsigned int b=2;
		Eigen::Vector3d v0={1,0,0};
		Eigen::Vector3d v1={0,1,0};
		Eigen::Vector3d v2={0,0,1};
		TriangolaFaccia(mesh,v0,v1,v2,b);
		Eigen::Vector2i l0={0,1};
		Eigen::Vector2i l1={1,3};
		Eigen::Vector2i l2={0,3};
		
		vector<unsigned int> fv={0,1,3};
		vector<unsigned int> fe={0,1,2};
		EXPECT_EQ(mesh.NumCell0Ds,6);
		EXPECT_EQ(mesh.NumCell1Ds,9);
		EXPECT_EQ(mesh.NumCell2Ds,4);
		EXPECT_EQ(mesh.Cell1DsExtrema.col(0),l0);
		EXPECT_EQ(mesh.Cell1DsExtrema.col(1),l1);
		EXPECT_EQ(mesh.Cell1DsExtrema.col(2),l2);
		EXPECT_EQ(mesh.Cell2DsVertices[0],fv);
		EXPECT_EQ(mesh.Cell2DsEdges[0],fe);
		
		
	}
}