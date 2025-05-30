#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <limits>
#include "Eigen/Eigen"


namespace PolygonalLibrary
{
	
	
	
	
// TODO controllo su p
bool costruzione_poliedro(int q, PolygonalMesh& mesh){
	
	if (q==3){
		//Cell0Ds
		mesh.NumCell0Ds=4;
		mesh.Cell0DsId = {0,1,2,3}; 
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		mesh.Cell0DsCoordinates.col(0) << 1.0/sqrt(3), 1.0/sqrt(3), 1.0/sqrt(3);
		mesh.Cell0DsCoordinates.col(1) << -1.0/sqrt(3), -1.0/sqrt(3), 1.0/sqrt(3);
		mesh.Cell0DsCoordinates.col(2) << -1.0/sqrt(3), 1.0/sqrt(3), -1.0/sqrt(3);
		mesh.Cell0DsCoordinates.col(3) << 1.0/sqrt(3), -1.0/sqrt(3), -1.0/sqrt(3);

		//Cell1Ds
		mesh.NumCell1Ds=6;
		mesh.Cell1DsId = {0,1,2,3,4,5}; 
		
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 1 ;
		mesh.Cell1DsExtrema.col(1) << 0, 2 ;
		mesh.Cell1DsExtrema.col(2) << 0, 3 ;
		mesh.Cell1DsExtrema.col(3) << 1, 2 ;
		mesh.Cell1DsExtrema.col(4) << 1, 3 ;
		mesh.Cell1DsExtrema.col(5) << 2, 3 ;
		
		//Cell2Ds
		mesh.NumCell2Ds = 4;
		mesh.Cell2DsId = {0, 1 ,2, 3};
		mesh.Cell2DsNumVert = {3, 3, 3, 3};
		mesh.Cell2DsNumEdg = {3, 3, 3, 3};
		
		
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds); 
		
		vector<unsigned int> v1 = {0,1,2};
		vector<unsigned int> v2 = {1,2,3};
		vector<unsigned int> v3 = {0,2,3};
		vector<unsigned int> v4 = {0,1,3};
		
		mesh.Cell2DsVertices= {v1, v2, v3, v4};
		
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,3,1};
		vector<unsigned int> e2 = {3,5,4};
		vector<unsigned int> e3 = {1,5,2};
		vector<unsigned int> e4 = {0,4,2};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4};
		
		//Cell3Ds
		mesh.Cell3DsId=0; 
		
		mesh.Cell3DsNumVert = mesh.NumCell0Ds;
		mesh.Cell3DsNumEdg = mesh.NumCell1Ds;
		mesh.Cell3DsNumFaces = mesh.NumCell2Ds;
		
		mesh.Cell3DsVertices = mesh.Cell0DsId; 
		mesh.Cell3DsEdges = mesh.Cell1DsId;
		mesh.Cell3DsFaces = mesh.Cell2DsId;
		
		
		}

	else if (q==4){
		//Cell0Ds
		mesh.NumCell0Ds=6;
		mesh.Cell0DsId = {0,1,2,3,4,5}; 
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		
		mesh.Cell0DsCoordinates.col(0) << 1.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(1) << -1.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(2) << 0.0, 0.0, 1.0;
		mesh.Cell0DsCoordinates.col(3) << 0.0, 0.0, -1.0;
		mesh.Cell0DsCoordinates.col(4) << 0.0, 1.0, 0.0;
		mesh.Cell0DsCoordinates.col(5) << 0.0, -1.0, 0.0;
		
		
		//Cell1Ds
		mesh.NumCell1Ds=12;
		mesh.Cell1DsId = {0,1,2,3,4,5,6,7,8,9,10,11};
		
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 2;
		mesh.Cell1DsExtrema.col(1) << 0, 3;
		mesh.Cell1DsExtrema.col(2) << 0, 4;
		mesh.Cell1DsExtrema.col(3) << 0, 5;
		mesh.Cell1DsExtrema.col(4) << 1, 2;
		mesh.Cell1DsExtrema.col(5) << 1, 3;
		mesh.Cell1DsExtrema.col(6) << 1, 4;
		mesh.Cell1DsExtrema.col(7) << 1, 5;
		mesh.Cell1DsExtrema.col(8) << 2, 4;
		mesh.Cell1DsExtrema.col(9) << 2, 5;
		mesh.Cell1DsExtrema.col(10) << 3, 4;
		mesh.Cell1DsExtrema.col(11) << 3, 5;
		
		//Cell2Ds
		mesh.NumCell2Ds = 8;
		mesh.Cell2DsId = {0, 1 ,2, 3, 4, 5, 6, 7};
		mesh.Cell2DsNumVert = {3, 3, 3, 3, 3, 3, 3, 3};
		mesh.Cell2DsNumEdg = {3, 3, 3, 3, 3, 3, 3, 3};
		
		
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> v1 = {0,2,4};
		vector<unsigned int> v2 = {1,2,4};
		vector<unsigned int> v3 = {1,2,5};
		vector<unsigned int> v4 = {0,2,5};
		vector<unsigned int> v5 = {0,3,5};
		vector<unsigned int> v6 = {1,3,5};
		vector<unsigned int> v7 = {1,3,4};
		vector<unsigned int> v8 = {0,3,4};

		
		mesh.Cell2DsVertices= {v1, v2, v3, v4, v5, v6, v7, v8};
		
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,8,2};
		vector<unsigned int> e2 = {4,8,6};
		vector<unsigned int> e3 = {4,9,7};
		vector<unsigned int> e4 = {0,9,3};
		vector<unsigned int> e5 = {1,11,3};
		vector<unsigned int> e6 = {5,11,7};
		vector<unsigned int> e7 = {5,10,6};
		vector<unsigned int> e8 = {1,10,2};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8};
		
		//Cell3D
		mesh.Cell3DsId=0; 
		
		mesh.Cell3DsNumVert = mesh.NumCell0Ds;
		mesh.Cell3DsNumEdg = mesh.NumCell1Ds;
		mesh.Cell3DsNumFaces = mesh.NumCell2Ds;
		
		mesh.Cell3DsVertices = mesh.Cell0DsId; 
		mesh.Cell3DsEdges = mesh.Cell1DsId;
		mesh.Cell3DsFaces = mesh.Cell2DsId;
		}
		
		
		
	else if (q==5){
		//Cell0Ds
		mesh.NumCell0Ds=12;
		mesh.Cell0DsId = {0,1,2,3,4,5,6,7,8,9,10,11}; 
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		double phi = (1+sqrt(5))/2;
		double X = 1/(sqrt(1+pow(phi,2)));
		double Y = phi/(sqrt(1+pow(phi,2)));
		
		mesh.Cell0DsCoordinates.col(0) << -X, Y, 0.0;
		mesh.Cell0DsCoordinates.col(1) << X, -Y, 0.0;
		mesh.Cell0DsCoordinates.col(2) << X, Y, 0.0;
		mesh.Cell0DsCoordinates.col(3) << -X, -Y, 0.0;
		mesh.Cell0DsCoordinates.col(4) << 0.0, X, Y;
		mesh.Cell0DsCoordinates.col(5) << 0.0, -X, -Y;
		mesh.Cell0DsCoordinates.col(6) << 0.0, -X, Y;
		mesh.Cell0DsCoordinates.col(7) << 0.0, X, -Y;
		mesh.Cell0DsCoordinates.col(8) << -Y, 0.0, X;
		mesh.Cell0DsCoordinates.col(9) << -Y, 0.0, -X;
		mesh.Cell0DsCoordinates.col(10) << Y, 0.0, X;
		mesh.Cell0DsCoordinates.col(11) << Y, 0.0, -X;

		
		//Cell1Ds
		mesh.NumCell1Ds=30;
		mesh.Cell1DsId = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29}; // è efficiente? reserve? Vanno ordinati?
		
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 2;
		mesh.Cell1DsExtrema.col(1) << 0, 4;
		mesh.Cell1DsExtrema.col(2) << 0, 7;
		mesh.Cell1DsExtrema.col(3) << 0, 8;
		mesh.Cell1DsExtrema.col(4) << 0, 9;
		mesh.Cell1DsExtrema.col(5) << 1, 3;
		mesh.Cell1DsExtrema.col(6) << 1, 6;
		mesh.Cell1DsExtrema.col(7) << 1, 5;
		mesh.Cell1DsExtrema.col(8) << 1, 10;
		mesh.Cell1DsExtrema.col(9) << 1, 11;
		mesh.Cell1DsExtrema.col(10) << 2, 4;
		mesh.Cell1DsExtrema.col(11) << 2, 7;
		mesh.Cell1DsExtrema.col(12) << 2, 11;
		mesh.Cell1DsExtrema.col(13) << 2, 10;
		mesh.Cell1DsExtrema.col(14) << 3, 5;
		mesh.Cell1DsExtrema.col(15) << 3, 9;
		mesh.Cell1DsExtrema.col(16) << 3, 8;
		mesh.Cell1DsExtrema.col(17) << 3, 6;
		mesh.Cell1DsExtrema.col(18) << 4, 10;
		mesh.Cell1DsExtrema.col(19) << 4, 6;
		mesh.Cell1DsExtrema.col(20) << 4, 8;
		mesh.Cell1DsExtrema.col(21) << 5, 11;
		mesh.Cell1DsExtrema.col(22) << 5, 7;
		mesh.Cell1DsExtrema.col(23) << 5, 9;
		mesh.Cell1DsExtrema.col(24) << 6, 8;
		mesh.Cell1DsExtrema.col(25) << 6, 10;
		mesh.Cell1DsExtrema.col(26) << 7, 9;
		mesh.Cell1DsExtrema.col(27) << 7, 11;
		mesh.Cell1DsExtrema.col(28) << 8, 9;
		mesh.Cell1DsExtrema.col(29) << 10, 11;
		
		
		//Cell2Ds
		mesh.NumCell2Ds = 20;
		mesh.Cell2DsId = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
		mesh.Cell2DsNumVert = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		mesh.Cell2DsNumEdg = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		
		
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> v1 = {0,2,4};
		vector<unsigned int> v2 = {0,4,8};
		vector<unsigned int> v3 = {0,8,9};
		vector<unsigned int> v4 = {0,7,9};
		vector<unsigned int> v5 = {0,2,7};
		vector<unsigned int> v6 = {2,7,11};
		vector<unsigned int> v7 = {5,7,11};
		vector<unsigned int> v8 = {5,7,9};
		vector<unsigned int> v9 = {3,5,9};
		vector<unsigned int> v10 = {3,8,9};
		vector<unsigned int> v11 = {3,6,8};
		vector<unsigned int> v12 = {4,6,8};
		vector<unsigned int> v13 = {4,6,10};
		vector<unsigned int> v14 = {1,6,10};
		vector<unsigned int> v15 = {1,3,6};
		vector<unsigned int> v16 = {1,3,5};
		vector<unsigned int> v17 = {1,5,11};
		vector<unsigned int> v18 = {1,10,11};
		vector<unsigned int> v19 = {2,10,11};
		vector<unsigned int> v20 = {2,4,10};

		
		mesh.Cell2DsVertices= {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20};
		
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,10,1};
		vector<unsigned int> e2 = {1,20,3};
		vector<unsigned int> e3 = {3,28,4};
		vector<unsigned int> e4 = {2,26,4};
		vector<unsigned int> e5 = {0,11,2};
		vector<unsigned int> e6 = {11,27,12};
		vector<unsigned int> e7 = {22,27,21};
		vector<unsigned int> e8 = {22,26,23};
		vector<unsigned int> e9 = {14,23,15};
		vector<unsigned int> e10 = {16,28,15};
		vector<unsigned int> e11 = {17,24,16};
		vector<unsigned int> e12 = {19,24,20};
		vector<unsigned int> e13 = {19,25,18};
		vector<unsigned int> e14 = {6,25,8};
		vector<unsigned int> e15 = {5,17,6};
		vector<unsigned int> e16 = {5,14,7};
		vector<unsigned int> e17 = {7,21,9};
		vector<unsigned int> e18 = {8,29,9};
		vector<unsigned int> e19 = {13,29,12};
		vector<unsigned int> e20 = {10,18,13};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20};
		
		//Cell3D
		mesh.Cell3DsId=0; 
		
		mesh.Cell3DsNumVert = mesh.NumCell0Ds;
		mesh.Cell3DsNumEdg = mesh.NumCell1Ds;
		mesh.Cell3DsNumFaces = mesh.NumCell2Ds;
		
		mesh.Cell3DsVertices = mesh.Cell0DsId; 
		mesh.Cell3DsEdges = mesh.Cell1DsId;
		mesh.Cell3DsFaces = mesh.Cell2DsId;
		}
		
		
		
	else{
		cerr<<"valore di q non valido"<<endl;
		return false;
	}
	
	return true;
}


