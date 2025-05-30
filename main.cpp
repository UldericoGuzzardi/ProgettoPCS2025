#include <iostream>
#include "Polygons.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main(){
	
	//int argc, char *argv[]
	
	/*if(argc == 1)
		cout << "primo: " << argv[0] << endl;
	
	//unsigned int p;
	if(argc == 5)
	{
		cout << "cinque: " << argv[0]  << " " << argv[1]  << " " << argv[2]  << " " << argv[4]  << " "  << endl;
		//istringstream convert(argv[1]);
		//convert >> p;
		//p = argv[1]
	}*/
	
	
	PolygonalMesh mesh;
	PolygonalMesh duale;
	
	unsigned int p=3;
	unsigned int q =5;
	unsigned int b=3;
	//unsigned int c=0;
	
	unsigned int num_facce_iniziali;
	unsigned int num_lati_iniziali;
	
	if (p==3){
		bool pol = costruzione_poliedro(q, mesh);
	
		if (!pol){
			cout<<"Errore nella costruzione del poliedro"<<endl;
		}
		
		if (!check_ed_vert(mesh)){
		cout<<"Errore nel controllo di lati e vertici del poliedro"<<endl;
		}
		
		if (b==1){
			num_facce_iniziali =0;
			num_lati_iniziali=0;
		} else{
			num_facce_iniziali = mesh.NumCell2Ds;
			num_lati_iniziali= mesh.NumCell1Ds;
			TriangolazionePoliedro(mesh, b);
			ProiezioneSfera(mesh);
		}
		Gedim::UCDUtilities utilities;
		{ 
		utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates);
		}
		{
		utilities.ExportSegments("./Cell1Ds.inp",
                                 mesh.Cell0DsCoordinates,
                                 mesh.Cell1DsExtrema,
                                 {});
		}
		
		return 0;
		
		
	} else {
		if (q!=3){
			cout<<"Errore, poliedro non valido"<<endl;
			
			return 0;
			
		} else{
			bool pol = costruzione_poliedro(p, mesh);
	
			if (!pol){
				cout<<"Errore nella costruzione del poliedro"<<endl;
			}
			
			if (!check_ed_vert(mesh)){
			cout<<"Errore nel controllo di lati e vertici del poliedro"<<endl;
			}
			
			if (b==1){
				num_facce_iniziali =0;
				num_lati_iniziali=0;
			} else{
				num_facce_iniziali = mesh.NumCell2Ds;
				num_lati_iniziali= mesh.NumCell1Ds;
				TriangolazionePoliedro(mesh, b);
			
			}
			duale = costruzione_duale(mesh, num_facce_iniziali, num_lati_iniziali);
			ProiezioneSfera(duale);
			
			if (!check_ed_vert(duale)){
				cout<<"Errore nel controllo di lati e vertici del poliedro"<<endl;
			}
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
		}
	}
	
	
	
	
	
	
	
	
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