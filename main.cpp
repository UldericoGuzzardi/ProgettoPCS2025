#include <iostream>
#include <fstream>
#include <vector>
#include "Polygons.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main(int argc, char *argv[]){
	int p;
	int q;
	int b;
	int c;
	int id_vertice_1;
	int id_vertice_2;
	bool cammino;
	
	
	if (argc==5){
		p = atoi(argv[1]);
		q = atoi(argv[2]);
		b = atoi(argv[3]);
		c = atoi(argv[4]);
		cammino= false;
		
	} else if(argc==7){
		p = atoi(argv[1]);
		q = atoi(argv[2]);
		b = atoi(argv[3]);
		c = atoi(argv[4]);
		id_vertice_1 = atoi(argv[5]);
		id_vertice_2 = atoi(argv[6]);
		cammino= true;
		
	} else{
		cerr<< "Errore: devi inserire 4 o 6 numeri"<<endl;
		return 1;
	}
	
	
	PolygonalMesh mesh;
	PolygonalMesh duale;
	
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
	
	if (p<3 || q<3){
		cerr<<"Errore: Valori di p e q non validi"<<endl;
		
	}else if (p==3){
		
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
		if (!genera_poliedro(mesh, num_lati_iniziali,num_facce_iniziali)){
			cerr << "Errore nella generazione del poliedro"<<endl;
			return 1;
		}
	
		cout << "Poliedro generato correttamente"<<endl;
		
		if (cammino){
			//Calcolo del cammino minimo
			 if (!TrovaCamminoMinimo(mesh, id_vertice_1, id_vertice_2, num_lati_iniziali)){
				 
				 return 1;
			}
		}
		
		Esportazione_ParaView(mesh, cammino);
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
			cerr <<"Errore nel controllo di lati e vertici del poliedro"<<endl;
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
			
			if (!check_ed_vert(duale)){
				cerr<<"Errore nel controllo di lati e vertici del poliedro"<<endl;
			}
			
			ProiezioneSfera(duale);
			
			if (!genera_poliedro(mesh, 0,0)){
				cerr << "Errore nella generazione del poliedro"<<endl;
				return 1;
			}
			
			cout << "Poliedro generato correttamente"<<endl;
			
			
			if (cammino){
				
				//Calcolo del cammino minimo
				if (!TrovaCamminoMinimo(duale, id_vertice_1, id_vertice_2, 0)){
					
					 return 1;
				}
			}
			
			Esportazione_ParaView(duale, cammino);

		}
	}
	
	
	
	
	return 0;
}