#include "piste.h"
#include "fys-rutiinit.h"
#include <iostream>

#ifndef SIDOS_H_INCLUDED
#define SIDOS_H_INCLUDED

namespace fysiikka {
    /** Kahden pisteen v‰linen vuorovaikutus. Pyrkii pit‰m‰‰n pisteiden
     *  v‰lisen et‰isyyden tiettyn‰ arvona. Kappale koostuu pisteist‰ ja
        vuorovaikutuksista. */
    class Vuorovaikutus {

        public:
            Vuorovaikutus(Piste &p1, Piste &p2) :
                    piste1(p1), piste2(p2),
                    t_etaisyys(1.0),
                    t_voima(1.0 * 0.01)
            {}

            Vuorovaikutus(Piste &p1, Piste &p2, double et, double vo) :
                    piste1(p1), piste2(p2),
                    t_etaisyys(et),
                    t_voima(vo * 0.01)
            {
                std::cout << et << " " << distance(p1.getX(), p1.getY(), p2.getX(), p2.getY()) << std::endl;
            }

            Vuorovaikutus(Piste &p1, Piste &p2,  double vo) :
                    piste1(p1), piste2(p2),
                    t_etaisyys(distance(p1.getX(), p1.getY(), p2.getX(), p2.getY())),
                    t_voima(vo * 0.01)
            {}

            void teeVuorovaikutus();
            void setEtaisyys(double et);
            double getEtaisyys() const;

        private:
            Piste &piste1;
            Piste &piste2;

            void vastavoima(double voimax, double voimay);

            // Et‰isyys, johon vuorovaikutus pyrkii.
            double t_etaisyys;

            // Voima, jolla et‰isyyteen pyrit‰‰n.
            double t_voima;
    };
}

#endif // SIDOS_H_INCLUDED
