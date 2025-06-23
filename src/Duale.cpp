#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <utility>


namespace PolygonalLibrary


{

//Calcolo del baricentro di una faccia
Eigen::Vector3d calcolo_baricentro(const PolygonalMesh& mesh, vector<unsigned int> verts){
	
	Eigen::Vector3d v0= {mesh.Cell0DsCoordinates(0,verts[0]),mesh.Cell0DsCoordinates(1,verts[0]),mesh.Cell0DsCoordinates(2,verts[0])};
	Eigen::Vector3d v1= {mesh.Cell0DsCoordinates(0,verts[1]),mesh.Cell0DsCoordinates(1,verts[1]),mesh.Cell0DsCoordinates(2,verts[1])};
	Eigen::Vector3d v2= {mesh.Cell0DsCoordinates(0,verts[2]),mesh.Cell0DsCoordinates(1,verts[2]),mesh.Cell0DsCoordinates(2,verts[2])};
	
	Eigen::Vector3d baricentro = (v0 + v1 + v2)/3.0;
	
	return baricentro;
}


//Funzione che controlla se un vertice sta in una faccia
bool VerticeInFaccia(vector<unsigned int> faccia, unsigned int vertice){
	for (unsigned int i=0; i<faccia.size();i++){
		if(faccia[i]==vertice)
			return true;
	}
	return false;
}

// Duale triangolare di un poliedro con facce triangolari
PolygonalMesh costruzione_duale(const PolygonalMesh& mesh, unsigned int num_facce_iniziali, unsigned int num_lati_iniziali){
	PolygonalMesh duale;
	
	//1. Calcolo dei baricentri
	duale.NumCell0Ds = mesh.NumCell2Ds - num_facce_iniziali;
	duale.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, duale.NumCell0Ds);
	
	//Inserimento dei vertici nel duale
	for (unsigned int i=0; i<duale.NumCell0Ds; i++){ 
		duale.Cell0DsId.push_back(i);
		Eigen::Vector3d baricentro = calcolo_baricentro(mesh, mesh.Cell2DsVertices[num_facce_iniziali+i]);
		duale.Cell0DsCoordinates.col(i)=baricentro;
	}
	
	//2. Costruzione dei lati
	duale.NumCell1Ds=mesh.NumCell1Ds - num_lati_iniziali; //Il numero di lati del duale è uguale al numero di lati del poliedro
	duale.Cell1DsExtrema = Eigen::MatrixXi(2, duale.NumCell1Ds);
	
	//tolgo il numero di lati iniziali perché i lati del poliedro prima della triangolazione non sono più lati
	
	//Creo una mappa che associa ad ogni lato gli ID della coppia di facce che condividono quel lato (tutto riguardo alla mesh originale)
	map<vector<unsigned int>, vector<unsigned int>> lati_facce;
	for (unsigned int i = num_facce_iniziali; i< mesh.NumCell2Ds; i++){
		vector<unsigned int> vertici = mesh.Cell2DsVertices[i];
		for (unsigned int j=0; j<3; j++){
			unsigned int v1 = vertici[j];
			unsigned int v2 = vertici[(j+1)%3];
			vector<unsigned int> lato = {min(v1,v2), max(v1,v2)};
			lati_facce[lato].push_back(i-num_facce_iniziali); //le facce partono da num_facce_iniziali, voglio salvarle partendo da 0
		}
	}
	
	//Aggiungo i lati al duale
	unsigned int id_lato=0;
	
	for (auto& [lato, facce] : lati_facce){ //Prende ogni elemento della mappa come [chiave, valore], la chiave viene messa in lato e il valore in facce
											//Ricorda che ogni lato appartiene a due facce
									
		//Salvo gli ID delle facce per poi usarli come estremi del lato. Gli ID sono già ordinati in ordine crescente
		
		unsigned int v1 = facce[0]; 
        unsigned int v2 = facce[1];
		duale.Cell1DsId.push_back(id_lato);
        duale.Cell1DsExtrema(0,id_lato)=v1;
		duale.Cell1DsExtrema(1,id_lato)=v2;
		id_lato++;
	}
	
	
	//3. Costruzione delle facce 
	duale.NumCell2Ds=mesh.NumCell0Ds; //Il numero di facce del duale è uguale al numero di vertici del poliedro originale
	
	
	//Crea una mappa che a ogni vertice originale del poliedro (chiave) associa gli ID delle facce a cui quel vertice appartiene (valori)
	map<unsigned int, vector<unsigned int>> vertici_facce; //mappa che dice tutte le facce dell’originale che hanno come vertice il punto v.
	
    //Usando questa lista, si ordinano i baricentri di quelle facce e si costruisce la faccia corrispondente del duale
	for (unsigned int i= num_facce_iniziali; i < mesh.NumCell2Ds; i++){ //Per ogni faccia
		vector<unsigned int> verts=mesh.Cell2DsVertices[i]; //Prendo i vertici della faccia
		
		for (unsigned int j=0; j<verts.size(); j++){ //Per ogni vertice nella faccia i
		
			//Nella mappa aggiungo alla chiave corrispondente all'ID del vertice la faccia i che lo contiene
			unsigned int vert= verts[j];
			vertici_facce[vert].push_back(i-num_facce_iniziali); 
			
		}
	}
	
