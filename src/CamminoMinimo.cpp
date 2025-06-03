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
#include <unordered_map>
#include <set>
#include "Eigen/Eigen"
#include "UCDUtilities.hpp"
using namespace std;

namespace PolygonalLibrary
{


bool TrovaCamminoMinimo(PolygonalMesh& mesh, unsigned int id_vertice_1, unsigned int id_vertice_2, unsigned int num_lati_iniziali) {
	
    if (id_vertice_1 >= mesh.NumCell0Ds || id_vertice_2 >= mesh.NumCell0Ds) {
        cerr << "ID dei vertici non valido." << endl;
        return false;
    }

    unsigned int N = mesh.NumCell0Ds;

    //Inizializzo la lista di adiacenza
	//Uso un vettore di vettori. L'i-esimo vettore corrisponde all'i-esimo vertice, ed è costituito da coppie vertice-peso, cioè contiene i vertici vicini e la relativa distanza
    vector<vector<pair<unsigned int, double>>> LA(N); 

	//Riempio la lista di adiacenza
    for (unsigned int i = num_lati_iniziali; i < mesh.NumCell1Ds; i++) {//Considero solo i nuovi lati, quelli prima della triangolazione "non esistono più"
	
        unsigned int v1 = mesh.Cell1DsExtrema(0, i);
        unsigned int v2 = mesh.Cell1DsExtrema(1, i);

        Eigen::Vector3d c1 = mesh.Cell0DsCoordinates.col(v1);
        Eigen::Vector3d c2 = mesh.Cell0DsCoordinates.col(v2);
        double peso = (c1 - c2).norm();

        LA[v1].push_back({v2, peso});
        LA[v2].push_back({v1, peso});
    }

    // Inizializzazione Dijkstra
    vector<double> distanze(N, numeric_limits<double>::infinity()); //Vettore delle distanze, inizializzate tutte ad un numero molto grande
    vector<int> pred(N, -1); //Vettore dei predecessori, inizializzati tutti a -1
    vector<bool> visitati(N, false); //Vettore dei vertici visitati, inizializzati a false

    distanze[id_vertice_1] = 0.0; //La distanza del primo vertice da sè stesso è nulla
    
    priority_queue<pair<double,unsigned int>, vector<pair<double, unsigned int>>, greater<pair<double, unsigned int>>> pq; //Inizializzo la coda di priorità
	//La pq è costituita da una coppia (pair) dove salviamo la distanza e l'identificativo del vertice. Il greater ci permette di ordinare la coda in modo da prendere sempre 
	//per primo il vertice con la distanza minore
	//All'interno della pq c'è un altro contenitore, ovvero un vettore anch'esso costituito da coppie distanza, vertice, e che ci permette di memorizzare gli elementi
	
    pq.push({0.0, id_vertice_1}); //Aggiungo il primo vertice
	
	
	//Uso Dijkstra per il cammino minimo pesato
	
    while (!pq.empty()) {
		//Estraggo l'elemento dalla coda
        unsigned int u = pq.top().second; 
        pq.pop();


        if (visitati[u]) continue;
        visitati[u] = true;

        for (auto& [v, peso] : LA[u]) { //Vado a prendere ogni vertice con il relativo peso nella lista di adiacenza
            if (visitati[v]) continue; //Se l'ho già visitato non lo considero più

            if (distanze[u] + peso < distanze[v]) { //Altrimenti, controllo se aggiungerlo alla coda
                distanze[v] = distanze[u] + peso;
                pred[v] = u;
                pq.push({distanze[v], v});
            }
        }
    }

    // Ricostruisco il cammino (controllo se esiste)
    if (pred[id_vertice_2] == -1) {
        cerr << "Nessun cammino trovato da " << id_vertice_1 << " a " << id_vertice_2 << endl;
        return false;
    }


    vector<unsigned int> cammino;
	int nodo_corrente = id_vertice_2;

	//Costruisco il cammino partendo dall'ultimo vertice
	//Faccio così perchè mi serve la condizione sul predecessore (pari a -1), in modo tale da fermarmi una volta arrivato al nodo iniziale
	while (nodo_corrente != -1) {
		cammino.push_back(nodo_corrente);
		nodo_corrente = pred[nodo_corrente];  
	}

    reverse(cammino.begin(), cammino.end()); //Inverto l'ordine in modo da avere il cammino vero

    //Inizializzo le proprietà della mesh
    mesh.Cell0DsShortPath.resize(mesh.NumCell0Ds, 0);
    mesh.Cell1DsShortPath.resize(mesh.NumCell1Ds, 0);
	
	
	//Aggiungo i vertici visitati
    for (int v : cammino) {
        mesh.Cell0DsShortPath[v] = 1;
    }

 
    double Lunghezza_tot = 0.0;
    unsigned int Lunghezza_cammino = 0;
	
	//Aggiungo i lati visitati, aggiorno il numero di lati e la distanza totale percorsa
    for (unsigned int i = 0; i < cammino.size() - 1; ++i) {
        unsigned int u = cammino[i];
        unsigned int v = cammino[i + 1];

        
        for (unsigned int j = num_lati_iniziali; j < mesh.NumCell1Ds; j++) {
            unsigned int v1 = mesh.Cell1DsExtrema(0, j);
            unsigned int v2 = mesh.Cell1DsExtrema(1, j);
            if ((v1 == u && v2 == v) || (v1 == v && v2 == u)) {
                mesh.Cell1DsShortPath[j] = 1;
                Eigen::Vector3d c1 = mesh.Cell0DsCoordinates.col(v1);
                Eigen::Vector3d c2 = mesh.Cell0DsCoordinates.col(v2);
                Lunghezza_tot += (c1 - c2).norm();
                Lunghezza_cammino++;
                break;
            }
        }
    }

    cout << "Numero di archi nel cammino: " << Lunghezza_cammino << endl;
    cout << "Lunghezza totale: " << Lunghezza_tot << endl;
	
	return true;
}

}
