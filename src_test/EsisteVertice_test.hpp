#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{
	
	TEST(TestVertici, TestEsisteVertice)
	{
		//Mesh vuota
		PolygonalMesh mesh;
		mesh.NumCell0Ds=0;
		mesh.Cell0DsCoordinates.resize(3,3);
		
		//Aggiungo un primo vertice
		Eigen::Vector3d new_vert={1,0,0};
		unsigned int id_1= EsisteVertice(mesh,new_vert);
		double tol=1e-15;
		
		EXPECT_EQ(id_1, 0);
		EXPECT_EQ(mesh.NumCell0Ds, 1);
		EXPECT_EQ(mesh.Cell0DsId.size(), 1);
		EXPECT_TRUE((mesh.Cell0DsCoordinates.col(id_1)-new_vert).norm()<tol);
		
		//Provo a riaggiungerlo, verifico che l'ID sia sempre zero e che non sia aumentato il numero di vertici
		unsigned int id_2 = EsisteVertice(mesh,new_vert);
		
		EXPECT_EQ(id_2, 0);
		EXPECT_EQ(mesh.NumCell0Ds, 1);
		EXPECT_EQ(mesh.Cell0DsId.size(), 1);
		
		//Provo ad aggiungere un vertice molto vicino, all'interno di EsisteVertice la tolleranza è fissata a 1e-15;
		Eigen::Vector3d close_new_vert={1-tol/2.0,0,0};
		unsigned int id_3= EsisteVertice(mesh,close_new_vert);
		
		//La funzione non dovrebbe aggiungerlo
		EXPECT_EQ(id_3, 0);
		EXPECT_EQ(mesh.NumCell0Ds, 1);
		EXPECT_EQ(mesh.Cell0DsId.size(), 1);
		
		//Infine, provo ad aggiungere un nuovo vertice 
		Eigen::Vector3d vert={2.5,1.6,2};
		unsigned int id_4 = EsisteVertice(mesh,vert);
		
		EXPECT_EQ(id_4, 1);
		EXPECT_EQ(mesh.NumCell0Ds, 2);
		EXPECT_EQ(mesh.Cell0DsId.size(), 2);
		EXPECT_TRUE((mesh.Cell0DsCoordinates.col(id_4)-vert).norm()<tol);
		
	
		
		
		
		
	}
	
	
	
	
	
}