bool check_ed_vert(const PolygonalMesh& mesh){
	for (unsigned int i=0; i<mesh.NumCell2Ds; i++){
		for (unsigned int j=0; j<(mesh.Cell2DsEdges[i]).size(); j++){
			
			int vert_id = mesh.Cell2DsVertices[i][j];
			unsigned int ed_id = mesh.Cell2DsEdges[i][j];
			unsigned int next_ed_id = mesh.Cell2DsEdges[i][(j+1)%(mesh.Cell2DsEdges[i]).size()];
			unsigned int count =0;
			
			//Controllo Lati
			if (mesh.Cell1DsExtrema(0,ed_id) == mesh.Cell1DsExtrema(0,next_ed_id))
				count++;
			if (mesh.Cell1DsExtrema(0,ed_id) == mesh.Cell1DsExtrema(1,next_ed_id))
				count++;
			if (mesh.Cell1DsExtrema(1,ed_id) == mesh.Cell1DsExtrema(0,next_ed_id))
				count++;
			if (mesh.Cell1DsExtrema(1,ed_id) == mesh.Cell1DsExtrema(1,next_ed_id))
				count++;
			
			if (count != 1){
				cout<<"lati: "<<count<<" i: "<<i<<" j: "<<j<<endl;
				return false;
			}
			
			// Controllo Vertici
			if (vert_id == mesh.Cell1DsExtrema(0,ed_id))
				count++;
			if (vert_id == mesh.Cell1DsExtrema(1,ed_id))
				count++;
			
			if (count != 2){
				cout<<"vertici: "<<count<<" i: "<<i<<" j: "<<j<<endl;
				return false;
			}
			
			
		}
			
	}
	return true;
}

