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
	unsigned int q =3;
	unsigned int b=0;
	unsigned int c=2;
	
	unsigned int num_facce_iniziali;
	unsigned int num_lati_iniziali;
	
	if (b==c && b==0){
		cerr<<"Errore: Valori di b e c non validi"<<endl;
		return 1;
	} 
	if (b!=c && b!=0 && c!=0){
		cerr<<"Errore: Valori di b e c non validi"<<endl;
		return 1;
	}
	
	
	if (p==3){
		bool pol = costruzione_poliedro(q, mesh);
	
		if (!pol){
			cerr<<"Errore nella costruzione del poliedro"<<endl;
		}
		
		if (!check_ed_vert(mesh)){
		cerr<<"Errore nel controllo di lati e vertici del poliedro"<<endl;
		}
		
		if (b==1 && c==0){
			num_facce_iniziali =0;
			num_lati_iniziali=0;
			
		} else if (b==0 && c==1){
			num_facce_iniziali=0;
			num_lati_iniziali=0;
			
		} else{
			num_facce_iniziali = mesh.NumCell2Ds;
			num_lati_iniziali= mesh.NumCell1Ds;
			TriangolazionePoliedro(mesh,b,c);
			
		}
		ProiezioneSfera(mesh);
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
			cerr<<"Errore, poliedro non valido"<<endl;
			
			return 0;
			
		} else{
			bool pol = costruzione_poliedro(p, mesh);
	
			if (!pol){
				cerr<<"Errore nella costruzione del poliedro"<<endl;
			}
			
			if (!check_ed_vert(mesh)){
			cerr<<"Errore nel controllo di lati e vertici del poliedro"<<endl;
			}
			
			if (b==1){
				num_facce_iniziali =0;
				num_lati_iniziali=0;
			} else{
				num_facce_iniziali = mesh.NumCell2Ds;
				num_lati_iniziali= mesh.NumCell1Ds;
				TriangolazionePoliedro(mesh, b, c);
			
			}
			duale = costruzione_duale(mesh, num_facce_iniziali, num_lati_iniziali);
			ProiezioneSfera(duale);
			
			if (!check_ed_vert(duale)){
				cerr<<"Errore nel controllo di lati e vertici del poliedro"<<endl;
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
	
	//DA AGGIUNGERE: chiamata alla funzione TrovaCamminoMinimo
	
	return 0;
}