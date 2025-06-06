#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include "Utils.hpp"
#include <gtest/gtest.h>

using namespace std;

namespace PolygonalLibrary{
	
	TEST(TestPolygons, TestAggiungiFaccia){
		PolygonalMesh mesh;
		
		//Inizializziamo la mesh con 3 vertici per creare una faccia
		mesh.NumCell0Ds = 3;
		mesh.Cell0DsId = {0, 1, 2};
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		mesh.Cell0DsCoordinates.col(0) << 0.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(1) << 1.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(2) << 0.0, 1.0, 0.0;
		
		//Inizialmente non si ha nessuna faccia
		mesh.NumCell2Ds = 0;
		
		//Aggiungiamo una faccia triangolare
		vector<unsigned int> faccia = {0, 1, 2};
		AggiungiFaccia(mesh, faccia);
		
		//Verifico che la faccia sia stata aggiunta correttamente
		EXPECT_EQ(mesh.NumCell2Ds, 1);
		EXPECT_EQ(mesh.Cell2DsId.size(), 1);
		EXPECT_EQ(mesh.Cell2DsVertices.size(), 1);
		EXPECT_EQ(mesh.Cell2DsNumVert.size(), 1);
		
		//Controllo il contenuto
		EXPECT_EQ(mesh.Cell2DsId[0], 0);
		EXPECT_EQ(mesh.Cell2DsVertices[0], faccia);
		EXPECT_EQ(mesh.Cell2DsNumVert[0], 3);
	}
}