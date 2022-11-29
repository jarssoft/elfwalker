#include "sidos.h"

#ifndef LIHAS_H_INCLUDED
#define LIHAS_H_INCLUDED

namespace fysiikka {
    /** Jokin arvo fysikaalisessa maailmassa, johon "aivot" vaikuttaa. */
    class Lihas {

        public:
            Lihas(fysiikka::Sidos &sidos, double kerroin) :
                    sidos(sidos),
                    min_etaisyys(sidos.getEtaisyys() - kerroin * sidos.getEtaisyys() / 2),
                    kerroin(kerroin) {}
            void setArvo(double et);

        private:
            fysiikka::Sidos &sidos;
            double min_etaisyys, kerroin;
    };
}
#endif // LIHAS_H_INCLUDED
