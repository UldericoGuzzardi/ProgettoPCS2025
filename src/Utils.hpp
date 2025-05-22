#pragma once

#include <iostream>
#include "Polygons.hpp"

using namespace std;

namespace PolygonalLibrary
{

bool costruzione_poliedro(int q, PolygonalMesh& mesh);

bool check_ed_vert(const PolygonalMesh& mesh);

bool new_vert(vector<array<double,3>>& verts, array<double,3> v0, array<double,3> v1, unsigned int j,unsigned int& count);

vector<array<double,3>> triang_vert(PolygonalMesh& mesh, unsigned int b);

}