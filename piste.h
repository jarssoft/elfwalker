#include "vuoristo.h"

#ifndef PISTE_H_INCLUDED
#define PISTE_H_INCLUDED

namespace fysiikka {

    class Piste {
        public:
            Piste(double x=0, double y=0);

            void teeVuorovaikutus(Piste &piste, double &etaisyys, double voima);
            void toString();
            void paivitaSijainti(double);
            void addNopeus(double x, double y);
            /** Laskee vuorovaikutuksen maahan niin, ett� korkeus
                m��ritet��n y-akselille. */
            void teeMaaVuorovaikutusY(double kaltevuus, double korkeus, double aika);
            /** Laskee vuorovaikutuksen maahan niin, ett� korkeus
                m��ritet��n y-akselille. */
            void teeMaaVuorovaikutusY(korkeusJaKaltevuus kjk, double aika);
            /** Laskee vuorovaikutuksen maahan siten, ett� korkeus
                m��ritell��n suorana origon kautta kulkevana funktiona. */
            void teeMaaVuorovaikutus(double kaltevuus, double korkeus, double aika);
            /** Laskee vuorovaikutuksen vuoristoon. */
            void teeMaaVuorovaikutus(Vuoristo& vuoristo, double aika);

            double getX();
            double getY();

            //Aisti
            double getKulma(Piste piste);
            double getPaine();
            double getYNopeus();
            double getXNopeus();

            void replace(Piste piste);

        private:

            double paine;

            struct{
                struct{
                    double x, y;
                } p, n;
            } koord;

    };
}
#endif // PISTE_H_INCLUDED
