#pragma once

#include <iostream>
#include "Polygons.hpp"

using namespace std;

namespace PolygonalLibrary
{

bool costruzione_poliedro(int q, PolygonalMesh& mesh);

bool check_ed_vert(const PolygonalMesh& mesh);

}