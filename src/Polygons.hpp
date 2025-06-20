#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
	// Cell0D
    unsigned int NumCell0Ds = 0; ///< Numero vertici
    std::vector<unsigned int> Cell0DsId = {}; ///< Cell0D id, dimensione 1 x NumberCell0D
    Eigen::MatrixXd Cell0DsCoordinates = {}; ///< Cell0D coordinate
	std::vector<unsigned int> Cell0DsShortPath = {}; ///< 1 se il vertice appartiene al cammino minimo, altrimenti 0
   
	
	//Cell1D
    unsigned int NumCell1Ds = 0; ///< Numero lati
    std::vector<unsigned int> Cell1DsId = {}; ///< Cell1D id, dimensione 1 x NumberCell1D
    Eigen::MatrixXi Cell1DsExtrema = {}; ///< Cell1D id dei vertici che compono il lato, size 2 x NumberCell1D (fromId,toId)
    std::vector<unsigned int> Cell1DsShortPath = {}; ///< 1 se il lato (cella 1D) appartiene al cammino minimo, altrimenti 0
	std::vector<unsigned int> Cell1DsEsistente = {}; ///< 1 se il lato (cella 1D) va visualizzato su Paraview, altrimenti 0
	
	//Cell2D
    unsigned int NumCell2Ds = 0; ///< Numero facce
    std::vector<unsigned int> Cell2DsId = {}; ///< Cell2D id, dimensione 1 x NumberCell2D
	std::vector<unsigned int> Cell2DsNumVert = {}; // vettore di interi positivi, ciascuno si riferisce al numero di vertici della faccia i-esima
	std::vector<unsigned int> Cell2DsNumEdg = {}; // vettore di interi positivi, ciascuno si riferisce al numero di lati della faccia i-esima
	std::vector<vector<unsigned int>> Cell2DsVertices = {}; // contiene gli id dei vertici di ogni faccia,
    std::vector<vector<unsigned int>> Cell2DsEdges = {}; // contiene gli id dei lati di ogni faccia,
	
	
	//Cell3D
	unsigned int NumCell3Ds = 1;
	unsigned int Cell3DsId; 
	unsigned int Cell3DsNumVert =0;
	unsigned int Cell3DsNumEdg =0;
	unsigned int Cell3DsNumFaces =0;
	vector<unsigned int> Cell3DsVertices = {};
	vector<unsigned int> Cell3DsEdges = {};
	vector<unsigned int> Cell3DsFaces = {};
	
	
};

}