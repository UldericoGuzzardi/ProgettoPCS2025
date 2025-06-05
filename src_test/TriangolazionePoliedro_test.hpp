#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{
	
	TEST(TestPoliedri, TestTriangolazionePoliedro)
	{
		PolygonalMesh mesh;
		
		//Costruzione di un ottaedro (q = 4)
		ASSERT_TRUE(costruzione_poliedro(4, mesh));
		
		//Numero iniziale di facce, lati e vertici
		//unsigned int iniziali_0D = mesh.NumCell0Ds; (non necessarie)
		//unsigned int iniziali_1D = mesh.NumCell1Ds; (non necessarie)
		unsigned int iniziali_2D = mesh.NumCell2Ds;
		
		//Applichiamo la triangolazione: es. testiamo con b=0, c = 1 --> Triangolazione di Prima Specie
		TriangolazionePoliedro(mesh, 0, 1);
		
		//Dopo la triangolazione il numero di facce dovrebbe essere maggiore o uguale a quelle iniziali_0D
		EXPECT_GE(mesh.NumCell2Ds, iniziali_2D);
		
		//Verifichiamo che siano stati aggiornati i dati della cella 3D
		EXPECT_EQ(mesh.Cell3DsNumVert, mesh.NumCell0Ds);
		EXPECT_EQ(mesh.Cell3DsNumEdg, mesh.NumCell1Ds);
		EXPECT_EQ(mesh.Cell3DsNumFaces, mesh.NumCell2Ds);
		
		//Verifica che tutti i vertici stiano ancora sulla sfera unitaria
		for (unsigned int i = 0; i < mesh.NumCell0Ds; ++i){
			double x = mesh.Cell0DsCoordinates(0, i);
			double y = mesh.Cell0DsCoordinates(1, i);
			double z = mesh.Cell0DsCoordinates(2, i);
			double norma = std::sqrt(x*x + y*y + z*z);
			EXPECT_NEAR(norma,1.0, 1e-12);
		}
	}
}