//Controlla se il nuovo vertice generato esiste già nel tetraedro. Se esiste, non aggiunge nulla e restituisce il suo ID. 
//Se non esiste, aggiorna NumCell0Ds, Cell0DsId e la matrice con le coordinate
unsigned int EsisteVertice(PolygonalMesh& mesh,const Eigen::Vector3d new_vert){

	//Fisso una tolleranza per confrontare i vertici
	double tol=1e-10;

	//devo confrontare tutti i vertici, quindi itero su NumCell0Ds
	for (unsigned int i = 0; i < mesh.NumCell0Ds; ++i) {
        if ((mesh.Cell0DsCoordinates.col(i) - new_vert).norm()<tol) { //Se il vertice esiste, allora restituisco il suo ID (bisogna fare un controllo con la tolleranza?)
            return mesh.Cell0DsId[i];  
        }
    }

    //Se siamo arrivati a questo punto allora il vertice non esiste, e il suo ID è uguale al numero corrente di celle
	//Ricorda che se ci sono n celle, allora l'ultimo ID è pari a n-1
    unsigned int new_id = mesh.NumCell0Ds; 
    mesh.NumCell0Ds++; //Aggiorno il numero di celle
    mesh.Cell0DsId.push_back(new_id); //Aggiungo l'ID nelle Cell0Ds
    
    // Aggiungo la nuova colonna con le coordinate alla matrice, adesso le coordinate non servono per la costruzione dei lati e delle facce
    mesh.Cell0DsCoordinates.conservativeResize(3, mesh.NumCell0Ds); 
    mesh.Cell0DsCoordinates.col(mesh.NumCell0Ds - 1) = new_vert;

    return new_id;
}
	
