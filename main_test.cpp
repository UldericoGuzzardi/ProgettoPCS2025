#include <gtest/gtest.h>

#include "calcolo_baricentro_test.hpp"
#include "costruzione_duale_test.hpp"
#include "EsisteVertice_test.hpp"
#include "genera_poliedro_test.hpp"
#include "TriangolaFaccia_2_test.hpp"
#include "TriangolaFaccia_test.hpp"
#include "TrovaCamminoMinimo_test.hpp"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}