	// Costruzione facce duali per ogni vertice originale
	for (unsigned int i = 0; i < mesh.NumCell0Ds; i++) {
		vector<unsigned int> facce = vertici_facce[i]; //prendo la lista di facce che hanno i come vertice
		//if (facce.size() < 3) continue; // Non formano una faccia chiusa

		// Costruisco una mappa che ad ogni faccia triangolare del poliedro associa le facce adiacenti ad essa lungo un lato che contiene il vertice i
		map<unsigned int, vector<unsigned int>> adiacenti;
		
		//Ogni faccia del poliedro adesso è un vertice del duale, grazie al baricentro
		//Prendo tutte le facce che contengono il vertice i
		for (unsigned int f = num_facce_iniziali; f < mesh.NumCell2Ds; f++) {//f è l'ID della faccia del poliedro, che riscalato mi darà l'ID del vertice del duale
			vector<unsigned int> verts = mesh.Cell2DsVertices[f];

			// Se la faccia f contiene il vertice i 
			if (VerticeInFaccia(verts,i)) {
				
				// Prendo due vertici all'interno della faccia triangolare, uno dei due deve essere il vertice i
				for (int j = 0; j < 3; j++) {
					unsigned int v1 = verts[j];
					unsigned int v2 = verts[(j+1)%3];

					if (v1 != i && v2 != i) continue; // deve contenere il vertice i

					vector<unsigned int> lato = {min(v1, v2), max(v1, v2)}; //riscrivo il lato che contiene il vertice i e un altro vertice
					vector<unsigned int> facce_adiacenti = lati_facce[lato]; //prendo le facce adiacenti che hanno quel lato
					
					//ciclo sulle due facce adiacenti al lato
					for (unsigned int k=0; k< facce_adiacenti.size(); k++) { 
						//itero sulle due facce adiacenti e 
						
						//controllo che la faccia da aggiungere non sia la f che sto già considerando, e controllo che abbia i come vertice
						if ((facce_adiacenti[k] != f - num_facce_iniziali) && VerticeInFaccia(facce,facce_adiacenti[k])) {
							
							//se la condizione si verifica, aggiungo la faccia alle facce adiacenti ad f tramite un lato che contiene i
							adiacenti[f - num_facce_iniziali].push_back(facce_adiacenti[k]);
						}
					}
				}
			}
		}
		//adiacenti contiene al massimo due elementi per faccia, e non sono ordinati in nessun modo, questa mappa però serve per ordinare i baricentri 
		
		
		//Adesso ho una mappa che ad ogni baricentro associa le facce adiacenti che lo contengono
		vector<unsigned int> baricentri_ordinati; //riordino i baricentri
		vector<unsigned int> baricentri_visitati; //salvo i baricentri visitati

		unsigned int centro = facce[0]; //inizio dal primo baricentro, prendendo la prima faccia associata al vertice i nel poliedro originale
		//in generale, centro ha il ruolo di "ultimo baricentro inserito nella lista dei vertici"
		baricentri_ordinati.push_back(centro); 
		baricentri_visitati.push_back(centro);

		while (baricentri_ordinati.size() < facce.size()) {//non mi fermo finché non ho aggiunto tutti i baricentri
		
			for (unsigned int j=0; j< adiacenti[centro].size();j++) { //per il baricentro fissato, prendo le facce adiacenti che adesso sono i vertici vicini
			
				if (!VerticeInFaccia(baricentri_visitati, adiacenti[centro][j])) { // controllo se il vertice vicino è già stato visitato 
				//(uso la funzione VerticeInFaccia che si adatta bene)
				
					//se non l'ho già visitato, lo aggiungo, e al prossimo ciclo vedrò i vertici vicini al "nuovo centro"
					baricentri_ordinati.push_back(adiacenti[centro][j]);
					baricentri_visitati.push_back(adiacenti[centro][j]);
					centro = adiacenti[centro][j];
					break;
				}
			}
		}
		
		//Aggiungo l'ID della faccia
		duale.Cell2DsId.push_back(i);
		
		//Aggiungo i vertici della faccia, i baricentri ordinati
		duale.Cell2DsVertices.push_back(baricentri_ordinati);
		
		//Aggiorno la dimensione dell'i-esima faccia
		duale.Cell2DsNumVert.push_back(baricentri_ordinati.size());
		
		
		//Una volta che ho costruito i vertici in modo ordinato, uso la funzione EsisteLato per ogni coppia di vertici consecutivi
		//Questa funzione mi permette di salvare automaticamente i lati in modo ordinato 
		vector<unsigned int> lati_duale;
		for (unsigned int j = 0; j < baricentri_ordinati.size(); j++) {
			unsigned int v0 = baricentri_ordinati[j];
			unsigned int v1 = baricentri_ordinati[(j + 1) % baricentri_ordinati.size()];
			Eigen::Vector2i lato(v0, v1);
			unsigned int id_lato = EsisteLato(duale, lato);
			lati_duale.push_back(id_lato);
		}
		duale.Cell2DsEdges.push_back(lati_duale);
		duale.Cell2DsNumEdg.push_back(lati_duale.size());

	}
		
	duale.Cell3DsId=0;
	
	duale.Cell3DsNumVert = duale.NumCell0Ds;
	duale.Cell3DsNumEdg = duale.NumCell1Ds;
	duale.Cell3DsNumFaces = duale.NumCell2Ds;
		
	duale.Cell3DsVertices = duale.Cell0DsId; 
	duale.Cell3DsEdges = duale.Cell1DsId;
	duale.Cell3DsFaces = duale.Cell2DsId;
	
	return duale;
}
}