//Controlla se il nuovo lato generato esiste già nel tetraedro. Se esiste, non aggiunge nulla e restituisce il suo ID. 
//Se non esiste, aggiorna NumCell1Ds, Cell1DsId e la matrice con gli estremi
unsigned int EsisteLato(PolygonalMesh& mesh, Eigen::Vector2i new_lato){
	
	//Voglio salvare i lati in modo ordinato così come fatto inizialmente nella mesh
	//Questo permette anche di evitare di salvare due lati identici ma in "direzioni diverse"
	//Per esempio, se ho salvato il lato {5,6} e in un'altra faccia avrò il lato {6,5}, questo ordinamento mi permette di salvare il lato solo una volta
	if (new_lato[0] > new_lato[1]) {
		swap(new_lato[0], new_lato[1]);
	}
	
	
	//devo confrontare tutti i lati, quindi itero su NumCell1Ds
	for (unsigned int i = 0; i < mesh.NumCell1Ds; ++i) {
        if (mesh.Cell1DsExtrema.col(i) == new_lato) { //Se il lato esiste, allora restituisco il suo ID (bisogna fare un controllo con la tolleranza?)
            return mesh.Cell1DsId[i];  
        }
    }
	


    //Se siamo arrivati a questo punto allora il lato non esiste, e il suo ID è uguale al numero corrente di celle
	//Ricorda che se ci sono n celle, allora l'ultimo ID è pari a n-1
    unsigned int new_id = mesh.NumCell1Ds; 
    mesh.NumCell1Ds++; //Aggiorno il numero di celle
    mesh.Cell1DsId.push_back(new_id); //Aggiungo l'ID nelle Cell1Ds
    
    // Aggiungo la nuova colonna con gli estremi alla matrice
    mesh.Cell1DsExtrema.conservativeResize(2, mesh.NumCell1Ds); 
    mesh.Cell1DsExtrema.col(mesh.NumCell1Ds - 1) = new_lato;

    return new_id;
}

