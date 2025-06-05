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
        for (std::size_t i = 0; i < mesh.NumCell0Ds; ++i) {
            double x = mesh.Cell0DsCoordinates(0, i);
            double y = mesh.Cell0DsCoordinates(1, i);
            double z = mesh.Cell0DsCoordinates(2, i);
            double norm = std::sqrt(x*x + y*y + z*z);
            EXPECT_NEAR(norm, 1.0, 1e-12);
        }
    }

	
	//Test per la costruzione di un ottaedro
	TEST(TestPoliedri, TestOttaedro)
	{
		PolygonalMesh mesh;
		
		//Eseguiamo la costruzione del poliedro con q = 4 (ottaedro)
		ASSERT_TRUE(costruzione_poliedro(4, mesh));
		
		ASSERT_EQ(mesh.NumCell0Ds, 6);
        ASSERT_EQ(mesh.NumCell1Ds, 12);
        ASSERT_EQ(mesh.NumCell2Ds, 8);

        // Verifica che ogni vertice sia sulla sfera unitaria
        for (std::size_t i = 0; i < mesh.NumCell0Ds; ++i) {
            double x = mesh.Cell0DsCoordinates(0, i);
            double y = mesh.Cell0DsCoordinates(1, i);
            double z = mesh.Cell0DsCoordinates(2, i);

            double norm = std::sqrt(x*x + y*y + z*z);
            EXPECT_NEAR(norm, 1.0, 1e-12);
        }
	}
	
	//Test per la costruzione di un icosaedro
	TEST(TestPoliedri, TestIcosaedro)
	{
		PolygonalMesh mesh;
		
		//Eseguiamo la costruzione del poliedro con q = 5
		ASSERT_TRUE(costruzione_poliedro(5, mesh));
		
		ASSERT_EQ(mesh.NumCell0Ds, 12);
        ASSERT_EQ(mesh.NumCell1Ds, 30);
        ASSERT_EQ(mesh.NumCell2Ds, 20);

        // Verifica che ogni vertice sia sulla sfera unitaria
        for (std::size_t i = 0; i < mesh.NumCell0Ds; ++i) {
            double x = mesh.Cell0DsCoordinates(0, i);
            double y = mesh.Cell0DsCoordinates(1, i);
            double z = mesh.Cell0DsCoordinates(2, i);

            double norm = std::sqrt(x*x + y*y + z*z);
            EXPECT_NEAR(norm, 1.0, 1e-12);
        }
	}
}