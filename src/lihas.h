#include "vuorovaikutus.h"

#ifndef LIHAS_H_INCLUDED
#define LIHAS_H_INCLUDED

namespace fysiikka {
    /** Jokin arvo fysikaalisessa maailmassa, johon "aivot" vaikuttaa. */
    class Lihas {

        public:
            Lihas(fysiikka::Vuorovaikutus &vuorovaikutus, double kerroin) :
                    sidos(vuorovaikutus),
                    min_etaisyys(vuorovaikutus.getEtaisyys() * (1.0 - kerroin)),
                    kerroin(kerroin*2) {}
            void setArvo(double et);

        private:
            fysiikka::Vuorovaikutus &sidos;
            double min_etaisyys, kerroin;
    };
}
#endif // LIHAS_H_INCLUDED
