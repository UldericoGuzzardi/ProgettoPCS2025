#include <iostream>
#include "Polygons.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main(){
	
	PolygonalMesh mesh;
	int q = 5;
	bool a = costruzione_poliedro(q, mesh);
	
	if (!a){
		cout<<"suca"<<endl;
	}
	
	bool b = check_ed_vert(mesh);
	
	if (!b){
		cout<<"fallisce controllo"<<endl;
	}
		
	
	
	return 0;
}