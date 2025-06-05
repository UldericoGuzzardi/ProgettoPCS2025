#pragma once

#include <vector>
#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;


namespace PolygonalLibrary {
	
	TEST(TestDual, TestVerticeInFaccia)
	{
		//Definiamo una faccia con dei vertici
		vector<unsigned int> faccia = {1, 3, 5, 7};
		
		//Test affinché un vertice presente venga effettivamente trovato
		EXPECT_TRUE(VerticeInFaccia(faccia, 3));
		
		//Test affinchè un vertice non presente non venga trovato
		EXPECT_FALSE(VerticeInFaccia(faccia, 4));
		
		//Test con vertice all'inizio della faccia
		EXPECT_TRUE(VerticeInFaccia(faccia, 1));
		
		//Test con vertice alla fine della faccia
		EXPECT_TRUE(VerticeInFaccia(faccia, 7));
		
		//Test con faccia vuota
		vector<unsigned int> faccia_vuota;
		EXPECT_FALSE(VerticeInFaccia(faccia_vuota, 1));	
	}
}