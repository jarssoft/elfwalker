#ifndef LIIKETAULUKKO_H_INCLUDED
#define LIIKETAULUKKO_H_INCLUDED

#include "aly-rutiinit.h"

namespace tekoaly {
    /**
    Suunnitelma on sekvenssi agentin kaikkien lihaksien liikkeistä tietyllä aikavälillä.
    Sisältää geneettisen päättelijän, joka tallentaa onnistuneet suunnitelmat.
    */
    class Suunnitelma {

        public:

            Suunnitelma(int sis, int van);

            /** Ottaa käyttöön seuraavan vanhemmasta mutatoidun vaihtoehdon,
                ja lopulta parhaaksi katsotun, lopullisen tuloksen.
                Palauttaa false, jos kaikki mutaatiot on suoritettu, ja
                paras tulos on valittu. Palauttaa true, jos mutaatioita jäljellä.
                Huom: Toimii vain konstruktori- tai arvostelu-kutsun jälkeen. */
            bool next();

            /** Palauttaa suunnitelmissa olevan lihaksen tilan tietyllä ajalla.
                Huom: Toimii vain next-kutsun jälkeen. */
            double getLihas(double aika, int lihasNro);

            /** Arvostelee tämän taulukon.
                Huom: Toimii vain getLihas-kutsun jälkeen. */
            void arvostele(double arvosana);

            /** Ottaa seuraavan ajanjakson suunniteltavaksi.
                Siirtyy halutun määrän soluissa eteenpäin. */
            void addTime(double siirtyma);

            /** Asettaa ajan, josta lähtien uusi suunnitelma tehdään
                halutulla ehdotuksella.
                Voi hyödyntää tarvittaessa aikaisempaa suunnitelmaa.*/
            void setTime(double uusi_aika);

            /** Palauttaa ylimmän taulukon, jossa paras tulos. */
            Suunnitelma* getYlin();

            /** Poistaa dynaamisessa muistissa olevat tiedot. */
            void poista();

        private:

            /** Palauttaa taulukon sisällön vanhemmalta. */
            void palautaVanhemmalta();

            /** Vie taulukon sisällön vanhemmalle. */
            void vieVanhemmalle();

            double lihakset[KOKO][LIHAKSET];

            /** Kuinka mones sisarus on käytössä? */
            int sisarus;

            /** Taulukko, jossa säilytetään onnistunutta versiota. */
            Suunnitelma *vanhempi;

            /** Kuinka monta sisarusta käytetään? */
            int sisarukset;

            /** Kuinka monta vanhempaa taulukolla on? */
            int syvyys;

            /** Onko taulukko alin. */
            bool onAlin;

            /** Kuinka laadukas taulukko on? (Vain jos taulukolla on lapsia).*/
            double arvosana;

            /** Vanhemman alkuperäinen arvosana. */
            double lahtoarvosana;

            /** Aikakorjaus 0-1 */
            double aikakorjaus;

            /** Aika frameina. */
            double aika;

            /** Taulukon käytön tilat. Olio vaatii, että sen metodeita
                kutsutaan oikeassa järjestyksessä. */
            enum {ALUSTETTU, MUTATOITU, LUETTU, ARVOSTELTU, VALMIS, POISTETTU};
            int tila;

    };
}
#endif // LIIKETAULUKKO_H_INCLUDED