//Fa la triangolazione della faccia, utilizza le due funzioni definite sopra. 
//Prende in input la mesh da modificare, i vertici della faccia del poliedro e la quantità b da cui dipende la triangolazione
void TriangolaFaccia(PolygonalMesh& mesh, Eigen::Vector3d v0, Eigen::Vector3d v1, Eigen::Vector3d v2, unsigned int b){
	
	//Opero una costruzione dei vertici a strati, ogni volta prendo gli estremi, divido il lato in b parti e 
	//costruisco i vertici. Poi "salgo di un piano". Salvo quindi in un vettore di vettori gli ID dei vertici di ogni strato	
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
	
	//Adesso ho la suddivisione della faccia in strati, costruisco i lati andando strato per strato
	
	//Itero sul numero di strati
	for (unsigned int j=0; j<strati_vertici.size(); j++){ 
	
		//Itero sul numero di vertici dello strato j-esimo
		for (unsigned int i=0; i<strati_vertici[j].size();i++){ 
		
			//Verifico se è possibile costruire il lato orizzontale "verso destra", ossia verificare se si tratta o meno dell'ultimo vertice relativo al piano orizzontale che si sta considerando
			if (i + 1 < strati_vertici[j].size()){ 
				
				Eigen::Vector2i new_lato={strati_vertici[j][i], strati_vertici[j][i+1]};
				unsigned int ed_id= EsisteLato(mesh,new_lato); //Se il lato esiste, ottengo il suo ID, altrimenti ne creo uno nuovo 
			}
			
				//Verifico se è possibile costruire i due lati diagonali verso il basso,
				if(j>0){ 
				
				//Primo lato, diagonale sinistra
					Eigen::Vector2i new_lato1={strati_vertici[j][i], strati_vertici[j-1][i]};
					unsigned int ed_id1= EsisteLato(mesh,new_lato1);
				
				//Secondo lato, diagonale destra				
					Eigen::Vector2i new_lato2={strati_vertici[j][i], strati_vertici[j-1][i+1]};
					unsigned int ed_id2= EsisteLato(mesh,new_lato2);
					
				}
		}
	}
	
	
	//Costruisco le facce
	//Anche in questo caso andiamo per strati, prendiamo due strati di vertici successivi, possiamo costruire dei parallelogrammi con quattro vertici, per poi dividerli
	//in due parti e fare i triangoli. Fuori da questi parallelogrammi c'è sempre un ultimo triangolo fatto dagli ultimi due vertici dello strato inferiore e l'ultimo 
	//vertice dello strato superiore
	for (unsigned int j=0; j<strati_vertici.size()-1; j++){
		for (unsigned int i=0; i<strati_vertici[j].size()-2; i++){
			//vertici dello strato inferiore
			unsigned int u0=strati_vertici[j][i];
			unsigned int u1=strati_vertici[j][i+1];
			
			//vertici dello strato superiorie
			unsigned int w0=strati_vertici[j+1][i];
			unsigned int w1=strati_vertici[j+1][i+1];
			
			//lati
			Eigen::Vector2i l1={u0, u1};
			Eigen::Vector2i l2={u1, w0};
			Eigen::Vector2i l3={u0, w0};
			Eigen::Vector2i l4={u1, w1};
			Eigen::Vector2i l5={w0, w1};
			
			
			//Primo triangolo u0,u1,w0
			
			vector<unsigned int> verts1={u0,u1,w0}; //vertici della faccia
			vector<unsigned int> edges1={EsisteLato(mesh, l1), EsisteLato(mesh, l2), EsisteLato(mesh,l3)};
			//Lati della faccia, EisteLato restituisce l'ID del lato che congiunge i due vertici
			
			//Aggiungo lati, vertici, aggiorno il numero di celle e gli ID
			mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
			mesh.Cell2DsVertices.push_back(verts1);
			mesh.Cell2DsEdges.push_back(edges1);
			mesh.Cell2DsNumVert.push_back(3);
			mesh.Cell2DsNumEdg.push_back(3);
			mesh.NumCell2Ds++;
			
			
			//Secondo triangolo 
			vector<unsigned int> verts2={u1,w1,w0};
			vector<unsigned int> edges2={EsisteLato(mesh, l4), EsisteLato(mesh, l5), EsisteLato(mesh,l2)};
			
			//Aggiungo lati, vertici, aggiorno il numero di celle e gli ID
			mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
			mesh.Cell2DsVertices.push_back(verts2);
			mesh.Cell2DsEdges.push_back(edges2);
			mesh.Cell2DsNumVert.push_back(3);
			mesh.Cell2DsNumEdg.push_back(3);
			mesh.NumCell2Ds++;
			
		
		}
		//Adesso dobbiamo costruire l'ultima faccia, prenderemo i due ultimi vertici dello strato j e l'ultimo vertice dello strato j+1
		//Avendo iterato con j che va da 0 e j strettamente minore del numero di strati - 1, non abbiamo problemi con il j+1
		
		//vertici
		unsigned int z0 = strati_vertici[j][strati_vertici[j].size()-2];
		unsigned int z1 = strati_vertici[j][strati_vertici[j].size()-1];
		unsigned int z2 = strati_vertici[j+1][strati_vertici[j+1].size()-1];
		
		//lati
		Eigen::Vector2i ed1={z0, z1};
		Eigen::Vector2i ed2={z1, z2};
		Eigen::Vector2i ed3={z2, z0};
		
		//faccia
		vector<unsigned int> verts={z0,z1,z2};
		vector<unsigned int> edges={EsisteLato(mesh, ed1), EsisteLato(mesh, ed2), EsisteLato(mesh,ed3)};
		
		mesh.Cell2DsId.push_back(mesh.NumCell2Ds);
		mesh.Cell2DsVertices.push_back(verts);
		mesh.Cell2DsEdges.push_back(edges);
		mesh.Cell2DsNumVert.push_back(3);
		mesh.Cell2DsNumEdg.push_back(3);
		mesh.NumCell2Ds++;							
	}
		
}	

