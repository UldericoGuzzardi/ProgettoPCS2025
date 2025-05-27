#include <iostream>
#include "Polygons.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main(){
	
	PolygonalMesh mesh;
	int q = 3;
	bool pol = costruzione_poliedro(q, mesh);
	
	if (!pol){
		cout<<"Errore nella costruzione del poliedro"<<endl;
	}
	
	if (!check_ed_vert(mesh)){
		cout<<"Il controllo di lati e vertici non è andato a buon fine"<<endl;
	}
	
	TriangolazionePoliedro(mesh, 2);
	
	/*for (unsigned int i=0; i < mesh.NumCell0Ds; i++){
		cout<<"Coordinate Vertice " << mesh.Cell0DsId[i] << ": "<< mesh.Cell0DsCoordinates(0,i)<<" "<<mesh.Cell0DsCoordinates(1,i)<<" "<<mesh.Cell0DsCoordinates(2,i)<<" "<<endl; 
	}
	
	cout<<endl;
	
	for (unsigned int i=0; i< mesh.NumCell1Ds; i++){
		cout<<"Estremi Lato " << mesh.Cell1DsId[i] << ": "<< mesh.Cell1DsExtrema(0,i)<< " " <<  mesh.Cell1DsExtrema(1,i) << endl;
	}*/
	
	return 0;
}