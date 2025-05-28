#include <iostream>
#include "Polygons.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main(){
	
	PolygonalMesh mesh;
	int q = 4;
	int b=1;
	unsigned int num_facce_iniziali;
	unsigned int num_lati_iniziali;
	
	
	bool pol = costruzione_poliedro(q, mesh);
	
	if (!pol){
		cout<<"Errore nella costruzione del poliedro"<<endl;
	}
	
	if (!check_ed_vert(mesh)){
		cout<<"Il controllo di lati e vertici non è andato a buon fine"<<endl;
	}
	
	if (b==1){
		num_facce_iniziali =0;
		num_lati_iniziali=0;
	} else{
		num_facce_iniziali = mesh.NumCell2Ds;
		num_lati_iniziali= mesh.NumCell1Ds;
		TriangolazionePoliedro(mesh, b);
		
	}
	
	PolygonalMesh duale = costruzione_duale(mesh, num_facce_iniziali, num_lati_iniziali);
	
	/*cout<<"POLIEDRO: "<<endl;
	cout<<endl;
	
	for (unsigned int i=0; i < mesh.NumCell0Ds; i++){
		cout<<"Coordinate Vertice " << mesh.Cell0DsId[i] << ": "<< mesh.Cell0DsCoordinates(0,i)<<" "<<mesh.Cell0DsCoordinates(1,i)<<" "<<mesh.Cell0DsCoordinates(2,i)<<" "<<endl; 
	}
	
	cout<<endl;
	
	for (unsigned int i=0; i< mesh.NumCell1Ds; i++){
		cout<<"Estremi Lato " << mesh.Cell1DsId[i] << ": "<< mesh.Cell1DsExtrema(0,i)<< " " <<  mesh.Cell1DsExtrema(1,i) << endl;
	}
	
	for (unsigned int i=0; i < mesh.NumCell2Ds; i++){
		cout<<"Faccia "<<i<<": "<<endl;
		cout<<"Vertici: "<<mesh.Cell2DsVertices[i][0]<<" "<<mesh.Cell2DsVertices[i][1]<<" "<<mesh.Cell2DsVertices[i][2]<<" "<<endl;
		cout<<"Lati: "<<mesh.Cell2DsEdges[i][0]<<" "<<mesh.Cell2DsEdges[i][1]<<" "<<mesh.Cell2DsEdges[i][2]<<" "<<endl;
		cout<<endl;
	}
	
	
	cout<<"DUALE: "<<endl;
	cout<<endl;
	
	for (unsigned int i=0; i < duale.NumCell0Ds; i++){
		cout<<"Coordinate Vertice " << duale.Cell0DsId[i] << ": "<< duale.Cell0DsCoordinates(0,i)<<" "<< duale.Cell0DsCoordinates(1,i)<<" "<< duale.Cell0DsCoordinates(2,i)<<" "<<endl; 
	}
	
	cout<<endl;
	
	for (unsigned int i=0; i< duale.NumCell1Ds; i++){
		cout<<"Estremi Lato " << duale.Cell1DsId[i] << ": "<< duale.Cell1DsExtrema(0,i)<< " " <<  duale.Cell1DsExtrema(1,i) << endl;
	}
	
	for (unsigned int i=0; i < duale.NumCell2Ds; i++){
		cout<<"Faccia "<<i<<": "<<endl;
		cout<<"Vertici: "<<duale.Cell2DsVertices[i][0]<<" "<<duale.Cell2DsVertices[i][1]<<" "<<duale.Cell2DsVertices[i][2]<<" "<<endl;
		cout<<"Lati: "<<duale.Cell2DsEdges[i][0]<<" "<<duale.Cell2DsEdges[i][1]<<" "<<duale.Cell2DsEdges[i][2]<<" "<<endl;
		cout<<endl;
	}
	*/
	
	    Gedim::UCDUtilities utilities;
		{ 
		utilities.ExportPoints("./Cell0Ds.inp",
                               duale.Cell0DsCoordinates);
		}
		{
		utilities.ExportSegments("./Cell1Ds.inp",
                                 duale.Cell0DsCoordinates,
                                 duale.Cell1DsExtrema,
                                 {});
		}
	
	return 0;
}