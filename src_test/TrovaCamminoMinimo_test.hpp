#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{
	
	TEST(TestCammino, TestCamminoMinimo){
		PolygonalMesh mesh;
		if (costruzione_poliedro(5,mesh)){
			mesh.Cell0DsCoordinates.col(4)<<5,5,5;
			
			//Ci sono due cammini disponibili tra i vertici 0 e 10 che attraversano solo un vertice in mezzo.
			//Il primo è 0-2-10, il secondo 0-4-10
			//Ho modificato le coordinate del vertice 4 in modo da forzare la scelta del cammino 0-2-10, i lati sono invece 0-13
			bool cammino=TrovaCamminoMinimo(mesh,0,10,0);
		}
		vector<unsigned int> camminov_exp={0,2,10};
		vector<unsigned int> camminov={};
		for (unsigned int i=0; i<mesh.NumCell0Ds;i++){
			if(mesh.Cell0DsShortPath[i]==1)
				camminov.push_back(i);
		}
		EXPECT_EQ(camminov_exp,camminov);
		
		vector<unsigned int> camminoe_exp={0,13};
		vector<unsigned int> camminoe={};
		for (unsigned int i=0; i<mesh.NumCell1Ds;i++){
			if(mesh.Cell1DsShortPath[i]==1)
				camminoe.push_back(i);
		}
		EXPECT_EQ(camminoe_exp,camminoe);
		
		//Controllo sulla lunghezza
		double lunghezza_exp=(mesh.Cell0DsCoordinates.col(0)-mesh.Cell0DsCoordinates.col(2)).norm()+(mesh.Cell0DsCoordinates.col(2)-mesh.Cell0DsCoordinates.col(10)).norm();
		
		double lunghezza=0;
		for(unsigned int i=0; i< camminov.size()-1;i++){
			lunghezza+=(mesh.Cell0DsCoordinates.col(camminov[i])-mesh.Cell0DsCoordinates.col(camminov[i+1])).norm();
		}
		double tol=1e-10;
		EXPECT_TRUE((lunghezza-lunghezza_exp)<tol);
		
	}
}
	
