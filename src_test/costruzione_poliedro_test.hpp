#pragma once

#include "Eigen/Eigen"
#include <vector>

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary{
	
	//Test per la costruzione di un tetraedro
	TEST(TestPoliedri, TestTetraedro)
	{
		PolygonalMesh mesh;
		
		//Costruiamo il poliedro con q = 3 (tetraedro)
		ASSERT_TRUE(costruzione_poliedro(3, mesh));
		
		//Test dei numeri di celle 0D, 1D, 2D
		ASSERT_EQ(mesh.NumCell0Ds, 4);
		ASSERT_EQ(mesh.NumCell1Ds, 6);
		ASSERT_EQ(mesh.NumCell2Ds, 4);
		
		//Verifica delle coordinate dei vertici (Tetraedro inscritto nella sfera unitaria)
		EXPECT_NEAR(mesh.Cell0DsCoordinates(0, 0), 1.0, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(1, 0), -1.0, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(2, 0), -1.0, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(3, 0), 1.0, 1e-16);
		
		EXPECT_NEAR(mesh.Cell0DsCoordinates(0, 1), 1.0, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(1, 1), -1.0, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(2, 1), 1.0, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(3, 1), -1.0, 1e-16);
		
		EXPECT_NEAR(mesh.Cell0DsCoordinates(0, 2), 1.0, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(1, 2), 1.0, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(2, 2), -1.0, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(3, 2), -1.0, 1e-16);
	}
	
	//Test per la costruzione di un cubo
	TEST(TestPoliedri, TestCubo)
	{
		PolygonalMesh mesh;
		
		//Eseguiamo la costruzione del poliedro con q = 4
		ASSERT_TRUE(costruzione_poliedro(4, mesh));
		
		//Verifica numero dei vertici, spigoli, facce del cubo
		EXPECT_EQ(mesh.NumCell0Ds, 8);
		EXPECT_EQ(mesh.NumCell1Ds, 12);
		EXPECT_EQ(mesh.NumCell2Ds, 6);
		
		//Verifica le coordinate (componente x) dei vertici (Cubo inscritto nella sfera unitaria)
		double inv_sqrt3 = 1.0 / std::sqrt(3);
		
		EXPECT_NEAR(mesh.Cell0DsCoordinates(0,0), inv_sqrt3, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(1,0), -inv_sqrt3, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(2,0), inv_sqrt3, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(3,0), -inv_sqrt3, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(4,0), inv_sqrt3, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(5,0), -inv_sqrt3, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(6,0), inv_sqrt3, 1e-16);
		EXPECT_NEAR(mesh.Cell0DsCoordinates(7,0), -inv_sqrt3, 1e-16);
	}
	
	//Test per la costruzione di un icosaedro
	TEST(TestPoliedri, TestIcosaedro)
	{
		PolygonalMesh mesh;
		
		//Eseguiamo la costruzione del poliedro con q = 5
		ASSERT_TRUE(costruzione_poliedro(5, mesh));
		
		//Verifica numero di vertici, spigoli e facce dell'icosaedro
		EXPECT_EQ(mesh.NumCell0Ds, 12);
		EXPECT_EQ(mesh.NumCell1Ds, 30);
		EXPECT_EQ(mesh.NumCell2Ds, 20);
		
		//Verifica le coordinate (componente x) dei vertici (Icosaedro inscritto nella sfera unitaria)
		double phi = (1.0 + std::sqrt(5.0)) / 2.0; //numero aureo
		double inv_sqrt3 = 1.0 / std::sqrt(3.0);
		
		EXPECT_NEAR(mesh.Cell0DsCoordinates(0, 0), 1.0, 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(1, 0), -1.0, 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(2, 0), phi / std::sqrt(1 + phi * phi), 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(3, 0), -phi / std::sqrt(1 + phi * phi), 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(4, 0), 0.0, 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(5, 0), 0.0, 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(6, 0), phi / std::sqrt(1 + phi * phi), 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(7, 0), -phi / std::sqrt(1 + phi * phi), 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(8, 0), -phi / std::sqrt(1 + phi * phi), 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(9, 0), phi / std::sqrt(1 + phi * phi), 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(10, 0), 0.0, 1e-16);
        EXPECT_NEAR(mesh.Cell0DsCoordinates(11, 0), 0.0, 1e-16);
	}
}