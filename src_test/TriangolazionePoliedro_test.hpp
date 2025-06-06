#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{

	//Test triangolazione di prima specie
	TEST(TestTriangolazionePoliedro, PrimaSpecie){
		PolygonalMesh mesh;

		// Inizializzo 3 vertici del triangolo
		mesh.NumCell0Ds = 3;
		mesh.Cell0DsId = {0, 1, 2};
		mesh.Cell0DsCoordinates = Eigen::MatrixXd(3, mesh.NumCell0Ds);
		mesh.Cell0DsCoordinates.col(0) << 0.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(1) << 1.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(2) << 0.0, 1.0, 0.0;

		// Inizializzo gli archi esistenti (i lati del triangolo)
		mesh.NumCell1Ds = 3;
		mesh.Cell1DsId = {0, 1, 2};
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 1;
		mesh.Cell1DsExtrema.col(1) << 1, 2;
		mesh.Cell1DsExtrema.col(2) << 2, 0;
		mesh.Cell1DsEsistente = {1, 1, 1};

		// Inizializzo una faccia triangolare (l’intero triangolo)
		mesh.NumCell2Ds = 1;
		mesh.Cell2DsId = {0};
		mesh.Cell2DsVertices = {{0, 1, 2}};
		mesh.Cell2DsEdges = {{0, 1, 2}};
		mesh.Cell2DsNumVert = {3};
		mesh.Cell2DsNumEdg = {3};

		// Chiamo la funzione per triangolare la faccia con parametro b=2 (esempio)
		TriangolaFaccia(mesh,
					mesh.Cell0DsCoordinates.col(0),
					mesh.Cell0DsCoordinates.col(1),
					mesh.Cell0DsCoordinates.col(2),
					2);

		// Controllo che siano state aggiunte facce e vertici
		EXPECT_GT(mesh.NumCell2Ds, 1);  // Sono stati creati nuovi triangoli
		EXPECT_GE(mesh.Cell0DsCoordinates.cols(), 3); // Vertici >= 3 (quelli iniziali)
		EXPECT_FALSE(mesh.Cell2DsVertices.empty());


}

}