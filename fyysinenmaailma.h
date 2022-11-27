#include <list>
#include "piste.h"
#include "sidos.h"
#include "lihas.h"
#include "poly.h"
#include "aly.h"
#include "liiketaulukko.h"
#include "tekoaly.h"

#ifndef FYSMAAILM_H_INCLUDED
#define FYSMAAILM_H_INCLUDED

namespace fysiikka {

    extern int flop;

    /**
        Maailma, jossa fysikaaliset asiat tapahtuu.
        Aluksi tietty malli on kovakoodattu tähän.
        Myöhemmin "parametrisoidaan".
    */
    class FyysinenMaailma {

        public:

            FyysinenMaailma(tekoaly::Liiketaulukko* liiketaulukko, Vuoristo* vuor);

            /** Palauttaa todellisen ajan. */
            void currentTime();

            /** Siirtyy kuviteltuun aikaan. */
            void set();

            /** Laskee maailmaa yhden framen verran eteenpäin
                halutulla resoluutiolla. */
            void makePhysics(const float resoluutio=10);

            /** Piirtää ruudulle maailman polygonit ym. */
            void piirra();

            /** Määrä, jolla tekoälyä palkitaan. */
            double fitness(bool todellisuus);

            /** Palauttaa aistitiedot.*/
            void getAistit(double aistit[tekoaly::KOKO][tekoaly::LIHAKSET]);

            /** Asettaa lihakset halutun liiketaulukon mukaisesti. */
            void setLihakset();

            /** Palauttaa maailman ajan.*/
            double getTime();

        private:

            /** Ajat frameina. */
            double aika, alkuaika;

            Piste alkupiste1, alkupiste2, alkupiste3, alkupiste4, alkupiste5;

            Piste piste1, piste2, piste3, piste4, piste5;
            std::list<Piste*> pisteet;

            Sidos *sidos1, *sidos2, *sidos3, *sidos4, *sidos5, *sidos6, *sidos7, *sidos8;
            std::list<Sidos*> sidokset;

            Lihas *lihas1, *lihas2, *lihas3, *lihas4, *lihas5, *lihas6, *lihas7, *lihas8;
            std::list<Lihas*> lihakset;

            Poly *poly1, *poly2, *poly3;
            std::list<Poly*> polyt;

            tekoaly::Liiketaulukko *liiketaulukko;
            Vuoristo *vuoristo;

            double kerroin =1;

    };
}
#endif // FYSMAAILM_H_INCLUDED
