#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <utility>


namespace PolygonalLibrary
{

//Triangolazione seconda classe
//Come per la prima classe, la triangolazione avviene faccia per faccia, in base alla classe chiamerò la funzione TriangolaFaccia o TriangolaFaccia2
void AggiungiFaccia(PolygonalMesh& mesh, vector<unsigned int> faccia){
	mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
	mesh.Cell2DsVertices.push_back(faccia);
	mesh.Cell2DsNumVert.push_back(3);
	mesh.NumCell2Ds++;
}
void TriangolaFaccia_2(PolygonalMesh& mesh, Eigen::Vector3d v0, Eigen::Vector3d v1, Eigen::Vector3d v2, unsigned int b){
	
	unsigned int num_facce_iniziali= mesh.NumCell2Ds; //Serve alla fine per aggiungere i lati alle facce
	//I vertici vengono assegnati a tre "categorie" diverse:
	
	//1. vertici "normali", sono i vertici della triangolazione di classe 1, che vengono generati anche nella triangolazione di classe 2
	
	//2. I baricentri, ad ogni faccia che viene costruita nella triangolazione di classe 1 corrisponde un vertice nella triangolazione di classe 2, 
	//	 il vertice è proprio il baricentro
	
	//3. I vertici "intermedi", sono i vertici che vengono costruiti in mezzo ai vertici "normali" solo ed esclusivamente sui lati originali del poliedro
	
	
	
	//Vertici 1. La costruzione è la stessa della triangolazione 1
	if (b!=1){
		vector<vector<unsigned int>> strati_vertici;
		
		//Itero sui "piani" del triangolo, il primo verrà diviso in b segmenti, il secondo in b-1 ecc.
		for(unsigned int j=0; j<=b; j++){
			
			Eigen::Vector3d new_extreme_0 = v0 + (v2-v0)*(double)j/b; //estremo sinistro del j-esimo strato
			Eigen::Vector3d new_extreme_1 = v1 + (v2-v1)*(double)j/b; //estremo destro del j-esimo strato
			
			vector<unsigned int> strato;
			
			if (j==b){
				unsigned int new_id = EsisteVertice(mesh, new_extreme_0); //nel caso in cui j=b i due estremi coincidono con v2 
				strato.push_back(new_id);
				
			
			} else { //evito di dividere per 0 per il caso j=b  
				for (unsigned int i=0; i<=b-j; i++){
					Eigen::Vector3d new_vert= new_extreme_0 + (new_extreme_1-new_extreme_0)*(double)i/(b-j);
					unsigned int new_id = EsisteVertice(mesh, new_vert); //verifico se esiste quell'ID
					strato.push_back(new_id); //aggiungo l'ID del vertice appena creato
				}
			}
			
			//Aggiungo lo strato
			strati_vertici.push_back(strato); 
				
		}
		
		//Vertici 2. Per costruire i baricentri uso lo stesso codice che ho utilizzato nella triangolazione di classe 1 per fare le facce.
		//			 Al posto di aggiungere una faccia, però utilizzo la funzione calcolo_baricentro, per poi aggiungerlo alla mesh. 
		//			 Anche gli ID dei baricentri vengono salvati per strati.
		
		
		vector<vector<unsigned int>> strati_baricentri;
		
		for (unsigned int j=0; j<strati_vertici.size()-1; j++){
			
			vector<unsigned int> strato; //strato in cui salverò il baricentro
			
			for (unsigned int i=0; i<strati_vertici[j].size()-2; i++){
				//vertici dello strato inferiore
				unsigned int u0=strati_vertici[j][i];
				unsigned int u1=strati_vertici[j][i+1];
				
				//vertici dello strato superiorie
				unsigned int w0=strati_vertici[j+1][i];
				unsigned int w1=strati_vertici[j+1][i+1];
				
				vector<unsigned int> verts1={u0,u1,w0}; 
				Eigen::Vector3d baricentro_1 = calcolo_baricentro(mesh, verts1); //coordinate del baricentro
				unsigned int b1_id= EsisteVertice(mesh, baricentro_1); //aggiungo il baricentro alla mesh 
				strato.push_back(b1_id); //aggiungo l'ID allo strato
				
				vector<unsigned int> verts2={u1,w1,w0};
				Eigen::Vector3d baricentro_2 = calcolo_baricentro(mesh, verts2); 
				unsigned int b2_id= EsisteVertice(mesh, baricentro_2); 
				strato.push_back(b2_id); 			
			}
			
			//ultimo baricentro dello strato
			unsigned int z0 = strati_vertici[j][strati_vertici[j].size()-2];
			unsigned int z1 = strati_vertici[j][strati_vertici[j].size()-1];
			unsigned int z2 = strati_vertici[j+1][strati_vertici[j+1].size()-1];
			
			vector<unsigned int> verts={z0,z1,z2};
			
			Eigen::Vector3d baricentro = calcolo_baricentro(mesh, verts); //coordinate del baricentro
			unsigned int b_id = EsisteVertice(mesh, baricentro); //aggiungo il baricentro alla mesh 
			strato.push_back(b_id);
			
			//posso aggiungere lo strato 
			strati_baricentri.push_back(strato);	
		}
		
		//Vertici 3. Sono i vertici intermedi. Anche questi vengono salvati a strati. Il primo strato è formato dai vertici intermedi tra i vertici normali dello strato zero. 
		//			 All'interno degli altri strati vi sono sempre e solo due vertici, che si posizionano a metà tra gli estremi dei vertici "normali" di due strati consecutivi.
		
		vector<vector<unsigned int>> strati_intermedi;
		
		//Costruisco il primo strato
		vector<unsigned int> primo_strato;
		
		vector<unsigned int> base= strati_vertici[0]; //è il primo strato del vettore di vettori "strati_vertici"
		
		for (unsigned int i=0; i<base.size()-1; i++){
			Eigen::Vector3d v0=mesh.Cell0DsCoordinates.col(base[i]);
			Eigen::Vector3d v1=mesh.Cell0DsCoordinates.col(base[i+1]);
			Eigen::Vector3d v_int = 0.5*(v0 +v1);
			unsigned int id_int = EsisteVertice(mesh, v_int);
			primo_strato.push_back(id_int);
		}
		
		strati_intermedi.push_back(primo_strato);
		
		
		
		//Costruisco gli strati successivi. Questa volta non stiamo andando orizzontalmente ma verticalmente
		for (unsigned int i=0; i<strati_vertici.size()-1; i++){
			vector<unsigned int> strato;
			
			unsigned int dimensione = strati_vertici[i].size()-1; //serve per prendere l'ultimo vertice di ogni strato
			
			//Estremo sinistro
			Eigen::Vector3d v0= mesh.Cell0DsCoordinates.col(strati_vertici[i][0]);
			Eigen::Vector3d v1= mesh.Cell0DsCoordinates.col(strati_vertici[i+1][0]);
			Eigen::Vector3d v_int_1 = 0.5*(v0 + v1);
			unsigned int id_int_1 = EsisteVertice(mesh, v_int_1);
			strato.push_back(id_int_1);
		
			
			//Estremo destro
			Eigen::Vector3d v2 = mesh.Cell0DsCoordinates.col(strati_vertici[i][dimensione]);
			Eigen::Vector3d v3 = mesh.Cell0DsCoordinates.col(strati_vertici[i+1][dimensione-1]);
			Eigen::Vector3d v_int_2 = 0.5*(v2 + v3);
			unsigned int id_int_2 = EsisteVertice(mesh, v_int_2);
			strato.push_back(id_int_2);
			
			
			strati_intermedi.push_back(strato);
		}
		
		//Ho creato tutti i vertici, adesso creo direttamente le facce. Una volta individuati i vertici di ogni faccia, infatti, con la funzione EsisteLato 
		//aggiungo i lati alla mesh e li aggiungo alle facce automaticamente.
		
		
		//Per capire quali vertici formano una faccia, bisogna avere presente come sono distribuiti i vari vertici e come si legano tra loro.
		//Per costruire le facce itero sui baricentri, che divido in due categorie. 
		//I baricentri esterni, ovvero gli estremi di ogni strato, e quelli interni. Questi seguono una procedura standard, ad eccezione dei baricentri del primo strato e del
		//baricentro finale
		//I baricentri interni, che invece hanno un comportamento diverso in base alla posizione che occupano, se pari o dispari. Nel caso in cui il baricentro ha posizione pari 
		//c'è un'ulteriore eccezione nel caso in cui ci troviamo nel primo strato. 
		
		//Itero sui baricentri, il primo e l'ultimo strato li faccio a parte
		//Primo strato.
		
		//Baricentro esterno sinistro:
		vector<unsigned int> vert1= {strati_baricentri[0][0], strati_vertici[0][0], strati_intermedi[0][0]};
		AggiungiFaccia(mesh,vert1);
				
		vector<unsigned int> vert2= {strati_baricentri[0][0], strati_vertici[0][0], strati_intermedi[1][0]};
		AggiungiFaccia(mesh,vert2);
						
		vector<unsigned int> vert3= {strati_baricentri[0][0], strati_vertici[0][1], strati_intermedi[0][0]};
		AggiungiFaccia(mesh,vert3);
						
		vector<unsigned int> vert4= {strati_baricentri[0][0], strati_vertici[1][0], strati_intermedi[1][0]};
		AggiungiFaccia(mesh,vert4);

		vector<unsigned int> vert5= {strati_baricentri[0][0], strati_vertici[1][0], strati_baricentri[0][1]};
		AggiungiFaccia(mesh,vert5);
						
		vector<unsigned int> vert6= {strati_baricentri[0][0], strati_vertici[0][1], strati_baricentri[0][1]};
		AggiungiFaccia(mesh,vert6);
		
		unsigned int count_p=0; //Numero di baricentri interni con posizione pari. Serve per la costruzione delle facce
		unsigned int count_d=0; //Numero di baricentri interni con posizione pari. Serve per la costruzione delle facce
		
		for (unsigned int j=1; j<strati_baricentri[0].size()-1; j++){
			if (j%2==0){
				
				count_p++;
				
				vector<unsigned int> v1 = {strati_baricentri[0][j], strati_vertici[0][j-count_p], strati_intermedi[0][j-count_p]};
				AggiungiFaccia(mesh,v1);
				
				vector<unsigned int> v2 = {strati_baricentri[0][j], strati_vertici[0][j-count_p+1], strati_intermedi[0][j-count_p]};
				AggiungiFaccia(mesh,v2);
					
				vector<unsigned int> v3 = {strati_baricentri[0][j], strati_vertici[0][j-count_p+1], strati_baricentri[0][j+1]};
				AggiungiFaccia(mesh,v3);
					
				vector<unsigned int> v4 = {strati_baricentri[0][j], strati_vertici[1][j-count_p], strati_baricentri[0][j+1]};
				AggiungiFaccia(mesh,v4);
					
					
			} else{
				
				count_d++;
				vector<unsigned int> v1 = {strati_baricentri[0][j], strati_vertici[1][j-count_d], strati_baricentri[1][j-1]};
				AggiungiFaccia(mesh,v1);
					
				vector<unsigned int> v2 = {strati_baricentri[0][j], strati_vertici[1][j-count_d+1], strati_baricentri[1][j-1]};
				AggiungiFaccia(mesh,v2);
					
				vector<unsigned int> v3 = {strati_baricentri[0][j], strati_vertici[0][j-count_d+1], strati_baricentri[0][j+1]};
				AggiungiFaccia(mesh,v3);
					
				vector<unsigned int> v4 = {strati_baricentri[0][j], strati_vertici[1][j-count_d+1], strati_baricentri[0][j+1]};
				AggiungiFaccia(mesh,v4);
				}
				
				
						
			}
			
		//Baricentro esterno destro:
		unsigned int dim_baseb = strati_baricentri[0].size()-1;
		unsigned int dim_basev = strati_vertici[0].size()-1;
		unsigned int dim_basei = strati_intermedi[0].size()-1;
		
		vector<unsigned int> vert7= {strati_baricentri[0][dim_baseb], strati_vertici[0][dim_basev], strati_intermedi[0][dim_basei]};
		AggiungiFaccia(mesh,vert7);
				
		vector<unsigned int> vert8= {strati_baricentri[0][dim_baseb], strati_vertici[0][dim_basev], strati_intermedi[1][1]};
		AggiungiFaccia(mesh,vert8);
						
		vector<unsigned int> vert9= {strati_baricentri[0][dim_baseb], strati_vertici[0][dim_basev-1], strati_intermedi[0][dim_basei]};
		AggiungiFaccia(mesh,vert9);
						
		vector<unsigned int> vert10= {strati_baricentri[0][dim_baseb], strati_vertici[1][dim_basev-1], strati_intermedi[1][1]};
		AggiungiFaccia(mesh,vert10);
		
		
		//Costruisco le facce per gli altri strati
		unsigned int num_strati= strati_baricentri.size();
		for (unsigned int i=1; i <num_strati; i++){
			
			unsigned int count_pa=0; //Numero di baricentri interni con posizione pari. Serve per la costruzione delle facce
			unsigned int count_di=0; //Numero di baricentri interni con posizione pari. Serve per la costruzione delle facce
			unsigned int dim_b=strati_baricentri[i].size()-1;
			unsigned int dim_v=strati_vertici[i].size()-1;
			
			if (i==num_strati-1){
				vector<unsigned int> v1= {strati_baricentri[i][0], strati_vertici[i][0], strati_intermedi[i+1][0]};
				AggiungiFaccia(mesh,v1);
								
				vector<unsigned int> v2= {strati_baricentri[i][0], strati_vertici[i+1][0], strati_intermedi[i+1][0]};
				AggiungiFaccia(mesh,v2);

				vector<unsigned int> v3= {strati_baricentri[i][0], strati_vertici[i][1], strati_intermedi[i+1][1]};
				AggiungiFaccia(mesh,v3);
										
				vector<unsigned int> v4= {strati_baricentri[i][0], strati_vertici[i+1][0], strati_intermedi[i+1][1]};
				AggiungiFaccia(mesh,v4);
				
			} else {
				for (unsigned int j=0; j<=dim_b;j++){
					if (j==0){
						vector<unsigned int> v1= {strati_baricentri[i][0], strati_vertici[i][0], strati_intermedi[i+1][0]};
						AggiungiFaccia(mesh,v1);
								
						vector<unsigned int> v2= {strati_baricentri[i][0], strati_vertici[i+1][0], strati_intermedi[i+1][0]};
						AggiungiFaccia(mesh,v2);

						vector<unsigned int> v3= {strati_baricentri[i][0], strati_vertici[i+1][0], strati_baricentri[i][1]};
						AggiungiFaccia(mesh,v3);
										
						vector<unsigned int> v4= {strati_baricentri[i][0], strati_vertici[i][1], strati_baricentri[i][1]};
						AggiungiFaccia(mesh,v4);
										
					} else if (j==dim_b){
						vector<unsigned int> v1= {strati_baricentri[i][dim_b], strati_vertici[i][dim_v], strati_intermedi[i+1][1]};
						AggiungiFaccia(mesh,v1);
								
						vector<unsigned int> v2= {strati_baricentri[i][dim_b], strati_vertici[i+1][dim_v-1], strati_intermedi[i+1][1]};
						AggiungiFaccia(mesh,v2);
						
					} else{
						if (j%2==0){
				
							count_pa++;
								
							vector<unsigned int> v1 = {strati_baricentri[i][j], strati_vertici[i][j-count_pa+1], strati_baricentri[i][j+1]};
							AggiungiFaccia(mesh,v1);
								
							vector<unsigned int> v2 = {strati_baricentri[i][j], strati_vertici[i+1][j-count_pa], strati_baricentri[i][j+1]};
							AggiungiFaccia(mesh,v2);
					
					
						} else{
				
							count_di++;
							vector<unsigned int> v1 = {strati_baricentri[i][j], strati_vertici[i+1][j-count_di], strati_baricentri[i+1][j-1]};
							AggiungiFaccia(mesh,v1);
								
							vector<unsigned int> v2 = {strati_baricentri[i][j], strati_vertici[i+1][j-count_di+1], strati_baricentri[i+1][j-1]};
							AggiungiFaccia(mesh,v2);
								
							vector<unsigned int> v3 = {strati_baricentri[i][j], strati_vertici[i][j-count_di+1], strati_baricentri[i][j+1]};
							AggiungiFaccia(mesh,v3);
								
							vector<unsigned int> v4 = {strati_baricentri[i][j], strati_vertici[i+1][j-count_di+1], strati_baricentri[i][j+1]};
							AggiungiFaccia(mesh,v4);
						}
						
					}
				}
			}
		}
		
		
			
	}else{//il caso in cui b e c sono uguali a uno lo gestisco diversamente e in modo più semplice
		unsigned int vert0 = EsisteVertice(mesh,v0);
		unsigned int vert1 = EsisteVertice(mesh,v1);
		unsigned int vert2 = EsisteVertice(mesh,v2);
		
		vector<unsigned int> verts = {vert0,vert1,vert2};
		Eigen::Vector3d baricentro = calcolo_baricentro(mesh, verts); //coordinate del baricentro
		unsigned int b_id = EsisteVertice(mesh, baricentro); //aggiungo il baricentro alla mesh 
		
		Eigen::Vector3d  u0 = 0.5*(v0+v1); //coordinate dei vertici intermedi per ogni lato
		unsigned int u0_id = EsisteVertice(mesh, u0); //aggiungo alla mesh 
		
		Eigen::Vector3d  u1 = 0.5*(v2+v1); 
		unsigned int u1_id = EsisteVertice(mesh, u1); 
		
		Eigen::Vector3d  u2 = 0.5*(v0+v2); 
		unsigned int u2_id = EsisteVertice(mesh, u2); 
		
		//Costruisco manualmente le nuove facce
		vector<unsigned int> faccia1={vert0, u0_id, b_id};
		AggiungiFaccia(mesh,faccia1);
		
		vector<unsigned int> faccia2={vert0, u2_id, b_id};
		AggiungiFaccia(mesh,faccia2);
		vector<unsigned int> faccia3={vert1, u0_id, b_id};
		AggiungiFaccia(mesh,faccia3);
		
		vector<unsigned int> faccia4={vert1, u1_id, b_id};
		AggiungiFaccia(mesh,faccia4);
		
		vector<unsigned int> faccia5={vert2, u2_id, b_id};
		AggiungiFaccia(mesh,faccia5);
		
		vector<unsigned int> faccia6={vert2, u1_id, b_id};
		AggiungiFaccia(mesh,faccia6);
		
		
		
	}
	
	//Aggiungo tutti i lati
	for (unsigned int i=num_facce_iniziali; i<mesh.NumCell2Ds; i++){
			vector<unsigned int> v = mesh.Cell2DsVertices[i];
			unsigned int v0= v[0];
			unsigned int v1= v[1];
			unsigned int v2= v[2];
			Eigen::Vector2i ed1={v0, v1};
			Eigen::Vector2i ed2={v1, v2};
			Eigen::Vector2i ed3={v0, v2};
			vector<unsigned int> edges={EsisteLato(mesh, ed1), EsisteLato(mesh, ed2), EsisteLato(mesh,ed3)};
			mesh.Cell2DsEdges.push_back(edges);
			mesh.Cell2DsNumEdg.push_back(3);		
			
		}

}
}