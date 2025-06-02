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
#include "UCDUtilities.hpp"

namespace PolygonalLibrary


{
//Costruiamo una funzione per trovare il cammino minimo tra due vertici nella mesh poliedrica
void TrovaCamminoMinimo(PolygonalMesh& mesh, unsigned int id_vertice_1, unsigned int id_vertice_2, std::vector<int>& VertexShortPath, std::vector<int>& EdgeShortPath, unsigned int num_lati_iniziali){
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
	for (unsigned int i = num_lati_iniziali; i < mesh.NumCell1Ds; ++i){
		unsigned int u = mesh.Cell1DsExtrema(0, i);
		unsigned int v = mesh.Cell1DsExtrema(1, i);
		double len = EdgeLengths[i];
		adj[u].emplace_back(v, len); // aggiunta dell'arco da u a v
		adj[v].emplace_back(u, len); // aggiunta dell'arco da v a u
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
	//VertexShortPath.assign(mesh.NumCell0Ds, 0); //Tutti i vertici inizialmente non appartengono al cammino
	//EdgeShortPath.assign(mesh.NumCell1Ds, 0); //Tutti i lati inizialmente non appartengono al cammino
	
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

void ExportCamminoMinimoPerParaview(const PolygonalMesh& mesh,
                                                       const std::vector<int>& VertexShortPath,
                                                       const std::vector<int>& EdgeShortPath,
                                                       const std::string& filename)
{
    using namespace Gedim;

    UCDUtilities utilities;

    // Proprietà per vertici, viene creato un vettore con tanti elementi quanti i vertici nella mesh
    std::vector<double> vertex_data(mesh.NumCell0Ds);
    for (unsigned int i = 0; i < mesh.NumCell0Ds; ++i)
        vertex_data[i] = static_cast<double>(VertexShortPath[i]); //Converte i valori interi in double (richiesto in UCDProperty), ogni valore indica se il vertice fa parte o meno del cammino

	//Creazione di un oggetto che rappresenta la proprietà associata ai vertici (cammino minimo)
    UCDProperty<double> ShortPathVertici;
    ShortPathVertici.Label = "ShortPath"; //Nome della proprietà visualizzata in Paraview
    ShortPathVertici.UnitLabel = ""; //Nessuna unità di misura
    ShortPathVertici.NumComponents = 1; //Proprietà scalare
    ShortPathVertici.Data = vertex_data.data(); //Puntatore ai dati
	//Viene inserità la proprietà in un vettore perché l'interfaccia accetta una lista
    std::vector<UCDProperty<double>> ProprietàVertici = { ShortPathVertici };

    // Proprietà per lati con stesse definizioni delle caratteristiche definite per i vertici
    std::vector<double> edge_data(mesh.NumCell1Ds);
    for (unsigned int i = 0; i < mesh.NumCell1Ds; ++i)
        edge_data[i] = static_cast<double>(EdgeShortPath[i]);

    UCDProperty<double> ShortPathLati;
    ShortPathLati.Label = "ShortPath";
    ShortPathLati.UnitLabel = "";
    ShortPathLati.NumComponents = 1;
    ShortPathLati.Data = edge_data.data();

    std::vector<UCDProperty<double>> ProprietàLati = { ShortPathLati };

    // Materiali (default 0), servono solo per compatibilità con la scrittura del file .inp, ma qui non hanno un significato
    Eigen::VectorXi materiali_lati = Eigen::VectorXi::Zero(mesh.NumCell1Ds);
	//Stampa di Debug
	std::cout << "Exporting to file:" << filename << std::endl;


    // Esportazione(scrittura del file usando le informazioni raccolte)
    utilities.ExportSegments(filename,
                             mesh.Cell0DsCoordinates,
                             mesh.Cell1DsExtrema,
                             ProprietàVertici,
                             ProprietàLati,
                             materiali_lati);
}

}