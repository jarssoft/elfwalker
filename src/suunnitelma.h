#ifndef LIIKETAULUKKO_H_INCLUDED
#define LIIKETAULUKKO_H_INCLUDED

#include "aly-rutiinit.h"

namespace tekoaly {
    /**
    Suunnitelma on sekvenssi agentin kaikkien lihaksien liikkeist� tietyll� aikav�lill�.
    Sis�lt�� geneettisen p��ttelij�n, joka tallentaa onnistuneet suunnitelmat.
    */
    class Suunnitelma {

        public:

            Suunnitelma(int sis, int van);

            /** Ottaa k�ytt��n seuraavan vanhemmasta mutatoidun vaihtoehdon,
                ja lopulta parhaaksi katsotun, lopullisen tuloksen.
                Palauttaa false, jos kaikki mutaatiot on suoritettu, ja
                paras tulos on valittu. Palauttaa true, jos mutaatioita j�ljell�.
                Huom: Toimii vain konstruktori- tai arvostelu-kutsun j�lkeen. */
            bool next();

            /** Palauttaa suunnitelmissa olevan lihaksen tilan tietyll� ajalla.
                Huom: Toimii vain next-kutsun j�lkeen. */
            double getLihas(double aika, int lihasNro);

            /** Arvostelee t�m�n taulukon.
                Huom: Toimii vain getLihas-kutsun j�lkeen. */
            void arvostele(double arvosana);

            /** Ottaa seuraavan ajanjakson suunniteltavaksi.
                Siirtyy halutun m��r�n soluissa eteenp�in. */
            void addTime(double siirtyma);

            /** Asettaa ajan, josta l�htien uusi suunnitelma tehd��n
                halutulla ehdotuksella.
                Voi hy�dynt�� tarvittaessa aikaisempaa suunnitelmaa.*/
            void setTime(double uusi_aika);

            /** Palauttaa ylimm�n taulukon, jossa paras tulos. */
            Suunnitelma* getYlin();

            /** Poistaa dynaamisessa muistissa olevat tiedot. */
            void poista();

        private:

            /** Palauttaa taulukon sis�ll�n vanhemmalta. */
            void palautaVanhemmalta();

            /** Vie taulukon sis�ll�n vanhemmalle. */
            void vieVanhemmalle();

            double lihakset[KOKO][LIHAKSET];

            /** Kuinka mones sisarus on k�yt�ss�? */
            int sisarus;

            /** Taulukko, jossa s�ilytet��n onnistunutta versiota. */
            Suunnitelma *vanhempi;

            /** Kuinka monta sisarusta k�ytet��n? */
            int sisarukset;

            /** Kuinka monta vanhempaa taulukolla on? */
            int syvyys;

            /** Onko taulukko alin. */
            bool onAlin;

            /** Kuinka laadukas taulukko on? (Vain jos taulukolla on lapsia).*/
            double arvosana;

            /** Vanhemman alkuper�inen arvosana. */
            double lahtoarvosana;

            /** Aikakorjaus 0-1 */
            double aikakorjaus;

            /** Aika frameina. */
            double aika;

            /** Taulukon k�yt�n tilat. Olio vaatii, ett� sen metodeita
                kutsutaan oikeassa j�rjestyksess�. */
            enum {ALUSTETTU, MUTATOITU, LUETTU, ARVOSTELTU, VALMIS, POISTETTU};
            int tila;

    };
}
#endif // LIIKETAULUKKO_H_INCLUDED