//Applico e chiamo la funzione definita in precedenza
void TriangolazionePoliedro(PolygonalMesh& mesh, unsigned int b){
	unsigned int num_facce=mesh.NumCell2Ds;
	for (unsigned int i=0; i<num_facce; i++){ //per ogni faccia, salvo i vertici, i lati e le nuove facce della triangolazione
		
		//cout<<"Faccia"<< i<<":"<<endl;
		//cout<<endl;
		unsigned int id_0 = mesh.Cell2DsVertices[i][0];
		unsigned int id_1 = mesh.Cell2DsVertices[i][1];
		unsigned int id_2 = mesh.Cell2DsVertices[i][2];
		Eigen::Vector3d v0= {mesh.Cell0DsCoordinates(0,id_0),mesh.Cell0DsCoordinates(1,id_0),mesh.Cell0DsCoordinates(2,id_0)};
		Eigen::Vector3d v1= {mesh.Cell0DsCoordinates(0,id_1),mesh.Cell0DsCoordinates(1,id_1),mesh.Cell0DsCoordinates(2,id_1)};
		Eigen::Vector3d v2= {mesh.Cell0DsCoordinates(0,id_2),mesh.Cell0DsCoordinates(1,id_2),mesh.Cell0DsCoordinates(2,id_2)};
		TriangolaFaccia(mesh, v0, v1, v2, b);

	}
	
	mesh.Cell3DsNumVert = mesh.NumCell0Ds;
	mesh.Cell3DsNumEdg = mesh.NumCell1Ds;
	mesh.Cell3DsNumFaces = mesh.NumCell2Ds;
		
	mesh.Cell3DsVertices = mesh.Cell0DsId; 
	mesh.Cell3DsEdges = mesh.Cell1DsId;
	mesh.Cell3DsFaces = mesh.Cell2DsId;
}


