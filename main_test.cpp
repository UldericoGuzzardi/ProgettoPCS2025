#include <gtest/gtest.h>

#include "calcolo_baricentro_test.hpp"
#include "costruzione_duale_test.hpp"
#include "EsisteVertice_test.hpp"
#include "genera_poliedro_test.hpp"
#include "TriangolaFaccia_2_test.hpp"
#include "TriangolaFaccia_test.hpp"
#include "TrovaCamminoMinimo_test.hpp"
#include "costruzione_poliedro_test.hpp"
#include "check_ed_vert_test.hpp"
#incluce "AggiungiFaccia_test.hpp"
#incluce "EsisteLato_test.hpp"
#incluce "Esportazione_Paraview_test.hpp"
#incluce "ProiezioneSfera_test.hpp"
#incluce "TriangolazionePoliedro_test.hpp"
#incluce "VerticeInFaccia_test.hpp"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}