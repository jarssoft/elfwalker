#include "piste.h"
#include "mate.h"
#include <iostream>

#ifndef SIDOS_H_INCLUDED
#define SIDOS_H_INCLUDED

namespace fysiikka {
    /** Kahden pisteen välinen vetovoima. */
    class Sidos {

        public:
            Sidos(Piste &p1, Piste &p2) :
                    piste1(p1), piste2(p2),
                    t_etaisyys(1.0), t_voima(1.0 * 0.01) {}

            Sidos(Piste &p1, Piste &p2, double et, double vo) :
                    piste1(p1), piste2(p2),
                    t_etaisyys(et),
                    t_voima(vo * 0.01) {
                std::cout << et << " " << distance(p1.getX(), p1.getY(), p2.getX(), p2.getY()) << std::endl;
            }

            Sidos(Piste &p1, Piste &p2,  double vo) :
                    piste1(p1), piste2(p2),
                    t_etaisyys(distance(p1.getX(), p1.getY(), p2.getX(), p2.getY())),
                    t_voima(vo * 0.01) {}

            void teeVuorovaikutus();
            void setEtaisyys(double et);
            double getEtaisyys() const;

        private:
            Piste &piste1;
            Piste &piste2;

            void vastavoima(double voimax, double voimay);

            //Näihin pyritään
            double t_etaisyys, t_voima;
    };
}

#endif // SIDOS_H_INCLUDED
