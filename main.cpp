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
	
	bool contr = check_ed_vert(mesh);
	
	if (!contr){
		cout<<"Il controllo di lati e vertici non è andato a buon fine"<<endl;
	}
	
	vector<array<double,3>> vertici = triang_vert(mesh, 2);
	
	unsigned int count = 4;
	for (unsigned int i=0; i<vertici.size(); i++){
		cout<<"vertice "<<count<<":"<<endl;
		count++;
		for (unsigned int j=0; j<3; j++){
		cout<< vertici[i][j] << " ";
		}
		cout<<endl;
		cout<<endl;
	}
	return 0;
}