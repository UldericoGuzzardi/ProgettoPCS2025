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
	
	
	
	return 0;
}