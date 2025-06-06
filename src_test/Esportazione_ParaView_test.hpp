#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

#include "Eigen/Eigen"
#include "Utils.hpp"
#include <gtest/gtest.h>

using namespace std;

namespace fs = std::filesystem;

namespace PolygonalLibrary{
	TEST(TestPolygons, TestEsportazioneParaView){
		PolygonalMesh mesh;
		
		mesh.NumCell0Ds = 2;
		mesh.Cell0DsId = {0, 1};
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		mesh.Cell0DsCoordinates.col(0) << 0.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(1) << 1.0, 0.0, 0.0;
		
		mesh.NumCell1Ds = 1;
		mesh.Cell1DsId = {0};
		mesh.Cell1DsExtrema.resize(2, 1);
		mesh.Cell1DsExtrema << 0, 1;
		
		mesh.Cell1DsShortPath = {0};
		mesh.Cell1DsEsistente = {1};
		mesh.Cell0DsShortPath = {0, 0};
		
		//Elimina i file di output se già presenti
		fs::remove("./Cell0Ds.inp");
		fs::remove("./Cell1Ds.inp");
		
		//Chiamata della funzione da testare
		Esportazione_ParaView(mesh, false);
		
		//Verifica che i file siano stati creati
		EXPECT_TRUE(fs::exists("./Cell0Ds.inp")) << "Cell0Ds.inp non è stato creato.";
		EXPECT_TRUE(fs::exists("./Cell1Ds.inp")) << "Cell1Ds.inp non è stato creato.";
		
		//Verifica sul contenuto dei file che non devono essere vuoti
		std::ifstream file0("Cell0Ds.inp");
		std::ifstream file1("Cell1Ds.inp");
		
		//Iteratore di input che legge carattere per carattere dal file0
		std::string content0 ((std::istreambuf_iterator<char>(file0)), std::istreambuf_iterator<char>());
		std::string content1 ((std::istreambuf_iterator<char>(file1)), std::istreambuf_iterator<char>());
		
		EXPECT_FALSE(content0.empty()) << "Cell0Ds.inp è vuoto.";
		EXPECT_FALSE(content1.empty()) << "Cell1Ds.inp è vuoto.";
		
		//Pulizia dei file generati
		fs::remove("./Cell0Ds.inp");
		fs::remove("./Cell1Ds.inp");	
	}
}