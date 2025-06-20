#pragma once

#include <iostream>
#include <vector>
#include <set>
#include "Eigen/Eigen"
#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestTriangolazionePoliedro, TriangolazionePrimaSpecie) {
		PolygonalMesh mesh;

		// Parametri di test (esempio per ottaedro)
		const unsigned int q = 3;  // q può essere 3, 4 o 5 in base al solido
		const unsigned int b = 2;
		const unsigned int c = 0;

		// Costruzione poliedro base
		bool costruito = costruzione_poliedro(q, mesh);
		ASSERT_TRUE(costruito) << "Costruzione poliedro fallita";

		// Esegui triangolazione prima specie (b, c)
		TriangolazionePoliedro(mesh, b, c);

		// Calcolo T come da formula (2)
		const unsigned int T = b * b + b * c + c * c;

		// Calcolo valori attesi in base a q come da formula (1): è stato aggiunto un termine correttivo poiché per come abbiamo definito la mesh, dopo la triangolazione vengono conteggiati
		//lati e facce in più, presenti nel poliedro di partenza ma che, a causa della triangolazione, non esistono più
		unsigned int V_atteso = 2 * T + 2;            //rimasta invariata
		unsigned int E_atteso = 6 * T + 6;			  // invece che 6T
		unsigned int F_atteso = 4 * T +4; 			  // invece che 4T
    
		// Controlli sui conteggi
		EXPECT_EQ(mesh.NumCell0Ds, V_atteso) << "Numero vertici non corretto";
		EXPECT_EQ(mesh.NumCell1Ds, E_atteso) << "Numero lati non corretto";
		EXPECT_EQ(mesh.NumCell2Ds, F_atteso) << "Numero facce non corretto";
	}
	
	//Ragionamento analogo ma ora testiamo la triangolazione di seconda specie eseguita su un poliedro
	TEST(TestTriangolazionePoliedro, TriangolazioneSecondaSpecie) {
		PolygonalMesh mesh;

		// Parametri di test (esempio per ottaedro)
		const unsigned int q = 3;  // q può essere 3, 4 o 5 in base al solido
		const unsigned int b = 2;
		const unsigned int c = 2;

		// Costruzione poliedro base
		bool costruito = costruzione_poliedro(q, mesh);
		ASSERT_TRUE(costruito) << "Costruzione poliedro fallita";

		// Esegui triangolazione prima specie (b, c)
		TriangolazionePoliedro(mesh, b, c);

		//Definisco il numero di vertici, lati e facce del poliedro di partenza (es ottaedro)
		const unsigned int num_v = 6 ;
		const unsigned int num_e = 12;
		const unsigned int num_f = 8;

		// Calcolo valori attesi in base a q come da formula (1): è stato aggiunto un termine correttivo poiché per come abbiamo definito la mesh, dopo la triangolazione vengono conteggiati
		//lati e facce in più, presenti nel poliedro di partenza ma che, a causa della triangolazione, non esistono più
		
		/* unsigned int V_atteso = num_v + num_e * (2*b -1) + num_f * (3 * b * b /2 - 3 * b / 2 + 1);         
		unsigned int E_atteso = num_e *(2*b) + num_f * (9 * b * b / 2 + 3 * b / 2);			 
		unsigned int F_atteso = num_f * (3 * b * b + 3 * b); */
		
		//C'è necessità di adattare le formule alla struttura delle nostre funzioni e delle nostre mesh
		// La funzione TriangolaFaccia_2 suddivide ogni faccia in b^2 triangoli con una griglia regolare di punti, ma questo cambia anche il numero di vertici e spigoli rispetto alle formule generiche
		unsigned int V_atteso = num_v + num_e * (2 * b - 1) + num_f * ((b - 1) * (b - 2) / 2);
		unsigned int F_atteso = num_f * 3 * b * b;
		unsigned int E_atteso = V_atteso + F_atteso - 2;

		// Controlli sui conteggi 
		EXPECT_EQ(mesh.NumCell0Ds, V_atteso) << "Numero vertici non corretto";
		EXPECT_EQ(mesh.NumCell1Ds, E_atteso) << "Numero lati non corretto";
		EXPECT_EQ(mesh.NumCell2Ds, F_atteso) << "Numero facce non corretto";
		EXPECT_EQ(num_v + num_f, num_e + 2) << "Relazione di Eulero non rispettata";
		EXPECT_EQ(V_atteso + F_atteso, E_atteso + 2) << "Relazione di Eulero non rispettata";
	}
}