//Scambio di ruolo tra vertici e facce
//Passi per costruire il duale: 1. costruizione dei baricentri 2. unione tra baricentri di facce adiacenti 

//Calcolo del baricentro di una faccia
Eigen::Vector3d calcolo_baricentro(const PolygonalMesh& mesh, vector<unsigned int> verts){
	
	Eigen::Vector3d v0= {mesh.Cell0DsCoordinates(0,verts[0]),mesh.Cell0DsCoordinates(1,verts[0]),mesh.Cell0DsCoordinates(2,verts[0])};
	Eigen::Vector3d v1= {mesh.Cell0DsCoordinates(0,verts[1]),mesh.Cell0DsCoordinates(1,verts[1]),mesh.Cell0DsCoordinates(2,verts[1])};
	Eigen::Vector3d v2= {mesh.Cell0DsCoordinates(0,verts[2]),mesh.Cell0DsCoordinates(1,verts[2]),mesh.Cell0DsCoordinates(2,verts[2])};
	
	Eigen::Vector3d baricentro = (v0 + v1 +v2)/3.0;
	
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
		if (facce.size() < 3) continue; // Non formano una faccia chiusa

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

					vector<unsigned int> lato = {std::min(v1, v2), std::max(v1, v2)}; //riscrivo il lato che contiene il vertice i e un altro vertice
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

//Proiezione dei vertici sulla sfera unitaria
void ProiezioneSfera(PolygonalMesh& mesh){
	
	//Si accede alle coordinate di ogni vertice nella matrice mesh.Cell0DsCoordinates e si normalizzano
	for (unsigned int i=0; i < mesh.NumCell0Ds; i++){
		
		//coordinate del vertice i
		double v_x = mesh.Cell0DsCoordinates(0,i);
		double v_y = mesh.Cell0DsCoordinates(1,i);
		double v_z = mesh.Cell0DsCoordinates(2,i);
		
		//calcolo la norma
		double norma= sqrt(v_x * v_x + v_y * v_y + v_z * v_z);
		
		//modifico le coordinate
		mesh.Cell0DsCoordinates(0,i)= mesh.Cell0DsCoordinates(0,i)/norma;
		mesh.Cell0DsCoordinates(1,i)= mesh.Cell0DsCoordinates(1,i)/norma;
		mesh.Cell0DsCoordinates(2,i)= mesh.Cell0DsCoordinates(2,i)/norma;
		
	}
	}
	
using namespace std;
//Costruiamo una funzione per trovare il cammino minimo tra due vertici nella mesh poliedrica
void TrovaCamminoMin(PolygonalMesh& mesh, unsigned int id_vertice_1, unsigned int id_vertice_2, std::vector<int>& VertexShortPath, std::vector<int>& EdgeShortPath){
	//Calcolo delle lunghezze dei lati nella mesh
	vector<double> EdgeLengths(mesh.NumCell1Ds);
	for(unsigned int i = 0; i < mesh.NumCell1Ds; ++i){
		unsigned int a = mesh.Cell1DsExtrema(0, i); //estremo iniziale del lato
		unsigned int b = mesh.Cell1DsExtrema(1, i); //estremo finale
		Eigen::Vector3d v1 = mesh.Cell0DsCoordinates.col(a); //coordinate del primo vertice 
		Eigen::Vector3d v2 = mesh.Cell0DsCoordinates.col(b); //idem per il secondo vertice
		EdgeLengths[i] = (v1 - v2).norm();
	}
	//Costruzione della lista di adiacenza
	using Edge = pair<unsigned int, double>; //coppia (vertice adiacente, peso)
	vector<vector<Edge>> adj(mesh.NumCell0Ds); //lista di adiacenza per ogni vertice
	for (unsigned int i = 0; i < mesh.NumCell1Ds; ++i){
		unsigned int u = mesh.Cell1DsExtrema(0, i);
		unsigned int v = mesh.Cell1DsExtrema(1, i);
		double len = EdgeLengths[i];
		adj[u].emplace_back(v, len); // aggiunta dell'arco da u a v
		adj[u].emplace_back(u, len); // aggiunta dell'arco da v a u
	}
	//Inizializzazione per l'algoritmo di Dijkstra
	vector<double> dist(mesh.NumCell0Ds, numeric_limits<double>::infinity()); //distanze minime dai vertici
	vector<int> pred(mesh.NumCell0Ds, -1); //predecessori nel cammino minimo
	priority_queue<pair<double, unsigned int>, vector<pair<double, unsigned int>>, greater<>>  pq; //Coda di priorità (prima quelle minori)
	
	dist[id_vertice_1] = 0.0; //distanza dal vertice sorgente a se stesso è nulla
	pred[id_vertice_1] = id_vertice_1; 
	pq.emplace(0.0, id_vertice_1); //inserimento del vertice sorgente nella coda
	
	//Algoritmo di Dijkstra
	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop(); //estrazione del vertice con distanza minima
		if (d > dist[u]) continue; //se la distanza è maggiore di quella già trovata, ignora gli elementi obsoleti
		//non si aggiorna direttamente la priorità di w nella cosa ma si inserisce un nuovo elemento con distanza aggiornata perchè la struttura non permette aggiornamenti diretti
		
		//Esplorazione dei vicini del vertice corrente
		for (auto [v, w] : adj[u]){
			if (dist[u] + w < dist[v]){ //se si trova un cammino minore
				dist[v] = dist[u] + w; //aggiorna la distanza
				pred[v] = u; //aggiorna il predecessore
				pq.emplace(dist[v], v); //inserisce il vertice nella coda con la nuova distanza
			}
		}
	}
	
	//Ricostruzione del cammino minimo dal vertice destinazione al sorgente
	vector<unsigned int> path;
	for (int at = id_vertice_2; at != -1; at = pred[at])
		path.push_back(at); //aggiunta del vertice al cammino
	reverse(path.begin(), path.end()); //inverte il cammino per ottenere l'ordine corretto
	
	//Verifica l'esistenza del cammino tra i due vertici
	if(path.front() != id_vertice_1){
		cerr << "Nessun cammino trovato tra i vertici" << id_vertice_1 << "e" << id_vertice_2 << endl;
		return;
	}
	//Inizializzazione dei vettori ShorthPath per i vertici e i lati
	VertexShortPath.assign(mesh.NumCell0Ds, 0); //Tutti i vertici inizialmente non appartengono al cammino
	EdgeShortPath.assign(mesh.NumCell1Ds, 0); //Tutti i lati inizialmente non appartengono al cammino
	
	//Etichettatura dei vertici appartenenti al cammino minimo 
	for (auto id : path)
		VertexShortPath[id] = 1;
	//Etichettatura dei lati appartenenti al cammino minimo e calcolo della lunghezza totale
	double total_length = 0.0;
	for (size_t i = 0; i < path.size() - 1; ++i){
		unsigned int u = path[i];
		unsigned int v = path[i+1];
		
		//Ricerca del lato che collega i due vertici consecutivi nel cammino
		for (unsigned int j = 0; j < mesh.NumCell1Ds; ++j){
			unsigned int a = mesh.Cell1DsExtrema(0, j);
			unsigned int b = mesh.Cell1DsExtrema(1, j);
			if ((a == u && b == v ) || (a == v && b == u)){
				EdgeShortPath[j] = 1; //Etichetta il lato come parte del cammino minimo
				total_length += EdgeLengths[j]; //Aggiunge la lunghezza del lato al totale
				break; //esce dal ciclo quando viene trovato il lato
			}
		}
	}
	
	//Output del numero di lati e della lunghezza totale del cammino minimo
	cout << "Numero di lati nel cammino minimo:" << path.size() - 1 << endl;
	cout << "Lunghezza totale del cammino: " << total_length << endl;
}

	
	
}
