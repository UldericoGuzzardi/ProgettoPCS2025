#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"
#include <string>
#include "Polygons.hpp"

using namespace std;

namespace PolygonalLibrary
{

bool costruzione_poliedro(int q, PolygonalMesh& mesh);

bool genera_poliedro(PolygonalMesh& mesh, unsigned int num_lati_iniziali, unsigned int num_facce_iniziali);

bool check_ed_vert(const PolygonalMesh& mesh);

unsigned int EsisteVertice(PolygonalMesh& mesh,const Eigen::Vector3d new_vert);

unsigned int EsisteLato(PolygonalMesh& mesh, const Eigen::Vector2i new_lato);

void TriangolaFaccia(PolygonalMesh& mesh, Eigen::Vector3d v0, Eigen::Vector3d v1, Eigen::Vector3d v2, unsigned int b);

void TriangolazionePoliedro(PolygonalMesh& mesh, unsigned int b,unsigned int c);

Eigen::Vector3d calcolo_baricentro(const PolygonalMesh& mesh, vector<unsigned int> verts);

bool VerticeInFaccia(vector<unsigned int> faccia, unsigned int vertice);

PolygonalMesh costruzione_duale(const PolygonalMesh& mesh, unsigned int num_facce_iniziali, unsigned int num_lati_iniziali);

void ProiezioneSfera(PolygonalMesh& mesh);

bool TrovaCamminoMinimo(PolygonalMesh& mesh, unsigned int id_vertice_1, unsigned int id_vertice_2, unsigned int num_lati_iniziali);

void AggiungiFaccia(PolygonalMesh& mesh, vector<unsigned int> faccia);

void TriangolaFaccia_2(PolygonalMesh& mesh, Eigen::Vector3d v0, Eigen::Vector3d v1, Eigen::Vector3d v2, unsigned int b);

void Esportazione_ParaView(PolygonalMesh& mesh, bool cammino);

}