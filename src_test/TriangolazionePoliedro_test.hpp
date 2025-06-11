#pragma once

#include <iostream>
#include <vector>
#include <set>
#include "Eigen/Eigen"
#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {

// Funzione helper per pulire i lati non più validi dopo triangolazione
void PulisciLatiDopoTriangolazione(PolygonalMesh& mesh) {
    std::vector<Eigen::Vector2i> lati_validi;
    std::set<std::pair<unsigned int, unsigned int>> lati_unici;

    // Ricostruisci lati unici da facce (Cell2DsVertices)
    for (const auto& faccia : mesh.Cell2DsVertices) {
        size_t n = faccia.size();
        for (size_t i = 0; i < n; ++i) {
            unsigned int v0 = faccia[i];
            unsigned int v1 = faccia[(i + 1) % n];
            if (v0 > v1) std::swap(v0, v1);

            auto lato = std::make_pair(v0, v1);
            if (lati_unici.find(lato) == lati_unici.end()) {
                lati_unici.insert(lato);
                lati_validi.push_back(Eigen::Vector2i(v0, v1));
            }
        }
    }

    // Aggiorna Cell1DsExtrema con i lati validi
    mesh.NumCell1Ds = static_cast<unsigned int>(lati_validi.size());
    mesh.Cell1DsExtrema.resize(2, mesh.NumCell1Ds);

    for (unsigned int i = 0; i < mesh.NumCell1Ds; ++i) {
        mesh.Cell1DsExtrema(0, i) = lati_validi[i][0];
        mesh.Cell1DsExtrema(1, i) = lati_validi[i][1];
    }

    // Aggiorna Cell1DsId come sequenza da 0 a NumCell1Ds-1
    mesh.Cell1DsId.resize(mesh.NumCell1Ds);
    for (unsigned int i = 0; i < mesh.NumCell1Ds; ++i) {
        mesh.Cell1DsId[i] = i;
    }
}

// Funzione helper per aggiornare i conteggi dopo triangolazione
void AggiornaMeshDopoTriangolazione(PolygonalMesh& mesh) {
    mesh.NumCell0Ds = static_cast<unsigned int>(mesh.Cell0DsCoordinates.cols());
    mesh.NumCell2Ds = static_cast<unsigned int>(mesh.Cell2DsVertices.size());

    // Pulisci i lati non più validi
    PulisciLatiDopoTriangolazione(mesh);

    mesh.Cell2DsNumVert.clear();
    mesh.Cell2DsNumEdg.clear();

    for (size_t i = 0; i < mesh.Cell2DsVertices.size(); ++i) {
        mesh.Cell2DsNumVert.push_back(static_cast<unsigned int>(mesh.Cell2DsVertices[i].size()));
        if (!mesh.Cell2DsEdges.empty()) {
            mesh.Cell2DsNumEdg.push_back(static_cast<unsigned int>(mesh.Cell2DsEdges[i].size()));
        } else {
            mesh.Cell2DsNumEdg.push_back(static_cast<unsigned int>(mesh.Cell2DsVertices[i].size()));
        }
    }

    mesh.NumCell1Ds = static_cast<unsigned int>(mesh.Cell1DsId.size());

    mesh.Cell3DsNumVert = mesh.NumCell0Ds;
    mesh.Cell3DsNumEdg = mesh.NumCell1Ds;
    mesh.Cell3DsNumFaces = mesh.NumCell2Ds;

    mesh.Cell3DsVertices = mesh.Cell0DsId;
    mesh.Cell3DsEdges = mesh.Cell1DsId;
    mesh.Cell3DsFaces = mesh.Cell2DsId;
}

TEST(TestTriangolazionePoliedro, TriangolazionePrimaSpecie) {
    PolygonalMesh mesh;

    // Parametri di test (esempio per ottaedro)
    const unsigned int q = 4;  // q può essere 3, 4 o 5 in base al solido
    const unsigned int b = 2;
    const unsigned int c = 0;

    // Costruzione poliedro base
    bool costruito = costruzione_poliedro(q, mesh);
    ASSERT_TRUE(costruito) << "Costruzione poliedro fallita";

    // Esegui triangolazione prima specie (b, c)
    TriangolazionePoliedro(mesh, b, c);

    // Aggiorna i conteggi dopo triangolazione, compresa pulizia lati
    AggiornaMeshDopoTriangolazione(mesh);

    // Calcolo T come da formula (2)
    const unsigned int T = b * b + b * c + c * c;

    // Calcolo valori attesi in base a q come da formula (1)
    unsigned int V_atteso = 0;
    unsigned int E_atteso = 0;
    unsigned int F_atteso = 0;

    switch (q) {
        case 3:
            V_atteso = 2 * T + 2;
            E_atteso = 6 * T;
            F_atteso = 4 * T;
            break;
        case 4:
            V_atteso = 4 * T + 2;
            E_atteso = 12 * T;
            F_atteso = 8 * T;
            break;
        case 5:
            V_atteso = 10 * T + 2;
            E_atteso = 30 * T;
            F_atteso = 20 * T;
            break;
        default:
            FAIL() << "Valore q non supportato nel test";
    }

    // Controlli sui conteggi
    EXPECT_EQ(mesh.NumCell0Ds, V_atteso) << "Numero vertici non corretto";
    EXPECT_EQ(mesh.NumCell1Ds, E_atteso) << "Numero lati non corretto";
    EXPECT_EQ(mesh.NumCell2Ds, F_atteso) << "Numero facce non corretto";
}

} 
