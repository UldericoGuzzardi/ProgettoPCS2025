#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{
	
	TEST(TestLati, TestEsisteLato)
	{
		PolygonalMesh mesh;
		
		//Inizializziamo la matrice degli estremi come vuota
		mesh.NumCell1Ds = 0;
		mesh.Cell1DsId.clear();
		mesh.Cell1DsExtrema.resize(2, 0);
		
		//Primo test: inserisco un lato, ad esempio {3, 1} che verrà ordinato in {1, 3}
		Eigen::Vector2i lato1(3, 1);
		unsigned int id1 = EsisteLato(mesh, lato1);
		
		EXPECT_EQ(id1, 0);
		EXPECT_EQ(mesh.NumCell1Ds, 1);
		EXPECT_EQ(mesh.Cell1DsId.size(), 1);
		EXPECT_EQ(mesh.Cell1DsExtrema(0, 0), 1);
		EXPECT_EQ(mesh.Cell1DsExtrema(1, 0), 3);
		
		//Secondo test: Inserisco di nuovo lo stesso lato ma ordinato {1, 3}
		Eigen::Vector2i lato2(1,3);
		unsigned int id2 = EsisteLato(mesh, lato2);
		
		EXPECT_EQ(id2, id1); // Deve restituire lo stesso ID
		EXPECT_EQ(mesh.NumCell1Ds, 1); // Numero di lati resta invariato
		EXPECT_EQ(mesh.Cell1DsId.size(), 1);
		
		//Terzo test: inserisco un nuovo lato {2, 4} che non esiste ancora
		Eigen::Vector2i lato3(2, 4);
		unsigned int id3 = EsisteLato(mesh, lato3);
		
		EXPECT_EQ(id3, 1); //secondo lato, quindi ID = 1
		EXPECT_EQ(mesh.NumCell1Ds, 2);
		EXPECT_EQ(mesh.Cell1DsId.size(), 2);
		EXPECT_EQ(mesh.Cell1DsExtrema(0, 1), 2);
		EXPECT_EQ(mesh.Cell1DsExtrema(1, 1), 4);
		
		//Quarto test: altro nuovo lato, inserito in ordine inverso {5, 0} che viene ordinato come {0, 5}
		Eigen::Vector2i lato4(5, 0);
		unsigned int id4 = EsisteLato(mesh, lato4);

		EXPECT_EQ(id4, 2); // terzo lato, quindi ID = 2
		EXPECT_EQ(mesh.NumCell1Ds, 3);
		EXPECT_EQ(mesh.Cell1DsExtrema(0, 2), 0);
		EXPECT_EQ(mesh.Cell1DsExtrema(1, 2), 5);
	}
}