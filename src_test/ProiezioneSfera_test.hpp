#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary{
	
	//Test base: verifica che dopo la proiezione ogni vertice abbia norma circa 1
	TEST(TestPolygons, TestProiezioneSfera){
		PolygonalMesh mesh;
		
		//Inizializziamo 3 vertici non normalizzati
		mesh.NumCell0Ds = 3;
		mesh.Cell0DsId = {0, 1, 2};
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		mesh.Cell0DsCoordinates.col(0) << 2.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(1) << 0.0, 3.0, 0.0;
		mesh.Cell0DsCoordinates.col(2) << 0.0, 0.0, 4.0;
		
		//Eseguiamo la proiezione sulla sfera unitaria
		ProiezioneSfera(mesh);
		
		//Verifico che tutti i vertici siano stati normalizzati
		double tol = 1e-10;
		for (unsigned int i = 0; i < mesh.NumCell0Ds; ++i){
			double x = mesh.Cell0DsCoordinates(0, i);
			double y = mesh.Cell0DsCoordinates(1, i);
			double z = mesh.Cell0DsCoordinates(2, i);

			double norma = sqrt(x * x + y * y + z * z);
			
			EXPECT_NEAR(norma, 1.0, tol) << "Vertice" << i << "non è stato normalizzato correttamente.";
	
		}
	}
	
	//Test: verifica che la direzione del vettore resti invariata dopo la normalizzazione
	TEST(TestPolygons, TestProiezioneSferaDirezioneInvariata){
		PolygonalMesh mesh;
		
		//Aggiungo un solo vertice in direzione (2, 2, 2)
		mesh.NumCell0Ds = 1;
		mesh.Cell0DsId = {0};
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		mesh.Cell0DsCoordinates.col(0) << 2.0, 2.0, 2.0;
		
		// Calcolo la direzione attesa (vettore normalizzato)
		Eigen::Vector3d originale = mesh.Cell0DsCoordinates.col(0).normalized();

		// Applico la proiezione
		ProiezioneSfera(mesh);

		//Recupero il risultato
		Eigen::Vector3d proiettato = mesh.Cell0DsCoordinates.col(0);
		
		//Confronto la direzione originale con quella ottenuta
		EXPECT_TRUE((originale - proiettato).norm() < 1e-10)
			<< "La direzione del vertice è cambiata dopo la normalizzazione.";	
	}
	
	//Test: se un vertice è già normalizzato, deve rimanere invariato
	TEST(TestPolygons, TestProiezioneSferaGiaNormalizzato){
		PolygonalMesh mesh;
		
		mesh.NumCell0Ds = 1;
		mesh.Cell0DsId = {0};
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		//Vertice già sulla sfera unitaria
		mesh.Cell0DsCoordinates.col(0) << 1.0 / sqrt(3), 1.0 / sqrt(3), 1.0 / sqrt(3);
		
		//Salvo la versione originale
		Eigen::Vector3d prima = mesh.Cell0DsCoordinates.col(0);
		
		//Applico la proiezione
		ProiezioneSfera(mesh);
		
		//Verifico che non sia cambiato
		Eigen::Vector3d dopo = mesh.Cell0DsCoordinates.col(0);
		EXPECT_TRUE((prima - dopo).norm() < 1e-10)
			<< "Il punto già normalizzato è stato modificato dalla funzione.";
	}
}