#pragma once

#include<gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary{
	
	//Test per la funzione check_ed_vert
	TEST(TestCheckEdVert, TestValidMesh)
	{
		//Creazione mesh valida (es. tetraedro)
		PolygonalMesh mesh;
		
		//Costruzione della mesh con un tetraedro (q = 3)
		ASSERT_TRUE(costruzione_poliedro(3, mesh));
		
		//Verifica che i vertici corrispondano agli estremi degli spigoli
		EXPECT_TRUE(check_ed_vert(mesh));
	}
	
	TEST(TestCheckEdVert, TestInvalidMesh)
	{
		//Creazione dii una mesh non valida
		PolygonalMesh mesh;
		
		//Creazione di una mesh con un numero di facce e spigoli errato
		mesh.NumCell2Ds = 1;
		mesh.Cell2DsEdges.push_back({0, 1, 2}); //es. errore nei dati degli spigoli
		mesh.Cell2DsVertices.push_back({0, 1, 2});
		
		mesh.Cell1DsExtrema.resize(2, 3);
		mesh.Cell1DsExtrema(0, 0) = 0; mesh.Cell1DsExtrema(1, 0) = 1;
		mesh.Cell1DsExtrema(0, 1) = 1; mesh.Cell1DsExtrema(1, 1) = 2;
		mesh.Cell1DsExtrema(0, 2) = 2; mesh.Cell1DsExtrema(1, 2) = 99;  // <-- vertice non valido
		
		
		//Controllo dei vertici e degli spigoli che fallisce
		EXPECT_FALSE(check_ed_vert(mesh));
	}
}